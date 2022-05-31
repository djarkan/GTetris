#include "button.hpp"

button::button()
{
}

//    buttonType
//  0: bouton lance 1 action quand pressé
//  1: bouton lance 1 action tant que pressé
//  2: bouton lance 1 action  quand relaché
button::button(const float x, const float y, const int width, const int higth, const buttonType buttonType, const unsigned int ButtonId, const unsigned int textureNumber, int state)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_higth = higth;
    m_buttonType = buttonType;
    m_buttonId = ButtonId;
    m_textureNumber = textureNumber;
    m_state = state;
}

button::~button()
{
}

button::buttonState button::whatButtonState(sf::RenderWindow &window)
{
    mouseEvent.checkmouseCoord(window);
    bool mouseOver = isMouseOver(mouseEvent.state.mouseX, mouseEvent.state.mouseY);
    if(!mouseOver ) {
        m_state = 0;
        return buttonState::noAction;
    }
    mouseEvent.checkMouseEvents(window);
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftUp){
        m_state = 1;
        return buttonState::mouseOver;
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftPressed){
        m_state = 2;
        if(m_buttonType == buttonType::pushedButton) {
            return buttonState::buttonPressed;
        }
        else {
            return buttonState::mouseOver;
        }
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftDown){
        m_state = 2;
        if(m_buttonType == buttonType::heldButton) {
                return buttonState::buttonHeld;
        }
        else {
                return buttonState::mouseOver;
        }
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftReleased){
        if(m_buttonType == buttonType::releasedButton && m_state == 2) {
                m_state = 0;
                return buttonState::buttonReleased;
        }
        else {
                m_state = 2;
                return buttonState::mouseOver;
        }
    }
    m_state = 0;
    return buttonState::noAction;
}

bool button::isMouseOver(const int mouseX, const int mouseY)
{
    return static_cast<float>(mouseX) >= m_x && static_cast<float>(mouseX) <= m_x + static_cast<float>(m_width) && static_cast<float>(mouseY) >= m_y && static_cast<float>(mouseY) <= m_y + static_cast<float>(m_higth);
}

