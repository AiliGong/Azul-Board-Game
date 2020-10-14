#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

class Constants
{
private:
    unsigned int NUM_OF_TILECOLOUR;
    unsigned int MOSAIC_GRID_DIM;

    unsigned int NUM_OF_TILE_EACH_COLOUR;
    unsigned int TOTAL_NUM_OF_TILE;
    unsigned int NUM_OF_FACTORIES;
    unsigned int NUM_OF_ALL_FACTORIES;
    unsigned int NUM_OF_TILES_EACH_FAC;
    unsigned int TOTAL_NUM_OF_GAME_ROUND;
    unsigned int NUM_OF_PLAYERS;

    // Any single tile indicator
    std::string TILE_PATTERN;

    std::string FACTORY_INDEX_PATTERN;

    std::string STORAGE_ROW_INDEX_PATTERN;

    // Literal "turn" followed by valid factory index (0 represents the broken
    // tile row), tile indicator, and storage row index, all separated by spaces
    std::string TURN_PATTERN;

    // Exactly TOTAL_NUM_OF_TILE tile indicators, without separators
    std::string INITIAL_TILES_PATTERN;

    void initialConstants(unsigned int mode);


public:
    Constants(unsigned int mode);
    ~Constants();
    void standardMode();
    void sixTileMode();
    void greyMode();

    unsigned int getNUM_OF_TILECOLOUR();
    unsigned int getMOSAIC_GRID_DIM();

    unsigned int getNUM_OF_TILE_EACH_COLOUR();
    unsigned int getTOTAL_NUM_OF_TILE();
    unsigned int getNUM_OF_FACTORIES();
    unsigned int getNUM_OF_ALL_FACTORIES();
    unsigned int getNUM_OF_TILES_EACH_FAC();
    unsigned int getTOTAL_NUM_OF_GAME_ROUND();
    unsigned int getNUM_OF_PLAYERS();

    // Any single tile indicator
    std::string getTILE_PATTERN();

    std::string getFACTORY_INDEX_PATTERN();

    std::string getSTORAGE_ROW_INDEX_PATTERN();

    // Literal "turn" followed by valid factory index (0 represents the broken
    // tile row), tile indicator, and storage row index, all separated by spaces
    std::string getTURN_PATTERN();

    // Exactly TOTAL_NUM_OF_TILE tile indicators, without separators
    std::string getINITIAL_TILES_PATTERN();

    

};

#endif  // CONSTANTS_H
