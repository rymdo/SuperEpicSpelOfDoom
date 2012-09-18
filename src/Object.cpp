#include "../include/Object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "../include/sprite.h"

using namespace std;

Object::Object(int X, int Y, string file) : Sprite(X, Y)
{
    vec.x = 0;
    vec.y = 0;
    Load(file);
}

void Object::Update()
{
    Move();
    posX = ceil(FposX);
    posY = ceil(FposY);
}

void Object::Move()
{
    FposX += vec.x;
    FposY += vec.y;


    if(vec.x < 0.0)
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
    }


}

void Object::SetMovement(float X, float Y)
{
    vec.x = X;
    vec.y = Y;
}

Object::~Object()
{
    //dtor
}
