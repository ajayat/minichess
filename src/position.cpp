#include "position.hpp"

#include <stdexcept>
#include <string>

Square::Square(int x, int y)
    : x{x}, y{y}, name(static_cast<char>('a' + x) + std::to_string(y + 1))
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        throw std::out_of_range("x and y must be between 0 and 7");
}

Square::Square(std::string const name)
    : x(name[0] - 'a'), y(name[1] - '1'), name(name)
{
    if (name.size() != 2)
        throw std::invalid_argument("name must be 2 characters long");
    if (x < 0 || x > 7 || y < 0 || y > 7)
        throw std::out_of_range("x and y must be between 0 and 7");
}

Move::Move(std::string const uci)
    : _from(uci.substr(0, 2)), _to(uci.substr(2, 2))
{
    if (uci.size() != 4)
        throw std::invalid_argument("UCI must be 4 characters long");
}