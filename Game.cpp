#include "Game.hpp"
#include <iostream>
#include <fstream>

Game::Game(int numHouses, int numSeeds) : kalah(numHouses, numSeeds), printBoard(true) {}

void Game::doMove(string token) {
    if (printBoard) {
        kalah.showBoard();
    }

    if (token == "q") {
        cout << endl << "Saving and quitting game at user's request\nGame over -- goodbye!" << endl;
        saveState();
        exit(EXIT_SUCCESS);
    }

    try {
        int move = stoi(token);
        printBoard = kalah.doMove(move);
    } catch (const invalid_argument&) {
        cout << endl << "Bad input (" << token << ") -- please try again" << endl;
    }
}

void Game::playGame(istringstream* iss) {
    if (iss == nullptr) {
        string line;
        while (std::getline(cin, line)) {
            istringstream iss(line);
            playGame(&iss);
        }
    } else {
        string token;
        while (*iss >> token && !kalah.isGameOver()) {
            doMove(token);
        }

        // Query Kalah to check if game is over, print end game message
        if (kalah.isGameOver()) {
            cout << endl << "----------\nGame over -- " << kalah << "  -->  ";
            Outcome gameOutcome = kalah.getGameOutcome();
            if (gameOutcome == Outcome::NorthWin) {
                cout << "North wins!" << endl;
            } else if (gameOutcome == Outcome::SouthWin) {
                cout << "South wins!" << endl;
            } else {
                cout << "Game is a tie!" << endl;
            }
            exit(EXIT_SUCCESS);
        }

        if (printBoard) {
            kalah.showBoard();
        }
    }

    printBoard = false;
}

void Game::saveState() {
    Snapshot ss = Snapshot(kalah);
    ofstream file("kalah.state");
    ss.print(file);
}

void Game::restoreState(const Snapshot& ss) {
    kalah.restoreState(ss);
}