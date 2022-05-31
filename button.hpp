#ifndef    __button__
#define    __button__

#include <SFML/window/mouse.hpp>
#include "screenmanagement.hpp"
#include "mouseevent.hpp"

class button{

public:
    enum class buttonType {pushedButton = 0, heldButton, releasedButton};
    enum class buttonState{noAction = 0, mouseOver, buttonPressed, buttonReleased, buttonHeld};

    button();
    button(const float x, const float y, const int width, const int higth, const buttonType buttonType, const unsigned int ButtonId, const unsigned int textureNumber, int state);
    ~button();
    buttonState whatButtonState(sf::RenderWindow &window);

    float m_x;
    float m_y;
    int m_width;
    int m_higth;
    buttonType m_buttonType;
    unsigned int m_buttonId;
    unsigned int m_textureNumber;
    int m_state;

private:
    bool isMouseOver(int mouseX, int mouseY);
    mouseEvent mouseEvent;
};
#endif
