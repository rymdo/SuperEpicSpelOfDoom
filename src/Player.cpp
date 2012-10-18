#include "../include/Player.h"

/**
Constructor for Player
@param Cam  Camera
@param X    X position
@param Y    Y position
@param Z    Z position (depth)
*/
Player::Player(Camera* Cam, float X, float Y, int Z) : Object(X, Y, Z, 4, 32)
{
    cam = Cam;
}

/**
Load all spritemaps for the player, selects a current spritemap and sets the movement (Pixel Per Second)
*/
void Player::Load()
{
    string standFront = "files/sprites/monk/monk_stand_front.png";
    string standRight = "files/sprites/monk/monk_stand_right.png";
    string standBack = "files/sprites/monk/monk_stand_back.png";
    string standLeft = "files/sprites/monk/monk_stand_left.png";
    string runFront = "files/sprites/monk/monk_run_front.png";
    string runRight = "files/sprites/monk/monk_run_right.png";
    string runBack = "files/sprites/monk/monk_run_back.png";
    string runLeft = "files/sprites/monk/monk_run_left.png";

    srcList.push_back(Surface::Load((char*)standFront.c_str())); //0 FRONT
    srcList.push_back(Surface::Load((char*)standRight.c_str())); //1 RIGHT
    srcList.push_back(Surface::Load((char*)standBack.c_str())); //2 BACK
    srcList.push_back(Surface::Load((char*)standLeft.c_str())); //3 LEFT
    srcList.push_back(Surface::Load((char*)runFront.c_str())); //4 FRONT
    srcList.push_back(Surface::Load((char*)runRight.c_str())); //5 RIGHT
    srcList.push_back(Surface::Load((char*)runBack.c_str())); //6 BACK
    srcList.push_back(Surface::Load((char*)runLeft.c_str())); //7 LEFT

    src = srcList[0];
    PPS = 200;
}

/**
Update the player and moves the camera to player position
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
*/
void Player::Update(Uint32 gameTime, Uint32 timeElapsed)
{
    Object::Update(gameTime, timeElapsed);
    cam->setPosition(x, y);
}

/**
Selects the appropiate spritemap for animation and draws the player
@param dest         Draw onto this surface
@param gameTime     Time(ms) of game
@param timeElapsed  Time(ms) since last update/draw
@return true on success, false on fail
*/
bool Player::Draw(SDL_Surface* dest, Uint32 gameTime, Uint32 timeElapsed)
{
    if (vec.Abs() == 0)
    {
        setFPS(4);

        if(lastVec.x < 0.0)
        {
            src = srcList[3];
        }
        else if(lastVec.x > 0.0)
        {
            src = srcList[1];
        }

        if(lastVec.y < 0.0)
        {
            src = srcList[2];
        }
        else if(lastVec.y > 0.0)
        {
            src = srcList[0];
        }
    }
    else
    {
        setFPS(12);

        if(vec.x < 0.0)
        {
            src = srcList[7];
        }
        else if(vec.x > 0.0)
        {
            src = srcList[5];
        }

        if(vec.y < 0.0)
        {
            src = srcList[6];
        }
        else if(vec.y > 0.0)
        {
            src = srcList[4];
        }
    }

    if (frameHeight != 0 && src != NULL)
        totalFrames = (src->h/frameHeight);

    return Sprite::Draw(dest, gameTime, timeElapsed);
}

/**
Places an item if less the 10 are already dislayed
@param time         A time variable that makes call to Popup from the function possible
@return true on success, false on fail
*/
bool Player::placeItem(Uint32 time)
{
    if(items.size()<=9)
    {
        Vec temp = lastVec;
        temp.Normalize();

        Object* testObj = new Object(0, 0, 10);
        if (testObj->Load("files/sprites/cinnamonbun.png"))
        {
            float newX = (x+16+50*lastVec.x)-(testObj->getHeight()/2);
            float newY = (y+16+50*lastVec.y)-(testObj->getWidth()/2);
            testObj->setPos(newX, newY);
            items.push_back(testObj);
            string str = "Congratz!! You have successfully stored ";
            string number = static_cast<ostringstream*>( &(ostringstream() << items.size()) )->str();
            str.append(number);
            str.append(" bun(s) in your garden! YAY!");


            popUp= new Popup(str , time);

             cout << "Player x: " << testObj->getPosX() << " y: " << testObj->getPosY() << endl;
        }
        return true;
    }
    popUp=new Popup("NO MORE BUNS 4 U!!", time);
    return false;
}

/**
Saves items that has been placed in the world
@param &file         A stream, passed by reference
*/
void Player::saveItems(ofstream &file)
{
    for(int i = 0; i<items.size(); i++)
    {
        file << items[i]->getPosX() << " " << items[i]->getPosY() << "\n";
    }
}

/**
Loads placed items
@param dest         A stream, passed by reference
*/
void Player::loadItems(ifstream &file)
{
    while(file.good())
    {
        float x;
        float y;
        file >> x >> y;
        Object * testObj = new Object(x,y,10);
        testObj->Load("files/sprites/cinnamonbun.png");
        items.push_back(testObj);
    }
}

Player::~Player()
{
    //dtor
}
