#include "Pawn.h"
#include <SFML/Graphics.hpp>

Pawn::Pawn(PieceColor color, const sf::Texture &texture) : Piece(color, PieceType::Pawn, texture)
{
    sprite.setTexture(texture);

    if (color == PieceColor::White)
    {
        sprite.setTextureRect(sf::IntRect{{1000, 0}, {200, 200}});
    }
    else
    {
        sprite.setTextureRect(sf::IntRect{{1000, 200}, {200, 200}});
    }

    float scaleFactor = 100.f / 200.f;
    sprite.setScale({scaleFactor, scaleFactor});
}