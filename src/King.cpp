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

    // --- CASTLING PHYSICS ---
    if (rowDiff == 0 && std::abs(colDiff) == 2) {
        if (this->hasMoved) return false; // Cannot castle if King has moved

        // Kingside Castling (e8 to g8 -> col 4 to 6)
        if (endCol == 6) {
            // Check if path is empty
            if (grid[startRow][5] != nullptr || grid[startRow][6] != nullptr) return false;
            // Check if the Rook is there and hasn't moved
            Piece* rook = grid[startRow][7];
            if (rook == nullptr || rook->getType() != PieceType::Rook || rook->getHasMoved()) return false;
            return true;
        }
        
        // Queenside Castling (e8 to c8 -> col 4 to 2)
        if (endCol == 2) {
            // Check if path is empty (needs 3 empty squares on Queenside!)
            if (grid[startRow][3] != nullptr || grid[startRow][2] != nullptr || grid[startRow][1] != nullptr) return false;
            // Check if the Rook is there and hasn't moved
            Piece* rook = grid[startRow][0];
            if (rook == nullptr || rook->getType() != PieceType::Rook || rook->getHasMoved()) return false;
            return true;
        }
    }

    // --- NORMAL KING PHYSICS ---
    if (std::abs(rowDiff) > 1 || std::abs(colDiff) > 1) return false;

    if (grid[endRow][endCol] != nullptr){
        if (grid[endRow][endCol]->getColor() == this->color) return false;
    }

    return true;
}