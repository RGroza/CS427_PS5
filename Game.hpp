#pragma once
#include <sstream>
#include <string>
#include "Kalah.hpp"
#include "Snapshot.hpp"
#include "Exception.hpp"

using namespace std;

class Game {
private:
    Kalah kalah;
    bool printBoard;
public:
    Game(int numHouses, int numSeeds);
    void doMove(string token);
    void playGame(istringstream* iss);
    void saveState() const;
    void restoreState(const Snapshot& ss);
};
