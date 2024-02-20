#include <algorithm>
#include <iostream>

#include "board.hpp"
#include "piece.hpp"

Board::Board() : _board{nullptr}
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
    std::cout << "     a     b     c     d     e     f     g     h    "
              << std::endl;
    std::cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+"
              << std::endl;
    for (int y = 7; y >= 0; y--) {
        std::cout << y + 1 << " "; // numérotation ligne dans affichage
        for (int x = 0; x < NCOL; x++) {
            std::cout << "|";
            _board[y][x]->print();
        }
        std::cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        std::cout << std::endl;
    }
}

Piece *Board::operator()(Square const &square) const
{
    return _board[square.x][square.y];
}

Move const Board::move(Move const &move)
{
    Piece *piece = _board[move.from.x][move.from.y];
    _board[move.to.x][move.to.y] = piece;
    _board[move.from.x][move.from.y] = nullptr;
    return move;
}

bool Board::is_pseudo_legal(Move const &move) const
{
    Piece *piece = _board[move.from.x][move.from.y];
    std::vector<Square> const squares =
        piece->pseudo_legal_moves(position(), move.from);

    return std::find(squares.begin(), squares.end(), move.to) != squares.end();
}

bool Board::is_legal(Move const &move) const
{
    return is_pseudo_legal(move) && !is_check(move, _turn);
}

bool Board::is_capture(Move const &move) const
{
    return is_pseudo_legal(move) && _board[move.to.x][move.to.y] != nullptr;
}
