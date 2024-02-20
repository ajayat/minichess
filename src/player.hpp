#pragma once

#include "position.hpp"
#include <string>
#include <vector>

/**
 * Abstract class that represents a player.
 */
class Player
{
  public:
    std::string const name;
    std::string const color;

  public:
    Player(std::string const pseudo, Color color);
    virtual void wait(std::vector<Position> const &_history) = 0;
};

class Engine : public Player
{
  public:
    Engine();
    void wait(std::vector<Position> const &_history) override;
};

class Human : public Player
{
  public:
    Human();
    void wait(std::vector<Position> const &_history) override;

  private:
    bool check(std::string const &uci) const;
};
