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

    void print() const;
    virtual bool is_pseudo_legal(Position const &position, Square const &from,
                                 Square const &to) const = 0;
};

class King : public Piece
{
  public:
    King(std::string const name, Color color) : Piece(KING, name, color) {}

    ~King() override = default;

    bool is_castling(Position const &position, Square const &from,
                     Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Queen : public Piece
{
  public:
    Queen(std::string const name, Color color) : Piece(QUEEN, name, color) {}

    ~Queen() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Rook : public Piece
{
  public:
    Rook(std::string const name, Color color) : Piece(ROOK, name, color) {}

    ~Rook() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Bishop : public Piece
{
  public:
    Bishop(std::string const name, Color color) : Piece(BISHOP, name, color) {}

    ~Bishop() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Knight : public Piece
{
  public:
    Knight(std::string const name, Color color) : Piece(KNIGHT, name, color) {}

    ~Knight() override = default;

    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};

class Pawn : public Piece
{
  public:
    Pawn(std::string const name, Color color) : Piece(PAWN, name, color) {}

    ~Pawn() override = default;

    bool is_en_passant(Position const &position, Square const &from,
                       Square const &to) const;
    bool is_pseudo_legal(Position const &position, Square const &from,
                         Square const &to) const override;
};
