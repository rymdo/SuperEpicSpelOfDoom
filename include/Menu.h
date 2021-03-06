#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/Surface.h"
#include "../include/Font.h"

using namespace std;

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        bool Draw(SDL_Surface* surface);
        bool Active();
        bool SetState();
        void next();
        void previous();
        string select();
    protected:
    private:
        SDL_Surface* renderdText;
        vector<string> menuItems;
        bool inMenu;
        int activeItem;
};

#endif // MENU_H
