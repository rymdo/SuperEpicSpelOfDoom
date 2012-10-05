#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <fstream>

#include "../include/Surface.h"
#include "../include/Event.h"
#include "../include/Sprite.h"
#include "../include/Menu.h"
#include "../include/Camera.h"
#include "../include/Tile.h"
#include "../include/Popup.h"
#include "../include/Object.h"
#include "../include/Player.h"
#include "../include/Font.h"


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

        bool NewGame();
        bool SaveGame();
        bool LoadGame();
        void ExitGame();

        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    protected:
    private:
        bool            run;
        SDL_Surface*    surface;
        Player*         player;
        Uint32          runTime;
        Uint32          gameTime;
        Uint32          timeElapsed;
        Menu*           mainMenu;
        Popup*          popUp;

};

#endif // GAME_H
