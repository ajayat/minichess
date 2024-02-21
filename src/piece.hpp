#pragma once

#include "position.hpp"
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
    std::string const name;
    PieceType type;

  public:
    Piece(PieceType type, std::string const name, Color color);
    Piece(Piece const &other);
    virtual ~Piece() = default;

    Color color() const { return _color; }

    virtual void print() = 0;
    virtual std::vector<Square> const
    pseudo_legal_moves(Position const &position, Square const &from) const = 0;

  private:
    Color _color;
};

class King : public Piece
{
  public:
    King(Color color) : Piece(KING, "\u265A", color){};
    void print() override;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Queen : public Piece
{
  public:
    Queen(Color color) : Piece(QUEEN, "\u265B", color){};
    void print() override;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Rook : public Piece
{
  public:
    Rook(Color color) : Piece(ROOK, "\u265C", color){};
    void print() override;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Bishop : public Piece
{
  public:
    Bishop(Color color) : Piece(BISHOP, "\u265D", color){};
    void print() override;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Knight : public Piece
{
  public:
    Knight(Color color) : Piece(KNIGHT, "\u265E", color){};
    void print() override;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};

class Pawn : public Piece
{
  public:
    Pawn(Color color) : Piece(PAWN, "\u265F", color){};
    void print() override;
    std::vector<Square> const
    pseudo_legal_moves(Position const &position,
                       Square const &from) const override;
};
