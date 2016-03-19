#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SEGMENTS 60
#define PI 3.14
#define FOND_R 0
#define FOND_V 128
#define FOND_B 232

// Structure check point
typedef struct CheckPoint {
  int rayon;
  int centreX;
  int centreY;
  int couleurR;
  int couleurV;
  int couleurB;
  int visible;
} CheckPoint;


// Structure terrain
typedef struct Terrain {
  int nbCheckPoints;
  CheckPoint tableCheckPoints[100];
} Terrain;


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Nombre max de points dessin�s*/
static const unsigned int NB_MAX_PT = 50;

void reshape(unsigned int windowWidth, unsigned int windowHeight) {
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, windowWidth, 0, windowHeight);
}

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

// Initialisation CheckPoint
void initCheckPoint(CheckPoint *point){
  point->rayon = 0;
  point->centreX = 0;
  point->centreY = 0;
  point->couleurR = 0;
  point->couleurV = 0;
  point->couleurB = 0;
}

// Initialisation Terrain
void initTerrain(Terrain * terrain){
  terrain->nbCheckPoints = 0;
  int i;
  for (i = 0; i < 100; i++) {
    initCheckPoint(&(terrain->tableCheckPoints[i]));
  }
}

// Lecture du fichier de terrain
void lectureInfosTerrain(char chaine[], Terrain * terrain){
  FILE *fichier = NULL;
  fichier = fopen("terrain.txt", "r");
  if (fichier == NULL){
    exit(EXIT_FAILURE);
  }
  fgets(chaine, 400, fichier);

  int i = 0, j = 0, k = 0, l = 0;
  char nbCheckPoints[3];
  char rayon[3];
  char centreX[3];
  char centreY[3];
  char couleurR[3];
  char couleurV[3];
  char couleurB[3];

  while(chaine[i] != '/') { // on parcourt jusqu'� la fin de la ligne
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
        // A AMELIORER
        for(l = 0; l <3; l++) {
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

void dessinCarre(int full){
  if(full==0){
    glBegin(GL_LINE_LOOP);
      glVertex2f(-0.5,-0.5);
      glVertex2f(-0.5, 0.5);
      glVertex2f( 0.5, 0.5);
      glVertex2f( 0.5,-0.5);
    glEnd();
  }
  else if(full==1){
    glBegin(GL_POLYGON);
      glVertex2f(-0.5,-0.5);
      glVertex2f(-0.5, 0.5);
      glVertex2f( 0.5, 0.5);
      glVertex2f( 0.5,-0.5);
    glEnd();
  }
}

void dessinCercle(int nbTraits,int full){
  float angle=(M_PI*2)/nbTraits;
  int i;
  if(full==0){
    glBegin(GL_LINE_LOOP);
    for(i=0; i<nbTraits;i++){
      glVertex2f(cos(i*angle)/2,sin(i*angle)/2);
    }
    glEnd();
  }
  else if(full==1){
    glBegin(GL_POLYGON);
    for(i=0; i<nbTraits;i++){
      glVertex2f(cos(i*angle)/2,sin(i*angle)/2);
    }
    glEnd();
  }
}

void dessinHovercraft() {
    //Structure : cercle
    glPushMatrix();
      glColor3f(0.15,0.15,0.15);
      dessinCercle(100,1);
    glPopMatrix();

    //Tableau de bord
    glPushMatrix();
      glColor3f(0,0,0);
      glScalef(0.8,0.8,1);
      dessinCercle(100,1);
    glPopMatrix();

    //Moteur
    glPushMatrix();
      glLineWidth(5);
      glColor3f(0,0,0);
      glTranslatef(0,-0.5,0);
      glScalef(0.4,0.4,1);
      dessinCercle(200,0);
    glPopMatrix();

    //Structure : carré
    glPushMatrix();
      glColor3f(0.15,0.15,0.15);
      glTranslatef(0,-0.25,0);
      glScalef(1,0.5,1);
      dessinCarre(1);
    glPopMatrix();

    // Dessin en M
    glPushMatrix();
      glColor3f(0,0,0);
      glLineWidth(1);
      glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.1, 0);
        glVertex2f(0, -0.5);
        glVertex2f(0.1, 0);
        glVertex2f(0.5,-0.5);
      glEnd();
    glPopMatrix();
}

void dessinCheckPoint(CheckPoint cp) {
  float diametre = 1;
  float alpha;
  int i;

  glTranslatef(cp.centreX, cp.centreY, 0);
  glScalef(cp.rayon, cp.rayon, 1);

  glBegin(GL_POLYGON);
  glColor3f(cp.couleurR/255.0, cp.couleurV/255.0, cp.couleurB/255.0);
  for(i = 0; i <= SEGMENTS; i ++){
    alpha = 2*PI*i/SEGMENTS;
    glVertex2f(cos(alpha)*(diametre/2), sin(alpha)*(diametre/2));
    alpha = 2*PI*(i+1)/SEGMENTS;
    glVertex2f(cos(alpha)*(diametre/2), sin(alpha)*(diametre/2));
  }
  glColor3f(1,1,1);
  glEnd();
}

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
  int x = positionX + tailleX;
  int y = positionY + tailleY;
  int xCercle, yCercle;
  for(i = 0; i < terrain->nbCheckPoints; i ++)
  {
    if((x >= terrain->tableCheckPoints[i].centreX - terrain->tableCheckPoints[i].rayon)&&
        (x <= terrain->tableCheckPoints[i].centreX + terrain->tableCheckPoints[i].rayon) &&
        (y >= terrain->tableCheckPoints[i].centreY - terrain->tableCheckPoints[i].rayon) &&
        (y <= terrain->tableCheckPoints[i].centreY + terrain->tableCheckPoints[i].rayon))
    {
      terrain->tableCheckPoints[i].visible = 0;
    }
  }
}

int main(int argc, char** argv) {

  if(argc != 2){
    printf("usage : %s terrain.txt\n",argv[0]);
    return EXIT_FAILURE;
  }

  Terrain terrain;
  initTerrain(&terrain);
  char infosTerrain[200] = "";
  int i;
  float chrono = 0;
  int avance;
  int positionX = 60, positionY = 90, acceleration = 1, rotation = 1;
  /* Lecture des infos du terrain et initialisation du terrain */
  lectureInfosTerrain(infosTerrain, &terrain);
  for(i = 0; i < terrain.nbCheckPoints; i ++) {
    printf("checkpoint num %d : centreX %d, centreY %d, R %d, V %d, B %d, rayon %d \n", i, terrain.tableCheckPoints[i].centreX, terrain.tableCheckPoints[i].centreY,
    terrain.tableCheckPoints[i].couleurR, terrain.tableCheckPoints[i].couleurV, terrain.tableCheckPoints[i].couleurB, terrain.tableCheckPoints[i].rayon);
  }

  /* Dimensions de la fenêtre */
  unsigned int windowWidth  = 1500;
  unsigned int windowHeight = 800;

  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Ouverture d'une fen�tre et cr�ation d'un contexte OpenGL */
  setVideoMode(windowWidth, windowHeight);
  reshape(windowWidth,windowHeight);

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("ColmyCraft", NULL);

  /* Boucle d'affichage */
  int loop = 1;
  while(loop) {
    /* R�cup�ration du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(FOND_R/255.0,FOND_V/255.0,FOND_B/255.0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    chrono ++;
    if(aGagne(terrain) == 1) {
      loop = 0;
      printf("vous avez gagné en %f secondes !", chrono/24);
    }
    /// DESSIN DES CHECKPOINTS
    for(i = 0; i < terrain.nbCheckPoints; i ++) {
      if(terrain.tableCheckPoints[i].visible == 1) {
        glPushMatrix();
          dessinCheckPoint(terrain.tableCheckPoints[i]);
        glPopMatrix();
      }
    }

    /// DESSIN DU HOVERCRAFT !!
    glPushMatrix();
      glTranslatef(positionX*acceleration, positionY*acceleration, 0);
      glScalef(60,60,1);
      dessinHovercraft();
    glPopMatrix();

   collision(positionX, positionY, 60, 60, &terrain); // taille de l'hovercraft + sa position

    /* Echange du front et du back buffer : mise �  jour de la fenêtre */
    SDL_GL_SwapBuffers();

    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenetre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        printf("Temps de jeu écoulé : %f\n", chrono/24);
        break;
      }

      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {
        /* resize window */
        case SDL_VIDEORESIZE:
        windowWidth  = e.resize.w;
        windowHeight = e.resize.h;
        setVideoMode(windowWidth, windowHeight);
        reshape(windowWidth, windowHeight);
        break;

        // gestion des touches du clavier
        case SDL_KEYDOWN:
        avance = 1;
        switch( e.key.keysym.sym ){
          case SDLK_RIGHT:
              positionX  = positionX + 50;
            break;

          case SDLK_LEFT:
          positionX  = positionX - 50;
          break;

          case SDLK_UP:
          positionY = positionY + 50;
          break;

          case SDLK_DOWN:
          positionY  = positionY - 50;
          break;

          case SDLK_SPACE:
          //acceleration ++;
          break;

          default:
          break;
        }
        break;

        case SDL_KEYUP:
          avance = 0;
        break;

        default:
        break;
      }
    }

    /* Calcul du temps �coul� */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    /* Si trop peu de temps s'est �coul�, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  /* Liberation des ressources associ�es �  la SDL */
  SDL_Quit();

  return EXIT_SUCCESS;
}
