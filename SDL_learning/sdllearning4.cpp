#include <SDL.h>
#include <stdio.h>

int main(int argn, char **argv)
{
	if(SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		fprintf(stderr, "Could not initialize SDL\n");
	}
	printf("SDL Initialized\n");
	
	SDL_Quit();
	printf("SDL Shutdown\n");
	return 0;
}
