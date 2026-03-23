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
            if (i == 1)
                grid[i][j] = new Pawn(PieceColor::Black, PieceTexture);
            if (i == 6)
                grid[i][j] = new Pawn(PieceColor::White, PieceTexture);

            // MAIN PIECES (Rows 0 for Black, Row 7 for White)
            if (i == 0 || i == 7)
            {
                PieceColor color = (i == 0) ? PieceColor::Black : PieceColor::White;

                if (j == 0 || j == 7)
                    grid[i][j] = new Rook(color, PieceTexture);
                else if (j == 1 || j == 6)
                    grid[i][j] = new Knight(color, PieceTexture);
                else if (j == 2 || j == 5)
                    grid[i][j] = new Bishop(color, PieceTexture);
                else if (j == 3)
                    grid[i][j] = new Queen(color, PieceTexture);
                else if (j == 4)
                    grid[i][j] = new King(color, PieceTexture);
            }
        }
    }
    
    // Initialize King trackers to their starting squares
    blackKingRow = 0;
    blackKingCol = 4;
    whiteKingRow = 7;
    whiteKingCol = 4;
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

// ---- game logic ---- //
// move piece
Piece *Board::getPiece(int row, int col)
{
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        return grid[row][col];
    }
    return nullptr;
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol)
{
    if (startRow == endRow && startCol == endCol) return false;

    Piece* pieceToMove = grid[startRow][startCol];
    if (pieceToMove == nullptr) return false;

    // Basic piece math validation
    if (!pieceToMove->isValidMove(startRow, startCol, endRow, endCol, grid)) {
        return false;
    }

    // Remember what is at the destination
    Piece* targetPiece = grid[endRow][endCol];

    // Temporarily make the move in the array
    grid[endRow][endCol] = pieceToMove;
    grid[startRow][startCol] = nullptr;

    // Get the King's position using our fast trackers!
    int kingRow = (pieceToMove->getColor() == PieceColor::White) ? whiteKingRow : blackKingRow;
    int kingCol = (pieceToMove->getColor() == PieceColor::White) ? whiteKingCol : blackKingCol;

    // If the piece we are simulating IS the King, we must use its simulated destination!
    if (pieceToMove->getType() == PieceType::King) {
        kingRow = endRow;
        kingCol = endCol;
    }

    // Use the radar: Is our King in check after making this move?
    bool inCheck = isSquareUnderAttack(kingRow, kingCol, pieceToMove->getColor());

    // UNDO LOGIC: The move was illegal!
    if (inCheck) {
        grid[startRow][startCol] = pieceToMove; // Put our piece back
        grid[endRow][endCol] = targetPiece;     // Put the enemy piece back
        return false; // Move failed
    }

    // MOVE SUCCESSFUL: Permanently update the tracker if the King actually moved
    if (pieceToMove->getType() == PieceType::King) {
        if (pieceToMove->getColor() == PieceColor::White) {
            whiteKingRow = endRow; whiteKingCol = endCol;
        } else {
            blackKingRow = endRow; blackKingCol = endCol;
        }
    }

    // Finally safe to permanently delete the captured piece
    if (targetPiece != nullptr) {
        delete targetPiece;
    }

    return true; 
}

bool Board::isSquareUnderAttack(int targetRow, int targetCol, PieceColor defenderColor) {
    // Scan the entire board
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = grid[row][col];

            // If there is a piece here, and it is an ENEMY piece
            if (piece != nullptr && piece->getColor() != defenderColor) {
                
                // check- can this enemy piece legally move to our target square?
                if (piece->isValidMove(row, col, targetRow, targetCol, grid)) {
                    return true; // The square is under attack!
                }
            }
        }
    }

    return false; 
}