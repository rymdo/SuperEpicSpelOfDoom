#include "../include/Surface.h"

using namespace std;
/*static*/ vector<Surface*> Surface::list;

//Constructor
Surface::Surface(string file, SDL_Surface* surf)
{
    filename = file; //string
    surface = surf; //SDL_Surface*

    list.push_back(this); //sparar instansen i en statisk lista (pekare)
}

Surface::~Surface()
{
    //dtor
}

//returnerar laddad surface för instans
SDL_Surface* Surface::getSurface()
{
    return surface;
}

//returnerar filename för instans
string Surface::getFilename()
{
    return filename;
}

//Söker i statiska Surface::list efter en surface med samma filnamn och returnerar dess surface i så fall
SDL_Surface* Surface::getLoaded(char* file)
{
    for(int i=0; i<list.size(); i++)
    {
        if(list[i]->getFilename()==file)
        {
            cout << list[i]->getFilename() << " already loaded, returning loaded SDL_Surface...\n";
            return list[i]->getSurface();
        }
    }
    return NULL;
}

//Ladda ny bildfil och spara i en SDL_Surface, sparar ett relationsobjekt Surface, mellan SDL_Surface och filename
/*static*/ SDL_Surface* Surface::Load(char* file)
{
    SDL_Surface* retg = getLoaded(file); //<-- getLoaded returnerar SDL_Surface* eller NULL

    if (ret != NULL)
        return ret; //om getLoaded lyckades hämta en redan laddad bild

    SDL_Surface* temp = NULL;

    if((temp = IMG_Load(file))==NULL)
    {
        return NULL;
    }

    ret = SDL_DisplayFormatAlpha(temp); //stöd för alpha
    SDL_FreeSurface(temp);

    new Surface(string(file), ret); //Skapar relationsobjektet surface

    //cout << list.size() << " surfaces loaded\n";

    return ret;
}

//Ritar en surface på en annan...
/*static*/ bool Surface::Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y)
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
