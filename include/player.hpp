#pragma once

#include <string>
#include <vector>

#include "position.hpp"

enum PlayerType { HUMAN, ENGINE };

enum Status { QUIT, CANCEL, DRAW, RESIGN, MOVE };

struct ResponseStatus {
    Status const status;
    std::string const move;
};

/**
 * Abstract class that represents a player.
 */
class Player
{
  public:
    Player(std::string const &name, Color const color, PlayerType const type);
    virtual ~Player() = default;

    virtual ResponseStatus wait_move(Position const &position) = 0;
    std::string const &name() const;
    Color color() const;

  public:
    PlayerType const type;

  protected:
    std::string _name;
    Color _color;
};

class Engine : public Player
{
  public:
    Engine(std::string const name, Color const color);
    ~Engine() override;

    ResponseStatus wait_move(Position const &position) override;

  private:
    int _engine[2];
    int _cli[2];
    pid_t _pid;
};

class Human : public Player
{
  public:
    Human(std::string const name, Color color);
    ~Human() override = default;

    ResponseStatus wait_move(Position const &position) override;
    PieceType wait_promotion();

  private:
    bool check(std::string &uci);
};
