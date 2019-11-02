#include "eventreader.h"

eventReader::eventReader()
{
}

eventReader::~eventReader()
{
}

sf::Keyboard::Key eventReader::getEvent(sf::RenderWindow& window)
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
                    case sf::Keyboard::Left:
                    case sf::Keyboard::Right:
                    case sf::Keyboard::RShift:
                    case sf::Keyboard::LShift:
                    case sf::Keyboard::C:
                    case sf::Keyboard::M:
                    case sf::Keyboard::Space:
                    case sf::Keyboard::Numpad0:
                    case sf::Keyboard::Numpad2:
                    case sf::Keyboard::Numpad4:
                    case sf::Keyboard::Numpad6:
                    case sf::Keyboard::Numpad8:
                    case sf::Keyboard::Enter:
                        return m_event.key.code;
                    default:
                        return sf::Keyboard::Unknown;
                }
            case sf::Event::KeyReleased:
                switch (m_event.key.code) {
                    case sf::Keyboard::Numpad1:
                    case sf::Keyboard::Numpad5:
                    case sf::Keyboard::Numpad9:
                    case sf::Keyboard::RControl:
                    case sf::Keyboard::LControl:
                    case sf::Keyboard::Numpad3:
                    case sf::Keyboard::Numpad7:
                    case sf::Keyboard::Z:
                    case sf::Keyboard::F1:
                    case sf::Keyboard::Escape:
                    case sf::Keyboard::Up:
                        return m_event.key.code;
                    default:
                        return sf::Keyboard::Unknown;
                }
            default:
                break;
        }
    }
    return sf::Keyboard::Unknown;
}
