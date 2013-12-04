#include "globals.h"

int ambient[8];
int diffuse[8];
int specular[8];
int lightOn[8];
int lightSelected = 0;
int lightX[8];
int lightY[8];
int lightZ[8];
int shine[8];
int colorIndex = 0;

float colors[8][4] = {
    {1.0,1.0,1.0,1.0}, //white
    {1.0,0.0,0.0,1.0}, //red
    {0.0,1.0,0.0,1.0}, //green
    {0.0,0.0,1.0,1.0}, //blue
    {1.0,1.0,0.0,1.0}, //yellow
    {0.0,1.0,1.0,1.0}, //cyan
    {1.0,0.0,1.0,1.0}, //magenta
    {0.2,0.5,0.8,1.0} //Don't Know
};
