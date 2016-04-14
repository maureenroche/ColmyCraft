#include "../include/fonctionsJeu.h"

int aGagne(Terrain t) {
  int gagne = 1;
  int i;
  for(i = 0; i < t.nbCheckPoints; i++) {
    if(t.tableCheckPoints[i].visible == 1) {
      gagne = 0;
    }
  }
  return gagne;
}

void collision(int positionX, int positionY, int tailleX, int tailleY, Terrain * terrain) {
  int i;
  for(i = 0; i < terrain->nbCheckPoints; i ++)
  {
    if((positionY + tailleY > terrain->tableCheckPoints[i].centreY) &&
        (positionY < terrain->tableCheckPoints[i].centreY + terrain->tableCheckPoints[i].rayon) &&
        (positionX + tailleX > terrain->tableCheckPoints[i].centreX) &&
        (positionX < terrain->tableCheckPoints[i].centreX + terrain->tableCheckPoints[i].rayon))
    {
      terrain->tableCheckPoints[i].visible = 0;
    }
  }
}

float distance(int xA, int yA, int xB, int yB)
{
  return sqrt(pow(xB-xA, 2) + pow(yB-yA, 2));
}
