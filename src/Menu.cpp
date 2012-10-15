#include "../include/Menu.h"

/**
Constructor for Menu, stores default values into the menuItems vector
*/
Menu::Menu()
{
    inMenu = true;
    activeItem=0;

    menuItems.push_back("New Game");
    menuItems.push_back("Load");
    menuItems.push_back("Save");
    menuItems.push_back("Exit");
}

/**
Default destructor
*/
Menu::~Menu()
{
    //dtor
}

/**
True if menu is open, false if it's closed
@return state of menu (open/closed)
*/
bool Menu::Active()
{
    return inMenu;
}

/**
Swithes state of the menu (open/cloed), if a new game has been initialized the "new game"-option is replaced with "resume"
@return new state (open/closed)
*/
bool Menu::SetState()
{
    menuItems[0] = "Resume";
    inMenu =!inMenu;
    return inMenu;
}

/**
Draws the menu by calling Surface::DrawStatic()
@param surface destination surface
@return true/false whether the inner function call was a success/failure.
*/
bool Menu::Draw(SDL_Surface* surface)
{
    SDL_FillRect(surface, NULL, 0x000000);

    SDL_Color WHITE = {255,255,255};
    SDL_Color RED = {255,0,0};
    SDL_Color color;
    int x = 320;
    int y = 80;

    for(int i=0; i<menuItems.size(); i++)
    {
        color = WHITE;
        if(activeItem==i)
        {
            color = RED;
        }

        renderdText = TTF_RenderText_Solid(Font::BITLIM, menuItems[i].c_str(), color);

        if(!Surface::DrawStatic(surface, renderdText, x-renderdText->w/2, y))
            return false;

        y+=80;
    }
    return true;
}

/**
Browses forth one step in the menu choice list and jumps to the geginning of the list if out of bounds
*/
void Menu::next()
{
    if(activeItem>=menuItems.size()-1)
    {
        activeItem=0;
        return;
    }
    activeItem++;
}

/**
Browses back one step in the menu choice list and jumps to the end of the list if out of bounds
*/
void Menu::previous()
{
    if(activeItem<=0)
    {
        activeItem=menuItems.size()-1;
        return;
    }
    activeItem--;
}

/**
Selects the current menu choice
@return the string name of selected item
*/
string Menu::select()
{
    if (menuItems[activeItem] == "Resume")
    {
        inMenu=false;
        return "";
    }

    return menuItems[activeItem];
}
