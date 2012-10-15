#include "../include/Object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "../include/sprite.h"

using namespace std;
/**
Kontruktor för Object
@param X            X position
@param Y            Y position
@param Z            Z position (depth)
@param FPS          'Frames per Second' for animation
@param FrameHeight  Height of one frame in Spritemap
*/
Object::Object(float X, float Y, int Z, int FPS, int FrameHeight) : Sprite(X, Y, Z, FPS, FrameHeight)
{
    isCollidable = true;
}

/**
Update the Object, also moves it with Object::Move
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
*/
void Object::Update(Uint32 gameTime, Uint32 timeElapsed)
{
    Move(timeElapsed);
    checkCollison();
}

/**
Moves the sprite
@param timeElapsed      Time(ms) since last update/draw
*/
void Object::Move(Uint32 timeElapsed)
{
    vec.Normalize();

    if(vec.Abs() != 0)
        lastVec = vec;

    float currentMovement = timeElapsed * (PPS/1000.0);
    vec *= currentMovement;

    x += vec.x;
    y += vec.y;
}

/**
Set X movement
@param X      X movement
*/
void Object::SetMovementX(float X)
{
    vec.x = X;
}

/**
Set Y movement
@param Y      Y movement
*/
void Object::SetMovementY(float Y)
{
    vec.y = Y;
}

/**
@return The movement Vector(Vec)
*/
Vec Object::getVec()
{
    return vec;
}

/**
@return The previous movement Vector(Vec)
*/
Vec Object::getLastVec()
{
    return lastVec;
}

/**
Sets the previous movement Vector(Vec)
*/
void Object::setLastVec(Vec v)
{
    lastVec=v;
}

/**
Check collision with all other objects
*/
void Object::checkCollison()
{
    if(!isCollidable) return; //if not set to be able to collide, dont check collisions
    if(getVec().Abs() == 0) return; //if not moving, dont check collisions

    bool isColliding;
    for(int i = 0; i < list.size(); i++)
    {
        isColliding = true;

        if (!list[i]->isCollidable) continue; //if the other object cant collide, dont check
        if (this == list[i]) continue; //dont check collisions with self

        if(getPosY() + getHeight() < list[i]->getPosY())
        {
            isColliding = false;
        }
        else if(getPosY() > list[i]->getPosY() + list[i]->getHeight())
        {
            isColliding = false;
        }

        if(getPosX() + getWidth() < list[i]->getPosX())
        {
            isColliding = false;
        }
        else if(getPosX() > list[i]->getPosX() + list[i]->getWidth())
        {
            isColliding = false;
        }

        //collision is happening! OMFG!
        if(isColliding)
            OnHit(list[i]);
    }
}

/**
Handle a hit
@param Sprite that hits
*/
void Object::OnHit(Sprite* s)
{
    Vec objVec = getVec();
    int objAx = getPosX();
    int objAy = getPosY();
    int objAw = (int)getWidth();
    int objAh = (int)getHeight();
    int objBx = s->getPosX();
    int objBy = s->getPosY();
    int objBw = (int)s->getWidth();
    int objBh = (int)s->getHeight();

    if(objVec.x < 0)
    {
        setPos(objBx+objBw+1,objAy);
    }
    else if(objVec.x > 0)
    {
        setPos(objBx-objAw-1,objAy);
    }

    if(objVec.y < 0)
    {
        setPos(objAx,objBy+objBh+1);
    }
    else if(objVec.y > 0)
    {
        setPos(objAx,objBy-objAh-1);
    }
}

Object::~Object()
{
    //dtor
}
