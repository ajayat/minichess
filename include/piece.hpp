#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "position.hpp"

#define NCOL 8
#define NROW 8

/**
 * @brief Abstract class that represents a piece on the board.
 */
class Piece
{
  public:
    PieceType const type;
    std::string const name;
    Color const color;

  public:
    /**
     * @brief Construct a new Piece object.
     */
    Piece(PieceType const type, std::string const name, Color const color);
    Piece(Piece const &other);
    virtual ~Piece() = default;
    /**
     * @brief Return the piece in printable format.
     */
    std::string const render() const;
    /**
     * @brief Check if a move is pseudo-legal according to the piece.
     *
     * A pseudo-legal move is a move that doesn't verify if the player's
     * king is in check after the move.
     * @param position The current position.
     * @param from The square where the piece is.
     * @param to The square where the piece wants to go.
     * @return true if the move is pseudo-legal, false otherwise.
     */
    virtual bool is_pseudo_legal(Position const &position, Square const &from,
                                 Square const &to) const = 0;
};

class King : public Piece
{
  public:
    King(Color const color);
    ~King() override = default;

    /**
     * @brief Check if the king's move is a castling move.
     * @param position The current position.
     * @param from The square where the king is.
     * @param to The square where the king wants to go.
     * @return true if the move is a castling move, false otherwise.
     */
    bool is_castling(Position const &position, Square const &from,
                     Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Queen : public Piece
{
  public:
    Queen(Color const color);
    ~Queen() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Rook : public Piece
{
  public:
    Rook(Color const color);
    ~Rook() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Bishop : public Piece
{
  public:
    Bishop(Color const color);
    ~Bishop() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Knight : public Piece
{
  public:
    Knight(Color const color);
    ~Knight() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Pawn : public Piece
{
  public:
    Pawn(Color const color);
    ~Pawn() override = default;

    /**
     * @brief Check if the pawn's move is an en passant move.
     *
     * @param position The current position.
     * @param from The square where the pawn is.
     * @param to The square where the pawn wants to go.
     * @return true if the move is an en passant move, false otherwise.
     */
    bool is_en_passant(Position const &position, Square const &from,
                       Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};
