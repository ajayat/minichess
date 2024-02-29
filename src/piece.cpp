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

King::King(Color color)
    : Piece(KING, (color == WHITE ? "\u2654" : "\u265a"), color)
{}

Queen::Queen(Color color)
    : Piece(QUEEN, (color == WHITE ? "\u2655" : "\u265b"), color)
{}

Rook::Rook(Color color)
    : Piece(ROOK, (color == WHITE ? "\u2656" : "\u265c"), color)
{}

Bishop::Bishop(Color color)
    : Piece(BISHOP, (color == WHITE ? "\u2657" : "\u265d"), color)
{}

Knight::Knight(Color color)
    : Piece(KNIGHT, (color == WHITE ? "\u2658" : "\u265e"), color)
{}

Pawn::Pawn(Color color)
    : Piece(PAWN, (color == WHITE ? "\u2659" : "\u265f"), color)
{}

bool is_pseudo_legal_diagonally(Position const &position, Square const &from,
                                Square const &to)
{
    if (std::abs(from.x - to.x) != std::abs(from.y - to.y))
        return false;
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
    return true;
}

bool is_pseudo_legal_horizontally(Position const &position, Square const &from,
                                  Square const &to)
{
    if (from.y != to.y || from.x == to.x)
        return false;
    int step = (to.x - from.x) > 0 ? 1 : -1;
    int x = from.x + step;

    while (x != to.x) {
        if (position.board[from.y][x].color != NOCOLOR)
            return false;
        x += step;
    }
    return true;
}

bool is_pseudo_legal_vertically(Position const &position, Square const &from,
                                Square const &to)
{
    if (from.x != to.x || from.y == to.y)
        return false;
    int step = (to.y - from.y) > 0 ? 1 : -1;
    int y = from.y + step;

    while (y != to.y) {
        if (position.board[y][from.x].color != NOCOLOR)
            return false;
        y += step;
    }
    return true;
}

bool King::is_castling(Position const &pos, Square const &from,
                       Square const &to) const
{
    if (pos.board[to.y][to.x].color != NOCOLOR)
        return false;

    if (from.name == "e1" && (to.name == "g1" || to.name == "c1"))
        return pos.castling[WHITE][to.name == "c1"]
               && is_pseudo_legal_horizontally(pos, from, to);

    else if (from.name == "e8" && (to.name == "g8" || to.name == "c8"))
        return pos.castling[BLACK][to.name == "c8"]
               && is_pseudo_legal_horizontally(pos, from, to);
    return false;
}

bool King::is_pseudo_legal(Position const &pos, Square const &from,
                           Square const &to) const
{
    Color color = pos.board[from.y][from.x].color;
    if (std::abs(from.x - to.x) <= 1 && std::abs(from.y - to.y) <= 1)
        return pos.board[to.y][to.x].color != color;

    return is_castling(pos, from, to);
}

bool Queen::is_pseudo_legal(Position const &pos, Square const &from,
                            Square const &to) const
{
    if (pos.board[to.y][to.x].color == pos.board[from.y][from.x].color)
        return false;
    return is_pseudo_legal_diagonally(pos, from, to)
           || is_pseudo_legal_horizontally(pos, from, to)
           || is_pseudo_legal_vertically(pos, from, to);
}

bool Rook::is_pseudo_legal(Position const &pos, Square const &from,
                           Square const &to) const
{
    if (pos.board[to.y][to.x].color == pos.board[from.y][from.x].color)
        return false;
    return is_pseudo_legal_horizontally(pos, from, to)
           || is_pseudo_legal_vertically(pos, from, to);
}

bool Bishop::is_pseudo_legal(Position const &pos, Square const &from,
                             Square const &to) const
{
    if (pos.board[to.y][to.x].color == pos.board[from.y][from.x].color)
        return false;
    return is_pseudo_legal_diagonally(pos, from, to);
}

bool Knight::is_pseudo_legal(Position const &pos, Square const &from,
                             Square const &to) const
{
    Color color = pos.board[from.y][from.x].color;
    int dx = std::abs(from.x - to.x);
    int dy = std::abs(from.y - to.y);
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
        return pos.board[to.y][to.x].color != color;
    return false;
}

bool Pawn::is_en_passant(Position const &pos, Square const &from,
                         Square const &to) const
{
    if (std::abs(to.y - from.y) == 1 && std::abs(to.x - from.x) == 1)
        return pos.en_passant != Square() && to == pos.en_passant;
    return false;
}

bool Pawn::is_pseudo_legal(Position const &pos, Square const &from,
                           Square const &to) const
{
    if (is_en_passant(pos, from, to))
        return true;

    Color color = pos.board[from.y][from.x].color;
    int dy = to.y - from.y;
    int dx = to.x - from.x;
    if (color == WHITE) {
        if ((dy == 1 && dx == 0) || (dy == 2 && dx == 0 && from.y == 1))
            return pos.board[to.y][to.x].color == NOCOLOR;  // move
        if (dy == 1 && std::abs(dx) == 1)
            return pos.board[to.y][to.x].color == BLACK;  // capture
    }
    else {
        if ((dy == -1 && dx == 0) || (dy == -2 && dx == 0 && from.y == 6))
            return pos.board[to.y][to.x].color == NOCOLOR;  // move
        if (dy == -1 && std::abs(dx) == 1)
            return pos.board[to.y][to.x].color == WHITE;  // capture
    }
    return false;
}
