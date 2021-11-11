#ifndef    __button__
#define    __button__

#include <SFML/window/mouse.hpp>
#include "screenmanagement.h"
#include "C:\Users\gilles.turboust\Documents\C++\sources\G_Tetris sfml\mouseevent.hpp"

class button{

public:
    enum class buttonType {pushedButton = 0, heldButton = 1,releasedButton = 2};
    enum class buttonState{noAction = 0, mouseOver, buttonPressed, buttonReleased, buttonHeld};
    button();
    button(const int x, const int y, const int width, const int higth, const buttonType buttonType, const unsigned int ButtonId, const unsigned int textureNumber, int state);
    ~button();
    buttonState whatButtonState(mouseEvent& mouseEvent);
    int m_x;
    int m_y;
    int m_width;
    int m_higth;
    buttonType m_buttonType;
    unsigned int m_buttonId;
    unsigned int m_textureNumber;
    int m_state;

private:
    bool isMouseOver(int mouseX, int mouseY);
};
#endif
