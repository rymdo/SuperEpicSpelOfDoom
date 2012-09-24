#include "../include/Camera.h"

using namespace std;

int Camera::width = 640;
int Camera::height = 480;

//constructor
Camera::Camera(int X, int Y)
{
    x = X;
    y = Y;
}

int Camera::getX()
{
    return x;
}

int Camera::getY()
{
    return y;
}

int Camera::getH()
{
    return height;
}

int Camera::getW()
{
    return width;
}

//ska kallas på med koordinater x och y från player, som blir kamerans fokus
void Camera::setPosition(int X, int Y)
{
    x = X-width/2;
    y = Y-height/2;
}

Camera::~Camera()
{
    //dtor
}
