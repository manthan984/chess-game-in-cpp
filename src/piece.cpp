#include "Piece.h"


Piece::Piece(PieceColor color, PieceType type, const sf::Texture& texture) : color(color), type(type), sprite(texture)
{
}

PieceColor Piece::getColor() const
{
    return color;
}

PieceType Piece::getType() const
{
    return type;
}

sf::Sprite& Piece::getSprite() {
    return sprite;
}