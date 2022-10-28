#ifndef    __game__
#define    __game__

#include <SFML/Graphics.hpp>
#include "screenmanagement.hpp"
#include "7-bag.hpp"
#include "eventreader.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "timer.hpp"
#include "setup.hpp"
#include "scorelist.hpp"
#include "sound.hpp"
#include "srs.hpp"
#include "pattern.hpp"
#include "statistics.hpp"
#include "inGameFlags.hpp"

class game {

public:
	 game();
	 ~game();

    void rotateRight(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
    void rotateLeft(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
	void drawTheFrame(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, Piece &currentPiece, Piece &shadowPiece, randomizer &random, std::string elapsedTime, bool ccountTdownPending);
	void setShadowPiecePosition(Piece &currentPiece, Piece &shadowPiece, board &board, thePieces &thePieces);
	int hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, manageScreen &screen);
	void softDrop();
	void holdPiece(randomizer &random, setup &setup, Piece &currentPiece, int &holdedPiece);
	void lockoutPiece(board &board, pattern &pattern, manageScreen &screen, setup &setup, Piece &currentPiece, randomizer &random, thePieces &thePieces, timer &fallingPieceTimer, sf::Int32& underPreasureTime, sound& gameSound, statistics& playerStats);
    void launchParty(manageScreen &screen, setup &setup, sound& gameSound, statistics& playerStats);
    sf::Int32 calculateFallingPieceTimerDuration(const int level);
    bool isLevelUp(int level, int nbLines);
    int calculateLevel(int level);
    int calculateScore(const pattern &pattern, int score, const int level);
    void clearInGameFlags();
    void countDown(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, Piece &currentPiece, Piece &shadowPiece, randomizer &random, sound& gameSound);

    private:
    void endOfParty(manageScreen &screen, bool gameOver, setup& setup);
    srs srs;
    jsonFile m_gameTtranslation;
    inGameFlags inGameFlags;
    void errorMessage(manageScreen &screen, int language);
    eventReader eventReader;
};

#endif // __game__
