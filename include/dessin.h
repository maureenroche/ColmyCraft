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

/** Dessin d'un carre unitaire **/
void dessinCarre(int full);

/** Dessin d'un cercle unitaire **/
void dessinCercle(int nbTraits,int full);

/** Dessin d'un carre arrondi unitaire **/
void dessinCarreArrondi();

/** Dessin de l'effet du moteur sur l'eau **/
void dessinJetMoteur();

/** Dessin de l'hovercraft **/
void dessinHovercraft();

/** Dessin du checkpoint **/
void dessinCheckPoint(CheckPoint cp);

#endif
