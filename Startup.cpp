#include <iostream>
#include <fstream>
#include <cstring>
#include "Startup.hpp"
#include "Game.hpp"
#include "tools.hpp"

Startup::Startup(int argc, char* argv[]) : game(0, 0) {
    cout << "Welcome to Kalah!" << endl;

    if (argc == 2 && strcmp(argv[1], "-r") == 0) {
        ifstream file("kalah.state");

        if (!file.is_open()) {
            fatal("File read error: unable to open kalah.state file");
        }

        string token;
        int houses;

        if (file >> token) {
            try {
                houses = stoi(token);
            } catch (const invalid_argument&) {
                fatal("File read error: first token is not an integer");
            } catch (const out_of_range&) {
                fatal("File read error: first token is out of integer range");
            }
        } else {
            fatal("File read error: missing first token");
        }

        if (file >> token) {
            if (token.size() > 1 || (token != "N" && token != "S")) {
                fatal("File read error: invalid active player label");
            }
        } else {
            fatal("File read error: missing second token");
        }

        Snapshot ss = Snapshot(file, houses, token.at(0));
        game = Game(houses, 0);
        game.restoreState(ss);
    } else if (argc == 3) {
        try {
            int numHouses = stoi(argv[1]);
            int numSeeds = stoi(argv[2]);
            
            game = Game(numHouses, numSeeds);
        } catch (const invalid_argument&) {
            cout << "Argument error: numHouses and numSeeds must be integers" << endl;
        } catch (const out_of_range&) {
            cout << "Arugment error: numHouses and numSeeds must be within integer range" << endl;
        }
    } else {
        fatal("Usage (2 options):\n(1)\tkalah numHouses numSeeds\n(2)\tkalah -r");
    }
}