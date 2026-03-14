#include "Knight.h"

Knight::Knight(PieceColor color, const sf::Texture& texture) 
    : Piece(color, PieceType::Knight, texture) 
{
    int X_OFFSET = 600;
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

bool Knight::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) {
    // get difference between starting and ending position
    int rowDiff = endRow - startRow;
    int colDiff = endCol - startCol;

    // we use Pythagorus theorem, (2*2 + 1*1 = 5);
    if (rowDiff*rowDiff + colDiff*colDiff != 5) return false;

    // check destination square for self OR enemy
    if (grid[endRow][endCol] != nullptr){
        if (grid[endRow][endCol]->getColor() == this->color) return false;
    }

    // else Valid Knight move
    return true;
}