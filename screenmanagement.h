#ifndef    __manageScreen__
#define    __manageScreen__

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "7-bag.h"
#include "pieces.h"
#include "board.h"
#include "eventreader.h"

class manageScreen{

public:
     manageScreen();
     ~manageScreen();
void close();
void render();
void clear();
void printIndicators(const int level, const int score, const int , std::string timeElapsed);
void loadBitmapFile(const std::string title);
void loadFontFile(const std::string title);
void displayText(const std::string textToDisplay, const int sizeText, const sf::Color color, const float x, const float y);
void drawPlayGround(std::string levelLabel, std::string  scoreLabel, std::string lineLabel, std::string timeLabel);
void rawRenderCopy(const sf::IntRect& sourceRectangle, const sf::Vector2f& destination, const sf::Uint8 alpha);
void drawRectangle(const float x, const float y, const float h, const float w, sf::Color couleur);
void drawNextPieces(bool enhanced, int nextPiecesNumber, int piecePositonInTheBag, int pieceGraphic, randomizer& random, thePieces& thePieces, const sf::Uint8 alpha);
void drawPieceToHold(int currentPiece, int pieceGraphic, thePieces& thePieces, const sf::Uint8 alpha);
void drawTheBoard(board& board, const int pieceGraphic);
void drawPiece(sf::IntRect& sourceRectangle, sf::Vector2f& destination, thePieces& thePieces,int pieceToDraw, int rotation, const sf::Uint8 alpha);
void drawCurrentPiece(Piece& currentPiece, thePieces& thePieces, const int pieceGraphic, const sf::Uint8 alpha);
void shiftedLinesAnimation(pattern& pattern, board& board, int pieceGraphic);
void drawButton(const int x, const int y, const int width,  const int higth, const int textureNumber, const int buttonState);
void drawGameName();
void drawBlock( int blockNumber);
void drawEmptyBoard(const int pieceGraphic);

sf::RenderWindow m_window;

private:
sf::Texture m_texturePiece;
sf::Texture m_textureMenu;
sf::Font m_font;
sf::Text m_text;                                                                            // another rectangle

void adjustxy(const int pieceToDraw, sf::Vector2f& destination);
void draw5NxetArea();
void drawNextArea();
void drawHoldArea();
void drawBoardArea();
};

#endif // __manageScreen__
