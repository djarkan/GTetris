#include "eventreader.hpp"
#include <SFML/window/mouse.hpp>

#include <iostream>

eventReader::eventReader()
{
}

eventReader::~eventReader()
{
}

eventReader::gameControl eventReader::getEvent(sf::RenderWindow &window)
{
    while(window.pollEvent(m_event)) {
        switch (m_event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (m_event.key.code)
                {
                    case sf::Keyboard::Down:
					case sf::Keyboard::Numpad2:
						return gameControl::softDrop;
						break;
					case sf::Keyboard::Space:
					case sf::Keyboard::Numpad8:
						return gameControl::hardDrop;
						break;
                    case sf::Keyboard::Left:
					case sf::Keyboard::Numpad4:
						return gameControl::shiftLeft;
						break;
                    case sf::Keyboard::Right:
					case sf::Keyboard::Numpad6:
						return gameControl::shiftRight;
						break;
                    case sf::Keyboard::RShift:
                    case sf::Keyboard::LShift:
                    case sf::Keyboard::C:
                    case sf::Keyboard::Numpad0:
						return gameControl::holdPiece;
						break;
                    default:
						return gameControl::none;
						break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (m_event.key.code) {
                    case sf::Keyboard::Numpad1:
                    case sf::Keyboard::Numpad5:
                    case sf::Keyboard::Numpad9:
					case sf::Keyboard::Up:
						return gameControl::rotateRight;
						break;
                    case sf::Keyboard::RControl:
                    case sf::Keyboard::LControl:
                    case sf::Keyboard::Numpad3:
                    case sf::Keyboard::Numpad7:
                    case sf::Keyboard::Z:
						return gameControl::rotateLeft;
						break;
                    case sf::Keyboard::F1:
                    case sf::Keyboard::Escape:
						return gameControl::pause;
						break;
                    default:
						return gameControl::none;
						break;
                }
            case sf::Event::MouseButtonPressed:
                if(m_event.mouseButton.button == sf::Mouse::Button::Left){
                    return gameControl::leftMouseButtonPressed;
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(m_event.mouseButton.button == sf::Mouse::Button::Left){
                    return gameControl::leftMouseButtonReleased;
                }
                break;
            default:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    return gameControl::leftMouseButtonHeld;
                }
                else{
                    return gameControl::none;
                }
                break;
        }
    }
	return gameControl::none;
}

bool eventReader::pseudoChar(sf::RenderWindow &window, std::string& pseudo, int language)
{
    while(window.pollEvent(m_event)) {
        char letter;
        switch (m_event.type) {
            case sf::Event::KeyReleased:
                switch (m_event.key.code) {
                    case 0 :
                        if(m_event.key.shift) { letter = 'A'; }
                        else { letter = 'a'; }
                        break;
                    case 1 :
                        if(m_event.key.shift) { letter = 'B'; }
                        else { letter = 'b'; }
                        break;
                    case 2 :
                        if(m_event.key.shift) { letter = 'C'; }
                        else { letter = 'c'; }
                        break;
                    case 3 :
                        if(m_event.key.shift) { letter = 'D'; }
                        else { letter = 'd'; }
                        break;
                    case 4 :
                        if(m_event.key.shift) { letter = 'E'; }
                        else { letter = 'e'; }
                        break;
                    case 5 :
                        if(m_event.key.shift) { letter = 'F'; }
                        else { letter = 'f'; }
                        break;
                    case 6 :
                        if(m_event.key.shift) { letter = 'G'; }
                        else { letter = 'g'; }
                        break;
                    case 7 :
                        if(m_event.key.shift) { letter = 'H'; }
                        else { letter = 'h'; }
                        break;
                    case 8 :
                        if(m_event.key.shift) { letter = 'I'; }
                        else { letter = 'i'; }
                        break;
                    case 9 :
                        if(m_event.key.shift) { letter = 'J'; }
                        else { letter = 'j'; }
                        break;
                    case 10 :
                        if(m_event.key.shift) { letter = 'K'; }
                        else { letter = 'k'; }
                        break;
                    case 11 :
                        if(m_event.key.shift) { letter = 'L'; }
                        else { letter = 'l'; }
                        break;
                    case 12 :
                        if(m_event.key.shift) { letter = 'M'; }
                        else { letter = 'm'; }
                        if(language == 3 && m_event.key.alt) { letter = 'µ'; }
                        break;
                    case 13 :
                        if(m_event.key.shift) { letter = 'N'; }
                        else { letter = 'n'; }
                        break;
                    case 14 :
                        if(m_event.key.shift) { letter = 'O'; }
                        else { letter = 'o'; }
                        break;
                    case 15 :
                        if(m_event.key.shift) { letter = 'P'; }
                        else { letter = 'p'; }
                        break;
                    case 16 :
                        if(m_event.key.shift) { letter = 'Q'; }
                        else { letter = 'q'; }
                        if(language == 3 && m_event.key.alt) { letter = '@'; }
                        break;
                    case 17 :
                        if(m_event.key.shift) { letter = 'R'; }
                        else { letter = 'r'; }
                        break;
                    case 18 :
                        if(m_event.key.shift) { letter = 'S'; }
                        else { letter = 's'; }
                        break;
                    case 19 :
                        if(m_event.key.shift) { letter = 'T'; }
                        else { letter = 't'; }
                        break;
                    case 20 :
                        if(m_event.key.shift) { letter = 'U'; }
                        else { letter = 'u'; }
                        break;
                    case 21 :
                        if(m_event.key.shift) { letter = 'V'; }
                        else { letter = 'v'; }
                        break;
                    case 22 :
                        if(m_event.key.shift) { letter = 'W'; }
                        else { letter = 'w'; }
                        break;
                    case 23 :
                        if(m_event.key.shift) { letter = 'X'; }
                        else { letter = 'x'; }
                        break;
                    case 24 :
                        if(m_event.key.shift) { letter = 'Y'; }
                        else { letter = 'y'; }
                        break;
                    case 25 :
                        if(m_event.key.shift) { letter = 'Z'; }
                        else { letter = 'z'; }
                        break;
                    case 26 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '0'; }
                                else { letter = 'à'; }
                                if(m_event.key.alt) { letter = '@'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = ')'; }
                                else { letter = '0'; }
                                break;
                            case 2 :
                            case 3 :
                                if(m_event.key.shift) { letter = '='; }
                                else { letter = '0'; }
                                if(language == 2 && m_event.key.alt) { letter = '}'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 27 :
                        if(language == 0) {
                            if(m_event.key.shift) { letter = '1'; }
                            else { letter = '&'; }
                        } else {
                            if(m_event.key.shift) { letter = '!'; }
                            else { letter = '1'; }
                            if(m_event.key.alt && language == 2 ) { letter = '|'; }
                        }
                        break;
                    case 28 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '2'; }
                                else { letter = 'é'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '@'; }
                                else { letter = '2'; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = '"'; }
                                else { letter = '2'; }
                                if(m_event.key.alt) { letter = '²'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = '"'; }
                                else { letter = '2'; }
                                if(m_event.key.alt) { letter = '@'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 29 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '3'; }
                                else { letter = '"'; }
                                if(m_event.key.alt) { letter = '#'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '#'; }
                                else { letter = '3'; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = '§'; }
                                else { letter = '3'; }
                                if(m_event.key.alt) { letter = '³'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = '·'; }
                                else { letter = '3'; }
                                if(m_event.key.alt) { letter = '#'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 30 :
                        if(language == 0 ){
                            if(m_event.key.shift) { letter = '4'; }
                            else { letter = '\''; }
                            if(m_event.key.alt) { letter = '{'; }
                            }
                        else {
                            if(m_event.key.shift) { letter = '$'; }
                            else { letter = '4'; }
                        }
                        break;
                    case 31 :
                        if(language == 0 ){
                            if(m_event.key.shift) { letter = '5'; }
                            else { letter = '('; }
                            if(m_event.key.alt) { letter = '['; }
                        }
                        else {
                            if(m_event.key.shift) { letter = '%'; }
                            else { letter = '5'; }
                        }
                        break;
                    case 32 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '6'; }
                                else { letter = '-'; }
                                if(m_event.key.alt) { letter = '|'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '^'; }
                                else { letter = '6'; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = '&'; }
                                else { letter = '7'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = '&'; }
                                else { letter = '6'; }
                                if(m_event.key.alt) { letter = '¬'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 33 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '7'; }
                                else { letter = 'è'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '&'; }
                                else { letter = '7'; }
                                break;
                            case 2 :
                            case 3 :
                                if(m_event.key.shift) { letter = '/'; }
                                else { letter = '7'; }
                                if(language == 2 && m_event.key.alt) { letter = '{'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 34 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '8'; }
                                else { letter = '_'; }
                                if(m_event.key.alt) { letter = '\\'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '*'; }
                                else { letter = '8'; }
                                break;
                            case 2 :
                            case 3 :
                                if(m_event.key.shift) { letter = '('; }
                                else { letter = '8'; }
                                if(language == 2 && m_event.key.alt) { letter = '['; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 35 :
                        switch (language){
                            case 0 :
                                    if(m_event.key.shift) { letter = '9'; }
                                    else { letter = 'ç'; }
                                    break;
                            case 1 :
                                if(m_event.key.shift) { letter = '('; }
                                else { letter = '9'; }
                                break;
                            case 2 :
                            case 3 :
                                if(m_event.key.shift) { letter = ')'; }
                                else { letter = '9'; }
                                if(language == 2 && m_event.key.alt) { letter = ']'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 36 :
                        pseudo = "";
                        return false;
                        break;
                    case 46 :
                        switch(language) {
                            case 0 :
                                if(m_event.key.shift) { letter = '°'; }
                                else { letter = ')'; }
                                if(m_event.key.alt) { letter = ']'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '{'; }
                                else { letter = '['; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = '?'; }
                                else { letter = 'ß'; }
                                if(m_event.key.alt) { letter = '\\'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = '?'; }
                                else { letter = '\''; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 47 :
                        if(language == 1){
                            if(m_event.key.shift) { letter = ']'; }
                            else { letter = '}'; }
                        }
                        else {
                            if(language == 2){
                                if(m_event.key.shift) { letter = '¿'; }
                                else { letter = '¡'; }
                            }
                        }
                        break;
                    case 48 :
                        switch(language){
                            case 0 :
                                if(m_event.key.shift) { letter = '£'; }
                                else { letter = '$'; }
                                break;
                            case 3:
                                if(m_event.key.shift) { letter = 'Ü'; }
                                else { letter = 'ü'; }
                                break;
                            case 2 :
                                if(m_event.key.alt) { letter = '['; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 49 :
                        switch(language) {
                            case 0 :
                                if(m_event.key.shift) { letter = '?'; }
                                else { letter = ','; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '<'; }
                                else { letter = ','; }
                                break;
                            case 2 :
                            case 3 :
                                if(m_event.key.shift) { letter = ';'; }
                                else { letter = ','; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 50 :
                        switch(language) {
                            case 0 :
                                if(m_event.key.shift) { letter = '.'; }
                                else { letter = ';'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '>'; }
                                else { letter = '.'; }
                                break;
                            case 2 :
                            case 3 :
                                if(m_event.key.shift) { letter = ':'; }
                                else { letter = '.'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case  51:
                        switch(language) {
                            case 0 :
                                letter = '²';
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '"'; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = 'Ä'; }
                                else { letter = 'ä'; }
                                break;
                            case 2 :
                                if(m_event.key.alt) { letter = '{'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 52 :
                        switch(language) {
                            case 0 :
                                if(m_event.key.shift) { letter = '/'; }
                                else { letter = ':'; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = '\''; }
                                else { letter = '#'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = 'Ç'; }
                                else { letter = 'ç'; }
                                if(m_event.key.alt) { letter = '}'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 53 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = 'µ'; }
                                else { letter = '*'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '|'; }
                                else { letter = '\\'; }
                                break;
                            case 3 :
                                if(m_event.key.shift) { letter = '°'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = 'ª'; }
                                else { letter = 'º'; }
                                if(m_event.key.alt) { letter = '\\'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 54 :
                        switch (language){
                            case 0 :
                                if(m_event.key.shift) { letter = '%'; }
                                else { letter = 'ù'; }
                                break;
                            case 1 :
                                if(m_event.key.shift) { letter = '~'; }
                                else { letter = '`'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 55 :
                        switch(language) {
                            case 0 :
                            case 1 :
                                if(m_event.key.shift) { letter = '+'; }
                                else { letter = '='; }
                                if(language == 0 && m_event.key.alt ) { letter = '}'; }
                                break;
                            case 3:
                                if(m_event.key.shift) { letter = '*'; }
                                else { letter = '+'; }
                                if(m_event.key.alt ) { letter = '~'; }
                                break;
                            case 2 :
                                if(m_event.key.shift) { letter = '*'; }
                                else { letter = '+'; }
                                if(m_event.key.alt ) { letter = ']'; }
                                break;
                            default :
                                break;
                        }
                        break;
                    case 56 :
                        if(language == 1){
                            if(m_event.key.shift) { letter = '_'; }
                            else { letter = '-'; }
                        }
                    case 57 :
                        letter = ' ';
                        break;
                    case 58 :
                        return false;
                    case 59 :
                        if(pseudo.size() > 0) {pseudo.pop_back(); }
                        return true;
                        break;
                        break;
                    case 67 :
                        letter = '+';
                        break;
                    case 68 :
                        letter = '-';
                        break;
                    case 69 :
                        letter = '*';
                        break;
                    case 70  :
                        letter = '/';
                        break;
                    case 75 :
                        letter = '0';
                        break;
                    case 76 :
                        letter = '1';
                        break;
                    case 77 :
                        letter = '2';
                        break;
                    case 78 :
                        letter = '3';
                        break;
                    case 79 :
                        letter = '4';
                        break;
                    case 80 :
                        letter = '5';
                        break;
                    case 81 :
                        letter = '6';
                        break;
                    case 82 :
                        letter = '7';
                        break;
                    case 83 :
                        letter = '8';
                        break;
                    case 84 :
                        letter = '9';
                        break;
                    default :
                        return true;
                        break;
                }
                pseudo += letter;
                break;
            default:
                break;
        }
    }
    return true;
}

bool eventReader::getSpace(sf::RenderWindow &window)
{
    while(window.pollEvent(m_event)) {
            switch (m_event.type) {
                case sf::Event::KeyReleased:
                    switch (m_event.key.code) {
                        case 57 :
                            m_event.key.code = sf::Keyboard::K;
                            return true;
                            break;
                        default:
                            return false;
                            break;
                    }
            }
    }
}
