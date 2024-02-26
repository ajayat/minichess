#pragma once

#include <string>
#include <vector>

#include "position.hpp"

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
    Player(std::string const &name, Color color);
    virtual ~Player() = default;

    virtual ResponseStatus wait(std::vector<Position> const &_history) = 0;
    std::string const &name() const;
    Color color() const;

  protected:
    std::string _name;
    Color _color;
};

class Engine : public Player
{
  public:
    Engine(std::string const name, Color color);
    ~Engine() override = default;

    ResponseStatus wait(std::vector<Position> const &_history) override;
};

class Human : public Player
{
  public:
    Human(std::string const name, Color color);
    ~Human() override = default;

    ResponseStatus wait(std::vector<Position> const &_history) override;

  private:
    bool check(std::string const &uci) const;
};
