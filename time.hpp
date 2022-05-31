#include <string>
#include <SFML/system/time.hpp>

struct time {
    sf::Int32 heures;
    sf::Int32 minutes;
    sf::Int32 secondes;
    sf::Int32 millisecondes;
};

//void convertTime(sf::Int32, time&);
std::string convertTimeToStringHourMinuteSecondMilisec(sf::Int32 elapsedTime);
std::string convertTimeToStringHourMinuteSecond(sf::Int32 elapsedTime);
std::string convertTimeToStringMinuteSecondMilisec(sf::Int32 elapsedTime);
std::string convertTimeToStringMinuteSecond(sf::Int32 elapsedTime);
