#include "../include/Object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "../include/sprite.h"

using namespace std;

Object::Object(int X, int Y, int Z, string file) : Sprite(X, Y, Z)
{
    vec.x = 0;
    vec.y = 0;
    Load(file);
}

void Object::Update(Uint32 timeElapsed)
{
    Move();
    posX = ceil(FposX);
    posY = ceil(FposY);
}

void Object::Move()
{
    FposX += vec.x;
    FposY += vec.y;

    /*Each call to Load goes through Surface::Load and generates an iteration through
    ALL loaded images which is fairly uneffective... Load images when instanciating instead
    in a class which derives from Object, as agreed earlier called Player...*/
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

/*instead of setmovement, maybe appendMovement could be used..
That way one key won't override another. Then simply limit the total movement by
normalize the vector and multiply it with a constant...*/
void Object::SetMovement(float X, float Y)
{
    vec.x = X;
    vec.y = Y;
}

Object::~Object()
{
    //dtor
}
