#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(PieceColor color, const sf::Texture& texture);

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) override;
};