#include <SFML/Graphics.hpp>
#include <iostream>
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
    //  Update Blink Timer 
    if (blinkCounter > 0) {
        // Change phase every 0.15 seconds
        if (blinkClock.getElapsedTime().asSeconds() > 0.15f) {
            blinkCounter--;
            blinkClock.restart();
        }
    }

    bool whiteInCheck = isKingInCheck(PieceColor::White);
    bool blackInCheck = isKingInCheck(PieceColor::Black);

    // Draw the Board Tiles
    for (int tempRow = 0; tempRow < 8; tempRow++) {
        for (int tempCol = 0; tempCol < 8; tempCol++) {
            sf::Color tileColor = ((tempRow + tempCol) % 2 == 0) ? sf::Color::White : sf::Color::Green;
            
            // Check Warning
            Piece* p = grid[tempRow][tempCol];
            if (p != nullptr && p->getType() == PieceType::King) {
                if ((p->getColor() == PieceColor::White && whiteInCheck) || 
                    (p->getColor() == PieceColor::Black && blackInCheck)) {
                    tileColor = sf::Color(255, 100, 100); 
                }
            }

            drawTile(Window, BorderOffset + tempCol * TileSize, BorderOffset + tempRow * TileSize, tileColor, tempCol, tempRow, selectedCol, selectedRow);

            // Valid Move Highlights (Only on EMPTY squares now)
            if (selectedRow != -1 && selectedCol != -1) {
                if (isMoveLegal(selectedRow, selectedCol, tempRow, tempCol) && grid[tempRow][tempCol] == nullptr) {
                    sf::CircleShape highlight(15.f);
                    highlight.setFillColor(sf::Color(0, 0, 0, 60)); 
                    float cx = BorderOffset + tempCol * TileSize + (TileSize / 2) - 15.f;
                    float cy = BorderOffset + tempRow * TileSize + (TileSize / 2) - 15.f;
                    highlight.setPosition({cx, cy});
                    Window.draw(highlight);
                }
            }
        }
    }

    // Draw the Pieces with Tints 
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (grid[row][col] != nullptr) {
                sf::Sprite &pieceSprite = grid[row][col]->getSprite();
                pieceSprite.setPosition({BorderOffset + col * TileSize, BorderOffset + row * TileSize});

                bool isCapturable = false;
                bool isBlinkingKing = false;

                // Check if this piece is currently capturable
                if (selectedRow != -1 && selectedCol != -1) {
                    if (isMoveLegal(selectedRow, selectedCol, row, col) && grid[row][col]->getColor() != grid[selectedRow][selectedCol]->getColor()) {
                        isCapturable = true;
                    }
                }

                // Check if this is the King throwing an illegal move tantrum
                if (blinkCounter > 0 && grid[row][col]->getType() == PieceType::King && grid[row][col]->getColor() == blinkingKingColor) {
                    if (blinkCounter % 2 != 0) { // Phases 5, 3, 1 are Red
                        isBlinkingKing = true;
                    }
                }

                // Apply the Colors
                if (isBlinkingKing) {
                    pieceSprite.setColor(sf::Color(255, 50, 50, 255)); // Bright solid red
                } else if (isCapturable) {
                    pieceSprite.setColor(sf::Color(255, 50, 50, 180)); // Transparent red glow
                } else {
                    pieceSprite.setColor(sf::Color::White); // Normal color
                }

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

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    if (startRow == endRow && startCol == endCol) return false;

    Piece* pieceToMove = grid[startRow][startCol];
    if (pieceToMove == nullptr) return false;

    // 1. Did they click somewhere completely invalid for this piece? Quietly reject.
    if (!pieceToMove->isValidMove(startRow, startCol, endRow, endCol, grid)) {
        return false; 
    }

    // 2. The physics are valid. Is the move legally safe for the King?
    if (!isMoveLegal(startRow, startCol, endRow, endCol)) {
        // It failed because it puts/leaves the King in Check! 
        triggerKingBlink(pieceToMove->getColor());
        return false;
    }

    // 3. The move is 100% legal. Commit it permanently.
    Piece* targetPiece = grid[endRow][endCol];
    grid[endRow][endCol] = pieceToMove;
    grid[startRow][startCol] = nullptr;

    if (pieceToMove->getType() == PieceType::King) {
        if (pieceToMove->getColor() == PieceColor::White) {
            whiteKingRow = endRow; whiteKingCol = endCol;
        } else {
            blackKingRow = endRow; blackKingCol = endCol;
        }
    }

    if (targetPiece != nullptr) delete targetPiece;

    // If the piece that just moved is a Pawn, check if it reached the end of the board
    if (pieceToMove->getType() == PieceType::Pawn) {
        if ((pieceToMove->getColor() == PieceColor::White && endRow == 0) ||
            (pieceToMove->getColor() == PieceColor::Black && endRow == 7)) {
            
            PieceColor promoteColor = pieceToMove->getColor();
            // 1. Delete the Pawn from memory
            delete grid[endRow][endCol]; 
            
            // 2. Spawn a brand new Queen in its place!
            grid[endRow][endCol] = new Queen(promoteColor, PieceTexture);
            
            std::cout << "Pawn promoted to Queen!" << std::endl;
        }
    }
    // mark piece as moved
    pieceToMove->setHasMoved(true);

    // telleport the rook if castling
    if (pieceToMove->getType() == PieceType::King && std::abs(startCol - endCol) == 2) {
        int rookStartCol = (endCol == 6) ? 7 : 0;
        int rookEndCol = (endCol == 6) ? 5 : 3;
        
        Piece* rook = grid[startRow][rookStartCol];
        grid[startRow][rookEndCol] = rook;       // Move Rook to new square
        grid[startRow][rookStartCol] = nullptr;  // Empty the corner
        rook->setHasMoved(true);
        std::cout << "Castling executed!" << std::endl;
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

// Check if a specific color's King is currently in Check
bool Board::isKingInCheck(PieceColor color) {
    int kRow = (color == PieceColor::White) ? whiteKingRow : blackKingRow;
    int kCol = (color == PieceColor::White) ? whiteKingCol : blackKingCol;
    return isSquareUnderAttack(kRow, kCol, color);
}

// Brute-force simulate every possible move to see if ANY legal moves exist
bool Board::hasLegalMoves(PieceColor color) {
    for (int startRow = 0; startRow < 8; startRow++) {
        for (int startCol = 0; startCol < 8; startCol++) {
            Piece* piece = grid[startRow][startCol];
            if (piece != nullptr && piece->getColor() == color) {
                for (int endRow = 0; endRow < 8; endRow++) {
                    for (int endCol = 0; endCol < 8; endCol++) {
                        
                        // Use our new helper!
                        if (isMoveLegal(startRow, startCol, endRow, endCol)) {
                            return true; 
                        }
                    }
                }
            }
        }
    }
    return false; 
}

bool Board::isMoveLegal(int startRow, int startCol, int endRow, int endCol) {
    Piece* pieceToMove = grid[startRow][startCol];

    // castling check and rules.
    if (pieceToMove->getType() == PieceType::King && std::abs(startCol - endCol) == 2) {
        if (isSquareUnderAttack(startRow, startCol, pieceToMove->getColor())) return false; // Currently in check
        
        int step = (endCol > startCol) ? 1 : -1;
        if (isSquareUnderAttack(startRow, startCol + step, pieceToMove->getColor())) return false; // Passing through check
    }

    if (pieceToMove == nullptr) return false;

    // Basic math validation
    if (!pieceToMove->isValidMove(startRow, startCol, endRow, endCol, grid)) {
        return false;
    }

    // Simulate the move
    Piece* targetPiece = grid[endRow][endCol];
    grid[endRow][endCol] = pieceToMove;
    grid[startRow][startCol] = nullptr;

    int kRow = (pieceToMove->getColor() == PieceColor::White) ? whiteKingRow : blackKingRow;
    int kCol = (pieceToMove->getColor() == PieceColor::White) ? whiteKingCol : blackKingCol;

    if (pieceToMove->getType() == PieceType::King) {
        kRow = endRow;
        kCol = endCol;
    }

    // Radar check
    bool inCheck = isSquareUnderAttack(kRow, kCol, pieceToMove->getColor());

    // Undo the simulation
    grid[startRow][startCol] = pieceToMove;
    grid[endRow][endCol] = targetPiece;

    // It is legal if it does NOT leave the king in check
    return !inCheck; 
}

void Board::triggerKingBlink(PieceColor color) {
    blinkingKingColor = color;
    blinkCounter = 6; // 3 full blinks
    blinkClock.restart();
}