#pragma once

#include <array>
#include <string>
#include <vector>

#include "piece.hpp"
#include "position.hpp"

class Move
{
  public:
    Square const from;
    Square const to;

  public:
    Move(Square const &from, Square const &to) : from(from), to{to} {};
    Move(std::string const &uci)
        : from{uci.substr(0, 2)}, to{uci.substr(2, 2)} {};
    Move(Move const &other) = default;
    ~Move();

    std::string const to_uci() const { return from.name + to.name; }

    bool operator==(Move const &other) const;
    bool operator!=(Move const &other) const;
};

class Board
{
  public:
    Board();
    Board(Board const &other) = delete;
    Board(Board &&other) = default;
    ~Board();

    void print() const;
    Move const move(Move const &move);
    Position const position() const;

    bool is_pseudo_legal(Move const &move) const;
    bool is_legal(Move const &move) const;
    bool is_capture(Move const &move) const;
    bool is_check(Move const &move, Color color) const;

    Piece *operator()(Square const &square) const;

  private:
    Color _turn;
    Piece *_board[NROW][NCOL];
};
