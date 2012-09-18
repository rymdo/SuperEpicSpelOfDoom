#include "../include/Sprite.h"

using namespace std;

vector<Sprite*> Sprite::list;

Sprite::Sprite(int X, int Y, int Z)
{
    src = NULL;
    posX = X;
    posY = Y;
    posZ = Z;

    FposX = (float)posX;
    FposY = (float)posY;

    list.push_back(this); //Sparar instansen i statiska Sprite::list
}

//Laddar sprite till src via Surface::Load
void Sprite::Load(string file)
{
    src = Surface::Load((char*)file.c_str());
}

//Ritar ut instansens src på dest via Surface::Draw
bool Sprite::Draw(SDL_Surface* dest)
{
    Surface::Draw(dest, src, posX, posY);
}

void Sprite::Update(Uint32 timeElapsed)
{

}

//Ritar ut alla instanser i Sprite::list
/*static*/ void Sprite::DrawAll(SDL_Surface* dest)
{
    //sorterar vektorn efter vilket lager de ligger i (vilken z-koordinat de har) i stigande ordn.
    sort(list.begin(), list.end(), Sprite::zSort);

    for(int i=0; i<list.size(); i++)
    {
        list[i]->Draw(dest);
    }
}

void Sprite::UpdateAll(Uint32 timeElapsed)
{
    for(int i=0; i<list.size(); i++)
    {
        list[i]->Update(timeElapsed);
    }
}

//hjälper operatorn att hantera sorteringen av pekarelementen i vektorn
/*static*/ bool Sprite::zSort(Sprite* a, Sprite* b)
{
    return *a<*b;
}

//operatoröverlagring för att möjliggöra sortering av vektorn list
bool operator<(Sprite a, Sprite b)
{
    if(a.posZ == b.posZ)
        return (a.posY < b.posY);

    return (a.posZ<b.posZ);
}

void Sprite::setPos(int X, int Y)
{
    posX = X;
    posY = Y;
}

Sprite::~Sprite()
{
    //dtor
}


