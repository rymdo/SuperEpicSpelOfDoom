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
        Tile(int X=0, int Y=0);
        virtual ~Tile();
        static bool loadAll();
        //void read(ifstream &in)
    //protected:
    private:
        static int height;
        static int width;
};

#endif // TILE_H
