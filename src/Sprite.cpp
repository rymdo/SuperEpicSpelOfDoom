#include "../include/Sprite.h"

using namespace std;

vector<Sprite*> Sprite::list;

Sprite::Sprite(float X, float Y, int Z, int FPS, int FrameHeight)
{
    src = NULL;
    x = X;
    y = Y;
    z = Z;

    //FposX = (float)posX;
    //FposY = (float)posY;

    fps = FPS;
    if (FPS != 0)
        frameTime = 1000/FPS;
    else
        frameTime = 1;
    frameHeight = FrameHeight;

    totalFrames = 1;

    list.push_back(this); //Sparar instansen i statiska Sprite::list
}

//Laddar sprite till src via Surface::Load
void Sprite::Load(string file)
{
    src = Surface::Load((char*)file.c_str());

    if (frameHeight != 0)
        totalFrames = (src->h/frameHeight);
}

//Ritar ut instansens src på dest via Surface::Draw
bool Sprite::Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{
    if (frameHeight == 0)
        return Surface::Draw(dest, src, x, y);

    int frame = gameTime/frameTime;
    frame = frame % totalFrames;
    int srcY = frame*frameHeight;

    return Surface::Draw(dest, src, x, y, 0, srcY, src->w, frameHeight);
}

void Sprite::Update(Uint32 timeElapsed)
{

}

//Ritar ut alla instanser i Sprite::list
/*static*/ void Sprite::DrawAll(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{
    //sorterar vektorn efter vilket lager de ligger i (vilken z-koordinat de har) i stigande ordn.
    sort(list.begin(), list.end(), Sprite::zSort);

    for(int i=0; i<list.size(); i++)
    {
        list[i]->Draw(dest, gameTime, timeElapsed);
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
    if(a.z == b.z)
        return (a.y < b.y);

    return (a.z<b.z);
}

void Sprite::setPos(int X, int Y)
{
    x = (float)X;
    y = (float)Y;
}

Sprite::~Sprite()
{
    //dtor
}


