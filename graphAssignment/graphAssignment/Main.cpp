/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: cube.c,v 1.1 2002/04/03 00:00:35 mshafae Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <signal.h>
#include <iostream>
#include "sceneModule.h"
#include "viewModule.h"
#include "inputModule.h"
#include "globals.h"
#include "print.h" 
#include "my_gl_library.h"
using namespace std;

int window;
int updateFlag;

perspectiveData pD;

void cleanup( int sig ){
  // insert cleanup code here (i.e. deleting structures or so)
  exit( 0 );
}


//##########################################3
// OpenGL Display function
#ifdef __cplusplus
extern "C"
#endif

void idle()
{
	ang1+=delta_ang1;
	ang2+=delta_ang2;
	glutPostRedisplay( );
}

void displayStart(void) {
  glClearColor(0.0,0.0,0.0,1.0);
  glClearIndex( 0 );
  glClearDepth( 1 );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  myGlLibrary ? my_GL_LoadIdentity() : glLoadIdentity();
}

void initDisplay( ){
  /* Perspective projection parameters */
  pD.fieldOfView = 45.0;
  pD.aspect      = (float)IMAGE_WIDTH/IMAGE_HEIGHT;
  pD.nearPlane   = 0.1;
  pD.farPlane    = 200.0;

  /* setup context */
  myGlLibrary ? my_GL_MatrixMode(GL_PROJECTION) : glMatrixMode( GL_PROJECTION );
  myGlLibrary ? my_GL_LoadIdentity() : glLoadIdentity();
  myGlLibrary ? my_GL_Perspective(pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane) : gluPerspective( pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane );
  myGlLibrary ? my_GL_MatrixMode(GL_MODELVIEW) : glMatrixMode( GL_MODELVIEW );
  myGlLibrary ? my_GL_LoadIdentity() : glLoadIdentity();
}

void drawGeometry() {
  myGlLibrary ? my_GL_translatef(position_cube_1[0],position_cube_1[1],position_cube_1[2]) : glTranslatef(position_cube_1[0],position_cube_1[1],position_cube_1[2]);
  myGlLibrary ? my_GL_rotatef(ang1,0,1,0) : glRotatef(ang1,0,1,0);
  myGlLibrary ? my_GL_pushMatrix() : glPushMatrix();
  myGlLibrary ? my_GL_scalef(scale_cube_1[0],scale_cube_1[1],scale_cube_1[2]) : glScalef(scale_cube_1[0],scale_cube_1[1],scale_cube_1[2]);
  glColor3f(1.0,0.0,0.0);
  drawScene( ); //cube one


  myGlLibrary ? my_GL_popMatrix() : glPopMatrix();
  myGlLibrary ? my_GL_translatef(-position_cube_1[0],-position_cube_1[1],-position_cube_1[2]) : glTranslatef(-position_cube_1[0],-position_cube_1[1],-position_cube_1[2]);
  myGlLibrary ? my_GL_pushMatrix() : glPushMatrix();
  myGlLibrary ? my_GL_translatef(position_cube_2[0],position_cube_2[1],position_cube_2[2]) : glTranslatef(position_cube_2[0],position_cube_2[1],position_cube_2[2]);

  
  myGlLibrary ? my_GL_pushMatrix() : glPushMatrix();
  myGlLibrary ? my_GL_rotatef(ang2,0,1,0) : glRotatef(ang2,0,1,0);
  myGlLibrary ? my_GL_translatef(position_cube_3[0],position_cube_3[1],position_cube_3[2]) : glTranslatef(position_cube_3[0],position_cube_3[1],position_cube_3[2]);
  myGlLibrary ? my_GL_scalef(scale_cube_3[0],scale_cube_3[1],scale_cube_3[2]) : glScalef(scale_cube_3[0],scale_cube_3[1],scale_cube_3[2]);
  glColor3f(0.0,1.0,0.0);
  drawScene( ); //cube three

  myGlLibrary ? my_GL_popMatrix() : glPopMatrix();

  myGlLibrary ? my_GL_scalef(scale_cube_2[0],scale_cube_2[1],scale_cube_2[2]) : glScalef(scale_cube_2[0],scale_cube_2[1],scale_cube_2[2]);
  glColor3f(0.0,0.0,1.0);
  drawScene( ); //cube two
  myGlLibrary ? my_GL_popMatrix() : glPopMatrix();
}

void setSingleLight(int curLightNum, int curLight) {

  if (lightOn[curLightNum] == true) {
    GLfloat Ambient[]   = {0.01*ambient[curLightNum] ,0.01*ambient[curLightNum] ,0.01*ambient[curLightNum] ,1.0};
    GLfloat Diffuse[]   = {0.01*diffuse[curLightNum] ,0.01*diffuse[curLightNum] ,0.01*diffuse[curLightNum] ,1.0};
    GLfloat Specular[]  = {0.01*specular[curLightNum],0.01*specular[curLightNum],0.01*specular[curLightNum],1.0};
    GLfloat Position[]  = {lightX[curLightNum],lightY[curLightNum],lightZ[curLightNum],1.0};

    /*  Draw light position as sphere (still no lighting here) */
    glColor3f(1.0, 1.0, 1.0);
    glDisable(GL_LIGHTING);
    myGlLibrary ? my_GL_pushMatrix() : glPushMatrix();
    myGlLibrary ? my_GL_translatef(Position[0],Position[1],Position[2]) : glTranslatef(Position[0],Position[1],Position[2]);
    glutSolidSphere(0.5,100.0,100.0);
    myGlLibrary ? my_GL_popMatrix() : glPopMatrix();


    /*  Set ambient, diffuse, specular components and position of light 0 */
    /*
      Light uses the Phong model
      Once light is enabled, colors assigned by glColor* isn't used
      Ambient is light that's been scattered by environment that its direction is impossible to determine
      Diffuse is is light that comes from one direction, so it's brighter if it comes squarely on surface rather than glances off
      Specular is light that comes from a particular direction and bounces off in preferred direction
      Position is the position of our light. In this case it is the same as the sphere.
     */
    glLightfv(lightSelected,GL_AMBIENT, Ambient);
    glLightfv(lightSelected,GL_DIFFUSE, Diffuse);
    glLightfv(lightSelected,GL_POSITION,Position);
    glLightfv(lightSelected,GL_SPECULAR,Specular);
      /*  Use glColorMaterial when you need to change a single material parameter for most vertices
    in your scene */
      /*  glColorMaterial sets ambient and diffuse color materials */
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      /*  Now glColor* changes ambient and diffuse reflection */
      /*  Other examples */
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING); 
    glEnable(curLight);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colors[0]);
    glMaterialfv(GL_FRONT,GL_SPECULAR,colors[colorIndex]);
    GLfloat shineV[] = {shine[curLightNum]};
    glMaterialfv(GL_FRONT,GL_SHININESS, shineV);
  }
  else
    glDisable(curLight);
}

void drawLights() {
  int curLight = 0;
  for (int i = 0; i < 8; i++) {
    switch (i) {
      case 0:
        curLight = GL_LIGHT0;
        break;
      case 1:
        curLight = GL_LIGHT1;
        break;
      case 2:
        curLight = GL_LIGHT2;
        break;
      case 3:
        curLight = GL_LIGHT3;
        break;
      case 4:
        curLight = GL_LIGHT4;
        break;
      case 5:
        curLight = GL_LIGHT5;
        break;
      case 6:
        curLight = GL_LIGHT6;
        break;
      case 7:
        curLight = GL_LIGHT7;
        break;
    }
    setSingleLight(i, curLight);
  }
}

void drawSettings(void) {
  int lS = lightSelected - 16384;
  glColor3f(1.0, 1.0, 1.0);
  printAt(265, 20, "|  My GL Library = %d", myGlLibrary);
  if (lightOn[lS]) {
    printAt(5, 40, "Ambient:%d, Diffuse:%d, Specular:%d, Shine:%d", ambient[lS], diffuse[lS], specular[lS], shine[lS]);
    printAt(5, 20, "Light %d at position: x:%d, y:%d, z:%d", lS, lightX[lS], lightY[lS], lightZ[lS]);
  }
}

void display( void ){
  displayStart();
  //glutSetWindow(window);

  /* Set up where the projection */
  setUserView( );
  /* Draw the scene into the back buffer */

  // Display the current settings
  drawSettings();

  // Bring the lights into the scene
  drawLights();

  // Draw the scene objects
  drawGeometry();
  glFlush();

  /* Swap the front buffer with the back buffer - assumes double buffering */
  glutSwapBuffers( );
}

void specialKeys(int key, int x, int y)
{
    int ls = lightSelected - 16384;
    switch (key) {
      case 101:
        lightY[ls] += 1.0;
        break;
      case 100:
        lightX[ls] -= 1.0;
        break;
      case 103:
        lightY[ls] -= 1.0;
        break;
      case 102:
        lightX[ls] += 1.0;
        break;
    }
  }

void initVariables(void) {
  for (int i = 0; i < 8; i++) {
    ambient[i] = 20;
    diffuse[i] = 80;
    specular[i] = 0;
    lightOn[i] = 0;
    lightX[i] = 0;
    lightY[i] = 0;
    lightZ[i] = 0;
    shine[i] = 0;
  }
}

//##########################################
// Main function

int main( int argc, char **argv ){
//  signal( SIGHUP, cleanup );

  lightSelected = GL_LIGHT0;
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |
                       GLUT_DEPTH | GLUT_MULTISAMPLE );

  glutInitWindowSize( IMAGE_WIDTH,IMAGE_HEIGHT );

  /* glutInitWindowPosition(0,0); */
  window = glutCreateWindow( "Xin | DeStefano | Malby - Graphics Assignment" );

  initVariables( );

  initDisplay( );

  /* Register the appropriate callback functions with GLUT */
  glutDisplayFunc( display );
  glutKeyboardFunc( readKeyboard );
  glutMouseFunc( mouseButtHandler );
  glutMotionFunc( mouseMoveHandler );
  glutPassiveMotionFunc( mouseMoveHandler );
  glutIdleFunc( idle );
  glutSpecialFunc( specialKeys );

  /* This function doesn't return - put all clean up code in
   * the cleanup function */
  glutMainLoop( );

  /* ANSI C requires main to return an int. */
  return( 0 );
}
