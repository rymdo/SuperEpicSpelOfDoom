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
        cout << "file is open";
        do
        {
            c=in.get();

            if(c=='\n')
            {
                row++; //correct
                column = 0;
                continue;
            }
            else if(c=='a') //istället för massa else if här, sätt ihop strängarna -> "../files/tiles/" + c + ".jpg" som parameter för load
            {
                Sprite* tmpSprite = new Sprite(column*width, row*height);
                tmpSprite->Load("files/tiles/a.png");
            }
            else if(c=='b')
            {
                Sprite* tmpSprite = new Sprite(column*width, row*height);
                tmpSprite->Load("files/tiles/b.png");
            }
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
