#include "screenmanagement.h"

manageScreen::manageScreen(): m_window(sf::VideoMode(1024, 768), "G_Tetris v0.1", sf::Style::Close)
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

void manageScreen::drawPlayGround()
{                                                       //Draw boards (playung area, hold, next
    drawBoardArea();
    draw5NxetArea();
    drawHoldArea();
    drawNextArea();
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
    drawPlayGround();
    sf::IntRect  sourceRectangle(11 * 32,(pieceGraphic - 1) * 32,30,30);
    sf::Vector2f destination(362, 70);
    for(auto i = 2; i < 23; i++) {
        for(auto j = 0; j < 10; j++) {
            rawRenderCopy(sourceRectangle, destination, m_texturePiece, 255);
            destination.x +=30;
        }
        destination.y += 30;
        destination.x = 362;
    }
    render();
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
    sf::IntRect sourceRectangle(pieceToDraw * 32,(pieceGraphic - 1) * 32,30,30);
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
    for(int i = 2; i <= nextPiecesNumber; ++i) {
        if(!enhanced && (piecePositonInTheBag + offset) > 6)
            offset = 4 + i;
        pieceToDraw = random.getPieceAtPosition(piecePositonInTheBag + offset);
        ++offset;
        sf::IntRect sourceRectangle(pieceToDraw * 32,(pieceGraphic - 1) * 32,30,30);
        destination.x = 774;
        destination.y = 110;
        destination.y += (100 * i);
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
    int blockToDraw{0} , x{0};
                                                                                                     // draw the piece
    x = destination.x;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            blockToDraw = thePieces.getBlock(pieceToDraw, rotation, j, i);
            if(blockToDraw > -1)
                rawRenderCopy(sourceRectangle, destination, m_texturePiece, alpha);
            destination.x += 30;
		}
        destination.x = x;
        destination.y +=30;
    }
}

void manageScreen::rawRenderCopy(const sf::IntRect& sourceRectangle, const sf::Vector2f& destination, const sf::Texture& texturePiece, const sf::Uint8 alpha)
{
    sf::Sprite sprite(texturePiece);
    sprite.setTextureRect(sourceRectangle);
    sprite.setPosition(destination);
    sprite.setColor(sf::Color(255,255,255,alpha));                                                          // 4 eme couleur pour transaparance  0 transparant, 255 opaque
    m_window.draw(sprite);
}

void manageScreen::drawCurrentPiece(currentPiece& currentPiece, thePieces& thePieces, const int pieceGraphic, const sf::Uint8 alpha)
{
    sf::IntRect sourceRectangle(currentPiece.current * 32,(pieceGraphic - 1) * 32,30,30);
    sf::Vector2f destination(362 + (currentPiece.x * 30),10 + (currentPiece.y * 30));
    drawPiece(sourceRectangle, destination, thePieces, currentPiece.current, currentPiece.rotation, alpha);
}

void manageScreen::drawPieceToHold(int currentPiece, int pieceGraphic, thePieces& thePieces, const sf::Uint8 alpha)
{
    sf::RectangleShape rectangle;

    rectangle.setPosition(100, 70);
    rectangle.setSize(sf::Vector2f(180, 110));
    rectangle.setFillColor(sf::Color(sf::Color::Black));
    m_window.draw(rectangle);                                                                               // clear hold piece zone
    sf::IntRect sourceRectangle(currentPiece * 32,(pieceGraphic - 1) * 32,30,30);
    sf::Vector2f destination(105,100);
    adjustxy(currentPiece, destination);
    drawPiece(sourceRectangle, destination, thePieces, currentPiece, 0, alpha);                             // draw the hold piece
}

void manageScreen::drawTheBoard(board& board, const int pieceGraphic)
{
    sf::IntRect sourceRectangle(0,(pieceGraphic - 1) * 32,30,30);
sf::Vector2f destination(362,10);                         // temporaire pour voir TOUTE LA MATRICE
for(int i = 0; i < 23; i++) {                             // i = 0 au lieu de 2  temporaire IDEM 
         for(int j = 0; j < 10; j++) {
            int blockToDraw = board.getBlockToDraw((i*10) + j);
            sourceRectangle.left = blockToDraw * 32;
            rawRenderCopy(sourceRectangle, destination, m_texturePiece, 255);
            destination.x +=30;
		 }
        destination.x = 362;
        destination.y += 30;
    }
}

void manageScreen::shiftedLinesAnimation(pattern& pattern, board& board, int pieceGraphic)
{
    sf::Uint8 alpha{250};

    for(int k = 0; k < 48; k++) {
        sf::IntRect sourceRectangle(0,(pieceGraphic - 1) * 32,30,30);
        for(int i = 0; i < pattern.nbLines; i++) {
            sf::Vector2f destination(362,(pattern.linesY[i] * 30) + 10);
            for(int j = 0; j < 10; j++) {
                sourceRectangle.left = 11 * 32;
                rawRenderCopy(sourceRectangle, destination, m_texturePiece, alpha);
                int blockToDraw = board.getBlockToDraw((pattern.linesY[i]*10) + j);
                sourceRectangle.left = blockToDraw * 32;
                rawRenderCopy(sourceRectangle, destination, m_texturePiece, alpha);
                destination.x += 30;
            }
        }
        alpha -= 5;
        render();
        sf::sleep(sf::milliseconds(8));
    }
}

int manageScreen::pauseMenu(board& board, int pieceGraphic, eventReader& eventReader)
{
    int option{1};
    sf::Keyboard::Key event{sf::Keyboard::Unknown};
    bool pause{true};
    drawEmptyBoard(pieceGraphic);
    while(pause) {
        event = eventReader.getEvent(m_window);
        switch (event) {
            case sf::Keyboard::F1:                   // pause
            case sf::Keyboard::Escape:
                if(option < 3)
                    option++;
                break;
            case sf::Keyboard::Down:
                if(option > 1)
                    option--;
                break;
//            case SDLK_RETURN:
            case sf::Keyboard::Enter:
                if(option == 1)
                    return option;
                else
                {
                    // refaire choix pour confirmation perte de la partie
                }
            default:
                break;
        }
    }
}
