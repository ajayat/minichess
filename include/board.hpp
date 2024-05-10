#pragma once

#include <string>
#include <vector>

#include "piece.hpp"
#include "position.hpp"

/**
 * @brief Represents the chess board and manage the pieces.
 * @details The Board class is responsible for managing the chess board and the
 * pieces and gathering information about the chess position (board state) It
 * doesn't interact with the players.
 */
class Board
{
  public:
    /**
     * @brief Construct a new Board object.
     * @details The constructor initializes the board with the initial position
     * and sets the turn to WHITE.
     */
    Board();
    Board(Board const &other) = delete;
    /**
     * @brief Delete the remaining pieces and the Board object.
     */
    ~Board();
    /**
     * @brief Print the board to the standard output.
     * @details Print the board using ASCII characters and colors,
     * the board is flipped for the black player.
     */
    void print() const;
    /**
     * @brief Move a piece on the board.
     * @details It takes into account specific moves like capture, castling, en
     * passant, and promotion. It doesn't check if the move is legal.
     * @param move The move to be made.
     */
    void move(Move const &move);

    Color turn() const;

    Position const get_position() const;

    void set_position(Position const &position);
    /**
     * @brief Check if a move is pseudo-legal.
     * @details A pseudo-legal move is a move that doesn't verify if the
     * player's king is in check after the move.
     * @return true if the move is pseudo-legal, false otherwise.
     * @see is_legal
     */
    bool is_pseudo_legal(Move const &move) const;
    /**
     * @brief Check if a move is legal.
     * @details A legal move is a valid move according to the chess rules.
     * @return true if the move is legal, false otherwise.
     * @see is_pseudo_legal
     */
    bool is_legal(Move const &move);
    /**
     * @brief Check if a move capture an opponent's piece.
     * @return true if the move is a capture, false otherwise.
     */
    bool is_capture(Move const &move) const;
    /**
     * @brief Check if the player's king is in check.
     * @param color The color of the king.
     * @return true if the player's king is in check, false otherwise.
     */
    bool is_checked(Color const color) const;

    bool is_promotion(Move const &move) const;
    /**
     * @brief Overload the operator () to get a piece from a square like
     * board("a5").
     * @return A pointer to the piece on the square or nullptr if the square is
     * empty.
     */
    Piece *operator()(Square const &square) const;

  private:
    /**
     * @brief Check if a square is attacked by an opponent's piece.
     */
    bool is_attacked(Color const color, Square const &square) const;

    Piece *create_piece(PieceType const type, Color const color);
    /**
     * @brief Update the board after a move and delete the potentially captured
     * piece.
     */
    void _move(Square const &from, Square const &to);

  private:
    Piece *_board[NROW][NCOL];
    Position _position;
};
