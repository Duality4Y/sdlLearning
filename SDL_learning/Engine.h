#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

class CEngine
{
	private:
		//last tick
		long m_lLastTick;
		//window width
		int m_iWidth;
		//window height
		int m_iHeight;
		//has quit been called?
		bool m_bQuit;
		//title for window
		const char* m_czTitle;
		//screen surface
		SDL_Surface* m_pScreen;
		//is window minimized?
		bool m_bMinimized;
		//variables to calculate the frame rate
		//tick counter
		int m_iFPSTickCounter;
		//frame rate counter
		int m_iFPSCounter;
		//store the last calculated frame rate.
		int m_iCurrentFPS;
	protected:
		void DoThink();
		void DoRender();
		void SetSize(const int& iWidth, const int& iHeight);
		void HandleInput();
	public:
		CEngine();
		virtual ~CEngine();
		void Init();
		void Start();
		//overload for data that should be initialized.
		virtual void AdditionalInit(){}
		//overlaod for all the game calculation and updateing.
		virtual void Think(const int& iElapsedTime){}
		//over load all the game rendering
		virtual void Render(SDL_Surface* pDestSurface){}
		//overload all the data that should be cleaned up.
		virtual void End(){}
		//overload window is active again.
		virtual void WindowActive(){}
		//overload window is inactive.
		virtual void WindowInactive(){}
		//overload keyboard key has released.
		virtual void KeyUp(const int& iKeyEnum){}
		//overload key been pressed.
		virtual void KeyDown(const int& iKeyEnum){}
		//mouse overload mouse been moved
		virtual void MouseMoved(const int& iButton,
								const int& iX,
								const int& iY,
								const int& iRelX,
								const int& iRelY){}
		//overload for mouse button up.
		virtual void MouseButtonUp(const int& iButton,
									const int& iX,
									const int& iY,
									const int& iRelX,
									const int& iRelY){}
		//overload for mouse button down.
		virtual void MouseButtonDown(const int& iButton,
									const int& iX,
									const int& iY,
									const int& iRelX,
									const int& iRelY){}
		//set title
		void SetTitle(const char* czTitle);
		//get current title
		const char* GetTitle();
		//get surface/screen
		SDL_Surface* GetSurface();
		//get frame rate
		int GetFPS();
};
#endif
