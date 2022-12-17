#ifndef READ_WRITE_HPP
#define READ_WRITE_HPP

#include <vector>
#include "classes.hpp"

void ProgressBar(long int nt, long int NT,double dt);
void EcritureData(char* nom_fichier, std::vector<ball> balls, long int nt);
void InitialiseFichierDeEcriture(char* nom_fichier, int nb_balls, double dt, double border_half);


#endif //READ_WRITE_HPP