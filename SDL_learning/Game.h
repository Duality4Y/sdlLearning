#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>

class Game
{
	public:
		Game();
		void Init();
		void HandleEvents();
		void Update();
		void Draw();
		void Clean();
	private:
		bool m_bRunning;
};
#endif
