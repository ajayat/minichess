#include "position.hpp"

#include <stdexcept>
#include <string>

Square::Square(int x, int y)
    : x{x}, y{y}, name(static_cast<char>('a' + x) + std::to_string(y + 1))
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        throw std::out_of_range("x and y must be between 0 and 7");
}
