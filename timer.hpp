#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>

class timer
{
    public:
        timer();
        timer(sf::Int32 timerDuration);
        ~timer();
        void startTimer();
        void restartTimer();
        void pauseTimer();
        bool isTimeElapsed();
        void setTimerDuration(sf::Int32 timerDuration);

        sf::Int32 m_timerDuration;

    private:
        sf::Clock clock;
        sf::Int32 m_pausedTimerDuration;
};

#endif // TIMER_H
