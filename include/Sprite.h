#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include "../include/Surface.h"
#include "../include/Vec.h"

using namespace std;

class Sprite
{
    public:
        Sprite(float X=0, float Y=0, int Z=0, int FPS = 0, int FrameHeight = 0);
        virtual ~Sprite();

        virtual void Load(string file);
        virtual bool Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        virtual void Update(Uint32 gameTime, Uint32 timeElapsed);

        virtual Vec getVec();

        static void DrawAll(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        static void UpdateAll(Uint32 gameTime, Uint32 timeElapsed);

        void setFPS(int FPS);
        virtual int getPosX();
        virtual int getPosY();
        virtual float getHeight();
        virtual float getWidth();
        virtual void doCollison(int CurrentID);

        friend bool operator<(Sprite a, Sprite b);
        static bool zSort(Sprite* a, Sprite* b);

    protected:
        float x;
        float y;
        int z;
        Vec vec;
        int frameHeight;
        int frameTime;
        int totalFrames;

        SDL_Surface* src;

        bool isCollidable;
        void setPos(int X, int Y);


    private:
        static vector<Sprite*> list; //lista för alla sprites
};

#endif // SPRITE_H
