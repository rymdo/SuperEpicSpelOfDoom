#include "../include/Popup.h"

using namespace std;

vector<Popup*> Popup::messages; // List of all current Popups

/**
Constructor for Popup, renders a popup message and stores the new popup object in a vector
@param inMessage popup message
@param dur time for the message to be displayed
*/
Popup::Popup(string inMessage, Uint32 dur)
{
    //ctor
    message=inMessage;
    makeTime=dur;
    SDL_Color TURQ = {130,255,180};
    renderdText = TTF_RenderText_Solid(Font::ARIAL,message.c_str(), TURQ);

    messages.push_back(this);
}

/**
Destructor for Popup
*/
Popup::~Popup()
{
    SDL_FreeSurface(renderdText);
}

/**
Displays a popup message until a certain time has passed
@param surface message to be displayed
@param x x-position of message
@param y y-position of message
@param now time
@return true if the message is still to be displayed, false if the time has elapsed
*/
bool Popup::Draw(SDL_Surface* surface, int x, int y, Uint32 now)
{
    if((now-makeTime)>3000)
    {
        return false;
    }
    Surface::DrawStatic(surface, renderdText, x, y);
    return true;
}

/**
Displays all active popups, erases elapseed messages
@param surface message to be displayed
@param now time
*/
void Popup::DrawAll(SDL_Surface* surface, Uint32 now)
{
    int x = 15;
    int y = 15;

    for(int i=messages.size()-1; i>=0; i--)
    {
        if(!messages[i]->Draw(surface, x, y, now))
        {
            delete messages[i];
            messages.erase(messages.begin()+i);
        }
        y+=15;
    }
}
