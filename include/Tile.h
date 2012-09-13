#ifndef TILE_H
#define TILE_H

#include "../include/sprite.h"


class Tile : public Sprite
{
    public:
        Tile();
        virtual ~Tile();
        static void Load;
    //protected:
    private:
        static int height;
        static int width;
};

#endif // TILE_H
