#include "../include/hovercraft.h"

#include "../include/structures.h"
#include "../include/fonctionsGL.h"
#include "../include/fonctionsInit.h"
#include "../include/lectureEcriture.h"
#include "../include/dessin.h"
#include "../include/fonctionsJeu.h"
#include "../include/audio.h"

int main(int argc, char** argv) {

  glutInit(&argc, argv);

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
  char niveauTexte[]= "niveau1.txt";
  char carte[]="background-Level1.jpg";
  fondR = 253;
  fondV = 217;
  fondB = 95;
  int niveau = 1;

  lectureInfosTerrain(infosTerrain, &terrain, niveauTexte);
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


  // CREATION D'UNE IMAGE
  SDL_Surface* image = IMG_Load(carte);
  if(image == NULL) {
    fprintf(stderr, "Impossible de charger l'image %s\n", carte);
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
    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", carte);
    return EXIT_FAILURE;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);

  SDL_FreeSurface(image);

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("ColmyCraft", NULL);


  // CREATION SON
  // Initialize SDL.
  if (SDL_Init(SDL_INIT_AUDIO) < 0) return 1;

  // local variables
  static Uint32 wav_length; // length of our sample
  static Uint8 *wav_buffer; // buffer containing our audio file
  static SDL_AudioSpec wav_spec; // the specs of our piece of music

  /* Load the WAV */
  // the specs, length and buffer of our wav are filled
  if(SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL){
    printf("Impossible de charger le fichier son. \n");
  }

  // set the callback function
  wav_spec.callback = my_audio_callback;
  wav_spec.userdata = NULL;
  // set our global static variables
  audio_pos = wav_buffer; // copy sound buffer
  audio_len = wav_length; // copy file length

  /* Open the audio device */
  if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
    printf("Impossible d'ouvrir le fichier son. \n");
  }

  /* Start playing */
  SDL_PauseAudio(0);



  /* BOUCLE D'AFFICHAGE */
  int loop = 1;
  while(loop /*&& audio_len > 0*/) {
    /* R�cup�ration du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    /* Attente d'1/10 de seconde */
    SDL_Delay(100);

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
    //Changement de niveau
    if(aGagne(terrain) == 1 && niveau<=3) {
      if (niveau == 3) {
        // Affichage page Winner
        SDL_Surface* imageGagne = IMG_Load("winner.jpg");
        if(imageGagne == NULL) {
          ecrireTexte(colmycraft.positionX - colmycraft.tailleX - 20, colmycraft.positionY + colmycraft.tailleY, GLUT_BITMAP_HELVETICA_18, "VOUS AVEZ GAGNE !");
        }
        GLuint textureWinnerId;
        glGenTextures(1, &textureWinnerId);
        glBindTexture(GL_TEXTURE_2D, textureWinnerId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        switch(imageGagne->format->BytesPerPixel) {
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
          fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", "winner.jpg");
          return EXIT_FAILURE;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageGagne->w, imageGagne->h, 0, format, GL_UNSIGNED_BYTE, imageGagne->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(imageGagne);

        // on affiche une texture 2D ici
        glEnable(GL_TEXTURE_2D);
        // à partir de maintenant, on parle de cette texture
        glBindTexture(GL_TEXTURE_2D, textureWinnerId);
        glBegin(GL_QUADS);
        glColor3f(1,1,1);

        glTexCoord2f(0, 1);
        glVertex2f(colmycraft.positionX - 350, colmycraft.positionY - 175);

        glTexCoord2f(1, 1);
        glVertex2f(colmycraft.positionX + 350, colmycraft.positionY - 175);

        glTexCoord2f(1, 0);
        glVertex2f(colmycraft.positionX + 350, colmycraft.positionY + 175);

        glTexCoord2f(0, 0);
        glVertex2f(colmycraft.positionX - 350, colmycraft.positionY + 175);

        glEnd();


        // on a fini avec la texture
        glBindTexture(GL_TEXTURE_2D, 0);
        // on affiche plus de texture
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

      }else{
        niveau ++;
        initTerrain(&terrain);
        checkPointsNonVisibles = 0;
        for (int j = 0; j < 12; j++) {
          niveauTexte[j]=' ';
        }
        for (int j = 0; j < 22; j++) {
          carte[j]=' ';
        }
        switch (niveau) {
          case 1:
          strcpy(niveauTexte, "niveau1.txt");
          strcpy(carte, "background-Level1.jpg");
          fondR = 253;
          fondV = 217;
          fondB = 95;
          break;
          case 2:
          strcpy(niveauTexte, "niveau2.txt");
          strcpy(carte, "background-Level2.jpg");
          fondR = 88;
          fondV = 162;
          fondB = 63;
          break;
          case 3:
          strcpy(niveauTexte, "niveau3.txt");
          strcpy(carte, "background-Level3.jpg");
          fondR = 58;
          fondV = 45;
          fondB = 36;
          break;
        }
        lectureInfosTerrain(infosTerrain, &terrain, niveauTexte);
        colmycraft.prochainCheckpoint = &terrain.tableCheckPoints[0];

        // Création de la map
        image = IMG_Load(carte);
        if(image == NULL) {
          fprintf(stderr, "Impossible de charger l'image %s\n", carte);
          return EXIT_FAILURE;
        }
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
          fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", carte);
          return EXIT_FAILURE;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(image);
      }
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
    if (colmycraft.vitesse > 3.0) {
      dessinJetMoteur();
    }
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
        break;
      }
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
  // shut everything down
  SDL_CloseAudio();
  SDL_FreeWAV(wav_buffer);

  glDeleteTextures(1, &textureId);
  /* Liberation des ressources associ�es �  la L */
  SDL_Quit();

  return EXIT_SUCCESS;
}
