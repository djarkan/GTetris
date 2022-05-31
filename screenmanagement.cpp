#include "screenmanagement.hpp"

manageScreen::manageScreen(): m_window(sf::VideoMode(1024, 768), "G_Tetris v0.8", sf::Style::Close)
{

}

manageScreen::~manageScreen()
{

}

void manageScreen::close()
{                                                       //Destroy window
	m_window.close();
}

void manageScreen::render()
{                                                       //Display the window
    m_window.display();
}

void manageScreen::clear()
{
	m_window.clear();
}

void manageScreen::drawPlayGround(std::string levelLabel, std::string  scoreLabel, std::string lineLabel, std::string timeLabel)
{														//Draw boards (playung area, hold, next
    drawBoardArea();
    draw5NxetArea();
    drawHoldArea();
    drawNextArea();
    displayText(levelLabel, 24, sf::Color::White, 55, 460);
    displayText(scoreLabel, 24, sf::Color::White, 55, 500);
    displayText(lineLabel, 24, sf::Color::White, 55, 540);
    displayText(timeLabel, 24, sf::Color::White, 55, 580);
}
void manageScreen::drawBoardArea()
{
    sf::RectangleShape rectangle;
                                                                    // Draw playing Area border
    drawRectangle(342, 100, 340, 620, sf::Color(0x777777FF));
    drawRectangle(346, 100, 332, 616, sf::Color(0x909090FF));
    drawRectangle(350, 100, 324, 612, sf::Color(0xAAAAAAFF));
    drawRectangle(354, 100, 316, 608, sf::Color(0x909090FF));
    drawRectangle(358, 100, 308, 604, sf::Color(0x777777FF));
    drawRectangle(362, 100, 300, 600, sf::Color(sf::Color::Black));
}

void manageScreen::drawHoldArea()
{
    sf::RectangleShape rectangle;
                                                                        // Draw hold border
    drawRectangle(744, 50, 220, 150, sf::Color(0x777777FF));
    drawRectangle(748, 54, 212, 142, sf::Color(0x909090FF));
    drawRectangle(752, 58, 204, 134, sf::Color(0xAAAAAAFF));
    drawRectangle(756, 62, 196, 126, sf::Color(0x909090FF));
    drawRectangle(760, 66, 188, 118, sf::Color(0x777777FF));
    drawRectangle(764, 70, 180, 110, sf::Color(sf::Color::Black));
}
void manageScreen::drawNextArea()
{
    sf::RectangleShape rectangle;
                                                                        // Draw next border
    drawRectangle(80, 50, 220, 150, sf::Color(0x777777FF));
    drawRectangle(84, 54, 212, 142, sf::Color(0x909090FF));
    drawRectangle(88, 58, 204, 134, sf::Color(0xAAAAAAFF));
    drawRectangle(92, 62, 196, 126, sf::Color(0x909090FF));
    drawRectangle(96, 66, 188, 118, sf::Color(0x777777FF));
    drawRectangle(100, 70, 180, 110, sf::Color(sf::Color::Black));
}

void manageScreen::draw5NxetArea()
{
    sf::RectangleShape rectangle;
                                                                    // dessine le cadre des next
    drawRectangle(744, 240, 220, 480, sf::Color(0x777777FF));
    drawRectangle(748, 244, 212, 472, sf::Color(0x909090FF));
    drawRectangle(752, 248, 204, 464, sf::Color(0xAAAAAAFF));
    drawRectangle(756, 252, 196, 456, sf::Color(0x909090FF));
    drawRectangle(760, 256, 188, 448, sf::Color(0x777777FF));
    drawRectangle(764, 260, 180, 440, sf::Color(sf::Color::Black));
}

void manageScreen::drawRectangle(const float x, const float y, const float h, const float w, sf::Color couleur)
{
    sf::RectangleShape rectangle;

    rectangle.setPosition(x, y);
    rectangle.setSize(sf::Vector2f(h, w));
    rectangle.setFillColor(couleur);
    m_window.draw(rectangle);
}

void manageScreen::loadBitmapFile(const std::string title)
{
    if (!m_texturePiece.loadFromFile(title)) {
        std::cout << "erreur chargement du fichier: " << title << std::endl << "Veuillez réinstaller le programme." << std::endl;
        m_window.close();
    }
}

void manageScreen::drawEmptyBoard(const int pieceGraphic)
{
    sf::IntRect  sourceRectangle(11 * 32,pieceGraphic * 32,30,30);
    sf::Vector2f destination(362, 100);
    for(auto i = 3; i < 23; i++) {
        for(auto j = 0; j < 10; j++) {
            rawRenderCopy(sourceRectangle, destination, 255);
            destination.x +=30;
        }
        destination.y += 30;
        destination.x = 362;
    }
}

void manageScreen::drawNextPieces(bool enhanced, int nextPiecesNumber, int piecePositonInTheBag, int pieceGraphic, randomizer& random, thePieces& thePieces, const sf::Uint8 alpha)
{
    sf::RectangleShape rectangle;
    int offset{1};

    if(!enhanced && (piecePositonInTheBag + offset) > 6)
        offset = 5;
    int pieceToDraw = random.getPieceAtPosition(piecePositonInTheBag + offset);
    rectangle.setPosition(764, 70);
    rectangle.setSize(sf::Vector2f(180, 110));
    rectangle.setFillColor(sf::Color(sf::Color::Black));
    m_window.draw(rectangle);
    sf::IntRect sourceRectangle(pieceToDraw * 32,pieceGraphic * 32,30,30);
    sf::Vector2f destination(774,100);                                                                     // clear next piece zone
    adjustxy(pieceToDraw, destination);
    drawPiece(sourceRectangle, destination, thePieces, pieceToDraw, 0, alpha);
    rectangle.setPosition(764, 260);
    rectangle.setSize(sf::Vector2f(180, 440));
    rectangle.setFillColor(sf::Color(sf::Color::Black));
    m_window.draw(rectangle);                                                                   // draw the next piece
    ++offset;
    if(!enhanced && (piecePositonInTheBag + offset) > 6)
            offset = 5;
    for(auto i = 2; i <= nextPiecesNumber; ++i) {
        if(!enhanced && (piecePositonInTheBag + offset) > 6)
            offset = 4 + i;
        pieceToDraw = random.getPieceAtPosition(piecePositonInTheBag + offset);
        ++offset;
        sourceRectangle.left = pieceToDraw * 32;
        destination.x = 774;
        destination.y = 110;
        destination.y += (100 * static_cast<float>(i));
        adjustxy(pieceToDraw, destination);
        drawPiece(sourceRectangle, destination, thePieces, pieceToDraw, 0, alpha);                                             // draw the next piece
    }
}

void manageScreen::adjustxy(const int pieceToDraw, sf::Vector2f& destination)
{
    switch (pieceToDraw) {                                                                                                      // center coord piece in the zone
        case 2:
            destination.x += 20;
            destination.y -= 20;
            break;
        case 9:
            destination.x += 35;
            destination.y -= 20;
            break;
        case 4:
        case 8:
            destination.x += 20;
            destination.y -= 5;
            break;
        case 10:
            destination.x += 35;
            destination.y += 10;
            break;
        default:
            destination.x += 35;
            destination.y -= 5;
            break;
    }
}

void manageScreen::drawPiece(sf::IntRect& sourceRectangle, sf::Vector2f& destination, thePieces& thePieces,int pieceToDraw, int rotation, const sf::Uint8 alpha)
{
    int blockToDraw{0};
                                                                                                     // draw the piece
    float x = destination.x;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            blockToDraw = thePieces.getBlock(pieceToDraw, rotation, j, i);
            if(blockToDraw > -1)
                rawRenderCopy(sourceRectangle, destination, alpha);
            destination.x += 30;
		}
        destination.x = x;
        destination.y +=30;
    }
}

void manageScreen::rawRenderCopy(const sf::IntRect& sourceRectangle, const sf::Vector2f& destination, const sf::Uint8 alpha)
{
    sf::Sprite sprite(m_texturePiece);
    sprite.setTextureRect(sourceRectangle);
    sprite.setPosition(destination);
    sprite.setColor(sf::Color(255,255,255,alpha));                                                          // 4 eme couleur pour transaparance  0 transparant, 255 opaque
    m_window.draw(sprite);
}

void manageScreen::drawCurrentPiece(Piece& currentPiece, thePieces& thePieces, const int pieceGraphic, const sf::Uint8 alpha)
{
    sf::IntRect sourceRectangle(currentPiece.current * 32,pieceGraphic * 32,30,30);
    sf::Vector2f destination(362 + static_cast<float>(currentPiece.x * 30), 10 + static_cast<float>(currentPiece.y * 30));
    drawPiece(sourceRectangle, destination, thePieces, currentPiece.current, currentPiece.rotation, alpha);
}

void manageScreen::drawPieceToHold(int currentPiece, int pieceGraphic, thePieces& thePieces, const sf::Uint8 alpha)
{
    sf::RectangleShape rectangle;

    rectangle.setPosition(100, 70);
    rectangle.setSize(sf::Vector2f(180, 110));
    rectangle.setFillColor(sf::Color(sf::Color::Black));
    m_window.draw(rectangle);                                                                               // clear hold piece zone
    sf::IntRect sourceRectangle(currentPiece * 32,pieceGraphic * 32,30,30);
    sf::Vector2f destination(105,100);
    adjustxy(currentPiece, destination);
    drawPiece(sourceRectangle, destination, thePieces, currentPiece, 0, alpha);                             // draw the hold piece
}

void manageScreen::drawTheBoard(board& board, const int pieceGraphic)
{
    sf::IntRect sourceRectangle(0,pieceGraphic * 32,30,30);
    sf::Vector2f destination(362,100);
    for(int i = 3; i < 23; i++) {
         for(int j = 0; j < 10; j++) {
            int blockToDraw = board.getBlockToDraw((i*10) + j);
            sourceRectangle.left = blockToDraw * 32;
            rawRenderCopy(sourceRectangle, destination, 255);
            destination.x +=30;
		 }
        destination.x = 362;
        destination.y += 30;
    }
}

void manageScreen::shiftedLinesAnimation(pattern& pattern, board& board, int pieceGraphic,sf::Uint8 alpha)
{
        sf::IntRect sourceRectangle(0,pieceGraphic * 32,30,30);
        for(int i = 0; i < pattern.nbLines; i++) {
            sf::Vector2f destination(362,static_cast<float>((pattern.linesY[i] * 30) + 10));
            for(int j = 0; j < 10; j++) {
                sourceRectangle.left = 11 * 32;
                rawRenderCopy(sourceRectangle, destination, alpha);
                int blockToDraw = board.getBlockToDraw((pattern.linesY[i]*10) + j);
                sourceRectangle.left = blockToDraw * 32;
                rawRenderCopy(sourceRectangle, destination, alpha);
                destination.x += 30;
            }
    }
}

void manageScreen::drawPatternLabelAnimation(pattern& pattern)
{
    if(pattern.tetris){ displayText("TETRIS", 60, sf::Color::White, 430, 220); }
    if(pattern.ClearBoard){ displayText("CLEAR", 60, sf::Color::White, 445, 220); }
    if(pattern.Tspin){
        displayText("Tspin", 60, sf::Color::White, 445, 220);
    }
    float offset{80};
    if(pattern.backToBack > 0 || pattern.combo) { offset = 0; }
    if(pattern.TspinSingle) {
        displayText("Tspin", 60, sf::Color::White, 445, 140 + offset);
        displayText("Single", 60, sf::Color::White, 435, 220 + offset);
    }
    if(pattern.TspinDouble) {
        displayText("Tspin", 60, sf::Color::White, 445, 140 + offset);
        displayText("Double", 60, sf::Color::White, 435, 220 + offset);
    }
    if(pattern.TspinTriple){
        displayText("Tspin", 60, sf::Color::White, 445, 140 + offset);
        displayText("Triple", 60, sf::Color::White, 435, 220 + offset);
    }
    if(pattern.combo > 0){ offset = 0; }
    else { offset = 80; }
    if(pattern.miniTspin){
        displayText("mini Tspin", 60, sf::Color::White, 380, 220);
    }
        if(pattern.miniTspinSingle) {
        displayText("mini Tspin", 60, sf::Color::White, 380, 140 + offset);
        displayText("Single", 60, sf::Color::White, 435, 220 + offset);
    }
    if(pattern.miniTspinDouble) {
        displayText("mini Tspin", 60, sf::Color::White, 380, 140 + offset);
        displayText("Double", 60, sf::Color::White, 435, 220 + offset);
    }
    if(pattern.backToBack > 0){
        displayText("Back to Back", 50, sf::Color::White, 380, 300);
        if(pattern.backToBack > 1){
            std::string comboNumber = "X " + std::to_string(pattern.backToBack);
            displayText(comboNumber, 72, sf::Color::White, 465, 360);
        }
    }
    if(pattern.combo > 0 && pattern.backToBack < 1){
        if(!pattern.miniTspin || !pattern.miniTspinSingle || !pattern.miniTspinDouble || !pattern.Tspin || !pattern.TspinSingle || !pattern.TspinDouble ||
           !pattern.TspinTriple || !pattern.tetris || !pattern.ClearBoard) {
               offset = -80;
        }
        displayText("COMBO", 50, sf::Color::White, 455, 300+ offset);
        if(pattern.combo > 1){
            std::string comboNumber = "X " + std::to_string(pattern.combo);
            displayText(comboNumber, 72, sf::Color::White, 465, 360+ offset);
        }
    }
}

void manageScreen::drawPatternAnimation(pattern& pattern, board& board, int pieceGraphic)
{
    sf::Uint8 alpha{250};
    for(int k = 0; k < 48; k++) {
        shiftedLinesAnimation(pattern, board, pieceGraphic, alpha);
        drawPatternLabelAnimation(pattern);
        render();
        sf::sleep(sf::milliseconds(8));
        alpha -= 5;
    }
    render();
}


void manageScreen::loadFontFile(const std::string title)
{
    if (!m_font.loadFromFile(title)) {
        std::cout << "erreur chargement du fichier: " << title << std::endl << "Veuillez réinstaller le programme." << std::endl;
        m_window.close();
    }
    m_text.setFont(m_font);
}

void manageScreen::displayText(const std::string textToDisplay, const int sizeText, const sf::Color color, const float x, const float y)
{
    m_text.setCharacterSize(sizeText);
    m_text.setFillColor(color);
    const sf::Vector2f position(x,y);
    m_text.setPosition(position);
    m_text.setString(textToDisplay);
    m_window.draw(m_text);
}

void manageScreen::printIndicators(const int level, const int score, const int nbLines, std::string timeElapsed)
{
	std::string temp = std::to_string(level);
	displayText(temp, 24, sf::Color::White, 250 - ((static_cast<float>(temp.size() - 1) * 12)), 460);
	temp = std::to_string(score);
	displayText(temp, 24, sf::Color::White, 250 - ((static_cast<float>(temp.size() - 1) * 12)), 500);
	temp = std::to_string(nbLines);
	displayText(temp, 24, sf::Color::White, 250 - ((static_cast<float>(temp.size() - 1) * 12)), 540);
	displayText(timeElapsed, 24, sf::Color::White, 260 - ((static_cast<float>(timeElapsed.size() - 1) * 12)), 580);
}

void manageScreen::drawButton(const float x, const float y, const int width, const int higth, const int textureNumber, const int buttonState)
{
    sf::IntRect sourceRectangle(0 + (width * buttonState), 250 + (100 * textureNumber), width, higth); //100 = width, higth of biggest button
    sf::Vector2f destination(x, y);
    rawRenderCopy(sourceRectangle, destination, 255);
}

void manageScreen::drawGameName()
{
    sf::IntRect sourceRectangle(0, 1000, 850, 275);
    sf::Vector2f destination(75, 50);
    rawRenderCopy(sourceRectangle, destination, 255);

}

void manageScreen::drawBlock( int blockNumber)
{
    sf::IntRect sourceRectangle(64, 0 + (blockNumber * 32), 30, 30);
    sf::Vector2f destination (750,150);

    rawRenderCopy(sourceRectangle, destination, 255);
}

void manageScreen::drawScoreList(const std::array<std::pair<std::string, int> , 20>& scoreArray,const int ranking, const int gameMode )  ////// ALIGNEMENT SCORE PAR LA DROITE       NUMEROTATION 1-20 ALIGNEE PAR LA DOITE      30 LINES C'EST UN TEMPS PAS UN SCORE
{
    clear();
    displayText("Meilleurs scores", 40, sf::Color::Red, 350, 15);
    float offset{0};
    int rank{1};
    sf::Color color;
    for(auto item : scoreArray){
        if(rank == ranking){ color = sf::Color(0xAAAAFFFF); }
        else { color = sf::Color::White; }
        displayText(item.first, 22, color, 250, 90 + offset);
        std::string label{""};
        if(gameMode == 2){
            label = convertTimeToStringMinuteSecondMilisec(static_cast<sf::Int32>(item.second));
            displayText(label, 22, color,650, 90 + offset);
        }
        else{
            std::string score = std::to_string(item.second);
            int stringLength = score.length();
            for(auto i = 0; i < 11 - stringLength; ++i){ label += " "; }
            label += score;
            displayText(label, 22, color,650, 90 + offset);
        }
        offset += 30;
        rank++;
    }
    displayText("Pressez Espace", 40, sf::Color::Red, 365, 700);
    render();
}

