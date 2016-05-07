#ifndef INIT_H_
#define INIT_H_

#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

/** Initialisation d'une structure CheckPoint **/
void initCheckPoint(CheckPoint *point);

/** Initialisation d'une structure Terrain **/
void initTerrain(Terrain * terrain);

/** Initialisation de l'hovercraft **/
void initHovercraft(Hovercraft * h, int x, int y, int tailleX, int tailleY);

#endif
