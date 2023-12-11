#include <iostream>
#include "Game.h"

int main() {
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    // Creating a window
    Game game;

    // Game loop
    while (game.running() && !game.getEndGame()) { // Keep the window open while it's not closed
 

        // Update
        game.update();

        // Rendering
        game.render();

    }

    return 0;
}
