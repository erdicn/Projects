#ifndef CLASSES_HPP
#define CLASSES_HPP
#include <iostream>
class vec2{
    public:
        double x,y;
    public:
        vec2(){
            this->x = 0;
            this->y = 0;
        }
        vec2(double val_x, double val_y){
            this->x = val_x;
            this->y = val_y;
        }
        vec2 operator+(const vec2& v){
            return vec2(this->x + v.x, this->y + v.y);
        } 
        void operator+=(const vec2 v){
            this->x = this->x + v.x;
            this->y = this->y + v.y;
        }
        vec2 operator-(const vec2& v){
            return vec2(this->x - v.x, this->y - v.y);
        } 
        void operator-=(const vec2 v){
            this->x = this->x - v.x;
            this->y = this->y - v.y;
        }
        vec2 operator*(const double s){
            return vec2(this->x*s, this->y*s);
        }  
        void operator*=(const double s){
            this->x = this->x*s;
            this->y = this->y*s;
        } 
        double operator*(const vec2 v){//produit scalaire
            return this->x * v.x + this->y * v.y;
        }
        vec2 operator/(const double s){
            return vec2(this->x/s, this->y/s);
        }   
        void print(){
            std::cout<<x<<" "<<y;
        }
};
class ball{
    private:
        /* data */
    public:
        vec2 pos;
        vec2 vel;
        vec2 acc;
        double radius = 1;
        double mass = 1;
    public:
        ball(){}
        ball(double x, double y){
            this->pos.x = x;
            this->pos.y = y;
        }
        ball(double x, double y, double val_radius){
            this->pos.x = x;
            this->pos.y = y;
            this->radius = val_radius;
        }
        ball(double x, double y, double val_radius, double val_mass){
            this->pos.x = x;
            this->pos.y = y;
            this->radius = val_radius;
            this->mass = val_mass;
        }
        ball(double x, double y, double v_x, double v_y, double val_radius, double val_mass){
            this->pos.x = x;
            this->pos.y = y;
            this->vel.x = v_x;
            this->vel.y = v_y;
            this->radius = val_radius;
            this->mass  = val_mass;
        }
        void print(){
            std::cout<<"| R "<< this->radius<<" | M " <<this->mass<<' ';
            std::cout<<"| pos ";pos.print();
            std::cout<<"| vel ";vel.print();
            std::cout<<"| acc ";acc.print();
            std::cout<<" |\n";
        }
        bool operator <(ball b) { return (pos.x < b.pos.x);}
};
class rectangle{
    public:
        double left  = -10;
        double right =  10;
        double up    =  10;
        double down  = -10;
        double absorbtion_coef = 1;
    public:
        rectangle(){}
        rectangle(double val){// makes so the rectangle is square
            this->left  = -val;
            this->right =  val;
            this->up    =  val;
            this->down  = -val; 
        }
        rectangle(double val_left, double val_right, double val_up, double val_down){
            this->left  = val_left;
            this->right = val_right;
            this->up    = val_up;
            this->down  = val_down;
        }
        ~rectangle(){}
        void print(){
            std::cout<<this->left<<' '<<this->right<<' '<<this->down<<' '<<this->up<<" coef="<<this->absorbtion_coef<<std::endl;
        }
};
class obstacle{
    public:
        vec2 centre;
        double rayon;
        obstacle(){
            this->rayon = 0;
            this->centre = vec2();
        }
        obstacle(double x, double y, double val_rayon){
            this->rayon = val_rayon;
            this->centre = vec2(x, y);
        }
};

#endif //CLASSES_HPP