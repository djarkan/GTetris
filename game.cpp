#include "game.hpp"
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
        if(currentPiece.current == 2) { offsetCoordToTest = srs.getoffsetRightRotationI(currentPiece.rotation, testNumber); }
        else { offsetCoordToTest = srs.getoffsetRightRotation(currentPiece.rotation, testNumber); }
        rotationOK = board.testMovement(offsetCoordToTest.first + currentPiece.x, offsetCoordToTest.second + currentPiece.y, virtualRotation, currentPiece.current, thePieces);
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
	if (virtualRotation == 0) { virtualRotation = 3; }
	else { virtualRotation--; }
    bool rotationOK{false};
    int testNumber{0};
    std::pair<int, int> offsetCoordToTest;
    do {
        if(currentPiece.current == 2) { offsetCoordToTest = srs.getoffsetLeftRotationI(currentPiece.rotation, testNumber); }
        else { offsetCoordToTest = srs.getoffsetLeftRotation(currentPiece.rotation, testNumber); }
        rotationOK = board.testMovement(offsetCoordToTest.first + currentPiece.x, offsetCoordToTest.second + currentPiece.y, virtualRotation, currentPiece.current, thePieces);
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

void game::drawTheFrame(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, Piece &currentPiece, Piece &shadowPiece, randomizer &random, std::string elapsedTime, bool countTdownPending)
{
	screen.drawPlayGround(m_gameTtranslation.m_Root["level"][setup.language].asString(),
                          m_gameTtranslation.m_Root["score"][setup.language].asString(),
                          m_gameTtranslation.m_Root["lines"][setup.language].asString(),
                          m_gameTtranslation.m_Root["time"][setup.language].asString(),
                          m_gameTtranslation.m_Root["hold"][setup.language].asString(),
                          m_gameTtranslation.m_Root["nextPiece"][setup.language].asString());
	if(allowDrawAll){
        screen.drawTheBoard(board, setup.pieceGraphic);
        if(!countTdownPending) {
            if (setup.nextPiece)
                screen.drawNextPieces(setup.enhanced, setup.nextPiecesNumber, inGameFlags.piecePositonInTheBag, setup.pieceGraphic, random, thePieces, 255);
            if (inGameFlags.holdedPiece > -1)
                screen.drawPieceToHold(inGameFlags.holdedPiece, setup.pieceGraphic, thePieces, 255);
            screen.drawCurrentPiece(currentPiece, thePieces, setup.pieceGraphic, 255);
            if (setup.shadow)
                screen.drawCurrentPiece(shadowPiece, thePieces, setup.pieceGraphic, 64);
        }
	}
	else { screen.drawEmptyBoard(setup.pieceGraphic); }
	screen.printIndicators(inGameFlags.level, inGameFlags.score, inGameFlags.nbLines, elapsedTime);
	if(setup.gameType == 3 && allowDrawAll){ sf::sleep(sf::seconds(1)); }

}

void game::holdPiece(randomizer &random, setup &setup, Piece &currentPiece, int &holdedPiece)
{
    if(holdedPiece < 0) {
        holdedPiece = currentPiece.current;                                             // if hold is empty hold is the current piece
        inGameFlags.piecePositonInTheBag = random.incrementPiecePositonInTheBag(setup.enhanced, inGameFlags.piecePositonInTheBag, setup.sevenBag);
        currentPiece.current = random.getPieceAtPosition(inGameFlags.piecePositonInTheBag);
    }
    else {
        int swapper = holdedPiece;                                                      // swap hold and current piece
        holdedPiece = currentPiece.current;
        currentPiece.current = swapper;
    }
}

void game::lockoutPiece(board &board, pattern &pattern, manageScreen &screen, setup &setup, Piece &currentPiece, randomizer &random, thePieces &thePieces, timer &fallingPieceTimer, sf::Int32& underPreasureTime, sound& gameSound, statistics& playerStats)
{
    board.copyPieceInBoard(currentPiece, thePieces);
    if(board.patternSearch(pattern, currentPiece)) {
        playerStats.addPatternsToStats(pattern);
        screen.drawTheBoard(board, setup.pieceGraphic);
        screen.drawPatternAnimation(pattern, board, setup.pieceGraphic);
        board.shiftBlocksAfterLines(pattern);
        if(pattern.nbLines > 0){
            if(setup.gameType == 5) { underPreasureTime += pattern.nbLines * 4000; }
            inGameFlags.nbLines += pattern.nbLines;
            if(isLevelUp(inGameFlags.level, inGameFlags.nbLines)  && inGameFlags.level < 9 && (setup.gameType != 1 && setup.gameType != 2)){
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

void game::launchParty(manageScreen &screen, setup &setup, sound& gameSound, statistics& playerStats)
{
        randomizer random;
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
//        eventReader eventReader;
        if(!m_gameTtranslation.loadJsonFile("language\\play.json"))
        {
            errorMessage(screen, setup.language);
            return;
        }
        countDown(allowDrawAll, screen, board, setup, thePieces, currentPiece, shadowPiece, random, gameSound);
        timer fallingPieceTimer(calculateFallingPieceTimerDuration(inGameFlags.level));
        fallingPieceTimer.startTimer();
        timer lockoutTimer(500);
        bool beginLockoutTimer{false};
        sf::Clock timePlayed;
        sf::Time timeElapsed;
        sf::Int32 elapsedTime;
        sf::Int32 elapsedTimePause = 0;
        timer underPreasureTimer(1000);
        sf::Int32 underPreasureTime{15000};
        if(setup.gameType == 5) {
            underPreasureTimer.startTimer();
        }
        else { timePlayed.restart(); }
        timer inclusionTimer(25000);
        if(setup.gameType == 4) { inclusionTimer.startTimer(); }
        eventReader::gameControl gameEvent;
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
                    ++inGameFlags.score;
                    break;
                case eventReader::gameControl::hardDrop:                    // hard drop
                    hardDropHigthFall = hardDrop(currentPiece, board, thePieces, setup, screen);
                    inGameFlags.score += hardDropHigthFall * 2;
                    inGameFlags.lockedout = true;
                    gameSound.playSound(0);
                    break;
                case eventReader::gameControl::shiftLeft:              // move left
                    if(board.testMovement(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces)) {
                        currentPiece.x--;
                        gameSound.playSound(2);
                    }
                    break;
                case eventReader::gameControl::shiftRight:             // move right
                    if(board.testMovement(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces)) {
                        currentPiece.x++;
                        gameSound.playSound(2);
                    }
                    break;
                case eventReader::gameControl::holdPiece:            // hold
                    if(!inGameFlags.holded && setup.hold) {
                        allowDrawAll = true;
                        inGameFlags.holded = true;
                        holdPiece(random, setup, currentPiece, inGameFlags.holdedPiece);
                        if(!board.putNewPieceInBoard(currentPiece, thePieces))
                            inGameFlags.gameOver = true;
                    }
                    break;
                case eventReader::gameControl::pause :  {                  // pause
                    std::string timeString;
                    sf::Clock timePaused;
                    timePaused.restart();
                    if(setup.gameType == 5){ underPreasureTimer.pauseTimer(); }
                    if(setup.gameType == 4){ inclusionTimer.pauseTimer(); }
                    screen.clear();
                    screen.drawPlayGround(m_gameTtranslation.m_Root["level"][setup.language].asString(),
                                            m_gameTtranslation.m_Root["score"][setup.language].asString(),
                                            m_gameTtranslation.m_Root["lines"][setup.language].asString(),
                                            m_gameTtranslation.m_Root["time"][setup.language].asString(),
                                            m_gameTtranslation.m_Root["hold"][setup.language].asString(),
                                            m_gameTtranslation.m_Root["nextPiece"][setup.language].asString());
                    screen.drawEmptyBoard(setup.pieceGraphic);
                    std::string label = m_gameTtranslation.m_Root["pause"][setup.language].asString();
                    float x = 512 - ((label.size() / 2.f) * 31);
                    screen.displayText(label, 72, sf::Color::White, x, 250);
                    label = m_gameTtranslation.m_Root["press"][setup.language].asString();
                    x = 512 - ((label.size() / 2.f) * 31);
                        screen.displayText(label, 72, sf::Color::White, x, 355);
                    label = m_gameTtranslation.m_Root["escape"][setup.language].asString();
                    x = 512 - ((label.size() / 2.f) * 31);
                    screen.displayText(label, 72, sf::Color::White, x, 470);
                    timeElapsed = timePlayed.getElapsedTime();
                    elapsedTime = timeElapsed.asMilliseconds() - elapsedTimePause;
                    timeString = convertTimeToStringMinuteSecond(elapsedTime);
                    screen.printIndicators(inGameFlags.level, inGameFlags.score, inGameFlags.nbLines, timeString);
                    screen.render();
                    while(eventReader.getEvent(screen.m_window) != eventReader::gameControl::pause) { ; }
                    screen.drawTheBoard(board,  setup.pieceGraphic);
                    if(setup.gameType == 5){ underPreasureTimer.restartTimer(); }
                    if(setup.gameType == 4){ inclusionTimer.restartTimer(); }
                    sf::Time pausedTime = timePaused.getElapsedTime();
                    elapsedTimePause += pausedTime.asMilliseconds();
                    countDown(allowDrawAll, screen, board, setup, thePieces, currentPiece, shadowPiece, random, gameSound);
                    break;
                }
                case eventReader::gameControl::none:
                    break;
                default:
                    break;

            }
            bool canShiftLower = board.testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces);
            if(setup.lockout && canShiftLower) { lockoutTimer.startTimer(); }
            if(!setup.lockout && !canShiftLower) { inGameFlags.lockedout = true; }
            if(setup.lockout && !canShiftLower && !beginLockoutTimer)  {
                beginLockoutTimer = true;
                lockoutTimer.startTimer();
            }
            if(fallingPieceTimer.isTimeElapsed()  && canShiftLower) {
                ++currentPiece.y;
                fallingPieceTimer.startTimer();
            }

            if(lockoutTimer.isTimeElapsed()) {
                inGameFlags.lockedout = true;
                fallingPieceTimer.startTimer();
            }
            if(inGameFlags.lockedout == true) {
                beginLockoutTimer = false;
                lockoutPiece(board, pattern, screen, setup, currentPiece, random, thePieces,fallingPieceTimer, underPreasureTime, gameSound, playerStats);
                allowDrawAll = true;
            }
            setShadowPiecePosition(currentPiece, shadowPiece, board, thePieces);
            timeElapsed = timePlayed.getElapsedTime();
            elapsedTime = timeElapsed.asMilliseconds() - elapsedTimePause;
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
            screen.clear();
            drawTheFrame(allowDrawAll, screen, board, setup, thePieces, currentPiece, shadowPiece, random, timeStr, false);
            screen.render();
            if(setup.gameType == 3) { allowDrawAll = false; }
        }
        gameSound.playSound(6);
        inGameFlags.holdedPiece = -1;
        endOfParty(screen, inGameFlags.gameOver, setup);
        scoreList scoreList;
        scoreList.buildScoreList(setup.gameType, setup.enhanced);
        if(setup.gameType == 2 && !inGameFlags.gameOver) {
            inGameFlags.score = static_cast<int>(elapsedTime);
        }
        if(setup.gameType == 2 && inGameFlags.gameOver) { return; }
        if(scoreList.isScoreEnterInScoreList(inGameFlags.score,setup.gameType)){
            int ranking = scoreList.enterScoreInList(setup.pseudo, inGameFlags.score, setup.gameType, setup.enhanced);
            screen.drawScoreList(scoreList.m_scoreArray,
                                 ranking,
                                 setup.gameType,
                                 m_gameTtranslation.m_Root["bestscore"][setup.language].asString(),
                                 m_gameTtranslation.m_Root["pressspace"][setup.language].asString());
            while(!eventReader.getSpace(screen.m_window)){}
        }
}

void game::endOfParty(manageScreen &screen, bool gameOver, setup& setup)
{
        screen.render();
        std::string label;
        if(gameOver) {
            label = m_gameTtranslation.m_Root["gameover"][setup.language].asString();
            float x = 512 - ((label.size() / 2.f) * 31);
            screen.displayText(label, 72, sf::Color::White, x, 250);
        }
        else {
            label = m_gameTtranslation.m_Root["ended"][setup.language].asString();
            float x = 512 - ((label.size() / 2.f) * 31);
            screen.displayText(label, 72, sf::Color::White, x, 250);
        }
        label = m_gameTtranslation.m_Root["press"][setup.language].asString();
        float x = 512 - ((label.size() / 2.f) * 31);
        screen.displayText(label, 72, sf::Color::White, x, 355);
        label = m_gameTtranslation.m_Root["escape"][setup.language].asString();
        x = 512 - ((label.size() / 2.f) * 31);
        screen.displayText(label, 72, sf::Color::White, x, 470);
        screen.render();
        while(!eventReader.getEscape(screen.m_window)){}
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
                    (50 * (pattern.combo - 1) * level) + pattern.ClearBoard * level * 300 ;
    if(pattern.backToBack > 1){
        return score + scoreAction + (static_cast<int>(scoreAction * 0.5));
    }
    else {
        return score + scoreAction;
    }
}

void game::clearInGameFlags()
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

void game::countDown(bool allowDrawAll, manageScreen &screen, board &board, setup &setup, thePieces &thePieces, Piece &currentPiece, Piece &shadowPiece, randomizer &random, sound& gameSound)
{
    timer countDonwTimer(1000);
    countDonwTimer.startTimer();
    int seconds{3};
    gameSound.playSound(8);
    do {
        screen.clear();
        drawTheFrame(allowDrawAll, screen, board, setup, thePieces, currentPiece, shadowPiece, random, "00:00",true);
        screen.drawCircles();
        screen.displayText(std::to_string(seconds), 100, sf::Color::White, 490, 325);
        screen.render();
        while(!countDonwTimer.isTimeElapsed()) {  }
        --seconds;
        countDonwTimer.restartTimer();
        if(seconds > 0) { gameSound.playSound(8); }
        else { gameSound.playSound(6); }
    }
    while(seconds > 0);
}

void game::errorMessage(manageScreen &screen, int language)
{
    screen.errorMessage(m_gameTtranslation.m_Root["error"][language].asString(), m_gameTtranslation.m_Root["reinstall"][language].asString(), m_gameTtranslation.m_Root["pressspace"][language].asString());
    while(!eventReader.getSpace(screen.m_window)) ;
}
