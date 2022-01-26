#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
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
    unsigned int BROKEN_TILE_SOLT;
    bool grey_mode;
    bool standard_mode;

    // Any single tile indicator
    std::string TILE_PATTERN;

    std::string FACTORY_INDEX_PATTERN;

    std::string STORAGE_ROW_INDEX_PATTERN;

    // Literal "turn" followed by valid factory index (0 represents the broken
    // tile row), tile indicator, and storage row index, all separated by spaces
    std::string TURN_PATTERN;

    // Exactly TOTAL_NUM_OF_TILE tile indicators, without separators
    std::string INITIAL_TILES_PATTERN;
    std::string TILE_BAG_MIDDLE_PATTERN;
    std::string MANNUAL_MOVE_PATTERN;

    void initialConfig(unsigned int mode);


public:
    Config(unsigned int mode);
    Config(Config& other);

    ~Config();
    void standardMode();
    void sixTileMode();
    void greyMode();
    void fiveTileGreyMode();
    void sixTileGreyMode();

    unsigned int getNUM_OF_TILECOLOUR();
    unsigned int getMOSAIC_GRID_DIM();

    unsigned int getNUM_OF_TILE_EACH_COLOUR();
    unsigned int getTOTAL_NUM_OF_TILE();
    unsigned int getNUM_OF_FACTORIES();
    unsigned int getNUM_OF_ALL_FACTORIES();
    unsigned int getNUM_OF_TILES_EACH_FAC();
    unsigned int getTOTAL_NUM_OF_GAME_ROUND();
    unsigned int getNUM_OF_PLAYERS();
    unsigned int getBROKEN_TILE_SOLT();
    
    bool isGreyMode();
    bool isStandardMode();

    // Any single tile indicator
    std::string getTILE_PATTERN();

    std::string getFACTORY_INDEX_PATTERN();

    std::string getSTORAGE_ROW_INDEX_PATTERN();

    // Literal "turn" followed by valid factory index (0 represents the broken
    // tile row), tile indicator, and storage row index, all separated by spaces
    std::string getTURN_PATTERN();

    // Exactly TOTAL_NUM_OF_TILE tile indicators, without separators
    std::string getINITIAL_TILES_PATTERN();
    std::string getMANNUAL_MOVE_PATTERN();
    std::string getTILE_BAG_MIDDLE_PATTERN();

};

#endif  // CONFIG_H
