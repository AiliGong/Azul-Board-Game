#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <fstream>
#include <set>

#include "TileBag.h"
#include "Player.h"
#include "Turn.h"
#include "Constants.h"

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
  Constants* getConstant() const;
  void setConstant(Constants* constant);



 private:
  void readSaveFile(std::istream& file);
  void writeSaveFile(std::ostream& out) const;
  TileBag* initial_tiles;
  std::set<std::string> player_names;
  std::vector<const Turn*> turns;
  int random_seed;
  std::vector<TileBag*> tile_bags_in_game;
  Constants* constant;

};

#endif  // GAMEHISTORY_H
