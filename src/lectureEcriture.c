#include "../include/lectureEcriture.h"

// Lecture du fichier de terrain
void lectureInfosTerrain(char chaine[], Terrain * terrain, char nomFichier[]) {
  if(strcmp(nomFichier, "niveau1.txt") != 0 && strcmp(nomFichier, "niveau2.txt") != 0 && strcmp(nomFichier, "niveau3.txt") != 0){
    exit(EXIT_FAILURE);
    }
  FILE *fichier = NULL;
  fichier = fopen(nomFichier, "r");
  if (fichier == NULL){
    exit(EXIT_FAILURE);
  }
  fgets(chaine, 800, fichier);

  int i = 0, j = 0, k = 0, l = 0;
  char nbCheckPoints[10];
  char rayon[10];
  char centreX[10];
  char centreY[10];
  char couleurR[10];
  char couleurV[10];
  char couleurB[10];

  while(chaine[i] != '\\') { // on parcourt jusqu'� la fin de la ligne
    /* R�cup�ration du nombre de checkpoints */
    if(chaine[i] == '-') {
      i ++;
      while(chaine[i] != '-') {
        nbCheckPoints[j] = chaine[i];
        i ++;
        j ++;
      }
      terrain->nbCheckPoints = atol(nbCheckPoints);
    }
    /* R�cup�ration des donn�es de chaque checkpoints */
    if(chaine[i] == '{'){
      i ++;
      while(chaine[i] != '}'){
        // pour chaque checkpoint
        if(chaine[i] == '['){
          j = 0;
          i++;
          // Récupération des coordonnées x et y
          while(chaine[i] != ',') {
            centreX[j] = chaine[i];
            j++;
            i++;
          }
          j = 0;
          i++;
          while(chaine[i] != ';') {
            centreY[j] = chaine[i];
            j++;
            i++;
          }
          j = 0;
          i++;
          // Récupération du rayon
          while(chaine[i] != ';') {
            rayon[j] = chaine[i];
            j++;
            i++;
          }
          j = 0;
          i++;
          // Récupération des 3 couleurs
          while(chaine[i] != ',') {
            couleurR[j] = chaine[i];
            j++;
            i++;
          }
          j = 0;
          i++;
          while(chaine[i] != ',') {
            couleurV[j] = chaine[i];
            j++;
            i++;
          }
          j = 0;
          i++;
          while(chaine[i] != ']'){
            couleurB[j] = chaine[i];
            j++;
            i++;
          }
          terrain->tableCheckPoints[k].centreX = atol(centreX);
          terrain->tableCheckPoints[k].centreY = atol(centreY);
          terrain->tableCheckPoints[k].couleurR = atol(couleurR);
          terrain->tableCheckPoints[k].couleurV = atol(couleurV);
          terrain->tableCheckPoints[k].couleurB = atol(couleurB);
          terrain->tableCheckPoints[k].rayon = atol(rayon);
          terrain->tableCheckPoints[k].visible = 1;
          for(l = 0; l < 10; l++) {
            rayon[l] = ' ';
            centreX[l] = ' ';
            centreY[l] = ' ';
            couleurR[l] = ' ';
            couleurV[l] = ' ';
            couleurB[l] = ' ';
          }
          k++;
        }
        i++;
      }
    }
    i++;
  }
  fclose(fichier);
}


void ecrireTexte(float x, float y, void* font, const char* s)
{
  glColor3f(1, 1, 1);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glRasterPos2f(x, y);
  while(*s)
  {
    glutBitmapCharacter(font, *s);
    s++;
  }
}
