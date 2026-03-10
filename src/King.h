#pragma once
#include "piece.h"

class King : public Piece {
public:
    King(PieceColor color, const sf::Texture& texture);
};