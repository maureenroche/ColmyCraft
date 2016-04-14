#ifndef JEU_H_
#define JEU_H_

#include "structures.h"

int aGagne(Terrain t);

void collision(int positionX, int positionY, int tailleX, int tailleY, Terrain * terrain);

float distance(int xA, int yA, int xB, int yB);

#endif
