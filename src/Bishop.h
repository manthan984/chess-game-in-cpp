#pragma once
#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(PieceColor color, const sf::Texture& texture);

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) override;
};