#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>

using namespace std;

class Map
{
    public:
        Map(string mapName);
        virtual ~Map();
    protected:
    private:
        //void loadMap(string mapName, int dimX, int dimY, Tile* mapArray);
        string mapName;
        vector<int> map;
};

#endif // MAP_H
