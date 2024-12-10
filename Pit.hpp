#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "Player.hpp"

using namespace std;

class Pit {
private:
    Player* owner;
    int number;
    int seeds;
    string label;
    Pit* next;
    Pit* opposite;

public:
    Pit();
    Pit(Player* p, int n, int s, const string& l, Pit* next, Pit* opposite);
    int getSeeds();
    Pit* getOpposite();
    void addSeed();
    void addSeeds(int s);
    int removeSeeds();
    string getLabel();
    friend ostream& operator<<(ostream& os, const Pit& pit);
};
