#ifndef OBJECT_H
#define OBJECT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "../include/sprite.h"
#include "../include/Vec.h"



class Object : public Sprite
{
    public:
        Object(float X=0, float Y=0, int Z=10, int FPS = 0, int FrameHeight = 0);
        virtual         ~Object();
        virtual void    Update(Uint32 gameTime, Uint32 timeElapsed);
        void            SetMovementX(float X);
        void            SetMovementY(float Y);
        Vec             getVec();
        Vec             getLastVec();
        void            setLastVec(Vec v);
        virtual void    checkCollison();
        void            OnHit(Sprite* s);
    protected:
        void    Move(Uint32 timeElapsed);
        float   PPS; // Pixels Per Second
        Vec     lastVec;

    private:

};

#endif // OBJECT_H
