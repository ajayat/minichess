#include <algorithm>
#include <iostream>

#include "board.hpp"

#define RESET "\e[0m"
#define BOLD_BLACK "\e[1;30m"
#define BLACKBG "\e[0;46m"
#define WHITEBG "\e[0;107m"
#define ITALIC "\e[3m"

Board::Board() : _board{nullptr}
{
    PieceType pieces[NCOL] = {
        ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};

    for (int x = 0; x < NCOL; x++) {
        _board[0][x] = create_piece(pieces[x], WHITE);
        _board[1][x] = create_piece(PAWN, WHITE);
        _board[7][x] = create_piece(pieces[x], BLACK);
        _board[6][x] = create_piece(PAWN, BLACK);
    }
    for (int i = 0; i < NROW; i++) {
        for (int j = 0; j < NCOL; j++) {
            Piece *piece = _board[i][j];
            if (piece)
                _position.board[i][j] = {piece->type, piece->color};
            else
                _position.board[i][j] = {NIL, NOCOLOR};
        }
    }
    _position.turn = WHITE;
    _position.castling[WHITE][KINGSIDE] = true;
    _position.castling[WHITE][QUEENSIDE] = true;
    _position.castling[BLACK][KINGSIDE] = true;
    _position.castling[BLACK][QUEENSIDE] = true;
    _position.fifty_move_rule = 0;
    _position.fullmove_number = 1;
}

Board::~Board()
{
    for (int i = 0; i < NROW; i++) {
        for (int j = 0; j < NCOL; j++) {
            delete _board[i][j];
            _board[i][j] = nullptr;
        }
    }
}

void Board::print() const
{
    std::cout << std::endl;
    std::cout << ITALIC << "   a  b  c  d  e  f  g  h  " << RESET << std::endl;

    int begin = NROW - 1, end = -1, step = -1;
    if (turn() == BLACK) {
        begin = 0;
        end = NROW;
        step = 1;
    }
    for (int i = begin; i != end; i += step) {
        std::cout << ITALIC << i + 1 << RESET " ";
        for (int j = 0; j < NROW; j++) {
            std::cout << ((i + j) & 1 ? WHITEBG : BLACKBG) << BOLD_BLACK;
            if (_board[i][j] != nullptr)
                std::cout << " " << _board[i][j]->render() << " ";
            else
                std::cout << "   ";
            std::cout << RESET;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Color Board::turn() const
{
    return _position.turn;
}

Piece *Board::operator()(Square const &square) const
{
    return _board[square.y][square.x];
}

void Board::_move(Square const &from, Square const &to)
{
    delete _board[to.y][to.x];
    _board[to.y][to.x] = _board[from.y][from.x];
    _board[from.y][from.x] = nullptr;
    _position.board[to.y][to.x] = _position.board[from.y][from.x];
    _position.board[from.y][from.x] = {NIL, NOCOLOR};
}

void Board::move(Move const &move)
{
    Square from = move.from, to = move.to;
    Piece *piece = _board[from.y][from.x];
    bool *castling = _position.castling[piece->color];

    if (piece->type == PAWN) {
        Pawn *pawn = static_cast<Pawn *>(piece);
        if (pawn->is_en_passant(get_position(), from, to)) {
            _board[from.y][to.x] = nullptr;  // remove captured pawn
            _position.board[from.y][to.x] = {NIL, NOCOLOR};
        }
        else if (move.promotion != NIL) {  // pawn promotion
            Color color = piece->color;
            delete _board[from.y][from.x];
            _board[from.y][from.x] = create_piece(move.promotion, color);
            _position.board[from.y][from.x] = {move.promotion, color};
        }
    }
    if (piece->type == KING) {
        King *king = static_cast<King *>(piece);
        if (king->is_castling(get_position(), from, to)) {

            if (to.x == 2)  // queenside castle
                _move(Square(0, from.y), Square(3, from.y));
            else  // kingside castle
                _move(Square(7, from.y), Square(5, from.y));
        }
        castling[KINGSIDE] = castling[QUEENSIDE] = false;
    }
    if (piece->type == ROOK) {
        if (from.x == 0)  // queenside rook
            castling[QUEENSIDE] = false;
        else if (from.x == 7)  // kingside rook
            castling[KINGSIDE] = false;
    }

    if (is_capture(move) || piece->type == PAWN)
        _position.fifty_move_rule = 0;
    else
        _position.fifty_move_rule++;

    if (piece->type == PAWN && std::abs(from.y - to.y) == 2)  // double move
        _position.en_passant = Square(from.x, (from.y + to.y) / 2);
    else
        _position.en_passant = Square();

    if (turn() == BLACK)
        _position.fullmove_number++;

    _position.turn = (turn() == WHITE) ? BLACK : WHITE;
    _move(from, to);  // Move piece
}

bool Board::is_pseudo_legal(Move const &move) const
{
    Piece *piece = _board[move.from.y][move.from.x];
    if (piece == nullptr)
        return false;
    return piece->is_pseudo_legal(get_position(), move.from, move.to);
}

bool Board::is_legal(Move const &move)
{
    if (!is_pseudo_legal(move))
        return false;

    Square from{move.from}, to{move.to};
    Piece *piece = _board[from.y][from.x];
    if (piece->type == KING && abs(from.x - to.x) == 2) {
        Color color = turn();
        return (  // Test if king is not attacked during castling
          !is_attacked(color, Square(from.x, from.y))
          && !is_attacked(color, Square((from.x + to.x) / 2, from.y))
          && !is_attacked(color, to));
    }
    Position position = get_position();
    this->move(move);  // Simulate move
    bool is_legal = !is_checked(position.turn);
    set_position(position);  // Undo move
    return is_legal;
}

bool Board::is_capture(Move const &move) const
{
    return _board[move.to.y][move.to.x] && is_pseudo_legal(move);
}

bool Board::is_attacked(Color const color, Square const &square) const
{
    for (int y = 0; y < NROW; y++) {
        for (int x = 0; x < NCOL; x++) {
            if (_board[y][x] && _board[y][x]->color != color
                && is_pseudo_legal(Move(Square(x, y), square)))
                return true;
        }
    }
    return false;
}

bool Board::is_checked(Color const color) const
{
    for (int y = 0; y < NROW; y++) {
        for (int x = 0; x < NCOL; x++) {
            if (_board[y][x] && _board[y][x]->type == KING
                && _board[y][x]->color == color)
                return is_attacked(color, Square(x, y));
        }
    }
    throw std::runtime_error("King not found");
}

bool Board::is_promotion(Move const &move) const
{
    Piece *piece = _board[move.from.y][move.from.x];
    return piece->type == PAWN && (move.to.y == 0 || move.to.y == 7);
}

Position const Board::get_position() const
{
    return _position;
}

Piece *Board::create_piece(PieceType const type, Color const color)
{
    switch (type) {
    case PAWN:
        return new Pawn(color);
    case KNIGHT:
        return new Knight(color);
    case BISHOP:
        return new Bishop(color);
    case ROOK:
        return new Rook(color);
    case QUEEN:
        return new Queen(color);
    case KING:
        return new King(color);
    default:
        return nullptr;
    }
}

void Board::set_position(Position const &position)
{
    _position = position;

    for (int i = 0; i < NROW; i++) {
        for (int j = 0; j < NCOL; j++) {
            delete _board[i][j];
            PieceInfo const &piece = position.board[i][j];
            _board[i][j] = create_piece(piece.type, piece.color);
        }
    }
}