#include "7-bag.h"

randomizer::randomizer():m_theBag {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10,0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
{
}

randomizer::~randomizer()
{
}
int randomizer::randomNumber(int mini, int maxi)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::seed_seq sseq{seed};
    std::mt19937 gen{sseq};
    std::uniform_int_distribution<int> dis(mini, maxi);
    sf::sleep(sf::milliseconds(3));
    return dis(gen);
}

void randomizer::shuffleTheBag(bool enhanced, bool sevenBag)
{
    for(int i = 0; i < 11; i++)
        m_theBag[i] = m_theBag[i + 11];
   #if defined(__MINGW32__)
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::seed_seq sseq{seed};
        std::mt19937 gen{sseq};
    #else
       std::random_device rd;
       std::mt19937 gen{rd()};
   #endif
    if(sevenBag) {
        if(enhanced)
            std::shuffle(m_theBag.begin() + 11, m_theBag.end(), gen);
        else
            std::shuffle(m_theBag.begin() + 11, m_theBag.begin() + 18, gen);
    }
    else {
        if(enhanced) {
            std::uniform_int_distribution<int> dis(0, 10);
            for(int i = 11; i < 22; i++)
                m_theBag[i] = dis(gen);
        }
        else {
            std::uniform_int_distribution<int> dis(0, 6);
            for(int i = 11; i < 22; i++)
                m_theBag[i] = dis(gen);
        }
    }
}

void randomizer::initTheBag(bool enhanced, bool sevenBag)
{
    #if defined(__MINGW32__)
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::seed_seq sseq{seed};
        std::mt19937 gen{sseq};
    #else // defined(__MINGW32__)
       std::random_device rd;  //Will be used to obtain a
       std::mt19937 gen{rd()}; //Standard mersenne_twister_engine seeded with rd()
   #endif // defined(__MINGW32__)
    if(sevenBag) {
        if(enhanced) {
            std::shuffle(m_theBag.begin(), m_theBag.begin() + 11, gen);
            std::shuffle(m_theBag.begin() + 11, m_theBag.end(), gen);
        }
        else {
            std::shuffle(m_theBag.begin(), m_theBag.begin() + 7, gen);
            std::shuffle(m_theBag.begin() + 11, m_theBag.begin() + 18, gen);
        }
    }
    else {
        if(enhanced) {
            std::uniform_int_distribution<int> dis(0, 10);
            for(int i = 0; i < 22; i++)
                m_theBag[i] = dis(gen);
        }
        else {
            std::uniform_int_distribution<int> dis(0, 6);
            for(int i = 0; i < 22; i++)
                m_theBag[i] = dis(gen);
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
