#ifndef    __eventReader__
#define    __eventReader__

#include <SFML/Graphics.hpp>

class eventReader{
private:
    sf::Event   m_event;
public:
    eventReader();
    ~eventReader();
	enum class gameControl { rotateLeft, rotateRight, shiftLeft, shiftRight, hardDrop, softDrop, pause, holdPiece, leftMouseButtonPressed, leftMouseButtonReleased, leftMouseButtonHeld, none };

	gameControl getEvent(sf::RenderWindow &window);
	bool pseudoChar(sf::RenderWindow &window, std::string& pseudo, int language);                                     // gamer interaction reading, and return le next action to do
	bool getSpace(sf::RenderWindow &window);

};
#endif
