#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>

#include "../include/Surface.h"

using namespace std;

//Basklass Sprite som symboliserar "ritbara" objekt
class Sprite
{
    public:
        Sprite(int X, int Y);
        virtual ~Sprite();
        void Load(string file);
        void Draw(SDL_Surface* dest);
        static void DrawAll(SDL_Surface* dest);

    private:
        SDL_Surface* src;
        int posX;
        int posY;
        static vector<Sprite*> list; //lista med alla instansierade Sprites
};

#endif // SPRITE_H
