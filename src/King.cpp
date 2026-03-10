#include "King.h"

King::King(PieceColor color, const sf::Texture& texture) 
    : Piece(color, PieceType::King, texture) 
{
    int X_OFFSET = 0;
    int W = 200;
    int H = 200;

    if (color == PieceColor::White) {
        sprite.setTextureRect(sf::IntRect({X_OFFSET, 0}, {W, H})); // White is top row
    } else {
        sprite.setTextureRect(sf::IntRect({X_OFFSET, H}, {W, H})); // Black is bottom row
    }

    // Scale it to fit the 100x100 tile size
    float scaleFactor = 100.f / W;
    sprite.setScale({scaleFactor, scaleFactor});
}