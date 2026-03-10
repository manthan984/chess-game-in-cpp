#include <SFML/Graphics.hpp>

#pragma once

class Board{
private:
    sf::RectangleShape &Square;
    sf::RenderWindow &Window;

    float TileSize;
    float BorderOffset;
    int SelectedRow;
    int SelectedCol;

public:
    Board(sf::RenderWindow &window, sf::RectangleShape &square, const float tileSize, const float borderOffset);
    void drawTile(const float x, const float y, const sf::Color &color, int tempCol, int tempRow, int selectedCol, int selectedRow);
    void drawBoard(int selectedCol, int selectedRow);
};
