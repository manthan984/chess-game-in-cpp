#include <SFML/Graphics.hpp>
#include "Board.h"

Board::Board(sf::RenderWindow &window, sf::RectangleShape &square, const float tileSize, const float borderOffset)
    : Square(square), Window(window), TileSize(tileSize), BorderOffset(borderOffset){}

void Board::drawTile(const float x, const float y, const sf::Color &color, int tempCol, int tempRow, int selectedCol, int selectedRow){
    Square.setPosition(sf::Vector2f(x, y));
    Square.setFillColor(color);

    // Highlight selected
    if (tempCol == selectedCol && tempRow == selectedRow)
    {
        Square.setOutlineColor(sf::Color::Red);
        Square.setOutlineThickness(-3.0f);
    }
    else {
        Square.setOutlineColor(sf::Color::Transparent);
        Square.setOutlineThickness(0.0f);
    }
    Window.draw(Square);
}

void Board::drawBoard(int selectedCol, int selectedRow)
{
    for (int tempRow = 0; tempRow < 8; tempRow++)
    {
        for (int tempCol = 0; tempCol < 8; tempCol++)
        {
            if ((tempRow + tempCol) % 2 == 0)
            { // even cell
                drawTile(BorderOffset + tempCol * TileSize, BorderOffset + tempRow * TileSize, sf::Color::White, tempCol, tempRow, selectedCol, selectedRow);
            }
            else
            {
                drawTile(BorderOffset + tempCol * TileSize, BorderOffset + tempRow * TileSize, sf::Color::Black, tempCol, tempRow, selectedCol, selectedRow);
            }
        }
    }
}