#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.h"

//Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
bool initGL();
/*
pre condition:
 -A valid opengl context
post condition:
 -Initializes matrices and clear color
 -Reporst to console if there was an opengl error
 -Returns fals if there was an error in initialization
Side effects:
 -Projection matrix is set to idetity matrix.
 -Modelview matrix is set to idetity matrix.
 -matrix mod is set to modelview
 -clear color is set to black
*/
void update();
/*
pre condition:
-none.
post condition:
-does per frame logic.
side effects:
-none.
*/
void render();
/*
Pre condition:
 -A valid openg context
 -active modelview matrix
post Condition:
 -Renders the scene
Side effects:
 -clear the color buffer
 -swaps the front/back buffer
 */
 
#endif
