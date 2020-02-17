#include "game.h"
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
    manageScreen screen;
	setup setup;
	inGameFlags inGameFlags;

    screen.loadBitmapFile("graphics/graphics.png");
    screen.loadFontFile("font/arial.ttf");
    inGameFlags.jejoue = true;
    while(inGameFlags.jejoue) {

            // debut prog : menu

        launchParty(screen, setup, inGameFlags);

        clearInGameFlags(inGameFlags);
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

int game::hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern, manageScreen &screen)
{
    int cpt{0};
	while (board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)) {
		++currentPiece.y;
		++cpt;
		screen.drawTheBoard(board, setup.pieceGraphic);
		screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
		screen.render();
		sf::sleep(sf::milliseconds(2));
	}
	return cpt;
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

void game::drawTheFrame(manageScreen &screen, board &board, setup &setup, thePieces &thePieces, int holdedPiece, Piece &currentPiece, Piece &shadowPiece, randomizer &random, int piecePositonInTheBag, inGameFlags &inGameFlags)
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
	screen.printIndicators(inGameFlags.level, inGameFlags.score, inGameFlags.nbLines);
	screen.render();
}

void game::holdPiece(randomizer &random, setup &setup, Piece &currentPiece, int &holdedPiece, int &piecePositonInTheBag)
{
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
}

void game::lockoutPiece(board &board, pattern &pattern, manageScreen &screen, setup &setup, inGameFlags &inGameFlags, Piece &currentPiece, randomizer &random, thePieces &thePieces, timer &fallingPieceTimer)
{
    board.copyPieceInBoard(currentPiece, thePieces);
    if(board.patternSearch(pattern, currentPiece)) {
        screen.drawTheBoard(board, setup.pieceGraphic);
        screen.shiftedLinesAnimation(pattern, board, setup.pieceGraphic);
        board.shiftBlocksAfterLines(pattern);
        board.IsThereClearBoard(pattern);
        if(pattern.nbLines > 0){
            inGameFlags.nbLines += pattern.nbLines;
            if(isLevelUp(inGameFlags.level, inGameFlags.nbLines)){
                ++inGameFlags.level;
                fallingPieceTimer.setTimerDuration(calculateFallingPieceTimerDuration(inGameFlags.level));
            }
        }
      // calcul score
        inGameFlags.score = calculateScore(pattern, inGameFlags.score, inGameFlags.level);
        board.clearPattern(pattern);        //n efface pas back to back
    }
    inGameFlags.piecePositonInTheBag = random.incrementPiecePositonInTheBag(setup.enhanced, inGameFlags.piecePositonInTheBag, setup.sevenBag);
    currentPiece.current = random.getPieceAtPosition(inGameFlags.piecePositonInTheBag);
    inGameFlags.lockedout = false;
    inGameFlags.holded = false;
    if (!board.putNewPieceInBoard(currentPiece, thePieces))
        inGameFlags.gameOver = true;
}

void game::launchParty(manageScreen &screen, setup &setup, inGameFlags &inGameFlags)
{
        randomizer random;
        timer fallingPieceTimer(calculateFallingPieceTimerDuration(inGameFlags.level));
        inGameFlags.fisrtShuffle = true;
        while(inGameFlags.fisrtShuffle) {
            random.initTheBag(setup.enhanced, setup.sevenBag);
            inGameFlags.fisrtShuffle = random.testFirstShuffle(setup.enhanced);
        }
        inGameFlags.piecePositonInTheBag = 0;
        board board;
        board.clearBoard();
        screen.drawTheBoard(board, setup.pieceGraphic);
        Piece currentPiece, shadowPiece;                                   // begin the party
        currentPiece.current = random.getPieceAtPosition(inGameFlags.piecePositonInTheBag);
        thePieces thePieces;
        if(setup.nextPiecesNumber > 0)
            screen.drawNextPieces(setup.enhanced, setup.nextPiecesNumber, inGameFlags.piecePositonInTheBag, setup.pieceGraphic, random, thePieces, 255);
        board.putNewPieceInBoard(currentPiece, thePieces);
        inGameFlags.gameOver = false;
        pattern pattern;
        eventReader eventReader;
        fallingPieceTimer.startTimer();
        while(!inGameFlags.gameOver) {
            eventReader::gameControl gameAction;
            gameAction = eventReader.getEvent(screen.m_window);
            int hardDropHigthFall{0};
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
                            inGameFlags.lockedout = true;   // SI LOCKOUT DISABLE TESTER SI PEUT DESCENDRE -> SI NON PASSE A PIECE SUIVANTE
                        else
                            inGameFlags.lockedout = true;         // lancer le timer du lockout
                    ++inGameFlags.score;
                    break;
                case eventReader::gameControl::hardDrop:                    // hard drop
                    hardDropHigthFall = hardDrop(currentPiece, board, thePieces, setup, pattern,screen);
                    inGameFlags.score += hardDropHigthFall * 2;
                    inGameFlags.lockedout = true;
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
                    if(!inGameFlags.holded && setup.hold) {
                        inGameFlags.holded = true;
                        holdPiece(random, setup, currentPiece, inGameFlags.holdedPiece, inGameFlags.piecePositonInTheBag);
                        if(!board.putNewPieceInBoard(currentPiece, thePieces))
                            inGameFlags.gameOver = true;
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
            if(fallingPieceTimer.isTimeElapsed())
            {
if(board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)){
    ++currentPiece.y;
}
else
    if(setup.lockout)         // faire une fonction pour le softdrop
        inGameFlags.lockedout = true;   // SI LOCKOUT DISABLE TESTER SI PEUT DESCENDRE -> SI NON PASSE A PIECE SUIVANTE
    else
        inGameFlags.lockedout = true;
                fallingPieceTimer.startTimer();
            }
            if(inGameFlags.lockedout)                                                                                           // piece locked
                lockoutPiece(board, pattern, screen, setup, inGameFlags, currentPiece, random, thePieces,fallingPieceTimer);
            setShadowPiecePosition(currentPiece, shadowPiece, board, thePieces);
            drawTheFrame(screen, board, setup, thePieces, inGameFlags.holdedPiece, currentPiece, shadowPiece, random, inGameFlags.piecePositonInTheBag, inGameFlags);
        }
        inGameFlags.holdedPiece = -1;
}

sf::Int32 game::calculateFallingPieceTimerDuration(const int level)
{
    return static_cast<sf::Int32>(pow((0.8 - ((level - 1) * 0.007)),level - 1) * 1000);
}

bool game::isLevelUp(int level, int nbLines)
{
    return ((nbLines / 10) + 1) > level;
}

int game::calculateScore(const pattern &pattern, int score, const int level)
{
    int scoreAction = ((pattern.singleLine * level * 100) + (pattern.doubleLine * level * 300) +
                    (pattern.tripleLine * level * 500) + (pattern.tetris * level * 800) +
                    (pattern.miniTspin * level *100) + (pattern.miniTspinSingle * level *200) +
                    (pattern.miniTspinDouble * level *400) +
                    (pattern.Tspin * level *400) + (pattern.TspinSingle * level *800) +
                    (pattern.TspinDouble * level *1200) + (pattern.TspinTriple * level *1600)) +
                    (50 * (pattern.combo - 1) * level);
    if(pattern.backToBack > 1){
        return score + scoreAction + (scoreAction * 0.5);
    }
    else {
        return score + scoreAction;
    }
}

void game::clearInGameFlags(inGameFlags &inGameFlags)
{
	inGameFlags.lockedout = false;
    inGameFlags.holded = false;
    inGameFlags.holdedPiece = -1;
    inGameFlags.jejoue = true;
    inGameFlags.gameOver = false;
    inGameFlags.fisrtShuffle = true;
    inGameFlags.piecePositonInTheBag = 0;								// store the N° of the holded piece
    inGameFlags.level = 1;
    inGameFlags.nbLines = 0;
	inGameFlags.score = 0 ;
}
