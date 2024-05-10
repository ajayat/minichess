#pragma once

#include <vector>

#include "board.hpp"
#include "player.hpp"

enum GameStatus {
    ONGOING,
    WHITE_WIN,
    BLACK_WIN,
    STALEMATE,
    FIFTY_MOVE_RULE,
    THREEFOLD_REPETITION,
    ABORTED
};

/**
 * @brief Interacts with the players and the board.
 * @details The Game class is responsible for managing the game and the players.
 */
class Game
{
  public:
    /**
     * @brief Construct a new Game object.
     * @details The constructor initializes the game with the two players
     * and call the Board constructor.
     */
    Game(Player *white, Player *black);
    /**
     * @brief Delete the players and the Game object.
     */
    ~Game();
    /**
     * @brief Show the board to the standard output.
     * @see Board::print
     */
    void show() const;
    /**
     * @brief Wait for a move from the player.
     * @details The wait method waits for a move from the player in UCI format
     * and applies it.
     * @param player The player who has to play.
     */
    void wait(Player *player);

    Player *current() const;

    Player *opponent(Player *player) const;

    GameStatus status() const;
    /**
     * @brief Get the game result.
     * @return The PGN string concatenated to the score.
     * @see Position::to_pgn
     */
    std::string const result() const;

  private:
    GameStatus move(Move move);
    /**
     * @brief Undo the last move.
     */
    GameStatus cancel();
    /**
     * @brief Send a draw request to the opponent.
     */
    GameStatus draw();
    /**
     * @brief Apply an action according to the response.
     * @param response The response from the player.
     */
    GameStatus apply(ResponseStatus &response);

    /**
     * @brief Check if the player has legal moves.
     * @see Board::is_legal
     */
    bool has_legal_moves(Player *player);
    /**
     * @brief Check if there is stalemate for the player.
     * @details A stalemate is a situation where the player has no legal moves
     * and the opponent's king is not in check.
     */
    bool is_stalemate(Player *player);
    /**
     * @brief Check if there is chessmate for the player.
     * @details A checkmate is a situation where the player has his king in
     * check but has no legal moves.
     */
    bool is_checkmate(Player *player);
    /**
     * @brief Check if the game is a draw by threefold repetition.
     * @details A threefold repetition is a situation where the same position
     * (with same castling rights and posssibles moves) occurs three times
     * during the game (not necessarily consecutive).
     */
    bool threefold_repetition() const;
    /**
     * @brief Check if the game is a draw by the fifty-move rule.
     * @details The fifty-move rule is a situation where no pawn has been moved
     * and no capture has been made during the last fifty moves.
     */
    bool fifty_move_rule() const;

  private:
    Board _board;
    Player *_white;
    Player *_black;
    std::vector<Position> _history;
    std::vector<Move> _moves;
    GameStatus _status;
};
