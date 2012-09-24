#include "../include/Player.h"

Player::Player(Camera* Cam, float X, float Y, int Z) : Object(X, Y, Z, 4, 32)
{
    cam = Cam;
}

void Player::Load()
{
    string standFront = "files/sprites/monk/monk_stand_front.png";
    string standRight = "files/sprites/monk/monk_stand_right.png";
    string standBack = "files/sprites/monk/monk_stand_back.png";
    string standLeft = "files/sprites/monk/monk_stand_left.png";

    srcList.push_back(Surface::Load((char*)standFront.c_str())); //0 FRONT
    srcList.push_back(Surface::Load((char*)standRight.c_str())); //1 SIDE
    srcList.push_back(Surface::Load((char*)standBack.c_str())); //2 BACK
    srcList.push_back(Surface::Load((char*)standLeft.c_str())); //2 BACK

    src = srcList[0];
}

void Player::Update(Uint32 gameTime, Uint32 timeElapsed)
{
    Move();
    cam->setPosition(x, y);
}

bool Player::Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{
    if(vec.x < 0.0)
    {
        src = srcList[3];
    }
    else if( vec.x > 0.0)
    {
        src = srcList[1];
    }

    if(vec.y < 0.0)
    {
        src = srcList[2];
    }
    else if( vec.y > 0.0)
    {
        src = srcList[0];
    }

    if (frameHeight != 0 && src != NULL)
        totalFrames = (src->h/frameHeight);

    return Sprite::Draw(dest, gameTime, timeElapsed);
}

Player::~Player()
{
    //dtor
}
