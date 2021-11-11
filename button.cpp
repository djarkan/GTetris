#include "button.h"

button::button()
{
}

//   int buttonType
//  0: bouton lance 1 action quand pressé
//  1: bouton lance 1 action quand relaché
//  2: bouton lance 1 action tant que pressé
button::button(const int x, const int y, const int width, const int higth, const buttonType buttonType, const unsigned int ButtonId, const unsigned int textureNumber, int state)
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

button::buttonState button::whatButtonState(mouseEvent& mouseEvent)
{

    bool mouseOver = isMouseOver(mouseEvent.state.mouseX, mouseEvent.state.mouseY);
    if(!mouseOver ) {
        m_state = 0;
        return buttonState::noAction;
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftUp){
        m_state = 1;
        return buttonState::mouseOver;
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftPressed){
        if(m_buttonType == buttonType::pushedButton) {
            m_state = 2;
            return buttonState::buttonPressed;
    }
        else {
                m_state = 2;
                return buttonState::mouseOver;
        }
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftDown){
        if(m_buttonType == buttonType::heldButton) {
                m_state = 2;
                return buttonState::buttonHeld;
        }
        else {
                m_state = 2;
                return buttonState::mouseOver;
        }
    }
    if(mouseOver && mouseEvent.state.mouseLeftButton == mouseEvent::mouseButtonAction::leftReleased){
        if(m_buttonType == buttonType::releasedButton) {
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
    return mouseX >= m_x && mouseX <= m_x + m_width && mouseY >= m_y && mouseY <= m_y + m_higth;
}

