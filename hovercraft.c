#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SEGMENTS 60
#define PI 3.14
#define FOND_R 69
#define FOND_V 141
#define FOND_B 244

// Structure check point
typedef struct CheckPoint {
    int rayon;
    int centreX;
    int centreY;
    int couleurR;
    int couleurV;
    int couleurB;
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
  gluOrtho2D(-200.0, 200.0,-((float)windowHeight/windowWidth)*200, ((float)windowHeight/windowWidth)*200);
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
    fgets(chaine, 100, fichier);

    int i = 0, j = 0, k = 0, l = 0;
    char nbCheckPoints[5];
    char rayon[10];
    char centreX[10];
    char centreY[10];

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
                    while(chaine[i] != ';') {
                        centreX[j] = chaine[i];
                        j++;
                        i++;
                    }
                    j = 0;
                    i++;
                    while(chaine[i] != ']'){
                        rayon[j] = chaine[i];
                        j++;
                        i++;
                    }
                    terrain->tableCheckPoints[k].centreX = atol(centreX);
                    terrain->tableCheckPoints[k].rayon = atol(rayon);
                    // A AMELIORER
                    for(l = 0; l <10; l++) {
                        rayon[l] = ' ';
                        centreX[l] = ' ';
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

// terrain = malloc(sizeof(int) + atol(nbCheckPoints)*sizeof(CheckPoint));
//
// for(l=0; l<terrain->nbCheckPoints;i++){
//   initCheckPoint(&(terrain->tableCheckPoints[l]));
// }

void dessinHovercraft() {
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f( 0.5, 0.5);
        glVertex2f( 0.5,-0.5);
    glEnd();
}

void dessinCheckPoint(CheckPoint cp) {
    float diametre = 1;
    float alpha;
    int i;
    glBegin(GL_LINES);
    glColor3f(cp.couleurR, cp.couleurV, cp.couleurB);
    for(i = 0; i <= SEGMENTS; i ++){
        alpha = 2*PI*i/SEGMENTS;
        glVertex2f(cos(alpha)*(diametre/2), sin(alpha)*(diametre/2));
        alpha = 2*PI*(i+1)/SEGMENTS;
        glVertex2f(cos(alpha)*(diametre/2), sin(alpha)*(diametre/2));
     }
     glColor3f(FOND_R, FOND_V, FOND_B);
     glEnd();
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

    int directionX = 0, directionY = 0, acceleration = 1;
    /* Lecture des infos du terrain et initialisation du terrain */
    lectureInfosTerrain(infosTerrain, &terrain);
    for(i = 0; i < terrain.nbCheckPoints; i ++) {
        printf("checkpoint num %d : centre %d, rayon %d \n", i, terrain.tableCheckPoints[i].centreX, terrain.tableCheckPoints[i].rayon);
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /// DESSIN D'UN CARRE POUR TESTER LE MOUVEMENT !!
    glPushMatrix();
        glScalef(10,10,1);
        glTranslatef(directionX*acceleration, directionY*acceleration, 0);
        dessinHovercraft();
    glPopMatrix();

    /// DESSIN DES CHECKPOINTS
    for(i = 0; i < terrain.nbCheckPoints; i ++) {
        glPushMatrix();
            
        glPopMatrix();
    }


    /* Echange du front et du back buffer : mise �  jour de la fenêtre */
    SDL_GL_SwapBuffers();

    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenetre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
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
            switch( e.key.keysym.sym ){
                case SDLK_RIGHT:
                    directionX ++;
                    break;

                case SDLK_LEFT:
                    directionX --;
                    break;

                case SDLK_UP:
                    directionY ++;
                    break;

                case SDLK_DOWN:
                    directionY --;
                    break;

                case SDLK_SPACE:
                    acceleration ++;
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

  /* Liberation des ressources associ�es �  la SDL */
  SDL_Quit();

  return EXIT_SUCCESS;
}
