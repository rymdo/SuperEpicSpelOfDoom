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
    PrevX = X;
    PrevY = Y;
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
Check collision with other objects
@param ID of object
*/
void Object::checkCollison(int ID)
{
    if(isCollidable)
    {
        if(getVec().x != 0 || getVec().y != 0)
        {
            bool isColliding;
            for(int i = 0; i < Sprite::getListSize(); i++)
            {
                isColliding = true;
                if(ID != i && Sprite::getListPos(i)->isCollidable)
                {
                    if(getPosY() + getHeight() < Sprite::getListPos(i)->getPosY())
                    {
                        isColliding = false;
                    }
                    else if(getPosY() > Sprite::getListPos(i)->getPosY() + Sprite::getListPos(i)->getHeight())
                    {
                        isColliding = false;
                    }

                    if(getPosX() + getWidth() < Sprite::getListPos(i)->getPosX())
                    {
                        isColliding = false;
                    }
                    else if(getPosX() > Sprite::getListPos(i)->getPosX() + Sprite::getListPos(i)->getWidth())
                    {
                        isColliding = false;
                    }
                    if(isColliding)
                    {
                        Vec objVec = getVec();
                        int objAx = getPosX();
                        int objAy = getPosY();
                        int objAw = (int)getWidth();
                        int objAh = (int)getHeight();
                        int objBx = Sprite::getListPos(i)->getPosX();
                        int objBy = Sprite::getListPos(i)->getPosY();
                        int objBw = (int)Sprite::getListPos(i)->getWidth();
                        int objBh = (int)Sprite::getListPos(i)->getHeight();

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
                }
            }
        }
    }
}


Object::~Object()
{
    //dtor
}
