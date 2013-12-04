/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: inputModule.c,v 1.2 2002/04/03 00:36:06 mshafae Exp $
 *
 */

#include <signal.h>
#include "inputModule.h"
#include <string>
#include <iostream>
#include <sstream>
#include "globals.h" 

using namespace std;

static int motionMode;
static int startX;
static int startY;
static GLfloat angle = 20;    /* in degrees */
static GLfloat angle2 = 30;   /* in degrees */
static GLfloat xdistance = 0.0;
static GLfloat ydistance = 0.0;
static GLfloat zdistance = 50.0;
string* theToken;

static string delimiter = ",";

string* getTokens(int numArgs, string inputStr){
	string* returnToks = new string[numArgs];
	int startPos = 0;
	string token;
	int i = 0;
	while( (startPos = inputStr.find(delimiter)) != (string::npos)){
		token = inputStr.substr(0,startPos);
		returnToks[i] = token;
		i++;
		inputStr.erase(0,startPos + delimiter.length());
	}
	returnToks[i] = inputStr;
	return returnToks;
}
void readKeyboard( unsigned char key, int x, int y ){
	string inputStr;
	string delimiter = ",";
	string tokens;
	string* theTokens;
	//cout << key;
  switch( key ){
  case  0x1B: /* esc */
  case  'q':
//    kill( getpid(), SIGHUP );
    break;
  case ' ':

    break;
  case '-':
	  //remove a light
	  break;
  case '+':
	  //add a light
	  break;
  case 't':
	  //change type of light
	  break;
  case ',':

    break;
  case '.':

    break;
  case 'w':
    lightY += 1.0;
    break;
  case 'a':
    lightX -= 1.0;
    break;
  case 's':
    lightY -= 1.0;
    break;
  case 'd':
    lightX += 1.0;
    break;
  case 'i':
    lightZ -= 1.0;
    break;
  case 'o':
    lightZ += 1.0;
    break; 
  case 'f':
    ambient -= 5;
    break;
  case 'g':
    ambient += 5;
    break;
  case 'h':
    diffuse -= 5;
    break;
  case 'v':
    diffuse += 5;
    break;
  case 'b':
    specular -= 5;
    break;
  case 'n':
    specular += 5;
    break;
  case 'l':
    // int lightNum;
    // cout << "Enter the number of the light you would like to select." << endl;
    // cin >> inputStr;
    // theToken[0] = getTokens(1, inputStr);
    // istringstream(theToken) >> lightNum;

    switch(lightSelected) {
      case 0:
        cout << "Light selected: " << lightSelected << endl;
        lightSelected = GL_LIGHT0;
        cout << "Light selected after: " << lightSelected << endl;
        break;
      case 1:
        lightSelected = GL_LIGHT1;
        break;
      case 2:
        lightSelected = GL_LIGHT2;
        break;
      case 3:
        lightSelected = GL_LIGHT3;
        break;
      case 4:
        lightSelected - GL_LIGHT4;
        break;
      case 5:
        lightSelected = GL_LIGHT5;
        break;
      case 6:
        lightSelected = GL_LIGHT6;
        break;
      case 7:
        lightSelected = GL_LIGHT7;
        break;
    }

    case 'p':
      lightOn = 1;
      break;
    case 'u':
      lightOn = 0;
      break;

  case 'r':
    /* reset initial view parameters */
    angle = 20;
    angle2 = 30;
    xdistance = 0.0;
    ydistance = 0.0;
    zdistance = 50.0;
    break;
  default:
    break;
  }
  glutPostRedisplay( );
}

void readSpecialKeys( int key, int x, int y ){
  cout << key << endl;
  switch( key ){
  case GLUT_KEY_UP:

    break;
  case GLUT_KEY_DOWN:

    break;
  case GLUT_KEY_RIGHT:

    break;
  case GLUT_KEY_LEFT:

    break;
  }
  glutPostRedisplay( );
}

void mouseButtHandler(int button, int state, int x, int y)
{
  motionMode = 0;

  switch( button ){
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Rotate object */
      motionMode = 1;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    if( state == GLUT_DOWN ){
      /* Translate object */
      motionMode = 2;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Zoom */
      motionMode = 3;
      startX = x;
      startY = y;
    }
    break;
  }
  glutPostRedisplay( );
}

void mouseMoveHandler( int x, int y ){
  switch(motionMode){
  case 0:
    /* No mouse button is pressed... do nothing */
    /* return; */
    break;

  case 1:
    /* Calculate the rotations */
    angle = angle + (x - startX);
    angle2 = angle2 + (y - startY);
    startX = x;
    startY = y;
    break;

  case 2:
    xdistance = xdistance - (x - startX)/100.0;
    ydistance = ydistance - (y - startY)/100.0;
    startX = x;
    startY = y;
    break;

  case 3:
    zdistance = zdistance - (y - startY)/10.0;
    startX = x;
    startY = y;
    break;
  }

  glutPostRedisplay( );
}

void setUserView( ){
  glLoadIdentity( );
  /* gluLookAt( 0.0,0.0,distance,0.0,0.0,0.0,0.0,1.0,0.0 ); */

  glTranslatef( -xdistance, ydistance, -zdistance );
  glRotatef( angle2, 1.0, 0.0, 0.0 );
  glRotatef( angle, 0.0, 1.0, 0.0 );
}
