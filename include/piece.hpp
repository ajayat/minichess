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
    Piece(PieceType type, std::string const name, Color color);
    Piece(Piece const &other);
    virtual ~Piece() = default;

    std::string to_pgn(bool view_color = true) const;
    void print() const;
    virtual bool is_pseudo_legal(Position const &position, Square const &from,
                                 Square const &to) const = 0;
};

class King : public Piece
{
  public:
    King(Color color);
    ~King() override = default;

    bool is_castling(Position const &position, Square const &from,
                     Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Queen : public Piece
{
  public:
    Queen(Color color);
    ~Queen() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Rook : public Piece
{
  public:
    Rook(Color color);
    ~Rook() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Bishop : public Piece
{
  public:
    Bishop(Color color);
    ~Bishop() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Knight : public Piece
{
  public:
    Knight(Color color);
    ~Knight() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Pawn : public Piece
{
  public:
    Pawn(Color color);
    ~Pawn() override = default;

    bool is_en_passant(Position const &position, Square const &from,
                       Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};
