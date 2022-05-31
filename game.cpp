#include "game.hpp"
#include "menu.hpp"
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

void game::rotateRight(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern)
{
	int virtualRotation = currentPiece.rotation;
	if (virtualRotation == 3) { virtualRotation = 0; }
	else { virtualRotation++; }
    bool rotationOK{false};
    int testNumber{0};
    std::pair<int, int> offsetCoordToTest;
    do {
        if(currentPiece.current == 2) { offsetCoordToTest = srs.getoffsetRightRotationI(virtualRotation, testNumber); }
        else { offsetCoordToTest = srs.getoffsetRightRotation(virtualRotation, testNumber); }
std::cout << "offset: (" << offsetCoordToTest.first << " , " << offsetCoordToTest.second << ")" << std::endl;
        rotationOK = board.testMovement(offsetCoordToTest.first + currentPiece.x, offsetCoordToTest.second + currentPiece.y, virtualRotation, currentPiece.current, thePieces);
std::cout << "rotation OK ? " ;
if(rotationOK) { std::cout << "oui" << std::endl; }
else  { std::cout << "non" << std::endl; }
        if(rotationOK) {
            currentPiece.x += offsetCoordToTest.first;
            currentPiece.y += offsetCoordToTest.second;
        }
        ++testNumber;
        if (!setup.superRotationSystem) { testNumber = 5; }
    } while (testNumber < 5 && !rotationOK);
    if(rotationOK) {
        currentPiece.rotation = virtualRotation;
        if (currentPiece.current == 3 && !board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)){
            pattern.TspinSearch = true;
        }
    }
}

void game::rotateLeft(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, pattern &pattern)
{
	int virtualRotation = currentPiece.rotation;
	if (virtualRotation == 3) { virtualRotation = 0; }
	else { virtualRotation++; }
    bool rotationOK{false};
    int testNumber{0};
    std::pair<int, int> offsetCoordToTest;
    do {
        if(currentPiece.current == 2) { offsetCoordToTest = srs.getoffsetLeftRotationI(virtualRotation, testNumber); }
        else { offsetCoordToTest = srs.getoffsetLeftRotation(virtualRotation, testNumber); }
std::cout << "offset: (" << offsetCoordToTest.first << " , " << offsetCoordToTest.second << ")" << std::endl;
        rotationOK = board.testMovement(offsetCoordToTest.first + currentPiece.x, offsetCoordToTest.second + currentPiece.y, virtualRotation, currentPiece.current, thePieces);
std::cout << "rotation OK ? " ;
if(rotationOK) { std::cout << "oui" << std::endl; }
else  { std::cout << "non" << std::endl; }
        if(rotationOK) {
            currentPiece.x += offsetCoordToTest.first;
            currentPiece.y += offsetCoordToTest.second;
        }
        ++testNumber;
        if (!setup.superRotationSystem) { testNumber = 5; }
    } while (testNumber < 5 && !rotationOK);
    if(rotationOK) {
        currentPiece.rotation = virtualRotation;
        if (currentPiece.current == 3 && !board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)){
            pattern.TspinSearch = true;
        }
    }
}

int game::hardDrop(Piece &currentPiece, board &board, thePieces &thePieces, setup &setup, manageScreen &screen)
{
    int cpt{0};
	while (board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)) {
		++currentPiece.y;
		++cpt;
		if(setup.gameType != 3){
            screen.drawTheBoard(board, setup.pieceGraphic);
            screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
            screen.render();
            sf::sleep(sf::milliseconds(3));
		}
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

void game::drawTheFrame(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, int holdedPiece, Piece &currentPiece, Piece &shadowPiece, randomizer &random, int piecePositonInTheBag, inGameFlags &inGameFlags, std::string elapsedTime)
{
    screen.clear();
	screen.drawPlayGround("NIVEAU", "SCORE", "LIGNES", "TEMPS");
	if(allowDrawAll){
        screen.drawTheBoard(board, setup.pieceGraphic);
        if (setup.nextPiece)
            screen.drawNextPieces(setup.enhanced, setup.nextPiecesNumber, piecePositonInTheBag, setup.pieceGraphic, random, thePieces, 255);
        if (holdedPiece > -1)
            screen.drawPieceToHold(holdedPiece, setup.pieceGraphic, thePieces, 255);
        screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
        if (setup.shadow)
            screen.drawCurrentPiece(shadowPiece, thePieces, setup.pieceGraphic, 64);
	}
	else { screen.drawEmptyBoard(setup.pieceGraphic); }
	screen.printIndicators(inGameFlags.level, inGameFlags.score, inGameFlags.nbLines, elapsedTime);
	screen.render();
	if(setup.gameType == 3 && allowDrawAll){ sf::sleep(sf::seconds(1)); }
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

void game::lockoutPiece(board &board, pattern &pattern, manageScreen &screen, setup &setup, inGameFlags &inGameFlags, Piece &currentPiece, randomizer &random, thePieces &thePieces, timer &fallingPieceTimer, sf::Int32& underPreasureTime, sound& gameSound)
{
    board.copyPieceInBoard(currentPiece, thePieces);
    if(board.patternSearch(pattern, currentPiece)) {
        screen.drawTheBoard(board, setup.pieceGraphic);
        screen.drawPatternAnimation(pattern, board, setup.pieceGraphic);
        board.shiftBlocksAfterLines(pattern);
        board.IsThereClearBoard(pattern);
        if(pattern.nbLines > 0){
            if(setup.gameType == 5) { underPreasureTime += pattern.nbLines * 4000; }
            inGameFlags.nbLines += pattern.nbLines;
            if(isLevelUp(inGameFlags.level, inGameFlags.nbLines)){
                ++inGameFlags.level;
                fallingPieceTimer.setTimerDuration(calculateFallingPieceTimerDuration(inGameFlags.level));
                gameSound.playSound(4);
            }
            gameSound.playSound(5);
        }
        inGameFlags.score = calculateScore(pattern, inGameFlags.score, inGameFlags.level);
        board.clearPattern(pattern);
    }
    inGameFlags.piecePositonInTheBag = random.incrementPiecePositonInTheBag(setup.enhanced, inGameFlags.piecePositonInTheBag, setup.sevenBag);
    currentPiece.current = random.getPieceAtPosition(inGameFlags.piecePositonInTheBag);
    inGameFlags.lockedout = false;
    inGameFlags.holded = false;
    if (!board.putNewPieceInBoard(currentPiece, thePieces))
        inGameFlags.gameOver = true;
}

void game::launchParty(manageScreen &screen, setup &setup, sound& gameSound)
{
        randomizer random;
        inGameFlags inGameFlags;
        inGameFlags.level = setup.startLevel;
        inGameFlags.fisrtShuffle = true;
        while(inGameFlags.fisrtShuffle) {
            random.initTheBag(setup.enhanced, setup.sevenBag);
            inGameFlags.fisrtShuffle = random.testFirstShuffle(setup.enhanced);
        }
        bool allowDrawAll{true};
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
        timer fallingPieceTimer(calculateFallingPieceTimerDuration(inGameFlags.level));
        fallingPieceTimer.startTimer();
        sf::Clock timePlayed;
        sf::Time timeElapsed;
        sf::Int32 elapsedTime;
        timer underPreasureTimer(1000);
        sf::Int32 underPreasureTime{15000};
        if(setup.gameType == 5) {
            underPreasureTimer.restartTimer();
        }
        else { timePlayed.restart(); }
        timer inclusionTimer(25000);
        if(setup.gameType == 4) { inclusionTimer.startTimer(); }
        eventReader::gameControl gameEvent;
        gameSound.playSound(6);
        while(!inGameFlags.gameOver && !inGameFlags.goalReached) {
            gameEvent = eventReader.getEvent(screen.m_window);
            int hardDropHigthFall{0};
            switch (gameEvent) {
                case eventReader::gameControl::rotateRight:
                    rotateRight(currentPiece, board, thePieces, setup, pattern);
                    gameSound.playSound(1);
                    break;
                case eventReader::gameControl::rotateLeft:
                    rotateLeft(currentPiece, board, thePieces, setup, pattern);
                    gameSound.playSound(1);
                    break;
                case eventReader::gameControl::softDrop:
                    if(board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)){
                        currentPiece.y++;
                        gameSound.playSound(2);
                    }
                    else
                        if(setup.lockout)
                            inGameFlags.lockedout = true;   // SI LOCKOUT DISABLE TESTER SI PEUT DESCENDRE -> SI NON PASSE A PIECE SUIVANTE
                        else
                            inGameFlags.lockedout = true;         // lancer le timer du lockout
                    ++inGameFlags.score;
                    break;
                case eventReader::gameControl::hardDrop:                    // hard drop
                    hardDropHigthFall = hardDrop(currentPiece, board, thePieces, setup, screen);
                    inGameFlags.score += hardDropHigthFall * 2;
                    inGameFlags.lockedout = true;
                    gameSound.playSound(0);
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
                        allowDrawAll = true;
                        inGameFlags.holded = true;
                        holdPiece(random, setup, currentPiece, inGameFlags.holdedPiece, inGameFlags.piecePositonInTheBag);
                        if(!board.putNewPieceInBoard(currentPiece, thePieces))
                            inGameFlags.gameOver = true;
                    }
                    break;
                case eventReader::gameControl::pause :
                    static sf::Time timeElapsedPlayed;
                    static sf::Int32 elapsedTimePlayed;
                    static std::string timeString;
                    while(eventReader.getEvent(screen.m_window) != eventReader::gameControl::pause) {
                        screen.clear();
                        screen.drawPlayGround("NIVEAU", "SCORE", "LIGNES", "TEMPS");
                        screen.drawEmptyBoard(setup.pieceGraphic);
                        screen.displayText("Pause", 72, sf::Color::White, 435, 250);
                        screen.displayText("Pressez", 72, sf::Color::White, 400, 355);
                        screen.displayText("Escape", 72, sf::Color::White, 415, 470);
                        if(setup.gameType == 5){
                            if(underPreasureTimer.isTimeElapsed()) {
                                if(underPreasureTime > 0)  {
                                    underPreasureTime -= 1000;
                                    underPreasureTimer.restartTimer();
                                }
                            }
                            timeString = convertTimeToStringMinuteSecond(underPreasureTime);
                        }
                        else {
                            timeElapsedPlayed = timePlayed.getElapsedTime();
                            elapsedTimePlayed = timeElapsedPlayed.asMilliseconds();
                            timeString = convertTimeToStringMinuteSecond(elapsedTimePlayed);
                        }
                        screen.printIndicators(inGameFlags.level, inGameFlags.score, inGameFlags.nbLines, timeString);
                        screen.render();                   // pause
                    }
                    screen.drawTheBoard(board,  setup.pieceGraphic);
                    break;
                case eventReader::gameControl::none:
                    break;
                default:
                    break;
            }
            bool canShiftLower = board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces);
            if(!setup.lockout && !canShiftLower) {
                inGameFlags.lockedout = true;
                fallingPieceTimer.startTimer();
            }
            if(fallingPieceTimer.isTimeElapsed()) {
                if(canShiftLower){ ++currentPiece.y; }
                else { inGameFlags.lockedout = true; }
                fallingPieceTimer.startTimer();
            }
            if(inGameFlags.lockedout) {
                lockoutPiece(board, pattern, screen, setup, inGameFlags, currentPiece, random, thePieces,fallingPieceTimer, underPreasureTime, gameSound);
                allowDrawAll = true;
            }
            setShadowPiecePosition(currentPiece, shadowPiece, board, thePieces);
            timeElapsed = timePlayed.getElapsedTime();
            elapsedTime = timeElapsed.asMilliseconds();
            std::string timeStr = convertTimeToStringMinuteSecond(elapsedTime);
            if(timeStr == "03:00" && setup.gameType == 1){
                inGameFlags.goalReached = true;
            }
            if(inGameFlags.nbLines >= 40 && setup.gameType == 2){
                inGameFlags.goalReached = true;
            }
            if(inclusionTimer.isTimeElapsed() && setup.gameType == 4){
                inclusionTimer.restartTimer();
                board.insertBricks();
            }
            if(setup.gameType == 5){
                if(underPreasureTimer.isTimeElapsed()) {
                    underPreasureTime -= 1000;
                    underPreasureTimer.restartTimer();
                    if(underPreasureTime < 0) { inGameFlags.gameOver = true; }
                }
                timeStr = convertTimeToStringMinuteSecond(underPreasureTime);
            }
            drawTheFrame(allowDrawAll, screen, board, setup, thePieces, inGameFlags.holdedPiece, currentPiece, shadowPiece, random, inGameFlags.piecePositonInTheBag, inGameFlags, timeStr);
            if(setup.gameType == 3) { allowDrawAll = false; }
        }
        gameSound.playSound(6);
        inGameFlags.holdedPiece = -1;
        endOfParty(screen, eventReader, inGameFlags.gameOver);
        scoreList scoreList;
        scoreList.buildScoreList(setup.gameType, setup.enhanced);
        if(setup.gameType == 2 && !inGameFlags.gameOver) {
            inGameFlags.score = static_cast<int>(elapsedTime);
        }
        if(setup.gameType == 2 && inGameFlags.gameOver) { return; }
        if(scoreList.isScoreEnterInScoreList(inGameFlags.score,setup.gameType)){
            int ranking = scoreList.enterScoreInList(setup.pseudo, inGameFlags.score, setup.gameType, setup.enhanced);
            screen.drawScoreList(scoreList.m_scoreArray, ranking, setup.gameType);
            while(!eventReader.getSpace(screen.m_window)){}
        }
}

void game::endOfParty(manageScreen &screen, eventReader &eventReader, bool gameOver)
{
        screen.render();
        if(gameOver) { screen.displayText("PERDU", 60 , sf::Color::White, 445, 320); }
        else { screen.displayText("FINI", 60, sf::Color::White, 455, 320); }
        screen.displayText("Pressez Espace", 35, sf::Color::White, 400, 390);
        screen.render();
        while(!eventReader.getSpace(screen.m_window)){}
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
        return score + scoreAction + (static_cast<int>(scoreAction * 0.5));
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
	inGameFlags.goalReached = false;
}
