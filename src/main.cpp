#include <iostream>

#include "game.hpp"

int main()
{
    Player *white = new Human("Alice", WHITE);
    Player *black = new Human("Bob", BLACK);
    Game game(white, black);
    game.show();

    while (true) {
        ResponseStatus response = game.wait(game.current());
        switch (response.status) {
        case QUIT:
            std::cout << "Game aborted" << std::endl;
            return 0;
        case CANCEL:
            game.cancel();
            continue;
        case DRAW:
            std::cout << game.opponent(game.current())->name()
                      << ", accept draw ? (y/n): " << std::endl;

            char answer;
            std::cin >> answer;
            if (answer == 'y') {
                std::cout << "Draw." << std::endl;
                return 0;
            }
            std::cout << "Draw refused." << std::endl;
            continue;
        case RESIGN:
            std::cout << game.opponent(game.current())->name() << " wins."
                      << std::endl;
            return 0;
        case MOVE:
            if (!game.move(response.move))
                continue;
        }
        game.show();

        if (game.is_checkmate(game.current())) {
            std::cout << game.current()->name() << "lose." << std::endl;
            break;
        } else if (game.is_stalemate(game.current())) {
            std::cout << "Stalemate." << std::endl;
            break;
        }
    }
}
