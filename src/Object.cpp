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
@param X X position
@param Y - afndf
@param Z - he
@param FPS - hehe
@param FrameHeight - test
*/
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
}

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
