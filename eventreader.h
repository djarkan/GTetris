#ifndef    __eventReader__
#define    __eventReader__

#include <SFML/Graphics.hpp>

class eventReader{
private:
    sf::Event   m_event;
public:
    eventReader();
    ~eventReader();
    sf::Keyboard::Key getEvent(sf::RenderWindow& window);                                         // gamer interaction reading, and return le next action to do
};
#endif
