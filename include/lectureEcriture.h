#ifndef LECTURE_ECRITURE_H_
#define LECTURE_ECRITURE_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

/** Lecture des informations du terrain dans un fichier **/
void lectureInfosTerrain(char chaine[], Terrain * terrain, char nomFichier[]);

/** Ecriture d'un texte sur l'ecran **/
void ecrireTexte(float x, float y, void* font, const char* s);


#endif
