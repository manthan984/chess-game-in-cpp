#pragma once

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

public:
    Piece(PieceColor color, PieceType type);

    PieceColor getColor() const;
    PieceType getType() const;
};
