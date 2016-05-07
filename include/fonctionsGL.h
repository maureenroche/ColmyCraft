#ifndef GL_H_
#define GL_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "hovercraft.h"

void reshape(unsigned int windowWidth, unsigned int windowHeight);

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight);

#endif
