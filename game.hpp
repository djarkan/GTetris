#ifndef    __game__
#define    __game__

#include <SFML/Graphics.hpp>
#include "screenmanagement.hpp"
#include "7-bag.hpp"
#include "eventreader.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "eventreader.hpp"
#include "timer.hpp"
#include "setup.hpp"
#include "scorelist.hpp"
#include "sound.hpp"
#include "srs.hpp"

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

    void rotateRight(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
    void rotateLeft(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);

	void drawTheFrame(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, int holdedPiece, Piece &currentPiece, Piece &shadowPiece, randomizer &random, int piecePositonInTheBag, inGameFlags &inGameFlags, std::string elapsedTime);
	void setShadowPiecePosition(Piece &currentPiece, Piece &shadowPiece, board &board, thePieces &thePieces);
	int hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, manageScreen &screen);
	void softDrop();
	void holdPiece(randomizer &random, setup &setup, Piece &currentPiece, int &holdedPiece, int &piecePositonInTheBag);
	void lockoutPiece(board &board, pattern &pattern, manageScreen &screen, setup &setup, inGameFlags &inGameFlags, Piece &currentPiece, randomizer &random, thePieces &thePieces, timer &fallingPieceTimer, sf::Int32& underPreasureTime, sound& gameSound);
    void launchParty(manageScreen &screen, setup &setup, sound& gameSound);
    sf::Int32 calculateFallingPieceTimerDuration(const int level);
    bool isLevelUp(int level, int nbLines);
    int calculateLevel(int level);
    int calculateScore(const pattern &pattern, int score, const int level);
    void clearInGameFlags(inGameFlags &inGameFlags);

    private:
    void endOfParty(manageScreen &screen, eventReader &eventReader, bool gameOver);
    srs srs;
};

#endif // __game__
