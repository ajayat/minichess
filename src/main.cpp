#include <iostream>

#include "game.hpp"

int main(int argc, char const *argv[])
{
    Player *white = new Human("Adrien", WHITE);
    Player *black;
    if (argc == 2 && std::string(argv[1]) == "--engine")
        black = new Engine("Stockfish", BLACK);
    else
        black = new Human("Bob", BLACK);
    Game game(white, black);

    while (game.status() == ONGOING) {
        if (game.current()->type == HUMAN)
            game.show();
        game.wait(game.current());
    }
    game.show();

    std::cout << std::endl << game.result() << std::endl;
    return 0;
}