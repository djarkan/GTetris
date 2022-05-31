#ifndef    __randomizer__
#define    __randomizer__

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include <C:\Users\Djarkan\Documents\C++\codeblocks\tetris_extended\sources\generics\random\randomint.hpp>

class randomizer{
public:
    randomizer();
    ~randomizer();
    randomInt randomInt;
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
