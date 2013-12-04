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
  glLoadIdentity();
}

void initDisplay( ){
  /* Perspective projection parameters */
  pD.fieldOfView = 45.0;
  pD.aspect      = (float)IMAGE_WIDTH/IMAGE_HEIGHT;
  pD.nearPlane   = 0.1;
  pD.farPlane    = 200.0;

  /* setup context */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluPerspective( pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void drawGeometry() {
  glTranslatef(position_cube_1[0],position_cube_1[1],position_cube_1[2]);
  glRotatef(ang1,0,1,0);
  glPushMatrix();
  glScalef(scale_cube_1[0],scale_cube_1[1],scale_cube_1[2]);
  glColor3f(1.0,0.0,0.0);
  drawScene( ); //cube one
  glPopMatrix();

  glTranslatef(-position_cube_1[0],-position_cube_1[1],-position_cube_1[2]);

  glPushMatrix();
  glTranslatef(position_cube_2[0],position_cube_2[1],position_cube_2[2]);

  
  glPushMatrix();
  glRotatef(ang2,0,1,0);
  glTranslatef(position_cube_3[0],position_cube_3[1],position_cube_3[2]);
  glScalef(scale_cube_3[0],scale_cube_3[1],scale_cube_3[2]);
  glColor3f(0.0,1.0,0.0);
  drawScene( ); //cube three
  glPopMatrix();

  glScalef(scale_cube_2[0],scale_cube_2[1],scale_cube_2[2]);
  glColor3f(0.0,0.0,1.0);
  drawScene( ); //cube two
  glPopMatrix();
}


void drawLight() {
  if (lightOn == true) {
    GLfloat Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    GLfloat Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    GLfloat Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    GLfloat Position[]  = {lightX,lightY,lightZ,1.0};

    /*  Draw light position as sphere (still no lighting here) */
    glColor3f(1.0, 1.0, 1.0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(Position[0],Position[1],Position[2]);
    glutSolidSphere(0.5,100.0,100.0);
    glPopMatrix();


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
    glEnable(lightSelected);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colors[0]);
    glMaterialfv(GL_FRONT,GL_SPECULAR,colors[colorIndex]);
    GLfloat shineV[] = {shine};
    glMaterialfv(GL_FRONT,GL_SHININESS, shineV);
  }
  else
    glDisable(lightSelected);
}

void drawSettings(void) {
  glColor3f(1.0, 1.0, 1.0);
  if (lightOn) {
    printAt(5, 40, "Ambient:%d, Diffuse:%d, Specular:%d, Shine:%d", ambient, diffuse, specular, shine);
    printAt(5, 20, "Light %d at position: x:%d, y:%d, z:%d", lightSelected - 16384, lightX, lightY, lightZ);
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
  drawLight();

  // Draw the scene objects
  drawGeometry();
  glFlush();

  /* Swap the front buffer with the back buffer - assumes double buffering */
  glutSwapBuffers( );
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
  window = glutCreateWindow( "Fuck this shit" );

  initDisplay( );

  /* Register the appropriate callback functions with GLUT */
  glutDisplayFunc( display );
  glutKeyboardFunc( readKeyboard );
  glutMouseFunc( mouseButtHandler );
  glutMotionFunc( mouseMoveHandler );
  glutPassiveMotionFunc( mouseMoveHandler );
  glutIdleFunc( idle );

  /* This function doesn't return - put all clean up code in
   * the cleanup function */
  glutMainLoop( );

  /* ANSI C requires main to return an int. */
  return( 0 );
}
