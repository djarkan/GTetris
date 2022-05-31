#ifndef    __randomInt__
#define    __randomInt__

#include <random>
#include <algorithm>
#include <chrono>

class randomInt{

public:
    randomInt();
    ~randomInt();
    int randomInteger(int, int);
    #if defined(__MINGW32__)
        long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::seed_seq sseq{seed};
        std::mt19937 m_gen{sseq};
    #else
       std::random_device rd;
       std::mt19937 m_gen{rd()};
   #endif

};
#endif
