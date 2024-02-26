#include "piece.hpp"

Piece::Piece(PieceType type, std::string const name, Color color)
    : type(type), name(name), color(color)
{}

Piece::Piece(Piece const &other)
    : type(other.type), name(other.name), color(other.color)
{}

void Piece::print() const
{
    std::cout << name;
}

static bool is_pseudo_legal_diagonally(Position const &position,
                                       Square const &from, Square const &to)
{
    if (std::abs(from.x - to.x) != std::abs(from.y - to.y))
        return false;
    Color color = position.board[from.y][from.x].color;
    int step_x = (to.x - from.x) > 0 ? 1 : -1;
    int step_y = (to.y - from.y) > 0 ? 1 : -1;
    int x = from.x + step_x;
    int y = from.y + step_y;

    while (x != to.x && y != to.y) {
        if (position.board[y][x].color != NOCOLOR)
            return false;
        x += step_x;
        y += step_y;
    }
    return position.board[to.y][to.x].color != color;
}

bool is_pseudo_legal_horizontally(Position const &position, Square const &from,
                                  Square const &to)
{
    if (from.y != to.y || from.x == to.x)
        return false;
    Color color = position.board[from.y][from.x].color;
    int step = (to.x - from.x) > 0 ? 1 : -1;
    int x = from.x + step;

    while (x != to.x) {
        if (position.board[from.y][x].color != NOCOLOR)
            return false;
        x += step;
    }
    return position.board[to.y][to.x].color != color;
}

bool is_pseudo_legal_vertically(Position const &position, Square const &from,
                                Square const &to)
{
    if (from.x != to.x || from.y == to.y)
        return false;
    Color color = position.board[from.y][from.x].color;
    int step = (to.y - from.y) > 0 ? 1 : -1;
    int y = from.y + step;

    while (y != to.y) {
        if (position.board[y][from.x].color != NOCOLOR)
            return false;
        y += step;
    }
    return position.board[to.y][to.x].color != color;
}

bool King::is_castling(Position const &position, Square const &from,
                       Square const &to) const
{
    if (position.board[from.y][from.x].color == WHITE) {
        if (from == Square("e1") && to == Square("g1")
            || from == Square("e1") && to == Square("c1"))
            return position.white_castle;
    } else {
        if (from == Square("e8") && to == Square("g8")
            || from == Square("e8") && to == Square("c8"))
            return position.black_castle;
    }
    return false;
}

bool King::is_pseudo_legal(Position const &position, Square const &from,
                           Square const &to) const
{
    Color color = position.board[from.y][from.x].color;
    if (std::abs(from.x - to.x) ^ std::abs(from.y - to.y))
        return position.board[to.y][to.x].color != color;

    return this->is_castling(position, from, to);
}

bool Queen::is_pseudo_legal(Position const &position, Square const &from,
                            Square const &to) const
{
    return is_pseudo_legal_diagonally(position, from, to)
           || is_pseudo_legal_horizontally(position, from, to)
           || is_pseudo_legal_vertically(position, from, to);
}

bool Rook::is_pseudo_legal(Position const &position, Square const &from,
                           Square const &to) const
{
    return is_pseudo_legal_horizontally(position, from, to)
           || is_pseudo_legal_vertically(position, from, to);
}

bool Bishop::is_pseudo_legal(Position const &position, Square const &from,
                             Square const &to) const
{
    return is_pseudo_legal_diagonally(position, from, to);
}

bool Knight::is_pseudo_legal(Position const &position, Square const &from,
                             Square const &to) const
{
    Color color = position.board[from.y][from.x].color;
    int dx = std::abs(from.x - to.x);
    int dy = std::abs(from.y - to.y);
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
        return position.board[to.y][to.x].color != color;
    return false;
}

bool Pawn::is_en_passant(Position const &position, Square const &from,
                         Square const &to) const
{
    if (std::abs(to.y - from.y) == 1 && std::abs(to.x - from.x) == 1)
        return position.en_passant != Square(0, 0) && to == position.en_passant;
    return false;
}

bool Pawn::is_pseudo_legal(Position const &position, Square const &from,
                           Square const &to) const
{
    Color color = position.board[from.y][from.x].color;
    int dy = to.y - from.y;
    int dx = to.x - from.x;
    if (color == WHITE) {
        if ((dy == 1 && dx == 0) || (dy == 2 && dx == 0 && from.y == 1))
            return position.board[to.y][to.x].color == NOCOLOR;  // move
        if (dy == 1 && std::abs(dx) == 1)
            return position.board[to.y][to.x].color == BLACK;  // capture
    } else {
        if ((dy == -1 && dx == 0) || (dy == -2 && dx == 0 && from.y == 6))
            return position.board[to.y][to.x].color == NOCOLOR;  // move
        if (dy == -1 && std::abs(dx) == 1)
            return position.board[to.y][to.x].color == WHITE;  // capture
    }
    return this->is_en_passant(position, from, to);
}
