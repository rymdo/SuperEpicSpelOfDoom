#include "../include/Camera.h"

using namespace std;

int Camera::width = 640; // the total focal width
int Camera::height = 480; // the total focal height

/**
Contructor for Camera
@param X focal X-position
@param Y focal Y-position
*/
Camera::Camera(int X, int Y)
{
    x = X;
    y = Y;
}

/**
@return X focal X-position
*/
int Camera::getX()
{
    return x;
}

/**
@return Y focal Y position
*/
int Camera::getY()
{
    return y;
}

/**
@return height focal height
*/
int Camera::getH()
{
    return height;
}

/**
@return width focal width
*/
int Camera::getW()
{
    return width;
}

/**
Sets the focal point
@param X X-position
@param Y Y-position
*/
void Camera::setPosition(int X, int Y)
{
    x = X-width/2;
    y = Y-height/2;
}

/**
Default destructor for Camera
*/
Camera::~Camera()
{
    //dtor
}
