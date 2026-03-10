#pragma once
#include "piece.h"

class Queen : public Piece {
public:
    Queen(PieceColor color, const sf::Texture& texture);
};