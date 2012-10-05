#include "../include/Object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "../include/sprite.h"

using namespace std;

Object::Object(float X, float Y, int Z, int FPS, int FrameHeight) : Sprite(X, Y, Z, FPS, FrameHeight)
{
    PrevX = X;
    PrevY = Y;
    isCollidable = true;
}

void Object::Update(Uint32 gameTime, Uint32 timeElapsed)
{
    Move(timeElapsed);
}

void Object::Move(Uint32 timeElapsed)
{
    vec.Normalize();

    if(vec.Abs() != 0)
        lastVec = vec;

    float currentMovement = timeElapsed * (PPS/1000.0);
    //vec = vec * currentMovement;
    vec *= currentMovement;

    x += vec.x;
    y += vec.y;
    /*Each call to Load goes through Surface::Load and generates an iteration through
    ALL loaded images which is fairly uneffective... Load images when instansiating instead
    in a class which derives from Object, as agreed earlier called Player...*/
    /*if(vec.x < 0.0)
    {
        Load("files/sprites/link/linkR.gif");
    }
    else if( vec.x > 0.0)
    {
        Load("files/sprites/link/linkL.gif");
    }

    if(vec.y < 0.0)
    {
        Load("files/sprites/link/linkU.gif");
    }
    else if( vec.y > 0.0)
    {
        Load("files/sprites/link/linkD1.gif");
    }*/
}

/*instead of setmovement, maybe appendMovement could be used..
That way one key won't override another. Then simply limit the total movement by
normalize the vector and multiply it with a constant...*/
void Object::SetMovementX(float X)
{
    vec.x = X;
}

void Object::SetMovementY(float Y)
{
    vec.y = Y;
}

Vec Object::getVec()
{
    return vec;
}

Vec Object::getLastVec()
{
    return lastVec;
}

void Object::setLastVec(Vec v)
{
    lastVec=v;
}

Object::~Object()
{
    //dtor
}
