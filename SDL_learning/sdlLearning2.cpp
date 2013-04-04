#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

class CEvent {
    public:
        CEvent();
 
        virtual ~CEvent();
 
        virtual void OnEvent(SDL_Event* Event);
 
        virtual void OnInputFocus();
 
        virtual void OnInputBlur();
 
        virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
 
        virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
 
        virtual void OnMouseFocus();
 
        virtual void OnMouseBlur();
 
        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
 
        virtual void OnMouseWheel(bool Up, bool Down);    //Not implemented
 
        virtual void OnLButtonDown(int mX, int mY);
 
        virtual void OnLButtonUp(int mX, int mY);
 
        virtual void OnRButtonDown(int mX, int mY);
 
        virtual void OnRButtonUp(int mX, int mY);
 
        virtual void OnMButtonDown(int mX, int mY);
 
        virtual void OnMButtonUp(int mX, int mY);
 
        virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
 
        virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
 
        virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
 
        virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
 
        virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
 
        virtual void OnMinimize();
 
        virtual void OnRestore();
 
        virtual void OnResize(int w,int h);
 
        virtual void OnExpose();
 
        virtual void OnExit();
 
        virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};
class CApp: public CEvent
{
	private:
		bool Running;
		SDL_Surface* Surf_Display;
		SDL_Surface* Surf_Test;
		
	public:
		CApp();
		int OnExecute();
	public:
		bool OnInit();
		void OnEvent(SDL_Event* Event);
		void OnExit();
		void OnLoop();
		void OnRender();
		void OnCleanup();
};

class CSurface
{
	public:
		CSurface();
	public:
		static SDL_Surface* OnLoad(const char* File);
		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);
		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h);
};

CApp::CApp()
{
	Surf_Display = NULL;
	Surf_Test = NULL;
	Running = true;
}

bool CApp::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		fprintf(stderr, "failed to initialize\n");
		return false;
	}
	if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
	{
		fprintf(stderr, "failed to create screen\n");
		return false;
	}
	if((Surf_Test = CSurface::OnLoad("apple-red.bmp")) == NULL)
	{
		fprintf(stderr, "failed to load image\n");
		return false;
	}
	return true;
}

void CApp::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CApp::OnExit()
{
	Running = false;
}

void CApp::OnLoop()
{
	return;
}

void CApp::OnRender()
{
	CSurface::OnDraw(Surf_Display, Surf_Test, 0,0);
	CSurface::OnDraw(Surf_Display, Surf_Test, 100,100, 0,0, 30,30);
	
	SDL_Flip(Surf_Display);
}

void CApp::OnCleanup()
{
	SDL_FreeSurface(Surf_Test);
	SDL_FreeSurface(Surf_Display);
	SDL_Quit();
}

int CApp::OnExecute()
{
	if(OnInit() == false)
	{
		return -1;
	}
	
	SDL_Event Event;
	while(Running)
	{
		while(SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
		OnLoop();
		OnRender();
	}
	OnCleanup();
	return 0;
}

CSurface::CSurface(){}

SDL_Surface* CSurface::OnLoad(const char* File)
{
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;
	if((Surf_Temp = SDL_LoadBMP(File)) == NULL)
	{
		return NULL;
	}
	
	Surf_Return = SDL_DisplayFormat(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);
	
	return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y)
{
	if(Surf_Dest == NULL || Surf_Src == NULL)
	{
		return false;
	}
	
	SDL_Rect DestR;
	
	DestR.x = x;
	DestR.y = y;
	
	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);
	return true;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h)
{
	if(Surf_Dest == NULL || Surf_Src == NULL)
	{
		return false;
	}
	SDL_Rect DestR;
	DestR.x = x;
	DestR.y = y;
	
	SDL_Rect SrcR;
	
	SrcR.x = x2;
	SrcR.y = y2;
	SrcR.w = w;
	SrcR.h = h;
	
	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);
	return true;
}

CEvent::CEvent() {
}
 
CEvent::~CEvent() {
    //Do nothing
}
 
void CEvent::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_ACTIVEEVENT: {
            switch(Event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( Event->active.gain )    OnMouseFocus();
                    else                OnMouseBlur();
 
                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( Event->active.gain )    OnInputFocus();
                    else                OnInputBlur();
 
                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( Event->active.gain )    OnRestore();
                    else                OnMinimize();
 
                    break;
                }
            }
            break;
        }
 
        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }
 
        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }
 
        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
 
        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }
 
        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }
 
        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        case SDL_QUIT: {
            OnExit();
            break;
        }
 
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }
 
        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }
 
        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }
 
        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}
 
void CEvent::OnInputFocus() {
    //Pure virtual, do nothing
}
 
void CEvent::OnInputBlur() {
    //Pure virtual, do nothing
}
 
void CEvent::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    //Pure virtual, do nothing
}
 
void CEvent::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseFocus() {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseBlur() {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseWheel(bool Up, bool Down) {
    //Pure virtual, do nothing
}
 
void CEvent::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyButtonDown(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyButtonUp(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMinimize() {
    //Pure virtual, do nothing
}
 
void CEvent::OnRestore() {
    //Pure virtual, do nothing
}
 
void CEvent::OnResize(int w,int h) {
    //Pure virtual, do nothing
}
 
void CEvent::OnExpose() {
    //Pure virtual, do nothing
}
 
void CEvent::OnExit() {
    //Pure virtual, do nothing
}
 
void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {
    //Pure virtual, do nothing
}

int main(int argc, char* argv[])
{
	CApp theApp;
	return theApp.OnExecute();
}
