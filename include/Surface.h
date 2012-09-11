#ifndef SURFACE_H
#define SURFACE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>

using namespace std;

class Surface
{
    public:
        Surface(string file, SDL_Surface* surf);
        ~Surface();

        static SDL_Surface* Load(char* file);
        static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
        SDL_Surface* getSurface();
        string getFilename();
    private:
        static SDL_Surface* getLoaded(char* file);
        static vector<Surface*> list;
        SDL_Surface* surface;
        string filename;
};

#endif // SURFACE_H
