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
 * @brief A square describes a location on the board.
 */
struct Square {
    int x; /* file */
    int y; /* rank */
    std::string name;

    Square() noexcept;
    Square(int file, int rank);
    Square(std::string const name);

    bool operator==(Square const &other) const;
};

/**
 * @brief A position is a board state (pieces, turn, castling rights, etc.).
 */
struct Position {
    PieceInfo board[8][8];
    Square en_passant;
    Color turn;
    bool castling[2][2]; /* castling[COLOR][SIDE] */
    int fifty_move_rule;
    int fullmove_number;

    bool operator==(Position const &other) const;
    /**
     * @brief Describe a position from a string in FEN format.
     */
    std::string const to_fen() const;
    /**
     * @brief Describe a position from a string in PGN format.
     */
    std::string const to_pgn() const;
};

/**
 * @brief Aggregates movement information.
 */
struct Move {
    Square from;
    Square to;
    PieceType promotion = NIL;

    Move(Square from, Square to, PieceType promotion = NIL);
    /**
     * @brief Describe a move from a string in UCI format.
     * @param uci The move in UCI format (e.g. e2e4).
     */
    Move(std::string const uci);

    std::string const to_uci() const;
};
