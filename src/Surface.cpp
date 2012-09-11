#include "../include/Surface.h"

using namespace std;

Surface::Surface(string file, SDL_Surface* surf)
{
    filename = file;
    surface = surf;

    list.push_back(this);
}

Surface::~Surface()
{
    //dtor
}

SDL_Surface* Surface::Load(char* file)
{
    SDL_Surface* temp   = NULL;
    SDL_Surface* ret    = NULL;

    if((temp = IMG_Load(file))==NULL)
    {
        return NULL;
    }

    ret = SDL_DisplayFormatAlpha(temp);
    SDL_FreeSurface(temp);

    new Surface(string(file), ret);

    return ret;
}

bool Surface::Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
    if(dest == NULL || src == NULL)
    {
        return false;
    }

    SDL_Rect destR;

    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(src, NULL, dest, &destR);

    return true;
}
