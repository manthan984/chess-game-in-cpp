#include <SFML/Graphics.hpp>

void drawSquare(sf::RenderWindow& window, sf::RectangleShape& square, const float x, const float y, const sf::Color& color){
    square.setPosition(sf::Vector2f(x, y));
    square.setFillColor(color);
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

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();  // black screen

        // make chess board window
        ChessBoardWindow.setPosition(sf::Vector2f(50.f, 50.f));
        ChessBoardWindow.setFillColor(sf::Color::Black);
        ChessBoardWindow.setOutlineColor(sf::Color(160, 82, 45));
        ChessBoardWindow.setOutlineThickness(50.f);
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

        for (int row=0; row<8; row++){
            for (int col=0; col<8; col++){
                if ((row + col) % 2 == 0){ // even cell
                    drawSquare(window, square, borderOffset + col*tileSize, borderOffset + row*tileSize, sf::Color::White);
                } else {
                    drawSquare(window, square, borderOffset + col*tileSize, borderOffset + row*tileSize, sf::Color::Black);
                }
            }
        }

        window.display();  // start displaying.
    }
}