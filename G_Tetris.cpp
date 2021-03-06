#include <SFML/Graphics.hpp>
#include <iostream>
#include "screenmanagement.h"
#include "7-bag.h"
#include "eventreader.h"
#include "board.h"
#include "pieces.h"
                                                                                            //Screen dimension constants
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
const int playGroundWidth = 300;
const int playGroundheigth = 600;

int main( int argc, char* args[] )
{
    struct setup{
        bool enhanced = true;                                                               // 11 or 7 pieces game
        bool sevenBag = true;                                                               // randow method : 7-bag or random
        bool shadow = true;                                                                 // display shadow piece ON/OFF
        bool superRotationSystem{true};                                                     // system de ration avancee ON/OFF
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
    }setup;

    bool lockedout{false},holded{false};
    int holdedPiece{-1};

    manageScreen screen;                                                                    // objects used
    randomizer random;
    eventReader eventReader;
    thePieces thePieces;
    board board;
    currentPiece currentPiece, shadowPiece;
    pattern pattern;

    screen.render();
	    screen.loadBitmapFile("graphics/graphics.png");
        bool jejoue(true);
        sf::Keyboard::Key eventKey;
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
                eventKey = eventReader.getEvent(screen.m_window);
                switch (eventKey) {
                    case sf::Keyboard::Numpad1:                     // rotation clockwise
                    case sf::Keyboard::Numpad5:
                    case sf::Keyboard::Numpad9:
                    case sf::Keyboard::Up:
                        virtualRotation = currentPiece.rotation;
                        if(virtualRotation == 3)
                            virtualRotation = 0;
                        else
                            virtualRotation++;
                        if(board.testMovement(currentPiece.x, currentPiece.y, virtualRotation, currentPiece.current, thePieces)) {
                            currentPiece.rotation = virtualRotation;
							if (currentPiece.current == 3 && !board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces))
								pattern.TspinSearch = true;
                        }
                        else
                            if(setup.superRotationSystem)
                                board.superRotationSystem(currentPiece, virtualRotation, thePieces);
                        break;
                    case sf::Keyboard::RControl:                    // Rotate Counterclockwise
                    case sf::Keyboard::LControl:
                    case sf::Keyboard::Numpad3:
                    case sf::Keyboard::Numpad7:
                    case sf::Keyboard::Z:
                        virtualRotation = currentPiece.rotation;
                        if(virtualRotation == 0)
                            virtualRotation = 3;
                        else
                            virtualRotation--;
                        if(board.testMovement(currentPiece.x, currentPiece.y, virtualRotation, currentPiece.current, thePieces)) {
                            currentPiece.rotation = virtualRotation;
                            if(currentPiece.current == 3 && !board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces))
								pattern.TspinSearch = true;
                        }
                        else
                            if(setup.superRotationSystem)
                                board.superRotationSystem(currentPiece, virtualRotation, thePieces);
                        break;
                    case sf::Keyboard::Down:                     // soft drop
                    case sf::Keyboard::Numpad2:
                        if(board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces))
                           currentPiece.y++;
// � changer par test si descente possible, si non d�clancher timer lockout
                        else
                           if(setup.lockout)
                                lockedout = true;   // � remplacer par lancement timer du lockout
                            else
                                lockedout = true;         // lancer le timer du lockout
                        break;
                    case sf::Keyboard::Space:                    // hard drop
                    case sf::Keyboard::Numpad8:
                        while(board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)) {
                            currentPiece.y++;
                            screen.drawTheBoard(board, setup.pieceGraphic);
                            screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
                            screen.render();
                            sf::sleep(sf::milliseconds(2));
                        }
                        if(setup.lockout)
                            lockedout = true;   // � remplacer par lancement timer du lockout
                        else
                            lockedout = true;
                        break;
                    case sf::Keyboard::Left:              // move left
                    case sf::Keyboard::Numpad4:
                        if(board.testMovement(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces))
                           currentPiece.x--;
                        break;
                    case sf::Keyboard::Right:             // move right
                    case sf::Keyboard::Numpad6:
                        if(board.testMovement(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces))
                           currentPiece.x++;
                        break;
                    case sf::Keyboard::RShift:            // hold
                    case sf::Keyboard::LShift:
                    case sf::Keyboard::Numpad0:
                    case sf::Keyboard::C:
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
                    case sf::Keyboard::F1:                   // pause
                    case sf::Keyboard::Escape:
                        screen.pauseMenu(board, setup.pieceGraphic, eventReader);
// arret des timers
//
// reprise des timers
                        break;
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
                screen.drawPlayGround();
                if(setup.nextPiecesNumber > 0)
                     screen.drawNextPieces(setup.enhanced, setup.nextPiecesNumber, piecePositonInTheBag, setup.pieceGraphic, random, thePieces, 255);
                if(holdedPiece > -1)
                    screen.drawPieceToHold(holdedPiece, setup.pieceGraphic, thePieces, 255);        // draw the holded piece
                screen.drawTheBoard(board, setup.pieceGraphic);
                screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
                if(setup.shadow) {
                    shadowPiece.x = currentPiece.x;
                    shadowPiece.y = currentPiece.y;
                    shadowPiece.current = currentPiece.current;
                    shadowPiece.rotation = currentPiece.rotation;
                    while(board.testMovement(shadowPiece.x, shadowPiece.y + 1, shadowPiece.rotation, shadowPiece.current, thePieces))
                        shadowPiece.y++;
                    screen.drawCurrentPiece(shadowPiece, thePieces, setup.pieceGraphic, 64);
                }
                screen.render();
            }
        }
	screen.m_window.close();
	return 0;
}
