#include "eventreader.h"

eventReader::eventReader()
{
}

eventReader::~eventReader()
{
}

eventReader::gameControl eventReader::getEvent(sf::RenderWindow& window)
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
            default:
				return gameControl::none;
                break;
        }
    }
	return gameControl::none;
}
