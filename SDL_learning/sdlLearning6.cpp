#define NUM_DOTS 100000

#include <time.h>
#include <SDL.h>
#include <stdlib.h>


/*types*/
typedef struct
{
	int red, green;
	float vx,vy;
	float x,y;
}dot;

/*globals*/
SDL_Surface *demo_screen;
float demo_time_measure = 0.0f;
float demo_time_step = 0.0f;
dot demo_dots[NUM_DOTS];

float demo_roll()
{
	float r;
	r = (float)(rand()%RAND_MAX);
	r /= (float)(RAND_MAX-1);
	return r;
}

void demo_init()
{
	int i;
	for(i=0;i<NUM_DOTS;i++)
	{
		demo_dots[i].red = rand()%255;
		demo_dots[i].green = rand()%255;
		demo_dots[i].vx = demo_roll()*16.0f-8.0f;
		demo_dots[i].vy = demo_roll()*16.0f-8.0f;
		demo_dots[i].x = demo_roll()*320.0f;
		demo_dots[i].y = demo_roll()*240.0f;
	}
}

void demo_handle()
{
	int i;
	for(i=0;i<NUM_DOTS;i++)
	{
		demo_dots[i].x += demo_dots[i].vx*demo_time_step;
		demo_dots[i].y += demo_dots[i].vy*demo_time_step;
		
		if(demo_dots[i].x < 0.0f || demo_dots[i].x >= 320.0f)
		{
			demo_dots[i].x -= demo_dots[i].vx*demo_time_step;
			demo_dots[i].vx *= -1;
		}
		if(demo_dots[i].y < 0.0f || demo_dots[i].y >= 240.0f)
		{
			demo_dots[i].y -= demo_dots[i].vy*demo_time_step;
			demo_dots[i].vy *= -1;
		}
	}
}

void demo_draw()
{
	int i, bpp, rank, x, y;
	Uint32 *pixel;
	SDL_LockSurface(demo_screen);
	rank = demo_screen->pitch/sizeof(Uint32);
	pixel = (Uint32*)demo_screen->pixels;
	for(i=0;i<NUM_DOTS;i++)
	{
		x = (int)demo_dots[i].x;
		y = (int)demo_dots[i].y;
		pixel[x+y*rank] = SDL_MapRGBA(demo_screen->format, demo_dots[i].red, demo_dots[i].green,0,255);
	}
	SDL_UnlockSurface(demo_screen);
}

float demo_convert_time(struct timespec *ts)
{
	float accu;
	accu = (float)ts->tv_sec;
	accu *= 1000000000.0f;
	accu += (float)ts->tv_nsec;
	accu /= 1000000.0f;
	return accu;
}

/*start time*/
void demo_start_time()
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	demo_time_measure = demo_convert_time(&ts);
}

/*End time*/

void demo_end_time()
{
	struct timespec ts;
	float delta;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	delta = demo_convert_time(&ts)-demo_time_measure;
	demo_time_step = delta/(1000.0f/16.0f);
}

int main(int argn, char **argv)
{
	SDL_Event ev;
	int active;
	if(SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		fprintf(stderr, "Couldn ot initialize SDL: %s\n", SDL_GetError());
	}
	demo_screen = SDL_SetVideoMode(320,240,0,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(!demo_screen)
	{
		fprintf(stderr, "couldn not set video mode: %s\n", SDL_GetError());
	}
	demo_init();
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
		
		demo_start_time();
		
		demo_handle();
		
		SDL_FillRect(demo_screen, NULL, SDL_MapRGBA(demo_screen->format, 0, 0, 255 ,255));
		
		demo_draw();
		SDL_Flip(demo_screen);
		demo_end_time();
	}
	SDL_Quit();
	return 0;
}
