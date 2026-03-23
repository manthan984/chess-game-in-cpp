#pragma once
#include <SFML/Graphics.hpp>

enum class PieceColor{
    White, 
    Black
};

enum class PieceType{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

class Piece{
protected:
    PieceColor color;
    PieceType type;

    sf::Sprite sprite;

    bool hasMoved = false;

    // Helper functions for move validation
    bool checkStraightLine(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]);
    bool checkDiagonalLine(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]);

public:
    Piece(PieceColor color, PieceType type, const sf::Texture& texture);
    virtual ~Piece() = default;

    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* grid[8][8]) = 0;

    PieceColor getColor() const;
    PieceType getType() const;

    bool getHasMoved() const;
    void setHasMoved(bool moved);
    
    sf::Sprite& getSprite();
};
