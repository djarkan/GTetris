#ifndef    __randomizer__
#define    __randomizer__

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#if defined(__MINGW32__)
#include <chrono>
#endif // defined(__MINGW32__)

class randomizer{
public:
    randomizer();
    ~randomizer();
    int randomNumber(int mini, int maxi);
    void initTheBag(bool enhanced, bool sevenBag);
    void shuffleTheBag(bool enhanced, bool sevenBag);
    bool testFirstShuffle(bool enhanced);
    int  getPieceAtPosition(int pos);
    int incrementPiecePositonInTheBag(bool enhanced, int piecePositonInTheBag, int sevenBag);
    void printTheBag();

private:
    std::array<int, 22> m_theBag;
};
#endif
