#include <SFML/Graphics.hpp>
#include "piece.h"

#pragma once

class Board
{
private:
    sf::RectangleShape &Square;

    float TileSize;
    float BorderOffset;
    int SelectedRow;
    int SelectedCol;

    const sf::Texture &PieceTexture;
    Piece *grid[8][8];

    int whiteKingRow, whiteKingCol;
    int blackKingRow, blackKingCol;
public:
    // Constructor/ Distructor
    Board(sf::RenderWindow &window, sf::RectangleShape &square, const float tileSize, const float borderOffset, const sf::Texture &texture);
    ~Board(); // distructor for the raw pointers.

    // Methods-
    void drawTile(sf::RenderWindow &Window, float x, const float y, const sf::Color &color, int tempCol, int tempRow, int selectedCol, int selectedRow);
    void drawBoard(sf::RenderWindow &Window, int selectedCol, int selectedRow);
    Piece *getPiece(int row, int col);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);

    bool isSquareUnderAttack(int targetRow, int targetCol, PieceColor defebderColor);
};
