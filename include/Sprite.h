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
        Sprite(float X=0, float Y=0, int Z=0, int FPS = 0, int FrameHeight = 0);
        virtual ~Sprite();

        virtual void Load(string file);
        virtual bool Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        virtual void Update(Uint32 gameTime, Uint32 timeElapsed);

        static void DrawAll(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        static void UpdateAll(Uint32 gameTime, Uint32 timeElapsed);

        virtual float getHeight();
        virtual float getWidth();

        friend bool operator<(Sprite a, Sprite b);
        static bool zSort(Sprite* a, Sprite* b);

    protected:
        float x;
        float y;
        int z;

        int frameHeight;
        int frameTime;
        int totalFrames;

        SDL_Surface* src;

        void setPos(int X, int Y);

    private:
        static vector<Sprite*> list; //lista f�r alla sprites
};

#endif // SPRITE_H
