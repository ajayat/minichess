#include <algorithm>
#include <iostream>

#include "board.hpp"
#include "piece.hpp"

Board::Board() : _board{nullptr}, _turn(WHITE)
{
    // Initial position of the pieces
    _board[0][0] = new Rook(WHITE);
    _board[1][0] = new Knight(WHITE);
    _board[2][0] = new Bishop(WHITE);
    _board[3][0] = new Queen(WHITE);
    _board[4][0] = new King(WHITE);
    _board[5][0] = new Bishop(WHITE);
    _board[6][0] = new Knight(WHITE);
    _board[7][0] = new Rook(WHITE);

    _board[0][7] = new Rook(BLACK);
    _board[1][7] = new Knight(BLACK);
    _board[2][7] = new Bishop(BLACK);
    _board[3][7] = new Queen(BLACK);
    _board[4][7] = new King(BLACK);
    _board[5][7] = new Bishop(BLACK);
    _board[6][7] = new Knight(BLACK);
    _board[7][7] = new Rook(BLACK);

    for (int x = 0; x < 8; x++) {
        _board[x][1] = new Pawn(WHITE);
        _board[x][6] = new Pawn(BLACK);
    }
}

Board::~Board()
{
    for (int i = 0; i < NROW; i++) {
        for (int j = 0; j < NCOL; j++)
            delete _board[i][j];
    }
}

void Board::print() const
{
    std::string space5 = std::string(5, ' ');
    std::cout << std::endl;
    std::cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+"
              << std::endl;
    for (int y = NCOL - 1; y >= 0; y--) {
        std::cout << y + 1 << " ";  // numérotation ligne dans affichage
        for (int x = 0; x < NROW; x++) {
            std::cout << "|";
            if (_board[y][x] == nullptr)
                std::cout << space5;
            else
                _board[y][x]->print();
        }
        std::cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+"
                  << std::endl;
    }
    std::cout << "     a     b     c     d     e     f     g     h    "
              << std::endl;
}

Color Board::turn() const
{
    return _turn;
}

Piece *Board::operator()(Square const &square) const
{
    return _board[square.x][square.y];
}

void Board::move(Square const &from, Square const &to)
{
    Piece *piece = _board[from.y][from.x];
    _board[to.y][to.x] = piece;
    _board[from.y][from.x] = nullptr;
}

bool Board::is_pseudo_legal(Square const &from, Square const &to) const
{
    Piece *piece = _board[from.x][from.y];
    std::vector<Square> const squares =
      piece->pseudo_legal_moves(position(), from);

    return std::find(squares.begin(), squares.end(), to) != squares.end();
}

bool Board::is_legal(Square const &from, Square const &to) const
{
    return is_pseudo_legal(from, to) && !is_check(from, to, _turn);
}

bool Board::is_capture(Square const &from, Square const &to) const
{
    return is_pseudo_legal(from, to) && _board[to.x][to.y] != nullptr;
}

Square const Board::find_king(Color color) const
{
    for (int x = 0; x < NCOL; x++) {
        for (int y = 0; y < NROW; y++) {
            if (_board[x][y]->type() == KING && _board[x][y]->color() == color)
                return Square(x, y);
        }
    }
    throw std::runtime_error("King not found");
}

bool Board::is_check(Square const &from, Square const &to, Color color) const
{
    Square king = find_king(color);
    for (int x = 0; x < NCOL; x++) {
        for (int y = 0; y < NROW; y++) {
            if (is_capture(Square(x, y), king))
                return true;
        }
    }
    return false;
}

Position const Board::position() const
{
    Position position = Position{
      {NIL},
      _turn,
      _fifty_move_rule,
      _white_castle,
      _black_castle,
      _en_passant,
    };

    for (int i = 0; i < 64; i++) {
        int y = i / 8;
        int x = i % 8;
        if (_board[y][x] != nullptr)
            position.board[i] = _board[y][x]->type();
    }
    return position;
}

/*
bool Board::is_move(Square *from, Square *to, Pawn *piece) const
{
    int x1 = move->from()->x(), y1 = from->y();
    int x2 = to->x(), y2 = to->y();

    if (!to->is_empty() &&
        from->get_piece()->color() == to->get_piece()->color())
        return false;

    if (piece->color() == WHITE) {
        if (x1 == x2) {
            if (y1 == 1 && y2 == 3 && to->is_empty())
                return true; // first move of step 2
            if (y1 + 1 == y2 && to->is_empty())
                return true; // step of 1
            return false;
        }
        if (y2 == y1 + 1 && abs(x1 - x2) == 1) {
            if (to->is_empty()) { // en passant
                Piece *p = get(x2, y2 - 1)->get_piece();
                return (p->is_pawn() && p->n_moves() == 1);
            }
            return true; // capture
        }
        return false;
    }

    if (piece->color() == BLACK) {
        if (x1 == x2) {
            if (y1 == 6 && y2 == 4 && to->is_empty())
                return true; // first move of step 2
            if (y1 - 1 == y2 && to->is_empty())
                return true; // step of 1
            return false;
        }
        if (y2 == y1 - 1 && abs(x1 - x2) == 1) {
            if (to->is_empty()) { // en passant
                Piece *p = get(x2, y2 + 1)->get_piece();
                return (p->is_pawn() && p->n_moves() == 1);
            }
            return true; // capture
        }
        return false;
    }
    return false;
}

bool Board::is_move(Square *from, Square *to, Rook *piece) const
{
    int x1 = from->x(), y1 = from->y();
    int x2 = to->x(), y2 = to->y();

    if (x1 != x2 && y1 != y2)
        return false;

    if (x1 == x2) {
        int y_min = std::min(y1, y2);
        int y_max = std::max(y1, y2);
        for (int y = y_min + 1; y < y_max; y++) {
            if (!_board[x1][y]->is_empty())
                return false;
        }
    }
    if (y1 == y2) {
        int x_min = std::min(x1, x2);
        int x_max = std::max(x1, x2);
        for (int x = x_min + 1; x < x_max; x++) {
            if (!_board[x][y1]->is_empty())
                return false;
        }
    }
    return true;
}

bool Board::is_move(Square *from, Square *to, Knight *piece) const
{
    int x1 = from->x(), y1 = from->y();
    int x2 = to->x(), y2 = to->y();

    if (abs(x1 - x2) == 2 && abs(y1 - y2) == 1)
        return true;
    if (abs(x1 - x2) == 1 && abs(y1 - y2) == 2)
        return true;
    return false;
}
*/