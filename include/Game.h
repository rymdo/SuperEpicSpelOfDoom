#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>

class Game
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

    protected:
    private:
        bool            run;
        SDL_Surface*    surface;
        SDL_Surface*    surface_test;

};



#endif // GAME_H
