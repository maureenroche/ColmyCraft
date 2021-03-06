#include "../include/fonctionsInit.h"

/** Initialisation d'une structure CheckPoint **/
void initCheckPoint(CheckPoint *point)
{
  point->rayon = 0;
  point->centreX = 0;
  point->centreY = 0;
  point->couleurR = 0;
  point->couleurV = 0;
  point->couleurB = 0;
  point->teste = 0;
}

/** Initialisation d'une structure Terrain **/
void initTerrain(Terrain * terrain)
{
  terrain->nbCheckPoints = 0;
  int i;
  for (i = 0; i < 100; i++)
  {
    initCheckPoint(&(terrain->tableCheckPoints[i]));
  }
}

/** Initialisation de l'hovercraft **/
void initHovercraft(Hovercraft * h, int x, int y, int tailleX, int tailleY)
{
  h->anglePosition = 90;
  h->angleMouvement = 30;
  h->positionX = x;
  h->positionY = y;
  h->tailleX = tailleX;
  h->tailleY = tailleY;
  h->vitesse = 0;
  h->acceleration = 4;
  h->deceleration = 0.2;
  h->prochainCheckpoint = NULL;
}
