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
        virtual         ~Sprite();

        virtual bool    Load(string file);
        virtual bool    Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        virtual void    Update(Uint32 gameTime, Uint32 timeElapsed);

        virtual Vec     getVec();

        static void     UpdateAll(Uint32 gameTime, Uint32 timeElapsed);
        static void     DrawAll(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        static void     Cleanup();

        void            setFPS(int FPS);
        virtual int     getPosX();
        virtual int     getPosY();
        virtual float   getHeight();
        virtual float   getWidth();
        virtual void    checkCollison();

        friend bool     operator<(Sprite a, Sprite b);
        static bool     zSort(Sprite* a, Sprite* b);
        void            setPos(float X, float Y);

        virtual void    setCollidable(bool state);
        bool            isCollidable;
    protected:
        float           x;
        float           y;
        int             z;
        Vec             vec;
        int             frameHeight;
        int             frameTime;
        int             totalFrames;
        SDL_Surface*    src;

        static vector<Sprite*> list; //lista f�r alla sprites

    private:
};

#endif // SPRITE_H
