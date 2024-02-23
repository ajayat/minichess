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
    Player(std::string const pseudo, Color color) : _name(pseudo), _color(color)
    {}

    virtual ~Player() = default;
    virtual Move const wait(std::vector<Position> const &_history) = 0;

    Color color() const { return _color; }

    std::string const name() const { return _name; }

  private:
    Color _color;
    std::string _name;
};

class Engine : public Player
{
  public:
    Engine();
    ~Engine() override = default;
    Move const wait(std::vector<Position> const &_history) override;
};

class Human : public Player
{
  public:
    Human() : Player("Human", Color::WHITE) {}

    ~Human() override = default;
    Move const wait(std::vector<Position> const &_history) override;

  private:
    bool check(std::string const &uci) const;
};
