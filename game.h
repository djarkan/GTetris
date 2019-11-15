#ifndef    __game__
#define    __game__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screenmanagement.h"
#include "7-bag.h"
#include "eventreader.h"
#include "board.h"
#include "pieces.h"

struct setup {
	bool enhanced = true;                                                               // 11 or 7 pieces game
	bool sevenBag = true;                                                               // randow method : 7-bag or random
	bool shadow = true;                                                                 // display shadow piece ON/OFF
	bool superRotationSystem{ true };                                                     // system de ration avancee ON/OFF
	bool nextPiece = true;                                                              // viewing the next piece ON/OFF
	bool music = true;                                                                  // play music ON/OFF
	int musicVolume = 100;                                                              // music volume 0-100
	bool sound = true;                                                                  // game sound ON/OFF
	int soundVolume = 100;                                                              // game sound 0-100
	int pieceGraphic = 3;                                                               // graphics types : 1 to x
	int nextPiecesNumber = 5;                                                           // number of next pieces viewable 0 up to 5
	int gameType = 1;                                                                   // 1 : marathon  2: sprint  3 limited time  ...
	bool lockout = true;                                                                // lockout ON/OFF
	bool hold = true;                                                                   // hold piece ON/OFF
};

class game {

public:
	 game();
	 ~game();
	int  start();


private:
	void drawTheFrame(manageScreen &screen, board &board, setup &setup, thePieces &thePieces, int holdedPiece, Piece &currentPiece, Piece &shadowPiece, randomizer &random, int piecePositonInTheBag);
	void setShadowPiecePosition(Piece &currentPiece, Piece &shadowPiece, board &board, thePieces &thePieces);
	void rotateRight(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
	void rotateLeft(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern);
	void hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern, manageScreen &screen);
	void softDrop();
};

#endif // __game__