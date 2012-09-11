#include "../include/Sprite.h"

using namespace std;

/*static*/ vector<Sprite*> Sprite::list; //Var tvungen att l�gga till denna av n�gon anledning, annars fanns inte referensen...

Sprite::Sprite(int X, int Y)
{
    src = NULL; //s�tter SDL_Surface till NULL f�r att det inte ska bli konstigheter
    posX = X;
    posY = Y;

    list.push_back(this); //Sparar pekare p� instansierat object i (Sprite*)listan
}

//Laddar surface via Surface
void Sprite::Load(string file)
{
    src = Surface::Load((char*)file.c_str());
}

//Ritar spritens bild (src) via Surface::Draw
void Sprite::Draw(SDL_Surface* dest)
{
    Surface::Draw(dest, src, posX, posY);
}

//Ritar alla instansierade sprites
/* static */ void Sprite::DrawAll(SDL_Surface* dest)
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


