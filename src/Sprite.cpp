#include "../include/Sprite.h"

using namespace std;

vector<Sprite*> Sprite::list;

Sprite::Sprite(int X, int Y)
{
    src = NULL;
    posX = X;
    posY = Y;

    list.push_back(this);
}

void Sprite::Load(string file)
{
    src = Surface::Load((char*)file.c_str());
}

void Sprite::Draw(SDL_Surface* dest)
{
    Surface::Draw(dest, src, posX, posY);
}

void Sprite::DrawAll(SDL_Surface* dest)
{
    for(int i=0; i<list.size(); i++)
    {
        list[i]->Draw(dest);
    }
}

Sprite::~Sprite()
{
    //dtor
}


