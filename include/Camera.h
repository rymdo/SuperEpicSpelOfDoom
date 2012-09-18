#ifndef CAMERA_H
#define CAMERA_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Camera
{
    public:
        Camera(int posX = 0, int posY = 0);
        virtual ~Camera();
        int getX();
        int getY();
        int getH();
        int getW();

        void setPosition();
    private:
        int X;
        int Y;
        static int height;
        static int width;
};

#endif // CAMERA_H
