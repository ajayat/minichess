#include <map>
#include <stdexcept>
#include <string>

#include "position.hpp"

Square::Square() noexcept : x{-1}, y{-1}, name("EMPTY") {}

Square::Square(int file, int rank)
    : x{file}, y{rank},
      name(static_cast<char>('a' + file) + std::to_string(rank + 1))
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        throw std::out_of_range("x and y must be between 0 and 7");
}

Square::Square(std::string const name)
    : x(name[0] - 'a'), y(name[1] - '1'), name(name)
{
    if (name.size() != 2)
        throw std::invalid_argument("name must be 2 characters long");
    if (x < 0 || x > 7 || y < 0 || y > 7)
        throw std::out_of_range("Invalid coordinates");
}

bool Square::operator==(Square const &other) const
{
    return x == other.x && y == other.y;
}

Move::Move(Square from, Square to, PieceType promotion)
    : from(from), to(to), promotion(promotion)
{}

Move::Move(std::string const uci)
{
    if (uci.size() != 4 && uci.size() != 5)
        throw std::invalid_argument("UCI must be 4 or 5 characters long");

    from = uci.substr(0, 2);
    to = uci.substr(2, 2);

    if (uci.size() == 5) {
        std::map<char, PieceType> map = {
            {'q', QUEEN}, {'r', ROOK}, {'b', BISHOP}, {'n', KNIGHT}};
        if (map.find(uci[4]) != map.end())
            promotion = map[uci[4]];
        else
            throw std::invalid_argument("Invalid promotion");
    }
}

std::string const Move::to_uci() const
{
    if (promotion == NIL)
        return from.name + to.name;

    std::map<PieceType, char> map = {
        {QUEEN, 'q'}, {ROOK, 'r'}, {BISHOP, 'b'}, {KNIGHT, 'n'}};
    return from.name + to.name + map[promotion];
}

bool Position::operator==(Position const &other) const
{
    if (turn != other.turn || en_passant != other.en_passant
        || castling[0][0] != other.castling[0][0]
        || castling[0][1] != other.castling[0][1]
        || castling[1][0] != other.castling[1][0]
        || castling[1][1] != other.castling[1][1])
        return false;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j].type != other.board[i][j].type
                || board[i][j].color != other.board[i][j].color)
                return false;
    return true;
}

std::string const Position::to_pgn() const
{
    std::string pgn = "";
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            PieceInfo const &piece = board[y][x];
            if (piece.type != NIL) {
                pgn += (piece.color == WHITE) ? "w" : "b";
                pgn += " PNBRQK"[piece.type];
            }
            pgn += ",";
        }
    }
    return pgn;
}

std::string const Position::to_fen() const
{
    std::string fen = "";
    for (int y = 7; y >= 0; y--) {
        int empty = 0;
        for (int x = 0; x < 8; x++) {
            PieceInfo const &piece = board[y][x];
            if (piece.type == NIL) {
                empty++;
                continue;
            }
            if (empty > 0) {
                fen += std::to_string(empty);
                empty = 0;
            }
            fen += (piece.color == WHITE) ? " PNBRQK"[piece.type]
                                          : " pnbrqk"[piece.type];
        }
        if (empty > 0)
            fen += std::to_string(empty);
        if (y > 0)
            fen += "/";
    }
    fen += (turn == WHITE) ? " w " : " b ";
    fen += (castling[0][0]) ? "K" : "";
    fen += (castling[0][1]) ? "Q" : "";
    fen += (castling[1][0]) ? "k" : "";
    fen += (castling[1][1]) ? "q " : " ";
    fen += (en_passant.name == "EMPTY") ? "-" : en_passant.name;
    fen += " " + std::to_string(fifty_move_rule);
    fen += " " + std::to_string(fullmove_number);
    return fen;
}