#include <iostream>

#include "player.hpp"

Player::Player(std::string const &name, Color color)
    : _name(name), _color(color)
{}

std::string const &Player::name() const
{
    return _name;
}

Color Player::color() const
{
    return _color;
}

Engine::Engine(std::string const name, Color color) : Player(name, color) {}

ResponseStatus Engine::wait(std::vector<Position> const &_history)
{
    return ResponseStatus{QUIT};
}

Human::Human(std::string const name, Color color) : Player(name, color) {}

bool Human::check(std::string const &uci) const
{
    try {
        Move move(uci);
        return true;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

ResponseStatus Human::wait(std::vector<Position> const &_history)
{
    std::string uci;
    do {
        std::cout << _name << ", enter your move: ";
        std::cin >> uci;
        if (uci == "/quit")
            return ResponseStatus{QUIT};
        if (uci == "/cancel")
            return ResponseStatus{CANCEL};
        if (uci == "/draw")
            return ResponseStatus{DRAW};
        if (uci == "/resign")
            return ResponseStatus{RESIGN};
    }
    while (!check(uci));

    return ResponseStatus{MOVE, uci};
}