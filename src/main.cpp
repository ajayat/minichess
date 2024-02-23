#include <iostream>

#include "game.hpp"

int main()
{
    Game game(new Human(), new Human());
    while (true) {
        game.show();
        Move move = game.wait_player();
        game.move(move);
    }
}
