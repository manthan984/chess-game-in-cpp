#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

// constructor
Board::Board(sf::RenderWindow &window, sf::RectangleShape &square, const float tileSize, const float borderOffset, const sf::Texture &texture)
    : Square(square), TileSize(tileSize), BorderOffset(borderOffset), PieceTexture(texture)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            grid[row][col] = nullptr;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            grid[i][j] = nullptr;

            // PAWNS
            if (i == 1) grid[i][j] = new Pawn(PieceColor::Black, PieceTexture);
            if (i == 6) grid[i][j] = new Pawn(PieceColor::White, PieceTexture);

            // MAIN PIECES (Rows 0 for Black, Row 7 for White)
            if (i == 0 || i == 7)
            {
                PieceColor color = (i == 0) ? PieceColor::Black : PieceColor::White;

                if (j == 0 || j == 7) grid[i][j] = new Rook(color, PieceTexture);
                else if (j == 1 || j == 6) grid[i][j] = new Knight(color, PieceTexture);
                else if (j == 2 || j == 5) grid[i][j] = new Bishop(color, PieceTexture);
                else if (j == 3) grid[i][j] = new Queen(color, PieceTexture);
                else if (j == 4) grid[i][j] = new King(color, PieceTexture);
            }
        }
    }
}

// distructor
Board::~Board()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (grid[row][col] != nullptr)
            {
                delete grid[row][col];
            }
        }
    }
}

void Board::drawTile(sf::RenderWindow &Window, const float x, const float y, const sf::Color &color, int tempCol, int tempRow, int selectedCol, int selectedRow)
{
    Square.setPosition(sf::Vector2f(x, y));
    Square.setFillColor(color);

    // Highlight selected
    if (tempCol == selectedCol && tempRow == selectedRow)
    {
        Square.setOutlineColor(sf::Color::Red);
        Square.setOutlineThickness(-3.0f);
    }
    else
    {
        Square.setOutlineColor(sf::Color::Transparent);
        Square.setOutlineThickness(0.0f);
    }
    Window.draw(Square);
}

void Board::drawBoard(sf::RenderWindow &Window, int selectedCol, int selectedRow)
{
    for (int tempRow = 0; tempRow < 8; tempRow++)
    {
        for (int tempCol = 0; tempCol < 8; tempCol++)
        {
            if ((tempRow + tempCol) % 2 == 0)
            { // even cell
                drawTile(Window, BorderOffset + tempCol * TileSize, BorderOffset + tempRow * TileSize, sf::Color::White, tempCol, tempRow, selectedCol, selectedRow);
            }
            else
            {
                drawTile(Window, BorderOffset + tempCol * TileSize, BorderOffset + tempRow * TileSize, sf::Color::Green, tempCol, tempRow, selectedCol, selectedRow);
            }
        }
    }
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (grid[row][col] != nullptr)
            {
                sf::Sprite &pieceSprite = grid[row][col]->getSprite();

                pieceSprite.setPosition({BorderOffset + col * TileSize, BorderOffset + row * TileSize});

                Window.draw(pieceSprite);
            }
        }
    }
}