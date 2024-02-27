#include <iostream>

#include "game.hpp"

int main()
{
    Player *white = new Human("Alice", WHITE);
    Player *black = new Human("Bob", BLACK);
    Game game(white, black);

    while (game.status() == ONGOING) {
        game.show();
        game.wait(game.current());
    }
    switch (game.status()) {
    case WHITE_WIN:
        std::cout << white->name() << "win." << std::endl;
        break;
    case BLACK_WIN:
        std::cout << black->name() << "win." << std::endl;
        break;
    case STALEMATE:
        std::cout << "Draw (Stalemate)" << std::endl;
        break;
    case FIFTY_MOVE_RULE:
        std::cout << "Draw (Fifty-move rule)" << std::endl;
        break;
    case THREEFOLD_REPETITION:
        std::cout << "Draw (Threefold repetition)" << std::endl;
        break;
    case ABORTED:
        std::cout << "Game aborted." << std::endl;
        break;
    default:
        std::cerr << "Game aborted for unknown reason." << std::endl;
    }
    return 0;
}
