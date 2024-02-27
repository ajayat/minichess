#pragma once

#include <string>

enum PieceType { NIL, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum Color { WHITE, BLACK, NOCOLOR };

struct PieceInfo {
    PieceType type;
    Color color;
};

/**
 * A square describe a location on the board
 */
struct Square {
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
    Color turn;
    int fifty_move_rule;
    bool white_castle;
    bool black_castle;
    Square en_passant;

    bool operator==(Position const &other) const;
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
