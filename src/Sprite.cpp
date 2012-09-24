#include "../include/Sprite.h"

using namespace std;

vector<Sprite*> Sprite::list;

Sprite::Sprite(float X, float Y, int Z, int FPS, int FrameHeight)
{
    src = NULL;
    x = X;
    y = Y;
    z = Z;

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

    if (frameHeight != 0 && src != NULL)
        totalFrames = (src->h/frameHeight);
}

//Ritar ut instansens src p� dest via Surface::Draw
bool Sprite::Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{
    if (src == NULL) return false;

    if (frameHeight == 0)
        return Surface::Draw(dest, src, x, y);

    int frame = gameTime/frameTime;
    frame = frame % totalFrames;
    int srcY = frame*frameHeight;

    return Surface::Draw(dest, src, x, y, 0, srcY, src->w, frameHeight);
}

void Sprite::Update(Uint32 gameTime, Uint32 timeElapsed)
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

void Sprite::UpdateAll(Uint32 gameTime, Uint32 timeElapsed)
{
    for(int i=0; i<list.size(); i++)
    {
        list[i]->Update(gameTime, timeElapsed);
    }
}

//hj�lper operatorn att hantera sorteringen av pekarelementen i vektorn
/*static*/ bool Sprite::zSort(Sprite* a, Sprite* b)
{
    return *a<*b;
}

//operator�verlagring f�r att m�jligg�ra sortering av vektorn list
bool operator<(Sprite a, Sprite b)
{
    if(a.z == b.z)
        return ((a.y+a.getHeight()) < (b.y+b.getHeight()));

    return (a.z < b.z);
}

void Sprite::setPos(int X, int Y)
{
    x = (float)X;
    y = (float)Y;
}

float Sprite::getHeight()
{
    if (frameHeight != 0)
        return (float)frameHeight;

    if (src == NULL)
        return 0;

    return (float)src->h;
}

float Sprite::getWidth()
{
    return src->w;
}

Sprite::~Sprite()
{
    //dtor
}


