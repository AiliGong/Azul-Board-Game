#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <fstream>
#include <set>

#include "TileBag.h"
#include "Player.h"
#include "Turn.h"

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

  void setInitialTiles(const TileBag* initial_tiles);

  TileBag* getInitialTiles() const;
  std::vector<Player*> getPlayers() const;
  std::vector<const Turn*> getTurns() const;

  void addPlayer(std::string player_name);

 private:
  void readSaveFile(std::istream& file);
  void writeSaveFile(std::ostream& out) const;
  TileBag* initial_tiles;
  std::set<std::string> player_names;
  std::vector<const Turn*> turns;
};

#endif  // GAMEHISTORY_H
