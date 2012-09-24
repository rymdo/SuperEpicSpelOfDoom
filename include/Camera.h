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
        Camera(int X = 0, int Y = 0);
        virtual ~Camera();
        int getX();
        int getY();
        int getH();
        int getW();

        void setPosition(int x, int y);
    private:
        int x;
        int y;
        static int height;
        static int width;
};

#endif // CAMERA_H
