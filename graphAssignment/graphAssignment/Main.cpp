/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: cube.c,v 1.1 2002/04/03 00:00:35 mshafae Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glut.h>
#include <signal.h>
#include <iostream>
#include "sceneModule.h"
#include "viewModule.h"
#include "inputModule.h"
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
void display( void ){
  glutSetWindow(window);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f( 1.0, 1.0, 1.0 );


  /* Set up where the projection */
  setUserView( );
  /* Draw the scene into the back buffer */

  
  //glLoadIdentity();
  GLfloat ambientColor[] = {0.2f,0.2f,0.2f,1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  GLfloat lightColor[] = {0.5f,0.5f,0.5f,1.0f};
  GLfloat lightPos[] = {0.0f, 0.0f, 5.0f,1.0f};
  glLightfv(GL_LIGHT0,GL_SPECULAR,lightColor);
  glLightfv(GL_LIGHT0,GL_POSITION,lightPos);


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

  /* Swap the front buffer with the back buffer - assumes double buffering */
  glutSwapBuffers( );
}

void idle()
{
	ang1+=delta_ang1;
	ang2+=delta_ang2;
	glutPostRedisplay( );
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

  glEnable( GL_DEPTH_TEST );
  glDisable( GL_CULL_FACE );

  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  glClearIndex( 0 );
  glClearDepth( 1 );

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  glMatrixMode( GL_MODELVIEW );
}

//##########################################
// Main function

int main( int argc, char **argv ){
//  signal( SIGHUP, cleanup );

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |
                       GLUT_DEPTH | GLUT_MULTISAMPLE );

  glutInitWindowSize( IMAGE_WIDTH,IMAGE_HEIGHT );

  /* glutInitWindowPosition(0,0); */
  window = glutCreateWindow( argv[0] );

  /* Register the appropriate callback functions with GLUT */
  glutDisplayFunc( display );
  glutKeyboardFunc( readKeyboard );
  glutMouseFunc( mouseButtHandler );
  glutMotionFunc( mouseMoveHandler );
  glutPassiveMotionFunc( mouseMoveHandler );
  glutIdleFunc( idle );

  initDisplay( );

  /* This function doesn't return - put all clean up code in
   * the cleanup function */
  glutMainLoop( );

  /* ANSI C requires main to return an int. */
  return( 0 );
}
