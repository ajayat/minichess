#include <iostream>

#include "game.hpp"

int main()
{
    Player *white = new Human("Alice", WHITE);
    Player *black = new Human("Bob", BLACK);
    Game game(white, black);
    game.show();

    while (game.status() == ONGOING) {
        game.wait(game.current());
        game.show();
    }
    std::cout << std::endl << game.result() << std::endl;
    return 0;
}
