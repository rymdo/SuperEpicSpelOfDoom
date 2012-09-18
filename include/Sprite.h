#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/Surface.h"

using namespace std;

class Sprite
{
    public:
        Sprite(int X=0, int Y=0, int Z=0);
        virtual ~Sprite();
        void Load(string file);
        bool Draw(SDL_Surface* dest);
        static void DrawAll(SDL_Surface* dest);
        friend bool operator<(Sprite a, Sprite b);
        static bool zSort(Sprite* a, Sprite* b);

    protected:
        int posX;
        int posY;
        int posZ;

        void setPos(int X, int Y);
        virtual void Update();
    protected:
        int posX;
        int posY;
        float FposX;
        float FposY;

    private:
        SDL_Surface* src;
        static vector<Sprite*> list; //lista för alla sprites
};

#endif // SPRITE_H
