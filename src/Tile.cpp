#include "../include/Tile.h"

using namespace std;


//static members
int Tile::width = 64;   //Tile width
int Tile::height = 64;  //Tile height

/**
Tile Constructor
@param X    X position
@param Y    Y position
*/
Tile::Tile(float X, float Y) : Sprite(X, Y, 5)
{

}

/**
    Load all tiles
    @return true on success, false on fail
*/
bool Tile::loadAll()
{
    ifstream in("files/maps/map_world.txt");

    int column = 0;
    int row = 0;
    char c;

    if(in.is_open())
    {
        //cout << "file is open";
        do
        {
            c=in.get();

            if(c=='\n')
            {
                row++; //correct
                column = 0;
                continue;
            }

            if(!isalnum(c)) continue;

            string cStr(1, c);

            string filepath = "files/tiles/";
            filepath.append(cStr);
            filepath.append(".png");

            Sprite* tmpSprite = new Sprite(column*width, row*height);

            switch((int)c)
            {
                case (int)'c':
                case (int)'d':
                case (int)'f':
                case (int)'g':
                case (int)'h':
                    tmpSprite->setCollidable(true);
                break;
                default:
                    tmpSprite->setCollidable(false);
                break;
            }

            tmpSprite->Load(filepath);

            column++;
        }
        while(!in.eof());

        in.close();
    } else
        return false;

    if(row == 0 || column == 0)
        return false;

    return true;
}

Tile::~Tile()
{
    //dtor
}
