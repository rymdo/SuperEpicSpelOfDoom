#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <fstream>

#include "../include/Surface.h"
#include "../include/Event.h"
#include "../include/Sprite.h"

#include "../include/Camera.h"
#include "../include/Tile.h"

#include "../include/Object.h"


using namespace std;

class Game : public Event
{
    public:
        Game();
        ~Game();
        void Execute();
        bool Init();
        bool Event(SDL_Event* event);
        void Loop();
        void Render();
        void CleanUp();
        void Exit();
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    protected:
    private:
        bool            run;
        SDL_Surface*    surface;
        //Sprite*         player;
        Object*         player;
        Uint32          gameTime;
        Uint32          timeElapsed;

};



#endif // GAME_H
