#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "../include/Object.h"
#include "../include/Surface.h"
#include "../include/Camera.h"

class Player : public Object
{
    public:
        Player(Camera* Cam, float X=0, float Y=0, int Z=20);
        virtual ~Player();
        virtual void Load();
        virtual bool Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        virtual void Update(Uint32 gameTime, Uint32 timeElapsed);
    protected:
    private:
        Camera* cam;
        vector<SDL_Surface*> srcList;
};

#endif // PLAYER_H
