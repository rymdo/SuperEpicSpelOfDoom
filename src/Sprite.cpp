#include "../include/Sprite.h"

using namespace std;

vector<Sprite*> Sprite::list;

Sprite::Sprite(float X, float Y, int Z, int FPS, int FrameHeight)
{
    src = NULL;
    x = X;
    y = Y;
    z = Z;

    isCollidable = false;
    vec.x = 0;
    vec.y = 0;

    this->setFPS(FPS);
    frameHeight = FrameHeight;

    totalFrames = 1;

    list.push_back(this); //Sparar instansen i statiska Sprite::list
}

void Sprite::setFPS(int FPS)
{
    frameTime = 1;

    if (FPS != 0)
        frameTime = 1000/FPS;
}

//Laddar sprite till src via Surface::Load
void Sprite::Load(string file)
{
    src = Surface::Load((char*)file.c_str());

    if (frameHeight != 0 && src != NULL)
        totalFrames = (src->h/frameHeight);
}

//Ritar ut instansens src på dest via Surface::Draw
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

//Ritar ut alla instanser i Sprite::list
/*static*/ void Sprite::Cleanup()
{
    list.clear();
}

void Sprite::UpdateAll(Uint32 gameTime, Uint32 timeElapsed)
{
    for(int i=0; i<list.size(); i++)
    {

        list[i]->Update(gameTime, timeElapsed);
        if(list[i]->isCollidable)
        {
            list[i]->doCollison(i);
        }

    }
}

void Sprite::doCollison(int CurrentID)
{
    bool isColliding;
    for(int j = 0; j < list.size(); j++)
    {
        isColliding = true;
        if(CurrentID != j && list[j]->isCollidable)
        {
            if(list[CurrentID]->getPosY() + list[CurrentID]->getHeight() < list[j]->getPosY())
            {
                isColliding = false;
            }
            else if(list[CurrentID]->getPosY() > list[j]->getPosY() + list[j]->getHeight())
            {
                isColliding = false;
            }

            if(list[CurrentID]->getPosX() + list[CurrentID]->getWidth() < list[j]->getPosX())
            {
                isColliding = false;
            }
            else if(list[CurrentID]->getPosX() > list[j]->getPosX() + list[j]->getWidth())
            {
                isColliding = false;
            }

            if(isColliding)
            {
                Vec objVec = list[CurrentID]->getVec();
                int objAx = list[CurrentID]->getPosX();
                int objAy = list[CurrentID]->getPosY();
                int objAw = (int)list[CurrentID]->getWidth();
                int objAh = (int)list[CurrentID]->getHeight();
                int objBx = list[j]->getPosX();
                int objBy = list[j]->getPosY();
                int objBw = (int)list[j]->getWidth();
                int objBh = (int)list[j]->getHeight();

                if(objVec.x < 0)
                {
                    list[CurrentID]->setPos(objBx+objBw+1,objAy);
                }
                else if(objVec.x > 0)
                {
                    list[CurrentID]->setPos(objBx-objAw-1,objAy);
                }

                if(objVec.y < 0)
                {
                    list[CurrentID]->setPos(objAx,objBy+objBh+1);
                }
                else if(objVec.y > 0)
                {
                    list[CurrentID]->setPos(objAx,objBy-objAh-1);
                }
            }
        }
    }
}
Vec Sprite::getVec()
{
    return vec;
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
        return ((a.y+a.getHeight()) < (b.y+b.getHeight()));

    return (a.z < b.z);
}

void Sprite::setPos(float X, float Y)
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
    if(src == NULL)
        return 0;

    return src->w;
}


int Sprite::getPosX()
{
    return (int)(floor(x));
}
int Sprite::getPosY()
{
    return (int)(floor(y));
}


Sprite::~Sprite()
{
    //dtor
}


