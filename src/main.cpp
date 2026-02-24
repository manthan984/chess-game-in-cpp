#include <SFML/Graphics.hpp>
#include <iostream>

void drawSquare(sf::RenderWindow &window, sf::RectangleShape &square, const float x, const float y, const sf::Color &color, int tempCol, int tempRow, int selectedCol, int selectedRow)
{
    square.setPosition(sf::Vector2f(x, y));
    square.setFillColor(color);

    // Highlight selected
    if (tempCol == selectedCol && tempRow == selectedRow)
    {
        square.setOutlineColor(sf::Color::Red);
        square.setOutlineThickness(-3.0f);
    }
    else
    {
        square.setOutlineThickness(0.0f);
        square.setOutlineColor(sf::Color::Transparent);
    }
    window.draw(square);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({900, 900}), "Chess");
    window.setFramerateLimit(30);

    // shapes
    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    sf::RectangleShape ChessBoardWindow(sf::Vector2f(800.f, 800.f));

    // constants
    const float tileSize = 100.f;
    const float borderOffset = 50.f;

    // variables
    int mouseX;
    int mouseY;
    int row, selectedRow = -1;
    int col, selectedCol = -1;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // mouse button press detection.
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        mouseX = mouseEvent->position.x;
                        mouseY = mouseEvent->position.y;
                        if (mouseX >= borderOffset &&
                            mouseX < borderOffset + 8 * tileSize &&
                            mouseY >= borderOffset &&
                            mouseY < borderOffset + 8 * tileSize)
                        {
                            col = (mouseX - borderOffset) / tileSize;
                            row = (mouseY - borderOffset) / tileSize;
                            selectedRow = row;
                            selectedCol = col;
                            std::cout << "Mouse clicked at: " << col << ", " << row << std::endl;
                        }
                        else
                        {
                            selectedCol = -1;
                            selectedRow = -1;
                        }
                    }
                }
            }
        }

        window.clear(); // black screen

        // make chess board window
        ChessBoardWindow.setPosition(sf::Vector2f(50.f, 50.f));
        ChessBoardWindow.setFillColor(sf::Color::Black);
        ChessBoardWindow.setOutlineColor(sf::Color(160, 82, 45));
        ChessBoardWindow.setOutlineThickness(10.f);
        window.draw(ChessBoardWindow);

        // drawing shapes;

        // hard coded // bad practice

        // for (int i = 0; i<4; i++){
        //     for (int j=0; j<4; j++){
        //         drawSquare(window, square, 200*i+(50.f), 200*j+(50.f));
        //     }
        // }
        // for (int i = 0; i<4; i++){
        //     for (int j=0; j<4; j++){
        //         drawSquare(window, square, 100 + 200*i+(50.f), 100 + 200*j+(50.f));
        //     }
        // }

        // better logic

        for (int tempRow = 0; tempRow < 8; tempRow++)
        {
            for (int tempCol = 0; tempCol < 8; tempCol++)
            {
                if ((tempRow + tempCol) % 2 == 0)
                { // even cell
                    drawSquare(window, square, borderOffset + tempCol * tileSize, borderOffset + tempRow * tileSize, sf::Color::White, tempCol, tempRow, selectedCol, selectedRow);
                }
                else
                {
                    drawSquare(window, square, borderOffset + tempCol * tileSize, borderOffset + tempRow * tileSize, sf::Color::Black, tempCol, tempRow, selectedCol, selectedRow);
                }
            }
        }

        window.display(); // start displaying.
    }
}