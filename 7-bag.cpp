#include "7-bag.hpp"

randomizer::randomizer():m_theBag {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10,0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
{
}

randomizer::~randomizer()
{
}

void randomizer::shuffleTheBag(bool enhanced, bool sevenBag)
{
    for(int i = 0; i < 11; i++)
        m_theBag[i] = m_theBag[i + 11];
    if(sevenBag) {
        if(enhanced)
            std::shuffle(m_theBag.begin() + 11, m_theBag.end(), randomInt.m_gen);
        else
            std::shuffle(m_theBag.begin() + 11, m_theBag.begin() + 18, randomInt.m_gen);
    }
    else {
        if(enhanced) {
            for(int i = 11; i < 22; i++)
                m_theBag[i] = randomInt.randomInteger(0, 10);
        }
        else {
            for(int i = 11; i < 22; i++)
                m_theBag[i] = randomInt.randomInteger(0, 6);
        }
    }
}

void randomizer::initTheBag(bool enhanced, bool sevenBag)
{
    if(sevenBag) {
        if(enhanced) {
            std::shuffle(m_theBag.begin(), m_theBag.begin() + 11, randomInt.m_gen);
            std::shuffle(m_theBag.begin() + 11, m_theBag.end(), randomInt.m_gen);
        }
        else {
            std::shuffle(m_theBag.begin(), m_theBag.begin() + 7, randomInt.m_gen);
            std::shuffle(m_theBag.begin() + 11, m_theBag.begin() + 18, randomInt.m_gen);
        }
    }
    else {
        if(enhanced) {
            for(int i = 0; i < 22; i++)
                m_theBag[i] = randomInt.randomInteger(0, 10);
        }
        else {
            for(int i = 0; i < 22; i++)
                m_theBag[i] = randomInt.randomInteger(0, 6);
        }
    }
}

bool randomizer::testFirstShuffle(bool enhanced)
{
    if(m_theBag[0] == 4 || m_theBag[0] == 5 || m_theBag[0] == 6 || (enhanced == true && m_theBag[0] == 9))
            return true;
    else
        return false;
}

int randomizer::getPieceAtPosition(int pos)
{
    return m_theBag[pos];
}

int randomizer::incrementPiecePositonInTheBag(bool enhanced, int piecePositonInTheBag, int sevenBag)
{
    if(enhanced)                                                      // increment piecePositonInTheBag
        if(piecePositonInTheBag == 10) {
            piecePositonInTheBag = 0;
            randomizer::shuffleTheBag(enhanced, sevenBag);
        }
        else {
            piecePositonInTheBag++;
            //std::cout << "increment fonction : " <<  piecePositonInTheBag << " main fonction : ";
        }
    else
        if(piecePositonInTheBag == 6) {
            piecePositonInTheBag = 0;
            randomizer::shuffleTheBag(enhanced, sevenBag);
        }
        else
            piecePositonInTheBag++;
    return piecePositonInTheBag;
}

void randomizer::printTheBag()
{
    for(auto x : m_theBag)
        std::cout << x << " ";
    std::cout << std::endl;
}
