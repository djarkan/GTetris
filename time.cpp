#include "time.hpp"

void convertTime(sf::Int32 elapsedTime, time& time)
{
    time.heures = elapsedTime / (1000 *60 * 60);
    sf::Int32 resteHeures = elapsedTime % (1000 *60 * 60);
    time.minutes = resteHeures / (1000 * 60);
    sf::Int32 resteMinutes = resteHeures % (1000 * 60);
    time.secondes = resteMinutes / (1000);
    time.millisecondes = resteMinutes % (1000);
}

std::string convertTimeToStringHourMinuteSecondMilisec(sf::Int32 elapsedTime)
{
    time time;
    convertTime(elapsedTime,time);
    std::string timeToDisplay{""};
    if (time.heures < 10) {
        timeToDisplay = "0" + std::to_string(time.heures) + ":";
    }
    else{
        timeToDisplay = std::to_string(time.heures) + ":";
    }
    if (time.minutes < 10) {
        timeToDisplay += "0" + std::to_string(time.minutes) + ":";
    }
    else{
        timeToDisplay += std::to_string(time.minutes) + ":";
    }
    if (time.secondes < 10) {
        timeToDisplay += "0" + std::to_string(time.secondes);
    }
    else{
        timeToDisplay += std::to_string(time.secondes);
    }
    timeToDisplay += "." + std::to_string(time.millisecondes);
    return timeToDisplay;
}

std::string convertTimeToStringHourMinuteSecond(sf::Int32 elapsedTime)
{
    time time;
    convertTime(elapsedTime,time);
    std::string timeToDisplay{""};
    if (time.heures < 10) {
        timeToDisplay = "0" + std::to_string(time.heures) + ":";
    }
    else{
        timeToDisplay = std::to_string(time.heures) + ":";
    }
    if (time.minutes < 10) {
        timeToDisplay += "0" + std::to_string(time.minutes) + ":";
    }
    else{
        timeToDisplay += std::to_string(time.minutes) + ":";
    }
    if (time.secondes < 10) {
        timeToDisplay += "0" + std::to_string(time.secondes);
    }
    else{
        timeToDisplay += std::to_string(time.secondes);
    }
    return timeToDisplay;
}

std::string convertTimeToStringMinuteSecondMilisec(sf::Int32 elapsedTime)
{
    time time;
    convertTime(elapsedTime,time);
    std::string timeToDisplay{""};
    std::to_string(time.minutes) + ":";
    timeToDisplay += std::to_string(time.minutes) + ":";
    if (time.secondes < 10) {
        timeToDisplay += "0" + std::to_string(time.secondes);
    }
    else{
        timeToDisplay += std::to_string(time.secondes);
    }
    timeToDisplay += "." + std::to_string(time.millisecondes);
    return timeToDisplay;
}

std::string convertTimeToStringMinuteSecond(sf::Int32 elapsedTime)
{
    time time;
    convertTime(elapsedTime,time);
    std::string timeToDisplay{""};
    if (time.minutes < 10) {
        timeToDisplay += "0" + std::to_string(time.minutes) + ":";
    }
    else{
        timeToDisplay += std::to_string(time.minutes) + ":";
    }
    if (time.secondes < 10) {
        timeToDisplay += "0" + std::to_string(time.secondes);
    }
    else{
        timeToDisplay += std::to_string(time.secondes);
    }
    return timeToDisplay;
}
