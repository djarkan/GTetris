#include "randomInt.hpp"

randomInt::randomInt()
{
}

randomInt::~randomInt()
{
}

int randomInt::randomInteger(int min, int max)
{
    std::uniform_int_distribution<> dis(min, max);
    return dis(m_gen);
}
