#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

#include "classes.hpp"
#include "read_write.hpp"
double sq(double x){                                    // Return s the square of x
    return x*x;
}
double cb(double x){                                    // returns the cube of x
    return x*x*x;
}
double Distance(vec2 a, vec2 b){                        // Returns distance between a and b
    return sqrt(sq(b.x-a.x) + sq(b.y - a.y));
}
vec2 DirectionAB(vec2 a, vec2 b){                       // Returns a normalised vector from a to b
    return (b-a)/Distance(a,b);
}
vec2 DirectionAB(vec2 a, vec2 b, double distance){      // Returns a normalised vector from a to b without needing to recalculaate the distance between objects
    return (b-a)/distance;
}
void CollisionRectangle(rectangle rec, ball& b){
    if (b.pos.x - b.radius < rec.left || b.pos.x + b.radius > rec.right){
        b.vel.x *= -1*rec.absorbtion_coef;
    } 
    if (b.pos.y - b.radius < rec.down || b.pos.y + b.radius > rec.up){
        b.vel.y *= -1*rec.absorbtion_coef;
    }
}
void CollisionBallBall(ball& b1, ball& b2, double distance_squared){
    vec2 new_v1 = b1.vel - (b1.pos-b2.pos) * ((2*b2.mass)/(b1.mass + b2.mass)) * 
                    (((b1.vel - b2.vel) * (b1.pos-b2.pos))/distance_squared);
    vec2 new_v2 = b2.vel - (b2.pos-b1.pos) * ((2*b1.mass)/(b1.mass + b2.mass)) * 
                    (((b2.vel - b1.vel) * (b2.pos-b1.pos))/distance_squared);
    b1.vel = new_v1;
    b2.vel = new_v2;
}
void CollisionBallBall(ball& b1, ball& b2){
    double distance_squared = sq(b1.pos.x - b2.pos.x) + sq(b1.pos.y - b2.pos.y);
    vec2 new_v1 = b1.vel - (b1.pos-b2.pos) * ((2*b2.mass)/(b1.mass + b2.mass)) * 
                    (((b1.vel - b2.vel) * (b1.pos-b2.pos))/distance_squared);
    vec2 new_v2 = b2.vel - (b2.pos-b1.pos) * ((2*b1.mass)/(b1.mass + b2.mass)) * 
                    (((b2.vel - b1.vel) * (b2.pos-b1.pos))/distance_squared);
    b1.vel = new_v1;
    b2.vel = new_v2;
}
double RandValAtInterval(double min, double max){
    double scale = rand() / (double) RAND_MAX;
    return min + scale * (max - min);
}
void VerletIntegration(ball& ball, double dt, vec2 force){
    ball.pos = ball.pos + ball.vel * dt + ball.acc * dt*dt*0.5;
    vec2 new_acc = force / ball.mass;
    ball.vel = ball.vel + (ball.acc + new_acc) * dt*0.5;
    ball.acc = new_acc;
}
void NoobCollisionCheckAndApply(std::vector<ball>& balls, rectangle border){
    double distance_squared;
    // used unsigned long int since .size() gives a long unsigned int so it doesnt convert one to signed (hopefuly this makes it a little faster)
    for(unsigned long int i = 0; i < balls.size(); i++){
        for(unsigned long int j = i+1; j < balls.size(); j++){
            distance_squared = sq(balls.at(j).pos.x-balls.at(i).pos.x) + sq(balls.at(j).pos.y-balls.at(i).pos.y);//Distance(i.pos, j.pos);
            if (distance_squared < sq(balls.at(i).radius + balls.at(j).radius) )
                CollisionBallBall(balls.at(i), balls.at(j), distance_squared);
        }
        CollisionRectangle(border, balls.at(i));
    }
}
void CollisionCheckAndApply(std::vector<ball>& balls,rectangle border){
    unsigned long int i,j;     // used unsigned long int since .size() gives a long unsigned int so it doesnt convert one to signed (hopefuly this makes it a little faster)
    double x_distance_squared; // since we sort it acording to x we are qoing to compare x distances if they are colliding
    double y_distance_squared; // if our x distance is shorter than we compare y distances 
    double radii_squared;
    std::sort(balls.begin(), balls.end(), [](ball const & a, ball const & b) -> bool { return a.pos.x < b.pos.x; });
    for(i = 0; i < balls.size(); i++){
        for(j = i + 1; j < balls.size(); j++){
            x_distance_squared = sq(balls.at(i).pos.x - balls.at(j).pos.x);
            radii_squared = sq(balls.at(i).radius+balls.at(j).radius);
            if (x_distance_squared < radii_squared){
                y_distance_squared = sq(balls.at(i).pos.y - balls.at(j).pos.y);
                if (y_distance_squared < radii_squared){
                    CollisionBallBall(balls.at(i), balls.at(j), x_distance_squared+y_distance_squared);
                }
            } else {
                break;
            }
        }
        CollisionRectangle(border, balls.at(i));
    }
}
void RadomiseBalls( std::vector<ball>& balls, int nb_balls, rectangle border, double min_r, double max_r, double min_v, double max_v){
    for(int i = 0; i < nb_balls; i++){
        double x = RandValAtInterval(border.left+max_r, border.right-max_r);
        double y = RandValAtInterval(border.down+max_r, border.up-max_r); 
        double v_x = RandValAtInterval(min_v, max_v);
        double v_y = RandValAtInterval(min_v, max_v); 
        balls.push_back(ball(x, y, v_x, v_y, RandValAtInterval(min_r, max_r), 1));
        //balls.at(i).print();
    }
}
int main(){  
    time_t t1;
    srand((unsigned) time(&t1));
    double square_half_length = 20;
    rectangle border(square_half_length);
    border.absorbtion_coef = 0.7;
    border.print();
    int nb_balls = 1000;
    vec2 g(0, -9.81);
    long int nt, NT = 30000;
    double dt = 0.001;
    int save_interval = (int) (1./dt/100.);
    std::cout<<"Interval "<< save_interval << std::endl;
    std::vector<ball> balls;
    double max_r = 0.3;
    double min_r = 0.1;
    char fichier_donnees[30]  =  "donnees.txt";//"Experience1.dat"; 
    InitialiseFichierDeEcriture(fichier_donnees, nb_balls, dt, square_half_length);
    RadomiseBalls(balls, nb_balls, border, min_r, max_r, -10, 10);
    std::sort(balls.begin(), balls.end(),  
                    [](ball const & a, ball const & b) -> bool { return a.pos.x < b.pos.x; });
    for(nt = 0; nt < NT; nt++){
        ProgressBar(nt, NT, dt);
        //NoobCollisionCheckAndApply(balls, border);
        CollisionCheckAndApply(balls, border);
        for(auto& b : balls){
            VerletIntegration(b,dt, g);
        }
        if (nt%10==0){
            EcritureData(fichier_donnees, balls, nt);
        }
    }
    return 0;
}