#ifndef POPUP_H
#define POPUP_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../include/Surface.h"
#include "../include/Font.h"
#include <vector>


using namespace std;


class Popup
{
    public:
        Popup(string inMessage, Uint32 dur);
        ~Popup();
        bool Draw(SDL_Surface* surface, int x, int y, Uint32 now);
        static void DrawAll(SDL_Surface* surface, Uint32 now);
    protected:
    private:
        static vector<Popup*> messages;
        string message;
        Uint32 makeTime;
        SDL_Surface* renderdText;
};

#endif // POPUP_H
