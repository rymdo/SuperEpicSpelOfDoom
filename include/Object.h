#ifndef OBJECT_H
#define OBJECT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "../include/sprite.h"

/*This is really confusing, Vec could really be of use in other classes,
especially if its made as a class itself with methods such as normalize etc.*/
struct Vec
{
    float x,y;
};

class Object : public Sprite
{
    public:
        Object(float X=0, float Y=0, int Z=10, int FPS = 0, int FrameHeight = 0);
        virtual ~Object();
        virtual void Update(Uint32 gameTime, Uint32 timeElapsed);
        void SetMovementX(float X);
        void SetMovementY(float Y);
    protected:
        Vec vec;
        void Move();
    private:
        int PrevX, PrevY;

};

#endif // OBJECT_H
