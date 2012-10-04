#include "../include/Menu.h"

Menu::Menu()
{
    inMenu = true;
    activeItem=0;

    menuItems.push_back("New Game");
    menuItems.push_back("Load");
    menuItems.push_back("Save");
    menuItems.push_back("Exit");
}

Menu::~Menu()
{
    //dtor
}

bool Menu::Active()
{
    return inMenu;
}

bool Menu::SetState()
{
    menuItems[0] = "Resume";
    inMenu =!inMenu;
    return inMenu;
}

bool Menu::Draw(SDL_Surface* surface, TTF_Font* arial_test)
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

        renderdText = TTF_RenderText_Solid(arial_test, menuItems[i].c_str(), color);

        Surface::DrawStatic(surface, renderdText, x-renderdText->w/2, y);

        y+=80;
    }
}

void Menu::UpdateMenu()
{

}

void Menu::next()
{
    if(activeItem>=menuItems.size()-1)
    {
        activeItem=0;
        return;
    }
    activeItem++;
}

void Menu::previous()
{
    if(activeItem<=0)
    {
        activeItem=menuItems.size()-1;
        return;
    }
    activeItem--;
}

string Menu::select()
{
    if (menuItems[activeItem] == "Resume")
    {
        inMenu=false;
        return "";
    }

    return menuItems[activeItem];
}
