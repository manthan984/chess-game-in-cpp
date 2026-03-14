#include "King.h"
#include <cmath>

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

bool King::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) {
    int rowDiff = endRow - startRow;
    int colDiff = endCol - startCol;

    // Only one step.
    if (std::abs(rowDiff) > 1 || std::abs(colDiff) > 1) return false;

    // Own piece check
    if (grid[endRow][endCol] != nullptr){
        if (grid[endRow][endCol]->getColor() == this->color) return false;
    }

    // else valid move (for now I am not thinking about the checking squares).
    return true;
}
