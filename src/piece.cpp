#include "Piece.h"

Piece::Piece(PieceColor color, PieceType type)
{
    this->color = color;
    this->type = type;
}

PieceColor Piece::getColor() const
{
    return color;
}

PieceType Piece::getType() const
{
    return type;
}