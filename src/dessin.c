#include "../include/dessin.h"

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

