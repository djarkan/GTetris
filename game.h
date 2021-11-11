#ifndef    __game__
#define    __game__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screenmanagement.h"
#include "7-bag.h"
#include "eventreader.h"
#include "board.h"
#include "pieces.h"
#include "eventreader.h"
#include "timer.h"
#include "setup.hpp"

struct inGameFlags{
    bool lockedout{false};
    bool holded{false};
    int holdedPiece{-1};
    bool jejoue{true};
    bool gameOver{false};
    bool goalReached{false};
    bool fisrtShuffle{true};
    int piecePositonInTheBag{0};								// store the N° of the holded piece
    int level{1};
    int nbLines{0};
	int score{ 0 };
	sf::Time ellapsedPartyTime;
};

class game {

public:
	 game();
	 ~game();
//	int  start();

	void drawTheFrame(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, int holdedPiece, Piece &currentPiece, Piece &shadowPiece, randomizer &random, int piecePositonInTheBag, inGameFlags &inGameFlags, std::string elapsedTime);
	void setShadowPiecePosition(Piece &currentPiece, Piece &shadowPiece, board &board, thePieces &thePieces);
	void rotateRight(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
	void rotateLeft(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
	int hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern, manageScreen &screen);
	void softDrop();
	void holdPiece(randomizer &random, setup &setup, Piece &currentPiece, int &holdedPiece, int &piecePositonInTheBag);
	void lockoutPiece(board &board, pattern &pattern, manageScreen &screen, setup &setup, inGameFlags &inGameFlags, Piece &currentPiece, randomizer &random, thePieces &thePieces, timer &fallingPieceTimer, sf::Int32& underPreasureTime);
    void launchParty(manageScreen &screen, setup &setup, inGameFlags &inGameFlags);
    sf::Int32 calculateFallingPieceTimerDuration(const int level);
    bool isLevelUp(int level, int nbLines);
    int calculateLevel(int level);
    int calculateScore(const pattern &pattern, int score, const int level);
    void clearInGameFlags(inGameFlags &inGameFlags);
    std::string convertTimeToString(sf::Int32 elapsedTime);

    private:

};

#endif // __game__
