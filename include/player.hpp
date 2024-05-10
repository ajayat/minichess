#pragma once

#include <string>
#include <vector>

#include "position.hpp"

enum PlayerType { HUMAN, ENGINE };

enum Status { QUIT, CANCEL, DRAW, RESIGN, MOVE };

struct ResponseStatus {
    Status const status;
    std::string const move; /* Optional UCI move */
};

/**
 * @brief Abstract class that represents a player.
 */
class Player
{
  public:
    /**
     * @brief Construct a new Player object.
     * @param name The player's name.
     * @param color The player's color.
     * @param type The player's type (HUMAN or ENGINE)
     */
    Player(std::string const &name, Color const color, PlayerType const type);

    virtual ~Player() = default;
    /**
     * @brief Wait for a move from the player.
     * @param position The current position.
     * @return The response status.
     * @see ResponseStatus
     */
    virtual ResponseStatus wait_move(Position const &position) = 0;

    std::string const &name() const;

    Color color() const;

  public:
    PlayerType const type;

  protected:
    std::string _name;
    Color _color;
};

/**
 * @brief Represents the engine.
 * @details Only Stockfish is supported.
 */
class Engine : public Player
{
  public:
    /**
     * @brief Construct a new Engine object.
     * @details The constructor initializes the engine and the communication via
     * pipes.
     * @param name The engine's name.
     * @param color The engine's color.
     */
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
    /**
     * @brief Ask the player which piece to promote.
     * @see PieceType
     */
    PieceType wait_promotion();

  private:
    /**
     * @brief Check if the UCI move is syntactically correct.
     * @param uci The move in UCI format (e.g. e2e4).
     */
    bool check(std::string &uci);
};
