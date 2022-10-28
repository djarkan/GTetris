#include "timer.hpp"

timer::timer()
{
    m_pausedTimerDuration = 0;
}

timer::timer(sf::Int32 timerDuration)
{
    m_timerDuration = timerDuration;
    m_pausedTimerDuration = 0;
}

timer::~timer(){
}

void timer::startTimer(){
    clock.restart();
    m_pausedTimerDuration = 0;
}

void timer::restartTimer(){
    clock.restart();
}

bool timer::isTimeElapsed(){
    sf::Time time = clock.getElapsedTime();
    sf::Int32 elapsedTime = time.asMilliseconds();
    return elapsedTime + m_pausedTimerDuration > m_timerDuration;
}

void timer::pauseTimer(){
    sf::Time time = clock.getElapsedTime();
    m_pausedTimerDuration = time.asMilliseconds();
}

void timer::setTimerDuration(sf::Int32 timerDuration){
    m_timerDuration = timerDuration;
}
