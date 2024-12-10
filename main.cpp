#include <unistd.h>
#include "Startup.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Startup start(argc, argv);
    string line;
    
    if (isatty(fileno(stdin))) {
        start.game.playGame(nullptr); // Interactive user input
    } else {
        while (getline(cin, line)) {
            istringstream iss(line);
            start.game.playGame(&iss); // Parse file line-by-line for each game
        }
    }
}
