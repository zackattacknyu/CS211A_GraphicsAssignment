#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

void printv(va_list args, const char* format);
void print(const char* format, ...);
void printAt(int x, int y, const char* format, ...);
