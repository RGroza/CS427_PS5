#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Kalah.hpp"
#include "Snapshot.hpp"

using namespace std;

class Game {
private:
    Kalah kalah;
    bool printBoard;
public:
    Game(int numHouses, int numSeeds);
    void doMove(string token);
    void playGame(istringstream* iss);
    void saveState();
    void restoreState(const Snapshot& ss);
};
