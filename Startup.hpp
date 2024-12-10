#pragma once
#include "Game.hpp"
#include "Exception.hpp"
#include "tools.hpp"

using namespace std;

class Startup {
public:
    Game game;
    Startup(int argc, char* argv[]);
};