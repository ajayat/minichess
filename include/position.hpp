#pragma once

#include <string>

enum PieceType { NIL, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum Color { WHITE, BLACK, NOCOLOR };

enum Castling { KINGSIDE = 0, QUEENSIDE = 1 };

struct PieceInfo {
    PieceType type;
    Color color;
};

/**
 * A square describe a location on the board
 */
class Square
{
  public:
    int x;  // file
    int y;  // rank
    std::string name;

    Square() noexcept;
    Square(int file, int rank);
    Square(std::string const name);

    bool operator==(Square const &other) const;
};

/**
 * A position is a board state
 */
struct Position {
    PieceInfo board[8][8];
    Square en_passant;
    Color turn;
    bool castling[2][2];  // [color][side]
    int fifty_move_rule;
    int fullmove_number;

    bool operator==(Position const &other) const;
    std::string const to_fen() const;
    std::string const to_pgn() const;
};

/**
 * Aggregates movement information
 */
class Move
{
  public:
    Square from;
    Square to;
    PieceType promotion = NIL;

  public:
    Move(Square from, Square to, PieceType promotion = NIL);
    Move(std::string const uci);
    std::string const to_uci() const;
};
