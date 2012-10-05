#include "../include/Popup.h"

using namespace std;

vector<Popup*> Popup::messages;


Popup::Popup(string inMessage, Uint32 dur)
{
    //ctor
    message=inMessage;
    makeTime=dur;
    SDL_Color TURQ = {130,255,180};
    renderdText = TTF_RenderText_Solid(Font::ARIAL,message.c_str(), TURQ);

    messages.push_back(this);
}

Popup::~Popup()
{
    SDL_FreeSurface(renderdText);
}

bool Popup::Draw(SDL_Surface* surface, int x, int y, Uint32 now)
{
    if((now-makeTime)>3000)
    {
        return false;
    }
    Surface::DrawStatic(surface, renderdText, x, y);
    return true;
}


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
