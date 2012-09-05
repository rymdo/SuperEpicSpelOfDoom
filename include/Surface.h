#ifndef SURFACE_H
#define SURFACE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Surface
{
    public:
        Surface();
        ~Surface();

        static SDL_Surface* Load(char* file);
        static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);

    protected:
    private:
};

#endif // SURFACE_H
