#ifndef    __eventReader__
#define    __eventReader__

#include <SFML/Graphics.hpp>
#include "timer.hpp"

class eventReader{
private:
    sf::Event   m_event;
    int m_joystickID;
    timer m_repeatLimitaionTimer;

    int isJoypadConnected();
public:
    eventReader();
	enum class gameControl { rotateLeft, rotateRight, shiftLeft, shiftRight, hardDrop, softDrop, pause, holdPiece, leftMouseButtonPressed, leftMouseButtonReleased, leftMouseButtonHeld, none };

	gameControl getEvent(sf::RenderWindow &window);
	bool pseudoChar(sf::RenderWindow &window, std::string& pseudo, int language);                                     // gamer interaction reading, and return le next action to do
	bool getSpace(sf::RenderWindow &window);
	bool getEscape(sf::RenderWindow &window);

};
#endif
