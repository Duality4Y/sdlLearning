#include "LUtil.h"

void runMainLoop(int val);
/*
pre condition:
	initialized freeglut
post condition:
	calls the main loop functions and set itself to be called back in 1000/screen_fps milliseconds.
side effects:
	sets gluttimerfunc
*/

int main(int argc, char* args[])
{
	//initialize freeglut
	glutInit(&argc, args);
	glutInitContextVersion(2,1);
	//create double buffered window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("OpenGL");
	//do post window/context creation initialization
	if(!initGL())
	{
		printf("Unable to initialize graphics library!\n");
		return 1;
	}
	//set rendering function
	glutDisplayFunc(render);
	//set main loop
	glutTimerFunc(1000/SCREEN_FPS, runMainLoop, 0);
	//start glut main loop
	glutMainLoop();
	return 0;
}

void runMainLoop(int val)
{
	//Frame logic
	update();
	render();
	//run frame on more time
	glutTimerFunc(1000/SCREEN_FPS, runMainLoop, val);
}
