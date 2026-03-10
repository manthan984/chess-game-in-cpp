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

public:
    Piece(PieceColor color, PieceType type, const sf::Texture& texture);
    virtual ~Piece() = default;

    PieceColor getColor() const;
    PieceType getType() const;
    
    sf::Sprite& getSprite();
};
