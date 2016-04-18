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

void dessinCarreArrondi(){
	glPushMatrix();
		glTranslatef(-0.5,0.5,0);
		dessinCercle(100,1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.5,0.5,0);
		dessinCercle(100,1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.5,-0.5,0);
		dessinCercle(100,1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.5,-0.5,0);
		dessinCercle(100,1);
	glPopMatrix();

	glPushMatrix();
		glScalef(1,2,0);
		dessinCarre(1);
	glPopMatrix();
	glPushMatrix();
		glScalef(2,1,0);
		dessinCarre(1);
	glPopMatrix();
}



void dessinJetMoteur() {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //Jet Gauche
      glPushMatrix();
        glLineWidth(5);
        glColor4f(1,1,1,0.2);
          glPushMatrix();
            glTranslatef(-0.2,-0.7,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
          glPushMatrix();
            glColor4f(1,1,1,0.2);
            glTranslatef(-0.23,-0.8,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
          glPushMatrix();
            glColor4f(1,1,1,0.2);
            glTranslatef(-0.25,-0.9,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
          glPushMatrix();
            glColor4f(1,1,1,0.2);
            glTranslatef(-0.27,-1,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
      glPopMatrix();

      //Jet Droit
      glPushMatrix();
        glLineWidth(5);
        glColor4f(1,1,1,0.2);
          glPushMatrix();
            glTranslatef(0.2,-0.7,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
          glPushMatrix();
            glColor4f(1,1,1,0.2);
            glTranslatef(0.23,-0.8,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
          glPushMatrix();
            glColor4f(1,1,1,0.2);
            glTranslatef(0.25,-0.9,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
          glPushMatrix();
            glColor4f(1,1,1,0.2);
            glTranslatef(0.27,-1,1);
            glScalef(0.3,0.3,1);
            dessinCercle(200,0);
          glPopMatrix();
      glPopMatrix();
}

void dessinHovercraft() {

    //Structure
    glPushMatrix();
      glColor3f(0.21,0.14,0.06);
      glBegin(GL_POLYGON);
        glVertex2f(0,1);
        glVertex2f(-0.5, 0.5);
        glVertex2f(-0.4, -0.7);
        glVertex2f(0.4,-0.7);
        glVertex2f(0.5,0.5);
      glEnd();
    glPopMatrix();

    //Centre du bateau
    glPushMatrix();
      glColor3f(0.36,0.22,0.08);
      glBegin(GL_POLYGON);
        glVertex2f(-0.4,0.4);
        glVertex2f(0.4,0.4);
        glVertex2f(0.26,-0.65);
        glVertex2f(-0.26,-0.65);
      glEnd();
    glPopMatrix();

    //Intérieur
    glPushMatrix();
      glColor3f(0.96,0.89,0.79);
      glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.4);
        glVertex2f(0.3,0.4);
        glVertex2f(0.2,-0.5);
        glVertex2f(-0.2, -0.5);
      glEnd();
    glPopMatrix();

    //Cabine
    glPushMatrix();
      glColor3f(0,0,0);
      glBegin(GL_POLYGON);
        glVertex2f(-0.25, -0.2);
        glVertex2f(0.25,-0.2);
        glVertex2f(0.2,-0.5);
        glVertex2f(-0.2, -0.5);
      glEnd();
    glPopMatrix();

    //Siege
    glPushMatrix();
      glColor3f(0,0,0);
      glTranslatef(0,0.1,0);
      glScalef(0.13,0.11,1);
      dessinCarreArrondi();
    glPopMatrix();

    //Tableau de bord
    glPushMatrix();
      glColor3f(0.87,0.80,0.71);
      glTranslatef(0,0.4,0);
      glScalef(0.6,0.3,1);
      dessinCercle(200,1);
    glPopMatrix();

    //Avant du bateau
    glPushMatrix();
      glColor3f(0.36,0.22,0.08);
      glBegin(GL_POLYGON);
        glVertex2f(0,1);
        glVertex2f(-0.4,0.4);
        glVertex2f(0.4,0.4);
      glEnd();
    glPopMatrix();

    //Atache devant
    glPushMatrix();
      glColor3f(0.96,0.89,0.79);
      glBegin(GL_POLYGON);
        glVertex2f(0,0.9);
        glVertex2f(-0.07,0.75);
        glVertex2f(0.07,0.75);
      glEnd();
    glPopMatrix();


    //Jet Gauche
    glPushMatrix();
      glLineWidth(5);
      glColor4f(1,1,1,0.2);
        glPushMatrix();
          glTranslatef(-0.2,-0.7,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
        glPushMatrix();
          glColor4f(1,1,1,0.2);
          glTranslatef(-0.23,-0.8,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
        glPushMatrix();
          glColor4f(1,1,1,0.2);
          glTranslatef(-0.25,-0.9,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
        glPushMatrix();
          glColor4f(1,1,1,0.2);
          glTranslatef(-0.27,-1,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
    glPopMatrix();

    //Jet Droit
    glPushMatrix();
      glLineWidth(5);
      glColor4f(1,1,1,0.2);
        glPushMatrix();
          glTranslatef(0.2,-0.7,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
        glPushMatrix();
          glColor4f(1,1,1,0.2);
          glTranslatef(0.23,-0.8,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
        glPushMatrix();
          glColor4f(1,1,1,0.2);
          glTranslatef(0.25,-0.9,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
        glPushMatrix();
          glColor4f(1,1,1,0.2);
          glTranslatef(0.27,-1,1);
          glScalef(0.3,0.3,1);
          dessinCercle(200,0);
        glPopMatrix();
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
