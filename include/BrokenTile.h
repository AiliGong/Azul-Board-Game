#ifndef BROKENTILE_H
#define BROKENTILE_H

#include <vector>
#include <string>

#include "Tile.h"

#define NO_OF_BROEKN_TILE_LOSE_POINTS       7

class BrokenTile
{
public:
    BrokenTile();
    ~BrokenTile();

    //add a broken tile to the back
    void addTile(Tile* tile);

    //calculate the total points lost
    unsigned int calculateLostPoints() const;

    void clear();

    //get nunmber of broken tiles
    unsigned int getSize() const;

    //get all broken tiles
    std::vector<Tile*> getAllTiles();

    std::string str();

private:
    std::vector<Tile*> broken_tiles;

};


#endif //BROKENTILE_H

