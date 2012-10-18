#include "../include/Sprite.h"

using namespace std;

vector<Sprite*> Sprite::list; //List for self documenting all sprites

/**
Constructor for Sprite
@param X            X position
@param Y            Y position
@param Z            Z position (depth)
@param FPS          the 'Frames Per Second' to animate the Sprite
@param FrameHeight  Height of one frame in the spritemap
@return true on success, false on fail
*/
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

/**
Sets the frames per second
@param FPS          the Frames per Second to animate the Sprite
*/
void Sprite::setFPS(int FPS)
{
    frameTime = 1;

    if (FPS != 0)
        frameTime = 1000/FPS;
}

/**
Loads a image file via Surface::Load
@param file     path to image
*/
bool Sprite::Load(string file)
{
    src = Surface::Load((char*)file.c_str());

    if (frameHeight != 0 && src != NULL)
        totalFrames = (src->h/frameHeight);

    if (src == NULL) return false;

    return true;
}

/**
Draws the Sprite surface/image onto a SDL_Surface* via Surface::Draw
@param dest         Draw onto this surface
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
@return true on success, false on fail
*/
bool Sprite::Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{
    if (src == NULL)
    {
        cout << "src is NULL";
        return false;
    }

    if (frameHeight == 0 || frameTime == 1)
        return Surface::Draw(dest, src, x, y);

    int frame = gameTime/frameTime;
    frame = frame % totalFrames;
    int srcY = frame*frameHeight;

    return Surface::Draw(dest, src, x, y, 0, srcY, src->w, frameHeight);
}

/**
Update the sprites
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
*/
void Sprite::Update(Uint32 gameTime, Uint32 timeElapsed)
{

}

/**
static: Draws all sprites. Iterates through all Sprite's and calls Sprite::Draw for each of them
@param dest         Draw onto this surface
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
*/
/*static*/ void Sprite::DrawAll(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{

    sort(list.begin(), list.end(), Sprite::zSort);

    int drawed = 0;
    bool ret;
    for(int i=0; i<list.size(); i++)
    {
        ret = list[i]->Draw(dest, gameTime, timeElapsed);

        if(ret == true)
            drawed++;
    }
    //cout << drawed << "/" << list.size() << endl;

    /*vector<Sprite*>::iterator it;

    for (it=list.begin() ; it < list.end(); it++)
    {
        if ((*it)->Draw(dest, gameTime, timeElapsed))
            drawed++;
    }*/
    //cout << drawed << "/" << list.size() << endl;
}

/**
static: Destroys all current Sprites
*/
/*static*/ void Sprite::Cleanup()
{
    list.clear();
}

/**
static: Updates all sprites. Iterates through all Sprite's and calls Sprite::Update for each of them
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
*/
/*static*/void Sprite::UpdateAll(Uint32 gameTime, Uint32 timeElapsed)
{
    for(int i=0; i<list.size(); i++)
    {

        list[i]->Update(gameTime, timeElapsed);
        //list[i]->checkCollison();
    }
}

/**
Checks collision with other objects
*/
void Sprite::checkCollison()
{

}

/**
@return vector representing movement
*/
Vec Sprite::getVec()
{
    return vec;
}

/**
static: Sort pointers of sprites
@param a    Pointer to a
@param b    Pointer to b
@return     true if a < b, else false
*/
/*static*/ bool Sprite::zSort(Sprite* a, Sprite* b)
{
    return *a<*b;
}

/**
Sort sprites by ascending Z-position(depth), and then ascending Y-position
@param a    Pointer to a
@param b    Pointer to b
@return     true if a < b, else false
*/
bool operator<(Sprite a, Sprite b)
{
    if(a.z == b.z)
        return ((a.y+a.getHeight()) < (b.y+b.getHeight()));

    return (a.z < b.z);
}

/**
Set the Sprite's the position (pivot: upper left corner)
@param X    X position
@param Y    Y position
*/
void Sprite::setPos(float X, float Y)
{
    x = (float)X;
    y = (float)Y;
}

/**
If the Sprite is animated it will return the frame height of the Sprite otherwise the surface/image height
@return  Sprite's height
*/
float Sprite::getHeight()
{
    if (frameHeight != 0)
        return (float)frameHeight;

    if (src == NULL)
        return 0;

    return (float)src->h;
}

/**
@return  Sprite's widht
*/
float Sprite::getWidth()
{
    if(src == NULL)
        return 0;

    return src->w;
}

/**
@return  Sprite's X position
*/
int Sprite::getPosX()
{
    return (int)(floor(x));
}

/**
@return  Sprite's Y position
*/
int Sprite::getPosY()
{
    return (int)(floor(y));
}

/**
Decide if a sprite is collidable
@param state    true if collidable, false otherwise
*/
void Sprite::setCollidable(bool state)
{
    isCollidable = state;
}

Sprite::~Sprite()
{
    //dtor
}


