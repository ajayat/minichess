#include "piece.hpp"

Piece::Piece(PieceType type, std::string const name, Color color)
    : _type(type), _name(name), _color(color)
{}

Piece::Piece(Piece const &other)
    : _type(other._type), _name(other._name), _color(other._color)
{}

void Piece::print()
{
    std::cout << _name;
}

std::vector<Square> const King::pseudo_legal_moves(Position const &position,
                                                   Square const &from) const
{
    return std::vector<Square>();
}

std::vector<Square> const Queen::pseudo_legal_moves(Position const &position,
                                                    Square const &from) const
{
    return std::vector<Square>();
}

std::vector<Square> const Rook::pseudo_legal_moves(Position const &position,
                                                   Square const &from) const
{
    return std::vector<Square>();
}

std::vector<Square> const Bishop::pseudo_legal_moves(Position const &position,
                                                     Square const &from) const
{
    return std::vector<Square>();
}

std::vector<Square> const Knight::pseudo_legal_moves(Position const &position,
                                                     Square const &from) const
{
    return std::vector<Square>();
}

std::vector<Square> const Pawn::pseudo_legal_moves(Position const &position,
                                                   Square const &from) const
{
    return std::vector<Square>();
}
