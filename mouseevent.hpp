#ifndef    __mouseEvent__
#define    __mouseEvent__

#include <SFML/Graphics.hpp>
#include <SFML/Window/mouse.hpp>

class mouseEvent{

public:
    enum mouseButtonAction {leftUp, leftPressed, leftDown, leftReleased,
                            rightUp, rightPressed, rightDown, rightReleased,
                            middleUp,middlePressed,middleDown, middle1Released,
                            xbutton1Up,xbutton1Pressed,xbutton1Down,xbutton1Released,
                            xbutton2Up,xbutton2Pressed,xbutton2Down,xbutton2Released,
                            wheelNoAction, VerticalWheelMoved, HorizontalWheelMoved};
   struct state{
        mouseButtonAction mouseLeftButton;
        mouseButtonAction mouseRightButton;
        mouseButtonAction mouseMiddleButton;
        mouseButtonAction mouseXButton1Button;
        mouseButtonAction mouseXButton2Button;
        int mouseX;
        int mouseY;
        mouseButtonAction mouseWheel;
        float wheelDelta;
    }state;

  //  mouseEvent();
  //  ~mouseEvent();
    void checkButtons(sf::RenderWindow &window);
    void checkmouseWheel(sf::RenderWindow &window);
    void checkMouseEvents(sf::RenderWindow &window);

private:
    sf::Event   m_event;

};
#endif
