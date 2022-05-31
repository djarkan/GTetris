#include "srs.hpp"

srs::srs()
{

}

std::pair<int, int> srs::getoffsetLeftRotation(int rotationNumber, int testNumber)
{
    return m_rotationToTheLeft[(rotationNumber * 5)+ testNumber];
}

std::pair<int, int> srs::getoffsetRightRotation(int rotationNumber, int testNumber)
{
    return m_rotationToTheRight[(rotationNumber * 5)+ testNumber];
}

std::pair<int, int> srs::getoffsetLeftRotationI(int rotationNumber, int testNumber)
{
    return m_rotationLeftPieceI[(rotationNumber * 5)+ testNumber];
}

std::pair<int, int> srs::getoffsetRightRotationI(int rotationNumber, int testNumber)
{
    return m_rotationRightPieceI[(rotationNumber * 5)+ testNumber];
}
