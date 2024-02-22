#include <iostream>

#include "game.hpp"

Game::Game(Player* white, Player* black)
    : _board(new Board), _white(white), _black(black), _turn(WHITE)
{
    std::cout << "Game created" << std::endl;
}