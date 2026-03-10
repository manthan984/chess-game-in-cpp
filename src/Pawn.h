#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(PieceColor color, const sf::Texture& texture);
};