#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define PI 3.141592653589793
#define SEGMENTS 60 // Précision dans le dessin d'un cercle
#define VITESSE_MAX 20 // Vitesse maximum de l'hovercraft
#define ZOOM 800

/** Structure Checkpoint **/
typedef struct CheckPoint
{
  int rayon;
  int centreX;
  int centreY;
  int couleurR;
  int couleurV;
  int couleurB;
  int visible;
  int teste;
} CheckPoint;


/** Structure Terrain **/
typedef struct Terrain
{
  int nbCheckPoints;
  CheckPoint tableCheckPoints[100];
} Terrain;

/** Structure Hovercraft **/
typedef struct Hovercraft
{
  int positionX;
  int positionY;
  int tailleX;
  int tailleY;
  // angle de départ
  int anglePosition;
  // angle de déviation
  int angleMouvement;
  // vitesse à l'instant t, en pixels par image
  float vitesse;
  // valeur d'augmentation de la vitesse en pixels par image
  float acceleration;
  // valeur de diminution de la vitesse en pixels par image
  float deceleration;
  // Checkpoint le plus près de l'hovercraft
  CheckPoint * prochainCheckpoint;
} Hovercraft;

#endif
