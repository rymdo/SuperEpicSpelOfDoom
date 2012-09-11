#include "../include/Surface.h"

using namespace std;

Surface::Surface(string file, SDL_Surface* surf)
{
    filename = file; //string
    surface = surf; //SDL_Surface*

    list.push_back(this);
}

Surface::~Surface()
{
    //dtor
}

SDL_Surface* Surface::Load(char* file)
{
    //KOLLA OM FILNAMNET FINNS I LISTAN list OCH RETURNERA DEN POINTERN
    SDL_Surface* ret    = NULL;
    //ret = getLoaded(file); //<-- getLoaded returnerar SDL_Surface*

    //if (ret != NULL)
    //    return ret;

    SDL_Surface* temp   = NULL;

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
