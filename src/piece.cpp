#include "Piece.h"
#include <cmath>

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

bool Piece::checkStraightLine(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) {
    if (startRow != endRow && startCol != endCol) return false;

    int rowStep = (endRow > startRow) ? 1 : (endRow < startRow) ? -1 : 0;
    int colStep = (endCol > startCol) ? 1 : (endCol < startCol) ? -1 : 0;

    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow != endRow || currentCol != endCol) {
        if (grid[currentRow][currentCol] != nullptr) return false;
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}

bool Piece::checkDiagonalLine(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) {
    if (std::abs(endRow - startRow) != std::abs(endCol - startCol)) return false;

    int rowStep = (endRow > startRow) ? 1 : -1;
    int colStep = (endCol > startCol) ? 1 : -1;

    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow != endRow && currentCol != endCol) {
        if (grid[currentRow][currentCol] != nullptr) return false;
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool moved) {
    hasMoved = moved;
}