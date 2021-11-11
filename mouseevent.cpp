#include "mouseevent.hpp"
#include <iostream>

/*mouseEvent::mouseEvent()
{

}

mouseEvent::~mouseEvent()
{

}*/

void mouseEvent::checkButtons(sf::RenderWindow &window)
{
    while(window.pollEvent(m_event)) {
        switch(m_event.type) {
            case sf::Event::MouseButtonPressed :
                    state.mouseX = m_event.mouseButton.x;
                    state.mouseY = m_event.mouseButton.y;
                    switch(m_event.mouseButton.button) {
                        case sf::Mouse::Button::Left:
                            state.mouseLeftButton = mouseEvent::mouseButtonAction::leftPressed;
                            break;
                        case sf::Mouse::Button::Right:
                            state.mouseRightButton = mouseEvent::mouseButtonAction::rightPressed;
                            break;
                        case sf::Mouse::Button::Middle:
                            state.mouseMiddleButton = mouseEvent::mouseButtonAction::middlePressed;
                            break;
                        case sf::Mouse::Button::XButton1:
                            state.mouseXButton1Button = mouseEvent::mouseButtonAction::xbutton1Pressed;
                            break;
                        case sf::Mouse::Button::XButton2:
                            state.mouseXButton2Button = mouseEvent::mouseButtonAction::xbutton2Pressed;
                            break;
                        default:
                            break;
                    }
                    return;
            case sf::Event::MouseButtonReleased :
                    state.mouseX = m_event.mouseButton.x;
                    state.mouseY = m_event.mouseButton.y;
                    switch(m_event.mouseButton.button) {
                        case sf::Mouse::Button::Left:
                            state.mouseLeftButton = mouseEvent::mouseButtonAction::leftReleased;
                            break;
                        case sf::Mouse::Button::Right:
                            state.mouseRightButton = mouseEvent::mouseButtonAction::rightReleased;
                            break;
                        case sf::Mouse::Button::Middle:
                            state.mouseMiddleButton = mouseEvent::mouseButtonAction::middle1Released;
                            break;
                        case sf::Mouse::Button::XButton1:
                            state.mouseXButton1Button = mouseEvent::mouseButtonAction::xbutton1Released;
                            break;
                        case sf::Mouse::Button::XButton2:
                            state.mouseXButton2Button = mouseEvent::mouseButtonAction::xbutton2Released;
                            break;
                        default: break;
                    }
                    return;
            default : break;
        }
    }
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    state.mouseX = pos.x;
    state.mouseY = pos.y;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){ state.mouseLeftButton = mouseEvent::mouseButtonAction::leftDown; }
    else { state.mouseLeftButton = mouseEvent::mouseButtonAction::leftUp; }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){ state.mouseRightButton = mouseEvent::mouseButtonAction::rightDown; }
    else { state.mouseRightButton = mouseEvent::mouseButtonAction::rightUp; }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)){ state.mouseMiddleButton = mouseEvent::mouseButtonAction::middleDown; }
    else { state.mouseMiddleButton = mouseEvent::mouseButtonAction::middleUp;}
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1)){ state.mouseXButton1Button = mouseEvent::mouseButtonAction::xbutton1Down; }
    else { state.mouseXButton1Button = mouseEvent::mouseButtonAction::xbutton1Up; }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2)){ state.mouseXButton2Button = mouseEvent::mouseButtonAction::xbutton2Down; }
    else { state.mouseXButton2Button = mouseEvent::mouseButtonAction::xbutton2Up;}
}

void mouseEvent::checkmouseWheel(sf::RenderWindow &window)
{
    while(window.pollEvent(m_event)) {
        switch(m_event.type) {
            case sf::Event::MouseWheelScrolled:
                if(m_event.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel) {
                    state.mouseWheel = VerticalWheelMoved;
                }
                else {
                    state.mouseWheel = HorizontalWheelMoved;
                }
                state.wheelDelta = m_event.mouseWheelScroll.delta;
                state.mouseX = m_event.mouseWheelScroll.x;
                state.mouseY = m_event.mouseWheelScroll.y;
                break;
            default:
                state.mouseWheel = wheelNoAction;
                break;
        }
    }
}

void mouseEvent::checkMouseEvents(sf::RenderWindow &window)
{
    checkButtons(window);
    checkmouseWheel(window);
}
