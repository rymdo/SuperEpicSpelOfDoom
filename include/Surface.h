#ifndef SURFACE_H
#define SURFACE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "../include/Camera.h"

using namespace std;

class Surface
{
    public:
        Surface(string file, SDL_Surface* surf);
        ~Surface();

        SDL_Surface* getSurface();
        string getFilename();

        static SDL_Surface* Load(char* file);
        static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
        static bool Draw(SDL_Surface* dest, SDL_Surface* src, int dest_x, int dest_y, int src_x, int src_y, int src_w, int src_h);
        static void setCamera(Camera* cam);
    private:
        static SDL_Surface* GetLoaded(char* file);

        SDL_Surface* surface;
        string filename;

        static Camera* cam;
        static vector<Surface*> list; //Lista med Surfaces som håller koll på vad som laddadts in
};

#endif // SURFACE_H
