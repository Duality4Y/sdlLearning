#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	printf("Initializing SDL.\n");
	if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)==-1))
	{
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}
	printf("SDL initialized.\n");
	printf("Quitting SDL.\n");
	SDL_Quit();
	printf("Quitting...\n");
	exit(0);
}
