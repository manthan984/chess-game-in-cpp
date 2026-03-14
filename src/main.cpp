#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

int main()
{
    // renders a 900x900 px window and set the frames to 30.
    sf::RenderWindow window(sf::VideoMode({900, 900}), "Chess");
    window.setFramerateLimit(30);

    // Load Textures, like Sprite or any media.
    sf::Texture pieceTexture;
    if (!pieceTexture.loadFromFile("assets/Chess_Pieces_Sprite.png"))
    {
        std::cerr << "Failed to load pieces image!!" << std::endl;
        return -1;
    }

    // shapes, for making 8x8 grid or the Game Board
    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    sf::RectangleShape ChessBoardWindow(sf::Vector2f(800.f, 800.f));

    // constants
    const float tileSize = 100.f;
    const float borderOffset = 50.f;

    // variables
    int selectedRow = -1;
    int selectedCol = -1;
    int clickState = 0;
    int sourceRow = -1, sourceCol = -1;

    // Objects
    Board board(window, square, tileSize, borderOffset, pieceTexture);

    // window
    while (window.isOpen()) // while the game window is open.
    {
        while (auto event = window.pollEvent()) // Event loop, renders 30 frames per seconds. i.e. loop runs 30 times per seconds.
        {
            if (event->is<sf::Event::Closed>()) // close the window
                window.close();

            // mouse button press detection.
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) 
                {
                    if (mouseEvent->button == sf::Mouse::Button::Left) // detect left click.
                    {
                        int mouseX = mouseEvent->position.x;
                        int mouseY = mouseEvent->position.y;

                        if (mouseX >= borderOffset &&
                            mouseX < borderOffset + 8 * tileSize &&
                            mouseY >= borderOffset &&
                            mouseY < borderOffset + 8 * tileSize)
                        {
                            int col = (mouseX - borderOffset) / tileSize;
                            int row = (mouseY - borderOffset) / tileSize;

                            // State checking.
                            if (clickState == 0)
                            {
                                // STATE 0: Trying to pick up a piece
                                if (board.getPiece(row, col) != nullptr)
                                {
                                    sourceRow = row;
                                    sourceCol = col;
                                    selectedRow = row; // Highlight the square
                                    selectedCol = col;
                                    clickState = 1; // Move to next state
                                    std::cout << "Grabbed piece at: " << col << ", " << row << std::endl;
                                }
                            }
                            else if (clickState == 1)
                            {
                                // STATE 1: Dropping the piece
                                board.movePiece(sourceRow, sourceCol, row, col);

                                // Reset everything back to State 0
                                clickState = 0;
                                sourceRow = -1;
                                sourceCol = -1;
                                selectedRow = -1; // Remove highlight
                                selectedCol = -1;
                                std::cout << "Moved to: " << col << ", " << row << std::endl;
                            }
                        }
                        else
                        {
                            // Clicked outside the board: cancel selection entirely
                            clickState = 0;
                            sourceRow = -1;
                            sourceCol = -1;
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

        // display the board status.
        board.drawBoard(window, selectedCol, selectedRow);

        window.display(); // start displaying.
    }
}