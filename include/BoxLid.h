#ifndef BOXLID_H
#define BOXLID_H

#include <vector>
#include "Tile.h"

class BoxLid
{
private:
    std::vector<Tile*> tiles;

public:
    BoxLid();
    ~BoxLid();
    std::vector<Tile*> getTiles();
    unsigned int size() const;
    void addBack(Tile* tile);
    void clear();

};

#endif //BOXLID_H


