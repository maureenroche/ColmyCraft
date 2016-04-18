#ifndef DESSIN_H
#define DESSIN_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"

void dessinCarre(int full);
void dessinCercle(int nbTraits,int full);
void dessinHovercraft();
void dessinCheckPoint(CheckPoint cp);

#endif
