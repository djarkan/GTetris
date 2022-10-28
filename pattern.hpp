#ifndef    __pattern__
#define    __pattern__

struct pattern {
    int nbLines{0};
    bool singleLine = false;
    bool doubleLine = false;
    bool tripleLine = false;
    bool tetris = false;
    std::vector<int> linesY;
    bool Tspin{false};
    bool TspinSingle = false;
    bool TspinDouble = false;
    bool TspinTriple = false;
    bool miniTspin{false};
    bool miniTspinSingle = false;
    bool miniTspinDouble = false;
    bool TspinSearch{false};
    bool ClearBoard{false};
    bool backToBackFlag{false};
    int backToBack{-1};
	int combo{-1};
};

#endif
