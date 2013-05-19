#include "LUtil.h"

bool initGL()
{
	//initialize projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);
	
	//check for error
	GLenum error = glGetError();
	if(error!=GL_NO_ERROR)
	{
		printf("Error initializing opengl! %s\n",gluErrorString(error));
		return false;
	}
	return true;
}

void update()
{
	
}

void render()
{
	//clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//render quad
	glBegin(GL_QUADS);
	
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	
	glEnd();
	
	//update screen
	glutSwapBuffers();
}
