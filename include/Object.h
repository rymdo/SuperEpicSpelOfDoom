#ifndef OBJECT_H
#define OBJECT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include "../include/sprite.h"

struct Vec
{
    float x,y;
};

class Object : Sprite
{
    public:
        Object(int X=0, int Y=0);
        virtual ~Object();
        void Update();
        void SetMovement(float X, float Y);
    protected:
        Vec vec;
    private:
        void Move();

};

#endif // OBJECT_H
