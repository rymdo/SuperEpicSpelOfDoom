#include "../include/Object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "../include/sprite.h"

using namespace std;

Object::Object(int X, int Y) : Sprite(X, Y)
{
    vec.x = 0;
    vec.y = 0;
    Load("files/sprites/link/linkD1.gif");
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
