/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: viewModule.h,v 1.1 2002/04/03 00:00:51 mshafae Exp $
 *
 */

#ifndef  __STEREOMODULE_H
#define  __STEREOMODULE_H

#define IMAGE_WIDTH  512
#define IMAGE_HEIGHT 512

typedef struct{
        float fieldOfView;
        float aspect;
        float nearPlane;
        float farPlane;
}perspectiveData;

static float position_cube_1[3] = {0.0, 0.0, 0.0}; 
static float position_cube_2[3] = {0.0, 0.0, 15.0}; 
static float position_cube_3[3] = {3.0, 0.0, 0.0}; 
static float scale_cube_1[3] = {2.0, 2.0, 2.0}; 
static float scale_cube_2[3] = {1.0, 1.0, 1.0}; 
static float scale_cube_3[3] = {0.5, 0.5, 0.5}; 
static float ang1=0;
static float delta_ang1=0.01;
static float ang2=0;
static float delta_ang2=0.045;
#endif
