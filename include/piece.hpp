#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "position.hpp"

#define NCOL 8
#define NROW 8

/**
 * Abstract class that represents a piece on the board.
 */
class Piece
{
  public:
    Color const color;
    PieceType const type;
    std::string const name;

  public:
    Piece(PieceType const type, std::string const name, Color const color);
    Piece(Piece const &other);
    virtual ~Piece() = default;

    std::string const render() const;
    virtual bool is_pseudo_legal(Position const &position, Square const &from,
                                 Square const &to) const = 0;
};

class King : public Piece
{
  public:
    King(Color const color);
    ~King() override = default;

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

    bool is_en_passant(Position const &position, Square const &from,
                       Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};
