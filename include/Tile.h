#ifndef TILE_H
#define TILE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include "../include/sprite.h"

using namespace std;

class Tile : Sprite
{
    public:
        //Tile();
        Tile(float X, float Y);
        virtual ~Tile();
        static bool loadAll();
        //void read(ifstream &in)
    //protected:
    private:
        static int height;
        static int width;
};

#endif // TILE_H
