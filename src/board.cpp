#include <algorithm>
#include <iostream>

#include "board.hpp"

Board::Board() : _board{nullptr}
{
    PieceType pieces[NCOL] = {
        ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    for (int x = 0; x < NCOL; x++) {
        _board[0][x] = this->create_piece(pieces[x], WHITE);
        _board[1][x] = this->create_piece(PAWN, WHITE);

        _board[7][x] = this->create_piece(pieces[x], BLACK);
        _board[6][x] = this->create_piece(PAWN, BLACK);

        for (int i = 0; i < NROW; i++) {
            for (int j = 0; j < NCOL; j++) {
                if (_board[i][j] == nullptr)
                    _position.board[i][j] = {.type = NIL, .color = NOCOLOR};
                else
                    _position.board[i][j] = {.type = _board[i][j]->type,
                                             .color = _board[i][j]->color};
            }
        }
        _position.turn = WHITE;
        _position.fifty_move_rule = 0;
        _position.white_castle = true;
        _position.black_castle = true;
    }
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
    std::string space5 = std::string(5, '\u0020');
    std::cout << std::endl;
    std::cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+"
              << std::endl;

    int begin = NROW - 1, end = -1, step = -1;
    if (this->turn() == BLACK) {
        begin = 0;
        end = NROW;
        step = 1;
    }
    for (int i = begin; i != end; i += step) {
        std::cout << i + 1 << " ";  // numérotation ligne dans affichage
        for (int j = 0; j < NROW; j++) {
            std::cout << "|";
            if (_board[i][j]) {
                std::cout << "\u0020\u0020";  // U+0020 est un espace utf-8
                _board[i][j]->print();
                std::cout << "\u0020\u0020";
            }
            else
                std::cout << space5;
        }
        std::cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+"
                  << std::endl;
    }
    std::cout << "     a     b     c     d     e     f     g     h    "
              << std::endl;
}

Color Board::turn() const
{
    return _position.turn;
}

Piece *Board::operator()(Square const &square) const
{
    return _board[square.x][square.y];
}

void Board::move(Move const &move)
{
    Square from = move.from, to = move.to;
    Piece *piece = _board[from.y][from.x];

    if (piece->type == PAWN) {
        Pawn *pawn = static_cast<Pawn *>(piece);
        if (pawn->is_en_passant(this->get_position(), from, to))
            _position.en_passant = to;
        else if (std::abs(from.y - to.y) == 2)  // pawn double move
            _position.en_passant = Square(from.x, (from.y + to.y) / 2);
        else if (move.promotion != NIL)
            piece = this->create_piece(move.promotion, piece->color);
    }
    if (piece->type == KING) {
        if (piece->color == WHITE)
            _position.white_castle = false;
        else
            _position.black_castle = false;
    }
    if (this->is_capture(move) || piece->type == PAWN)
        _position.fifty_move_rule = 0;
    else
        _position.fifty_move_rule++;

    // Update board
    _board[to.y][to.x] = piece;
    _board[from.y][from.x] = nullptr;
    _position.board[to.y][to.x] = _position.board[from.y][from.x];
    _position.board[from.y][from.x] = {.type = NIL, .color = NOCOLOR};
    // Update turn
    _position.turn = (this->turn() == WHITE) ? BLACK : WHITE;
}

bool Board::is_pseudo_legal(Move const &move) const
{
    Piece *piece = _board[move.from.y][move.from.x];
    if (piece == nullptr)
        return false;
    return piece->is_pseudo_legal(this->get_position(), move.from, move.to);
}

bool Board::is_legal(Move const &move)
{
    if (!is_pseudo_legal(move))
        return false;

    Position position = this->get_position();
    this->move(move);  // Simulate move
    bool is_legal = !is_checked(this->turn());
    this->set_position(position);  // Undo move
    return is_legal;
}

bool Board::is_capture(Move const &move) const
{
    return is_pseudo_legal(move) && _board[move.to.x][move.to.y] != nullptr;
}

Square const Board::find_king(Color color) const
{
    for (int y = 0; y < NROW; y++) {
        for (int x = 0; x < NCOL; x++) {
            if (_board[y][x] && _board[y][x]->type == KING
                && _board[y][x]->color == color)
                return Square(x, y);
        }
    }
    throw std::runtime_error("King not found");
}

bool Board::is_checked(Color color) const
{
    Square king = find_king(color);
    for (int i = 0; i < NCOL; i++) {
        for (int j = 0; j < NROW; j++) {
            if (is_capture(Move(Square(i, j), king)))
                return true;
        }
    }
    return false;
}

Position const Board::get_position() const
{
    return _position;
}

Piece *Board::create_piece(PieceType type, Color color)
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
            _board[i][j] = this->create_piece(piece.type, piece.color);
        }
    }
}
