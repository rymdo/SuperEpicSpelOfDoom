#include "../include/Tile.h"

using namespace std;


//static members
int Tile::width = 64;
int Tile::height = 64;

Tile::Tile(int X, int Y) : Sprite(X, Y)
{

}

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
            if(cStr.compare("c") == 0)
                tmpSprite->setCollidable(true);
            else if(cStr.compare("d") == 0)
                tmpSprite->setCollidable(true);
            else if(cStr.compare("f") == 0)
                tmpSprite->setCollidable(true);
            else if(cStr.compare("g") == 0)
                tmpSprite->setCollidable(true);
            else if(cStr.compare("h") == 0)
                tmpSprite->setCollidable(true);

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
