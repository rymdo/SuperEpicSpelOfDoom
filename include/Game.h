#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <fstream>

#include "../include/Surface.h"
#include "../include/Event.h"

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

    protected:
    private:
        bool            run;
        SDL_Surface*    surface;

};



#endif // GAME_H
