#pragma once

#include "position.hpp"
#include <iostream>
#include <string>
#include <vector>

#define NCOL 8
#define NROW 8

/**
 * Abstract class that represents a piece on the board.
 */
class Piece
{
  public:
    Piece(PieceType type, std::string const name, Color color);
    Piece(Piece const &other);
    virtual ~Piece() = default;

    Color color() const { return _color; }

    PieceType type() const { return _type; }

    std::string const name() const { return _name; }

    void print();
    virtual std::vector<Square> const
    pseudo_legal_moves(Position const &position, Square const &from) const = 0;

  private:
    Color _color;
    std::string _name;
    PieceType _type;
};

class King : public Piece
{
  public:
    King(Color color) : Piece(KING, "\u265A", color) {}

    ~King() override = default;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Queen : public Piece
{
  public:
    Queen(Color color) : Piece(QUEEN, "\u265B", color) {}

    ~Queen() override = default;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Rook : public Piece
{
  public:
    Rook(Color color) : Piece(ROOK, "\u265C", color) {}

    ~Rook() override = default;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Bishop : public Piece
{
  public:
    Bishop(Color color) : Piece(BISHOP, "\u265D", color) {}

    ~Bishop() override = default;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Knight : public Piece
{
  public:
    Knight(Color color) : Piece(KNIGHT, "\u265E", color) {}

    ~Knight() override = default;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Pawn : public Piece
{
  public:
    Pawn(Color color) : Piece(PAWN, "\u265F", color) {}

    ~Pawn() override = default;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};
