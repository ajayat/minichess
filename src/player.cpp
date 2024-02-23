#include "player.hpp"

Move const Engine::wait(std::vector<Position> const &_history)
{
    return Move("e2e4");
}

Move const Human::wait(std::vector<Position> const &_history)
{
    return Move("e7e5");
}