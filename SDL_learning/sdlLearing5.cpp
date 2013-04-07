#include <SDL.h>

SDL_Surface *demo_screen;

int main(int argn, char **argv)
{
	SDL_Event ev;
	int active;
	if(SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		fprintf(stderr, "could not initialize sdl video screen: %s \n", SDL_GetError());
	}
	demo_screen = SDL_SetVideoMode(320, 240, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(!demo_screen)
	{
		fprintf(stderr, "could not set screen %s\n",SDL_GetError());
	}
	active = 1;
	while(active)
	{
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_QUIT)
			{
				active = 0;
			}
		}
	}
	SDL_Quit();
	return 0;
}
