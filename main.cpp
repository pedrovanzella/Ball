#include <iostream>
#include "config.h"
#include "include/game.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Version " << ball_VERSION_MAJOR << "." << ball_VERSION_MINOR << endl;

    Dolly::Game game;
    game.Run();

    // release the resources here

    return 0;
}
