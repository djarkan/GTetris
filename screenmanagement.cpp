#include "screenmanagement.hpp"

manageScreen::manageScreen(): m_window(sf::VideoMode(1024, 768), "G_Tetris v 1.0", sf::Style::Close)
{

}

manageScreen::manageScreen(sf::Uint32 Style): m_window(sf::VideoMode(1024, 768), "G_Tetris v 1.0", Style)
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

bool manageScreen::loadBitmapFile(const std::string title)
{
    if(m_graphics.loadFromFile(title)) {
        m_graphics.createMaskFromColor(sf::Color(0xAAAA22FF));
        sf::IntRect surfaceImage(0,0,1024,2500);
        m_texturePiece.loadFromImage(m_graphics, surfaceImage);
        return true;
    }
    else { return false; }
}

bool manageScreen::loadBitmapCursor(const std::string title)
{
    if(myCursor.loadFromFile(title)) {
        myCursor.createMaskFromColor(sf::Color(0xAAAA22FF));
        return true;
    }
    else { return false; }
}

bool manageScreen::loadFontFile(const std::string title)
{
    if (m_font.loadFromFile(title)) {
        m_text.setFont(m_font);
        return true;
    }
    else { return false; }
}

void manageScreen::drawCircles()
{
    float radius{60};
    float x{452};
    float y {335};
    sf::Color color{0x0000BBFF};

    for(auto i = 0; i < 8; ++i) {
        sf::CircleShape circle;
        circle.setRadius(radius);
        circle.setFillColor(color);
        circle.setPosition(x,y);
        m_window.draw(circle);
        radius -= 10;
        x += 10;
        y +=10;
        color += static_cast<sf::Color>(0x00000FFF);
    }
}

void manageScreen::drawPlayGround(std::string levelLabel, std::string  scoreLabel, std::string lineLabel, std::string timeLabel, std::string holdLabel, std::string nextLabel)
{														//Draw boards (playung area, hold, next
    drawBoardArea();
    draw5NxetArea();
    drawHoldArea();
    drawNextArea();
    displayText(levelLabel, 24, sf::Color::White, 55, 460);
    displayText(scoreLabel, 24, sf::Color::White, 55, 500);
    displayText(lineLabel, 24, sf::Color::White, 55, 540);
    displayText(timeLabel, 24, sf::Color::White, 55, 580);
    displayText(holdLabel, 40, sf::Color(0xAAAAAAFF), 175 - ((static_cast<float>(holdLabel.size()) * 12) / 2.f), 3);
    displayText(nextLabel, 40, sf::Color(0xAAAAAAFF), 840 - ((static_cast<float>(nextLabel.size()) * 12) / 2.f), 3);
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
    sf::IntRect sourceRectangle(pieceToDraw * 32,pieceGraphic * 32,30,30);
    sf::Vector2f destination(774,100);                                                                     // clear next piece zone
    adjustxy(pieceToDraw, destination);
    drawPiece(sourceRectangle, destination, thePieces, pieceToDraw, 0, alpha);                                                                 // draw the next piece
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

void manageScreen::drawPatternLabelAnimation(pattern& pattern, sf::Uint8 alpha)
{
    if(pattern.tetris){ displayText("TETRIS", 60, sf::Color(254, 254, 254, alpha), 430, 220); }
    if(pattern.ClearBoard){ displayText("CLEAR", 60, sf::Color(254, 254, 254, alpha), 445, 220); }
    if(pattern.Tspin){
        displayText("Tspin", 60, sf::Color(254, 254, 254, alpha), 445, 220);
    }
    float offset{80};
    if(pattern.backToBack > 0 || pattern.combo) { offset = 0; }
    if(pattern.TspinSingle) {
        displayText("Tspin", 60, sf::Color(254, 254, 254, alpha), 445, 140 + offset);
        displayText("Single", 60, sf::Color(254, 254, 254, alpha), 435, 220 + offset);
    }
    if(pattern.TspinDouble) {
        displayText("Tspin", 60, sf::Color(254, 254, 254, alpha), 445, 140 + offset);
        displayText("Double", 60, sf::Color(254, 254, 254, alpha), 435, 220 + offset);
    }
    if(pattern.TspinTriple){
        displayText("Tspin", 60, sf::Color(254, 254, 254, alpha), 445, 140 + offset);
        displayText("Triple", 60, sf::Color(254, 254, 254, alpha), 435, 220 + offset);
    }
    if(pattern.combo > 0){ offset = 0; }
    else { offset = 80; }
    if(pattern.miniTspin){
        displayText("mini Tspin", 60, sf::Color(254, 254, 254, alpha), 380, 220);
    }
        if(pattern.miniTspinSingle) {
        displayText("mini Tspin", 60, sf::Color(254, 254, 254, alpha), 380, 140 + offset);
        displayText("Single", 60, sf::Color(254, 254, 254, alpha), 435, 220 + offset);
    }
    if(pattern.miniTspinDouble) {
        displayText("mini Tspin", 60, sf::Color(254, 254, 254, alpha), 380, 140 + offset);
        displayText("Double", 60, sf::Color(254, 254, 254, alpha), 435, 220 + offset);
    }
    if(pattern.backToBack > 0){
        displayText("Back to Back", 50, sf::Color(254, 254, 254, alpha), 380, 300);
        if(pattern.backToBack > 1){
            std::string comboNumber = "X " + std::to_string(pattern.backToBack);
            displayText(comboNumber, 72, sf::Color(254, 254, 254, alpha), 465, 360);
        }
    }
    if(pattern.combo > 0 && pattern.backToBack < 1){
        if(!pattern.miniTspin && !pattern.miniTspinSingle && !pattern.miniTspinDouble && !pattern.Tspin && !pattern.TspinSingle && !pattern.TspinDouble &&
           !pattern.TspinTriple && !pattern.tetris && !pattern.ClearBoard) {
               offset = -80;
        }
        displayText("COMBO", 50, sf::Color(254, 254, 254, alpha), 455, 300 + offset);
        if(pattern.combo > 1){
            std::string comboNumber = "X " + std::to_string(pattern.combo);
            displayText(comboNumber, 72, sf::Color(254, 254, 254, alpha), 465, 360 + offset);
        }
    }
}

void manageScreen::drawPatternAnimation(pattern& pattern, board& board, int pieceGraphic)
{
    sf::Uint8 alpha{250};
    for(int k = 0; k < 48; k++) {
        shiftedLinesAnimation(pattern, board, pieceGraphic, alpha);
        drawPatternLabelAnimation(pattern, static_cast<sf::Uint8>(255 - alpha));
        render();
        sf::sleep(sf::milliseconds(8));
        alpha = static_cast<sf::Uint8>(alpha - 5);
    }
    render();
}

void manageScreen::printChar(float& x, const float y, const int charSize, const char printedChar)
{
    m_text.setString(printedChar);
    m_text.setPosition(x, y);
    m_window.draw(m_text);
    x +=  m_text.getCharacterSize() * 0.4;
}

void manageScreen::displayText(const std::string textToDisplay, const int sizeText, const sf::Color color, float x, float y)
{
    float oldY = y;
    float oldx = x;
    m_text.setStyle(sf::Text::Regular);
    m_text.setCharacterSize(sizeText);
    m_text.setFillColor(color);
    m_text.setPosition(x, y);
    for(unsigned int i = 0; i < textToDisplay.size(); ++i) {
        if(textToDisplay[i] != '[') {
            if(textToDisplay[i] == '\n') {
                x = oldx;
                y += m_text.getCharacterSize() + 4;
                m_text.setPosition(x, y);
            }
            else { printChar(x, y , sizeText,textToDisplay[i]); }
        }
        else {                                                                                                           // enter in a boudary
            ++i;
            char letter = textToDisplay[i];
            bool addStyle;                                                                                               // add or remove text style
            sf::Uint32 style = m_text.getStyle();
            if(letter != '/') { addStyle = true; }
            else {
                    addStyle =  false;
                    ++i;
                    letter = textToDisplay[i];
            }
            if(letter == 'r' || letter == 'b' || letter == 'i' || letter == 'u' || letter == 't') {
                if(textToDisplay[i + 1] == ']') {
                    switch (letter) {
                        case 'r':                                                                                        // regular : remove all styles [r] or [/r]  only one is enough
                            m_text.setStyle(style& 0b00000000);
                            m_text.setCharacterSize(sizeText);
                            m_text.setFillColor(color);
                            break;
                        case 'b':                                                                                        // bold
                            if(addStyle) { m_text.setStyle(style | sf::Text::Bold); }
                            else { m_text.setStyle(style & 0b11111110); }
                            break;
                        case 'i':                                                                                        // italic
                            if(addStyle) { m_text.setStyle(style | sf::Text::Italic); }
                            else { m_text.setStyle(style & 0b11111101); }
                            break;
                        case 'u':                                                                                        // underlined
                            if(addStyle) { m_text.setStyle(style | sf::Text::Underlined); }
                            else { m_text.setStyle(style & 0b11111011); }
                            break;
                        case 't':                                                                                       // StrikeThrough
                            if(addStyle) { m_text.setStyle(style | sf::Text::StrikeThrough); }
                            else { m_text.setStyle(style & 0b11110111); }
                            break;
                        default:
                            break;
                    }
                    ++i;
                }
                else {
                    if(addStyle) {
                        printChar(x, y , sizeText,textToDisplay[i - 1]);
                        printChar(x, y , sizeText,textToDisplay[i]);
                    }
                    else {
                        printChar(x, y , sizeText,textToDisplay[i - 2]);
                        printChar(x, y , sizeText,textToDisplay[i - 1]);
                        printChar(x, y , sizeText,textToDisplay[i]);
                    }
                }
            }
            else {
                if(letter == 's' or letter == 'c') {
                    if(addStyle && textToDisplay[i + 1] == ']' || textToDisplay[i + 2] == ']' || textToDisplay[i + 3] == ']' || textToDisplay[i + 4] == ']' ) {
                        std::string numberSize{""};
                        ++i;
                        int offset{0};
                        bool isNumericDigit{true};
                        bool boundary{true};
                        int supposedSizeLength{0};
                        while(textToDisplay[i + supposedSizeLength] != ']') { ++supposedSizeLength; }
                        while(textToDisplay[i + offset] != ']' && offset < 3 && isNumericDigit && textToDisplay[i + offset] != ']') {
                            if(std::isdigit(textToDisplay[i + offset])) {
                                numberSize.push_back(textToDisplay[i + offset]);
                                ++offset;
                            }
                            else { isNumericDigit = false; }
                        }
                        if(numberSize.size() == supposedSizeLength && supposedSizeLength > 0) {
                            int number = std::stoi(numberSize);
                            i += numberSize.size();
                            if(letter == 's') {                                                                         // font size
                                m_text.setCharacterSize(number);
                                y = oldY;
                                if(number > sizeText) { y -= (number - sizeText); }
                                else { y += (sizeText - number);}
                            }
                            else { if(number <= 28) { m_text.setFillColor(selectColor(number)); }}                      // color
                        }
                        else {
                            printChar(x, y , sizeText, textToDisplay[i - 2]);
                            printChar(x, y , sizeText, textToDisplay[i - 1]);
                            printChar(x, y , sizeText, textToDisplay[i]);
                        }
                    }
                    else {
                        if(textToDisplay[i + 1] == ']') {
                            if(letter == 's'){
                                y = oldY;
                                m_text.setCharacterSize(sizeText);
                            }
                            else { m_text.setFillColor(color); }
                            ++i;
                        }
                        else {
                            printChar(x, y , sizeText, textToDisplay[i - 2]);
                            printChar(x, y , sizeText, textToDisplay[i - 1]);
                            printChar(x, y , sizeText, textToDisplay[i]);
                        }
                    }
                }
                else {
                    std::string letters{"["};
                    if(!addStyle) { letters.push_back(textToDisplay['/']); }
                    letters.push_back(textToDisplay[i]);
                    m_text.setString(letters);
                    m_text.setPosition(x, y);
                    m_window.draw(m_text);
                    x +=  sizeText * (0.40 * letters.size());
                }
            }
       }
    }
}

sf::Color manageScreen::selectColor( int colorNb)
{
    switch (colorNb) {
        case static_cast<int>(TextColor::Black):                                                // 0
            return sf::Color::Black;
        case static_cast<int>(TextColor::LightBrown):                                           // 1
            return  static_cast<sf::Color>(0xE49467FF);
        case static_cast<int>(TextColor::Brown):                                                // 2
            return static_cast<sf::Color>(0xB97A56FF);
        case static_cast<int>(TextColor::DarkBrown):                                            // 3
            return static_cast<sf::Color>(0x805740FF);
        case static_cast<int>(TextColor::LightRed):                                             // 4
            return static_cast<sf::Color>(0xff343cFF);
        case static_cast<int>(TextColor::Red):                                                  // 5
            return static_cast<sf::Color>(0xe61a22FF);
        case static_cast<int>(TextColor::DarkRed):                                              // 6
            return static_cast<sf::Color>(0xeb01b21FF);
        case static_cast<int>(TextColor::LightPink):                                            // 7
            return static_cast<sf::Color>(0xffacc7FF);
        case static_cast<int>(TextColor::Pink):                                                 // 8
            return static_cast<sf::Color>(0xff8eb2FF);
        case static_cast<int>(TextColor::DarkPink):                                             // 9
            return static_cast<sf::Color>(0xff6496FF);
        case static_cast<int>(TextColor::LightOrange):                                          // 10
            return static_cast<sf::Color>(0xffa263FF);
        case static_cast<int>(TextColor::Orange):                                               // 11
            return static_cast<sf::Color>(0xff7f27FF);
        case static_cast<int>(TextColor::DarkOrange):                                           // 12
            return static_cast<sf::Color>(0xe67a2fFF);
        case static_cast<int>(TextColor::LightYellow):                                          // 13
            return static_cast<sf::Color>(0xfffbb0FF);
        case static_cast<int>(TextColor::Yellow):                                               // 14
            return static_cast<sf::Color>(0xfff200FF);
        case static_cast<int>(TextColor::DarkYellow):                                           // 15
            return static_cast<sf::Color>(0xd1c707FF);
        case static_cast<int>(TextColor::LightBlue):                                            // 16
            return static_cast<sf::Color>(0x4479ffFF);
        case static_cast<int>(TextColor::Blue):                                                 // 17
            return static_cast<sf::Color>(0x0048ffFF);
        case static_cast<int>(TextColor::DarkBlue):                                             // 18
            return static_cast<sf::Color>(0x0534abFF);
        case static_cast<int>(TextColor::LightGreen):                                           // 19
            return static_cast<sf::Color>(0x18df50FF);
        case static_cast<int>(TextColor::Green):                                                // 20
            return static_cast<sf::Color>(0x16b944FF);
        case static_cast<int>(TextColor::DarkGreen):                                            // 21
            return static_cast<sf::Color>(0x0a8b2eFF);
        case static_cast<int>(TextColor::LightPurple):                                          // 22
            return static_cast<sf::Color>(0xfb07ffFF);
        case static_cast<int>(TextColor::Purple):                                               // 23
            return static_cast<sf::Color>(0xcd2bcfFF) ;
        case static_cast<int>(TextColor::DarkPurple):                                           // 24
            return static_cast<sf::Color>(0xa120a3FF);
        case static_cast<int>(TextColor::LightGrey):                                            // 25
            return static_cast<sf::Color>(0xBBBBBBFF);
        case static_cast<int>(TextColor::Grey):                                                 // 26
            return static_cast<sf::Color>(0x999999FF);
        case static_cast<int>(TextColor::DarkGrey):                                             // 27
            return static_cast<sf::Color>(0x777777FF);
        case static_cast<int>(TextColor::White):                                                // 28
        default:
            return sf::Color::White;
    }
    return sf::Color::White;
}

void manageScreen::simpleDisplayText(const std::string textToDisplay, const int sizeText, const sf::Color color, const float x, const float y)
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
    sf::Vector2f destination (735,173);

    rawRenderCopy(sourceRectangle, destination, 255);
}

void manageScreen::drawScoreList(const std::array<std::pair<std::string, int> , 20>& scoreArray,const int ranking, const int gameMode, std::string label1, std::string label2)  ////// ALIGNEMENT SCORE PAR LA DROITE       NUMEROTATION 1-20 ALIGNEE PAR LA DOITE      30 LINES C'EST UN TEMPS PAS UN SCORE
{
    clear();
    displayText(label1, 40, sf::Color::White, 512 - (((label1.size() - 7) * 16) / 2.f), 15);
    float offset{0};
    int rank{1};
    sf::Color color = sf::Color::White;
    std::string colorStartBoundary{""};
    for(auto i = 0; i < 20; ++i){
        if(rank == ranking){
            color = sf::Color(0xAAAAFFFF);
            colorStartBoundary = "";
        }
        else {
                if(i % 2) { colorStartBoundary = "[c25]"; }
                else { colorStartBoundary = "[c28]"; }
        }
        displayText(colorStartBoundary + scoreArray[i].first, 22, color, 300, 90 + offset);
        std::string label = "";
        if(gameMode == 2){
            label = colorStartBoundary + convertTimeToStringMinuteSecondMilisec(static_cast<sf::Int32>(scoreArray[i].second)) + " [/c]";
            displayText(colorStartBoundary + label + " [/c]", 22, color,600, 90 + offset);
        }
        else{
            std::string score = std::to_string(scoreArray[i].second);
            int stringLength = score.length();
            for(auto i = 0; i < 11 - stringLength; ++i){ label += " "; }
            label += score;
            displayText(colorStartBoundary + label + " [/c]", 22, color, 600, 90 + offset);
        }
        offset += 30;
        rank++;
    }
    displayText("[c28]" + label2 + " [/c]", 40, sf::Color::White, 512 - ((label2.size() * 16) / 2.f), 700);
    render();
}

void manageScreen::errorMessage(std::string error, std::string messageToDisplay, std::string pressSpace)
{
    clear();
    displayText(error, 48, sf::Color::Red, 512 - ((static_cast<float>(error.size() * 19.2) / 2.f)), 250);
    displayText(messageToDisplay, 32, sf::Color::White, 512 - ((static_cast<float>(messageToDisplay.size()) / 2.f) * 13), 370);
    displayText(pressSpace, 32, sf::Color::White, 512 - ((static_cast<float>(pressSpace.size()) / 2.f) * 13), 460);
    render();
}
