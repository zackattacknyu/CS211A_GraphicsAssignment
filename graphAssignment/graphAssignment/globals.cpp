#include "globals.h"

int ambient = 20;
int diffuse = 80;
int specular = 0;
int lightOn = 0;
int lightSelected = 0;
int lightX = 0;
int lightY = 0;
int lightZ = 0;
int shine = 0;
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
