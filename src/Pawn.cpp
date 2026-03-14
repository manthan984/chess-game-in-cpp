#include "Pawn.h"
#include <cmath>

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

bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece *grid[8][8])
{
    // direction
    int direction = (color == PieceColor::White) ? -1 : 1;

    // Forward move
    if (endCol == startCol && endRow == startRow + direction)
    {
        // check if the square is empty, return true
        if (grid[endRow][endCol] == nullptr)
            return true;
    }

    if (endCol == startCol && endRow == startRow + 2 * direction)
    {
        bool isStartingRow = (color == PieceColor::White && startRow == 6) || (color == PieceColor::Black && startRow == 1);

        // must be the starting square, and path must be empty (no pieces in between startting and end pos.)
        if (isStartingRow &&
            grid[startRow + direction][startCol] == nullptr &&
            grid[endRow][endCol] == nullptr) return true;
    }

    // capture Diagonally.
    if (std::abs(endCol - startCol) == 1 && endRow == startRow + direction) {
        // Destination MUST contain a piece, AND that piece must be an enemy
        if (grid[endRow][endCol] != nullptr && grid[endRow][endCol]->getColor() != this->color) {
            return true;
        }
    }

    // if nothing is true, return false
    return false;
}