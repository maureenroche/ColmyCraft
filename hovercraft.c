#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI 3.141592653589793
#define SEGMENTS 60
#define FOND_R 253
#define FOND_V 217
#define FOND_B 95
#define VITESSE_MAX 10
#define ZOOM 800

// Structure check point
typedef struct CheckPoint {
  int rayon;
  int centreX;
  int centreY;
  int couleurR;
  int couleurV;
  int couleurB;
  int visible;
  int teste;
} CheckPoint;


// Structure terrain
typedef struct Terrain {
  int nbCheckPoints;
  CheckPoint tableCheckPoints[100];
} Terrain;

// Structure Hovercraft
typedef struct Hovercraft {
    int positionX;
    int positionY;
    int tailleX;
    int tailleY;
    /* angle de départ */
    int anglePosition;
    /* angle de déviation */
    int angleMouvement;
    /* vitesse à l'instant t, en pixels par image */
    float vitesse;
    /* valeur d'augmentation de la vitesse en pixels par image */
    float acceleration;
    /* valeur de diminution de la vitesse en pixels par image */
    float deceleration;
    /* Checkpoint le plus près de l'hovercraft */
    CheckPoint * prochainCheckpoint;
} Hovercraft;


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
  gluOrtho2D(0, (float)ZOOM, 0, ((float)windowHeight/windowWidth)*ZOOM);
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
  point->teste = 0;
}

// Initialisation Terrain
void initTerrain(Terrain * terrain){
  terrain->nbCheckPoints = 0;
  int i;
  for (i = 0; i < 100; i++) {
    initCheckPoint(&(terrain->tableCheckPoints[i]));
  }
}

// Initialisation de l'hovercraft
void initHovercraft(Hovercraft * h, int x, int y, int tailleX, int tailleY) {
  h->anglePosition = 90;
  h->angleMouvement = 30;
  h->positionX = x;
  h->positionY = y;
  h->tailleX = tailleX;
  h->tailleY = tailleY;
  h->vitesse = 0;
  h->acceleration = 2;
  h->deceleration = 0.025;
  h->prochainCheckpoint = NULL;
}

// Lecture du fichier de terrain
void lectureInfosTerrain(char chaine[], Terrain * terrain, char nomFichier[]){
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


int main(int argc, char** argv) {

  if(argc != 3){
    printf("usage : %s terrain.txt image.jpg\n",argv[0]);
    return EXIT_FAILURE;
  }

  Terrain terrain;
  initTerrain(&terrain);
  char infosTerrain[800] = "";
  int i, checkPointsNonVisibles = 0;
  float chrono = 0;
  char texte[50];
  Hovercraft colmycraft;
  initHovercraft(&colmycraft, 0, 0, 30, 30);
  int fondR, fondV, fondB;
  /* Lecture des infos du terrain et initialisation du terrain */
  lectureInfosTerrain(infosTerrain, &terrain, argv[1]);
  colmycraft.prochainCheckpoint = &terrain.tableCheckPoints[0];

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

    if(strcmp(argv[2], "background-Level1.jpg") == 0){
          fondR = 253;
          fondV = 217;
          fondB = 95;
    }
    else if(strcmp(argv[2], "background-Level2.jpg") == 0) {
          fondR = 88;
          fondV = 162;
          fondB = 63;
    }
    else if(strcmp(argv[2], "background-Level3.jpg") == 0) {
          fondR = 58;
          fondV = 45;
          fondB = 36;
    }
    else {
          fondR = 0;
          fondV = 0;
          fondB = 0;
    }

  // CREATION D'UNE IMAGE
  SDL_Surface* image = IMG_Load(argv[2]);
    if(image == NULL) {
        fprintf(stderr, "Impossible de charger l'image %s\n", argv[2]);
        return EXIT_FAILURE;
  }

  GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    switch(image->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", argv[1]);
            return EXIT_FAILURE;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(image);

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("ColmyCraft", NULL);

  /* Boucle d'affichage */
  int loop = 1;
  while(loop) {
    /* R�cup�ration du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(fondR/255.0,fondV/255.0,fondB/255.0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // déplacement de la caméra
    glTranslatef(- colmycraft.positionX + colmycraft.tailleX + 350, - colmycraft.positionY + colmycraft.tailleY + 175, 1);

    // dessin des bordures
    glPushMatrix();

    // on affiche une texture 2D ici
        glEnable(GL_TEXTURE_2D);
        // à partir de maintenant, on parle de cette texture
        glBindTexture(GL_TEXTURE_2D, textureId);
      glBegin(GL_QUADS);
        glColor3f(1,1,1);

        glTexCoord2f(0, 1);
        glVertex2f(0, 0);

        glTexCoord2f(1, 1);
        glVertex2f(windowWidth, 0);

        glTexCoord2f(1, 0);
        glVertex2f(windowWidth, windowHeight);

        glTexCoord2f(0, 0);
        glVertex2f(0, windowHeight);
      glEnd();

      // on a fini avec la texture
      glBindTexture(GL_TEXTURE_2D, 0);
      // on affiche plus de texture
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    chrono ++;
    if(aGagne(terrain) == 1) {
      ecrireTexte(colmycraft.positionX - colmycraft.tailleX - 20, colmycraft.positionY + colmycraft.tailleY, GLUT_BITMAP_HELVETICA_18, "VOUS AVEZ GAGNE !");
    }

    /// DESSIN DES CHECKPOINTS
    for(i = 0; i < terrain.nbCheckPoints; i ++) {
      if(terrain.tableCheckPoints[i].visible == 1) {
        glPushMatrix();
          dessinCheckPoint(terrain.tableCheckPoints[i]);
        glPopMatrix();

        if(colmycraft.prochainCheckpoint->visible == 1)
        {
          if(distance(terrain.tableCheckPoints[i].centreX, terrain.tableCheckPoints[i].centreY, colmycraft.positionX, colmycraft.positionY)
            < distance(colmycraft.prochainCheckpoint->centreX, colmycraft.prochainCheckpoint->centreY, colmycraft.positionX, colmycraft.positionY)) {
            colmycraft.prochainCheckpoint = &terrain.tableCheckPoints[i];
          }
        }
        else {
          colmycraft.prochainCheckpoint = &terrain.tableCheckPoints[i];
        }
      }
      else if(terrain.tableCheckPoints[i].teste == 0) {
        checkPointsNonVisibles ++;
        terrain.tableCheckPoints[i].teste = 1;
      }
    }

    /// DESSIN DE LA FLECHE VERS LE PROCHAIN CHECKPOINT
    glPushMatrix();
      glColor3f(1, 1, 1);
      glBegin(GL_LINE_LOOP);
        glVertex2f(colmycraft.positionX, colmycraft.positionY);
        glVertex2f(colmycraft.positionX + (colmycraft.prochainCheckpoint->centreX - colmycraft.positionX)/2.5, colmycraft.positionY + (colmycraft.prochainCheckpoint->centreY - colmycraft.positionY)/2.5);
      glEnd();
    glPopMatrix();

    /// DESSIN DE L'HOVERCRAFT
    glPushMatrix();
      glTranslatef(colmycraft.positionX, colmycraft.positionY, 0);
      glScalef(colmycraft.tailleX,colmycraft.tailleY,1);
      glRotatef(colmycraft.anglePosition - 90, 0.0, 0.0, 1.0);
      dessinHovercraft();
    glPopMatrix();

    // ajoute à la chaîne de caractère texte le nombre de checkpoints non visibles
    sprintf(texte, "Score : %d / %d", checkPointsNonVisibles, terrain.nbCheckPoints);
    ecrireTexte(colmycraft.positionX - 350, colmycraft.positionY + 175, GLUT_BITMAP_HELVETICA_18, texte);

    collision(colmycraft.positionX, colmycraft.positionY, colmycraft.tailleX, colmycraft.tailleY, &terrain);

    // gestion de la décélération / des frottements
    if(colmycraft.vitesse > 0.000000 + colmycraft.deceleration) {
      colmycraft.vitesse -= colmycraft.deceleration;
    }

    //déplacement de l'hovercraft
    colmycraft.positionY  += colmycraft.vitesse*sin(PI * (colmycraft.anglePosition) / 180);
    colmycraft.positionX  += colmycraft.vitesse*cos(PI * (colmycraft.anglePosition) / 180);

    // Bords Y
    if(colmycraft.positionY + colmycraft.tailleY >= windowHeight) {
      colmycraft.positionY = windowHeight - colmycraft.tailleY;
    }
    if(colmycraft.positionY - colmycraft.tailleY <= 0) {
      colmycraft.positionY = colmycraft.tailleY;
    }
    // Bords X
    if(colmycraft.positionX + colmycraft.tailleX >= windowWidth) {
      colmycraft.positionX = windowWidth - colmycraft.tailleX;
    }
    if(colmycraft.positionX - colmycraft.tailleX <= 0) {
      colmycraft.positionX = colmycraft.tailleX;
    }

    /* Echange du front et du back buffer : mise �  jour de la fenêtre */
    SDL_GL_SwapBuffers();

    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenetre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        printf("Temps de jeu ecoule : %f\n", chrono/24);
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
        switch(e.key.keysym.sym ){
          case SDLK_RIGHT:
              colmycraft.anglePosition -= colmycraft.angleMouvement;
          break;

          case SDLK_LEFT:
            colmycraft.anglePosition += colmycraft.angleMouvement;
          break;

          case SDLK_UP:
            if(colmycraft.vitesse < VITESSE_MAX) {
              colmycraft.vitesse += colmycraft.acceleration;
            }
          break;

          default:
          break;
        }

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

  glDeleteTextures(1, &textureId);

  /* Liberation des ressources associ�es �  la L */
  SDL_Quit();

  return EXIT_SUCCESS;
}
