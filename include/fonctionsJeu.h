#ifndef JEU_H_
#define JEU_H_

#include "structures.h"

/** Verification si tous les checkpoints ont ete touches 
/// retourne 1 si le joueur a gagne le niveau
/// retourne 0 sinon  **/
int aGagne(Terrain t);

/** Verification si l'hovercraft a touche un checkpoint **/
void collision(int positionX, int positionY, int tailleX, int tailleY, Terrain * terrain);

/** Calcul de distance entre deux points A et B
/// retourne la distance **/
float distance(int xA, int yA, int xB, int yB);

#endif
