#include <cstdlib>
#include <iostream>
#include <vector>
#include "classes.hpp"
void ProgressBar(long int nt, long int NT,double dt){
	if (nt % (int)(NT / 100) == 0){
		printf("\r%%%ld nt = %ld (%.2lfs)", nt/(NT/100), nt, nt*dt); // pour voir l'avancement
		fflush(stdout); // le \r écrit par dessus la ligne et il ne faut pas mettre \n car ça fait tun flush implicitement mais nous on a besoin de flush apres pour reecrir
    }
}

void EcritureData(char* nom_fichier, std::vector<ball> balls, long int nt){
	FILE* fichier_de_ecriture= fopen(nom_fichier,"a"); 
	if (fichier_de_ecriture== NULL){
		printf("Error opening file!\n");
		exit(1);
	} else{
		// on parcour notre tableau et on mets chaque element du tableau dans le fichier 
		for(auto& i :balls){
			fprintf(fichier_de_ecriture, "%ld %.16lf %.16lf %.16lf\n",//%.16lf %.16lf %.16lf %.16lf %.16lf %.16lf %.16lf\n", //"%ld %g %g %g %g %g %g %g %g %g %g\n",
										nt, i.pos.x, i.pos.y, i.radius);
		}
		fclose(fichier_de_ecriture);
	}
}
void InitialiseFichierDeEcriture(char* nom_fichier, int nb_balls, double dt, double border_half){
	FILE* fichier_de_ecriture= fopen(nom_fichier,"w"); //When you open a file with "w" flag it creates an empty file for writing. If a file with the same name already exists its contents are erased and the file is treated as an empty new file. source: https://stackoverflow.com/questions/4815251/how-do-i-clear-the-whole-contents-of-a-file-in-c#:~:text=If%20a%20file%20with%20the,was%20in%20the%20file%20previously. 
	if (fichier_de_ecriture== NULL){
		printf("Error opening file!\n");
		exit(1);
	} else{
        fprintf(fichier_de_ecriture, "%d %lf %lf %d\n",nb_balls, dt, border_half, nb_balls);
		fclose(fichier_de_ecriture);
	}
}
