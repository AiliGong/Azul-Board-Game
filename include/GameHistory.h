#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <fstream>
#include <set>

#include "TileBag.h"
#include "Player.h"
#include "Turn.h"
#include "Config.h"

class GameHistory {
 public:
  GameHistory();

  GameHistory(TileBag* initial_tiles, std::set<std::string> player_names);
  GameHistory(GameHistory& other);
  ~GameHistory();

  static GameHistory* loadFromFile(std::string filename);

  void addTurn(const Turn* turn);
  void print() const;
  void print(std::ostream&) const;
  void saveToFile(const std::string filename) const;
  int numPlayers() const;
  int numTurns() const;

  void setInitialTiles(TileBag* initial_tiles);

  TileBag* getInitialTiles() const;
  std::vector<Player*> getPlayers() const;
  std::vector<const Turn*> getTurns() const;

  void addPlayer(std::string player_name);
  void setRandomSeed(int random_seed);
  void addTileBagInGame(TileBag* tile_bag);
  Config* getConfig() const;
  void setConfig(Config* config);
  int getRandomSeed() const;
  bool readFromFile() const;
  void resetAfterLoading();
  void addMannaulMove(const unsigned int move);
  std::vector<int> getMannualMoves();
  std::vector<TileBag*> getBagsInTheMiddle();

 private:
  void readSaveFile(std::istream& file);
  void readSaveFileAdvanced(std::istream& file);

  void writeSaveFile(std::ostream& out) const;
  void writeSaveFileStandard(std::ostream& out) const;
  void writeSaveFileAdvanced(std::ostream& out) const;


  TileBag* initial_tiles;
  std::set<std::string> player_names;
  std::vector<const Turn*> turns;
  std::vector<int> mannual_moves;
  int random_seed;
  std::vector<TileBag*> tile_bags_in_game;
  Config* config;
  bool read_from_file;

};

#endif  // GAMEHISTORY_H
