#include "Engine.h"

CEngine::CEngine()
{
	m_lLastTick = 0;
	m_iWidth = 800;
	m_iHeight = 600;
	m_czTitle = 0;
	
	m_pScreen = 0;
	
	m_iFPSTickCounter = 0;
	m_iFPSCounter = 0;
	m_iCurrentFPS = 0;
	
	m_bMinimized = false;
}

CEngine::~CEngine()
{
	SDL_Quit();
}

void CEngine::SetSize(const int& iWidth, const int& iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_pScreen = SDL_SetVideoMode(iWidth, iHeight, 0, SDL_SWSURFACE);
}

void CEngine::Init()
{
	atexit(SDL_Quit);
	if(SDL_Init(SDL_INIT_VIDEO < 0))
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	SetSize(m_iWidth, m_iHeight);
	if(m_pScreen == NULL)
	{
		fprintf(stderr, "unable to set video: %s\n", SDL_GetError());
		exit(1);
	}
	AdditionalInit();
}

void CEngine::Start()
{
	m_lLastTick = SDL_GetTicks();
	m_bQuit = false;
	
	while(!m_bQuit)
	{
		HandleInput();
		if(m_bMinimized)
		{
		}
		else
		{
			//do some thinking
			DoThink();
			//render stuff
			DoRender();
		}
	}
	End();
}

void CEngine::HandleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					m_bQuit = true;
					break;
				}
				KeyDown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				KeyUp(event.key.keysym.sym);
				break;
			case SDL_QUIT:
				m_bQuit = true;
				break;
			case SDL_MOUSEMOTION:
				MouseMoved(event.button.button, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				break;
			case SDL_MOUSEBUTTONUP:
				MouseButtonUp(event.button.button, event.motion.x, event.motion.y, event.motion.xrel,event.motion.yrel);
				break;
			case SDL_ACTIVEEVENT:
				if(event.active.state & SDL_APPACTIVE)
				{
					if(event.active.gain)
					{
						m_bMinimized = false;
						WindowActive();
					}
					else
					{
						m_bMinimized = true;
						WindowInactive();
					}
				}
				break;
		}
	}
}

//handles the updating routines.
void CEngine::DoThink()
{
	long iElapsedTicks = SDL_GetTicks() - m_lLastTick;
	m_lLastTick = SDL_GetTicks();
	Think(iElapsedTicks);
	m_iFPSTickCounter += iElapsedTicks;
}
//handles the rendering and fps calcualtions.
void CEngine::DoRender()
{
	++m_iFPSCounter;
	if(m_iFPSCounter >= 1000)
	{
		m_iCurrentFPS = m_iFPSCounter;
		m_iFPSCounter = 0;
		m_iFPSTickCounter = 0;
	}
	SDL_FillRect(m_pScreen, 0, SDL_MapRGB(m_pScreen->format, 0,0,0));
	//lock suface if needed
	if(SDL_MUSTLOCK(m_pScreen))
	{
		if(SDL_LockSurface(m_pScreen)<0)
		{
			return;
		}
	}
	Render(GetSurface());
	//unlock if needed
	if(SDL_MUSTLOCK(m_pScreen))
	{
		SDL_UnlockSurface(m_pScreen);
	}
	//tell sdl to update the while gScreen
	SDL_Flip(m_pScreen);
}

//set title of the window.
void CEngine::SetTitle(const char* czTitle)
{
	m_czTitle = czTitle;
	SDL_WM_SetCaption(czTitle, 0);
}

//retrieve the title of the application window.
const char* CEngine::GetTitle()
{
	return m_czTitle;
}
//retrieve the main surface
SDL_Surface* CEngine::GetSurface()
{
	return m_pScreen;
}
//get current FPS
int CEngine::GetFPS()
{
	return m_iCurrentFPS;
}
