#include "position.hpp"

#include <stdexcept>
#include <string>

Square::Square() noexcept : x{-1}, y{-1}, name("EMPTY") {}

Square::Square(int file, int rank)
    : x{file}, y{rank},
      name(static_cast<char>('a' + file) + std::to_string(rank + 1))
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

bool Square::operator==(Square const &other) const
{
    return x == other.x && y == other.y;
}

Move::Move(Square from, Square to, PieceType promotion)
    : from(from), to(to), promotion(promotion)
{}

Move::Move(std::string const uci)
{
    if (uci.size() != 4 && uci.size() != 5)
        throw std::invalid_argument("UCI must be 4 or 5 characters long");

    from = uci.substr(0, 2);
    to = uci.substr(2, 2);

    if (uci.size() == 5) {
        if (uci[4] == 'q')
            promotion = QUEEN;
        else if (uci[4] == 'r')
            promotion = ROOK;
        else if (uci[4] == 'b')
            promotion = BISHOP;
        else if (uci[4] == 'n')
            promotion = KNIGHT;
        else
            throw std::invalid_argument("Invalid promotion");
    }
}

std::string const Move::to_uci() const
{
    return from.name + to.name;
}
