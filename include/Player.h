#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "../include/Object.h"
#include "../include/Surface.h"
#include "../include/Camera.h"
#include "../include/Popup.h"
#include <sstream>
#include <iostream>
#include <fstream>

class Player : public Object
{
    public:
        Player(Camera* Cam, float X=0, float Y=0, int Z=20);
        virtual ~Player();
        virtual void Load();
        virtual bool Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed);
        virtual void Update(Uint32 gameTime, Uint32 timeElapsed);
        bool placeItem(Uint32 time);
        void saveItems(ofstream &file);
        void loadItems(ifstream &file);
    protected:
    private:
        Camera* cam;
        vector<SDL_Surface*> srcList;
        vector<Object*> items;
        Popup*          popUp;
};

#endif // PLAYER_H
