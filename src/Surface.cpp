#include "../include/Surface.h"

using namespace std;

vector<Surface*> Surface::list; //< static: vector for self documenting Surfaces
Camera* Surface::cam; // static: Camera* for drawing surfaces in the world

/**
@param file String search path to image
@param surf Corresponding loaded SDL_Surface*
*/
Surface::Surface(string file, SDL_Surface* surf)
{
    filename = file; //string
    surface = surf; //SDL_Surface*

    list.push_back(this); //sparar instansen i en statisk lista (pekare)
}

/**
Destructor
Frees member surface(SDL_Surface*)
*/
Surface::~Surface()
{
    SDL_FreeSurface(surface);
}

/**
static: Function to clean up the self documentation
*/
void Surface::Cleanup()
{
    Surface::list.clear();
}

/**
@return surface (SDL_Surface*)
*/
SDL_Surface* Surface::getSurface()
{
    return surface;
}

/**
@return filename (string)
*/
string Surface::getFilename()
{
    return filename;
}

/**
static: Searches for already loaded surfaces by filename
@param file filename to search for
@return surface if exists else NULL
*/
SDL_Surface* Surface::GetLoaded(char* file)
{
    for(int i=0; i<list.size(); i++)
    {
        if(list[i]->getFilename()==file)
        {
            //cout << list[i]->getFilename() << " already loaded, returning loaded SDL_Surface...\n";
            return list[i]->getSurface();
        }
    }
    return NULL;
}

/**
static: Loads filename and stores a new relation creates
@param file filename to load
@return the loaded SDL_Surface*
*/
SDL_Surface* Surface::Load(char* file)
{
    SDL_Surface* ret = GetLoaded(file); //<-- getLoaded returnerar SDL_Surface* eller NULL

    if (ret != NULL)
        return ret; //om getLoaded lyckades hämta en redan laddad bild

    SDL_Surface* temp = NULL;

    if((temp = IMG_Load(file))==NULL)
    {
        cout << "no such file: " << file << endl;
        return NULL;
    }

    ret = SDL_DisplayFormatAlpha(temp); //stöd för alpha
    SDL_FreeSurface(temp);

    new Surface(string(file), ret); //Skapar relationsobjektet surface

    //cout << list.size() << " surfaces loaded\n";

    return ret;
}

/**
static: Draws a surface (SDL_Surface*) onto another surface (SDL_Surface*) inside view of Surface::cam
Make sure to call Surface::setCamera before calling Draw
@param dest     Destination surface - draws onto this surface
@param src      Source surface - draws this surface onto the destination
@param dest_x   Begin to draw at this X position on destination surface
@param dest_y   Begin to draw at this Y position on destination surface
@param src_x    Begin drawing from this X position from the source
@param src_y    Begin drawing from this Y position from the source
@param src_w    Draw this width from the start X position
@param src_h    Draw this height from the start Y position
@return true on success, false on fail
*/
bool Surface::Draw(SDL_Surface* dest, SDL_Surface* src, int dest_x, int dest_y, int src_x, int src_y, int src_w, int src_h)
{
    if(dest == NULL || src == NULL)
    {
        return false;
    }

    //kontrollerar att de sprites som skrivs ut ej ligger utanför skärmen
    dest_x -= Surface::cam->getX();
    dest_y -= Surface::cam->getY();

    if(dest_x < -(src->w) || dest_x>=Surface::cam->getW() || dest_y < -src->h || dest_y >= Surface::cam->getH())
        return false;

    SDL_Rect destR, srcR;
    destR.x = dest_x;
    destR.y = dest_y;

    srcR.x = src_x;
    srcR.y = src_y;
    srcR.w = src_w;
    srcR.h = src_h;

    SDL_BlitSurface(src, &srcR, dest, &destR);

    return true;
}

/**
static: Draws a surface (SDL_Surface*) onto another surface (SDL_Surface*) inside view of Surface::cam
Make sure to call Surface::setCamera before calling Draw
@param dest     Destination surface - draws onto this surface
@param src      Source surface - draws this surface onto the destination
@param x        Begin to draw at this X position on destination surface
@param y        Begin to draw at this Y position on destination surface
@return true on success, false on fail
*/
/*static*/ bool Surface::Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
    if(dest == NULL || src == NULL)
    {
        return false;
    }

    //kontrollerar att de sprites som skrivs ut ej ligger utanför skärmen
    x -= Surface::cam->getX();
    y -= Surface::cam->getY();

    if(x < -(src->w) || x>=Surface::cam->getW() || y < -(src->h) || y >= Surface::cam->getH())
        return false;

    SDL_Rect destR;
    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(src, NULL, dest, &destR);

    return true;
}

/**
static: Draws a surface (SDL_Surface*) onto another surface (SDL_Surface*)
@param dest     Destination surface - draws onto this surface
@param src      Source surface - draws this surface onto the destination
@param x        Begin to draw at this X position on destination surface
@param y        Begin to draw at this Y position on destination surface
@return true on success, false on fail
*/
/*static*/ bool Surface::DrawStatic(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
    if(dest == NULL || src == NULL)
    {
        return false;
    }

    SDL_Rect destR;
    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(src, NULL, dest, &destR);

    return true;
}

/**
static: Set the camera which Draw depends on
@param a     A camera
*/
/*static*/void Surface::setCamera(Camera* a)
{
    Surface::cam = a;
}
