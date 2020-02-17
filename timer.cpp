#include "timer.h"

timer::timer(){
}

timer::timer(sf::Int32 timerDuration)
{
    m_timerDuration = timerDuration;
}

timer::~timer(){
}

void timer::startTimer(){
    clock.restart();
}

bool timer::isTimeElapsed(){
    sf::Time time = clock.getElapsedTime();
    sf::Int32 elapsedTime = time.asMilliseconds();
    return elapsedTime > m_timerDuration;
}

void timer::setTimerDuration(sf::Int32 timerDuration){
    m_timerDuration = timerDuration;
}
