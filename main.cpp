#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Startup.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Startup start = Startup(argc, argv);
    string line;
    
    if (isatty(fileno(stdin))) {
        start.game.playGame(nullptr);
    } else {
        while (getline(cin, line)) {
            istringstream iss(line);
            start.game.playGame(&iss);
        }
    }
}
