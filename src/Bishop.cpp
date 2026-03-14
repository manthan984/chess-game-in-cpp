#include "Bishop.h"
#include <cmath>

Bishop::Bishop(PieceColor color, const sf::Texture& texture) 
    : Piece(color, PieceType::Bishop, texture) 
{
    int X_OFFSET = 400;
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

bool Bishop::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) {
    // Friendly fire check
    if (grid[endRow][endCol] != nullptr && grid[endRow][endCol]->getColor() == this->color) return false;
    
    return checkDiagonalLine(startRow, startCol, endRow, endCol, grid);
}