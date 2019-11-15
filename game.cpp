/*#include <SFML/Graphics.hpp>
#include <iostream>
#include "screenmanagement.h"
#include "7-bag.h"

#include "board.h" */
#include "game.h" 
#include "eventreader.h"
                                                                                            //Screen dimension constants
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
const int playGroundWidth = 300;
const int playGroundheigth = 600;

game::game()
{

}

game::~game()
{

}

int game::start()
{
    bool lockedout{false},holded{false};
    int holdedPiece{-1};																								// store the N° of the holded piece

    manageScreen screen;                                                                    
    randomizer random;
    eventReader eventReader;
    thePieces thePieces;
    board board;
    Piece currentPiece, shadowPiece;
    pattern pattern;
	setup setup;

	    screen.loadBitmapFile("graphics/graphics.png");
		screen.loadFontFile("font/arial.ttf");
        bool jejoue(true);
		eventReader::gameControl gameAction;
        while(jejoue) {                          // debut prog : menu
            bool gameOver{false};
            bool fisrtShuffle{true};
            while(fisrtShuffle) {
                random.initTheBag(setup.enhanced, setup.sevenBag);
                fisrtShuffle = random.testFirstShuffle(setup.enhanced);
            }
            board.clearBoard();
            screen.drawTheBoard(board, setup.pieceGraphic);                                                             // begin the party
            int piecePositonInTheBag = 0;
            currentPiece.current = random.getPieceAtPosition(piecePositonInTheBag);
            if(setup.nextPiecesNumber > 0)
                screen.drawNextPieces(setup.enhanced, setup.nextPiecesNumber, piecePositonInTheBag, setup.pieceGraphic, random, thePieces, 255);
            board.putNewPieceInBoard(currentPiece, thePieces);
            while(!gameOver) {
                int virtualRotation{0};
				gameAction = eventReader.getEvent(screen.m_window);
                switch (gameAction) {
					case eventReader::gameControl::rotateRight:                     
						rotateRight(currentPiece, board, thePieces, setup, pattern);
                        break;
                    case eventReader::gameControl::rotateLeft:                   
						rotateLeft(currentPiece, board, thePieces, setup, pattern);
                        break;
                    case eventReader::gameControl::softDrop:                     
                        if(board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces))
                           currentPiece.y++;
                        else
                           if(setup.lockout)
                                lockedout = true;   // SI LOCKOUT DISABLE TESTER SI PEUT DESCENDRE -> SI NON PASSE A PIECE SUIVANTE
                            else
                                lockedout = true;         // lancer le timer du lockout
                        break;
                    case eventReader::gameControl::hardDrop:                    // hard drop
                        hardDrop(currentPiece, board, thePieces, setup, pattern,screen);
						lockedout = true;
                        break;
                    case eventReader::gameControl::shiftLeft:              // move left
                        if(board.testMovement(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces))
                           currentPiece.x--;
                        break;
                    case eventReader::gameControl::shiftRight:             // move right
                        if(board.testMovement(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces))
                           currentPiece.x++;
                        break;
                    case eventReader::gameControl::holdPiece:            // hold
                        if(!holded && setup.hold) {
                            holded = true;
                            if(holdedPiece < 0) {
                                holdedPiece = currentPiece.current;                                             // if hold is empty hold is the current piece
                                piecePositonInTheBag = random.incrementPiecePositonInTheBag(setup.enhanced, piecePositonInTheBag, setup.sevenBag);
                                currentPiece.current = random.getPieceAtPosition(piecePositonInTheBag);
                            }
                            else {
                                int swapper = holdedPiece;                                                      // swap hold and current piece
                                holdedPiece = currentPiece.current;
                                currentPiece.current = swapper;
                            }
                            if(!board.putNewPieceInBoard(currentPiece, thePieces))
                                gameOver = true;
                        }
                        break;
                    case eventReader::gameControl::pause:                   // pause
                        screen.pauseMenu(board, setup.pieceGraphic);
// arret des timers
//
// reprise des timers
                        break;
					case eventReader::gameControl::none:
                    default:
                        break;
                }
                if(lockedout) {                                                                                             // piece locked
                    board.copyPieceInBoard(currentPiece, thePieces);
                    if(board.patternSearch(pattern, currentPiece)) {
                        screen.drawTheBoard(board, setup.pieceGraphic);
                        screen.shiftedLinesAnimation(pattern, board, setup.pieceGraphic);
                        board.shiftBlocksAfterLines(pattern);
                        board.IsThereClearBoard(pattern);
        // calcul des points
                        board.clearPattern(pattern);
                    }
					piecePositonInTheBag = random.incrementPiecePositonInTheBag(setup.enhanced, piecePositonInTheBag, setup.sevenBag);
					currentPiece.current = random.getPieceAtPosition(piecePositonInTheBag);
					lockedout = false;
					holded = false;
					if (!board.putNewPieceInBoard(currentPiece, thePieces))
						gameOver = true;
                }
				setShadowPiecePosition(currentPiece, shadowPiece, board, thePieces);
				drawTheFrame(screen, board, setup, thePieces, holdedPiece, currentPiece, shadowPiece, random, piecePositonInTheBag);
            }
			holdedPiece = -1;
        }
	screen.m_window.close();
	return 0;
}

void game::rotateRight(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern)
{
	int virtualRotation = currentPiece.rotation;
	if (virtualRotation == 3)
		virtualRotation = 0;
	else
		virtualRotation++;
	if (board.testMovement(currentPiece.x, currentPiece.y, virtualRotation, currentPiece.current, thePieces)) {
		currentPiece.rotation = virtualRotation;
		if (currentPiece.current == 3 && !board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces))
			pattern.TspinSearch = true;
	}
	else
		if (setup.superRotationSystem)
			board.superRotationSystem(currentPiece, virtualRotation, thePieces);
}

void game::rotateLeft(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern)
{
	int virtualRotation = currentPiece.rotation;
	if (virtualRotation == 0)
		virtualRotation = 3;
	else
		virtualRotation--;
	if (board.testMovement(currentPiece.x, currentPiece.y, virtualRotation, currentPiece.current, thePieces)) {
		currentPiece.rotation = virtualRotation;
		if (currentPiece.current == 3 && !board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces))
			pattern.TspinSearch = true;
	}
	else
		if (setup.superRotationSystem)
			board.superRotationSystem(currentPiece, virtualRotation, thePieces);
}

void game::hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern, manageScreen &screen)
{
	while (board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)) {
		currentPiece.y++;
		screen.drawTheBoard(board, setup.pieceGraphic);
		screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
		screen.render();
		sf::sleep(sf::milliseconds(2));
	}
}

void game::setShadowPiecePosition(Piece &currentPiece, Piece &shadowPiece, board &board, thePieces &thePieces)
{
	shadowPiece.x = currentPiece.x;
	shadowPiece.y = currentPiece.y;
	shadowPiece.current = currentPiece.current;
	shadowPiece.rotation = currentPiece.rotation;
	while (board.testMovement(shadowPiece.x, shadowPiece.y + 1, shadowPiece.rotation, shadowPiece.current, thePieces))
		shadowPiece.y++;
}

void game::drawTheFrame(manageScreen &screen, board &board, setup &setup, thePieces &thePieces, int holdedPiece, Piece &currentPiece, Piece &shadowPiece, randomizer &random, int piecePositonInTheBag)
{
	screen.drawPlayGround();
	screen.drawTheBoard(board, setup.pieceGraphic);
	if (setup.nextPiecesNumber > 0)
		screen.drawNextPieces(setup.enhanced, setup.nextPiecesNumber, piecePositonInTheBag, setup.pieceGraphic, random, thePieces, 255);
	if (holdedPiece > -1)
		screen.drawPieceToHold(holdedPiece, setup.pieceGraphic, thePieces, 255);
	screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
	if (setup.shadow)
		screen.drawCurrentPiece(shadowPiece, thePieces, setup.pieceGraphic, 64);
	screen.render();
}