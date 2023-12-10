#include <iostream>
#include "Game.h"

int main() {
    // Creating a window
    Game game();

    // Game loop
    while (Game.running()) { // Keep the window open while it's not closed
 

        // Update
        game.update();

     // Rendering
     game.render();



    return 0;
}
