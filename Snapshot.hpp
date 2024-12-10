#pragma once
#include <vector>
#include "Player.hpp"

using namespace std;

class Kalah;

class Snapshot {
private:
    Player activePlayer;
    vector<int> seeds;
    int houses;

public:
    Snapshot(istream& in, int houses, char label);
    Snapshot(const Kalah& kg);
    Player getActivePlayer() const;
    const vector<int>& getSeedsState() const;
    ostream& print(ostream& out) const;
    istream& read(istream& in);
};
