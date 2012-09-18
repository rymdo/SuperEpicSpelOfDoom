#ifndef OBJECT_H
#define OBJECT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include "../include/sprite.h"

/*This is really confusing, Vec could really be of use in other classes,
especially if its made as a class itself with methods such as normalize etc. */
struct Vec
{
    float x,y;
};

class Object : Sprite
{
    public:
        Object(int X=0, int Y=0, int Z=10, string file="files/sprites/link/linkD1.gif");
        virtual ~Object();
        void Update(Uint32 timeElapsed);
        void SetMovement(float X, float Y);
    protected:
        Vec vec;
    private:
        void Move();

};

#endif // OBJECT_H
