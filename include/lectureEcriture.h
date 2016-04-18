#ifndef LECTURE_ECRITURE_H_
#define LECTURE_ECRITURE_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

// Lecture du fichier de terrain
void lectureInfosTerrain(char chaine[], Terrain * terrain, char nomFichier[]);

// Ecrire du texte
void ecrireTexte(float x, float y, void* font, const char* s);


#endif
