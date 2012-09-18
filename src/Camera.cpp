#include "../include/Camera.h"

using namespace std;

int Camera::width = 640;
int Camera::height = 480;

//constructor
Camera::Camera(int posX, int posY)
{
    X=posX;
    Y=posY;
}

int Camera::getX()
{
    return X;
}

int Camera::getY()
{
    return Y;
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
void Camera::setPosition()
{

}

Camera::~Camera()
{
    //dtor
}
