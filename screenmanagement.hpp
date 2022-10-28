#ifndef    __manageScreen__
#define    __manageScreen__

#include <string>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include "7-bag.hpp"
#include "pieces.hpp"
#include "board.hpp"
#include "eventreader.hpp"
#include "time.hpp"

class manageScreen{

public:
    manageScreen();
    manageScreen(sf::Uint32 style);
    ~manageScreen();
    void close();
    void render();
    void clear();
    void printIndicators(const int level, const int score, const int , std::string timeElapsed);
    bool loadBitmapFile(const std::string title);
    bool loadFontFile(const std::string title);
    void displayText(const std::string textToDisplay, const int sizeText, const sf::Color color, float x, float y);
    void simpleDisplayText(const std::string textToDisplay, const int sizeText, const sf::Color color, const float x, const float y);
    void drawPlayGround(std::string levelLabel, std::string  scoreLabel, std::string lineLabel, std::string timeLabel, std::string holdLabel, std::string nextLabel);
    void rawRenderCopy(const sf::IntRect& sourceRectangle, const sf::Vector2f& destination, const sf::Uint8 alpha);
    void drawRectangle(const float x, const float y, const float h, const float w, sf::Color couleur);
    void drawCircles();
    void drawCircle(float radius, sf::Texture texture);
    void drawNextPieces(bool enhanced, int nextPiecesNumber, int piecePositonInTheBag, int pieceGraphic, randomizer& random, thePieces& thePieces, const sf::Uint8 alpha);
    void drawPieceToHold(int currentPiece, int pieceGraphic, thePieces& thePieces, const sf::Uint8 alpha);
    void drawTheBoard(board& board, const int pieceGraphic);
    void drawPiece(sf::IntRect& sourceRectangle, sf::Vector2f& destination, thePieces& thePieces,int pieceToDraw, int rotation, const sf::Uint8 alpha);
    void drawCurrentPiece(Piece& currentPiece, thePieces& thePieces, const int pieceGraphic, const sf::Uint8 alpha);
    void drawPatternAnimation(pattern& pattern, board& board, int pieceGraphic);
    void drawButton(const float x, const float y, const int width,  const int higth, const int textureNumber, const int buttonState);
    void drawGameName();
    void drawBlock(int blockNumber);
    void drawEmptyBoard(const int pieceGraphic);
    void drawScoreList(const std::array<std::pair<std::string, int> , 20>& scoreArray,const int ranking, const int gameMode, std::string label1, std::string label2);
    bool loadBitmapCursor(const std::string title);
    void errorMessage(std::string error, std::string messageToDisplay, std::string pressSpace);

    sf::RenderWindow m_window;
    sf::Image myCursor;

private:
    sf::Image m_graphics;
    sf::Texture m_texturePiece;
    sf::Texture m_textureMenu;
    sf::Font m_font;
    sf::Text m_text;
    enum class TextColor {Black = 0, LightBrown = 1, Brown = 2, DarkBrown = 3, LightRed = 4, Red = 5, DarkRed = 6, LightPink = 7, Pink = 8, DarkPink = 9, LightOrange = 10, Orange = 11, DarkOrange = 12, LightYellow = 13, Yellow = 14,
                          DarkYellow = 15, LightBlue = 16, Blue = 17, DarkBlue = 18, LightGreen = 19, Green = 20, DarkGreen = 21, LightPurple = 22, Purple = 23, DarkPurple = 24, LightGrey = 25, Grey = 26, DarkGrey = 27, White = 28};

    void shiftedLinesAnimation(pattern& pattern, board& board, int pieceGraphic, sf::Uint8 alpha);
    void drawPatternLabelAnimation(pattern& pattern, sf::Uint8 alpha);
    void adjustxy(const int pieceToDraw, sf::Vector2f& destination);
    void draw5NxetArea();
    void drawNextArea();
    void drawHoldArea();
    void drawBoardArea();
    void printChar(float& x, const float y, const int charSize, const char printedChar);
    sf::Color selectColor(int colorNb);
};

#endif // __manageScreen__
