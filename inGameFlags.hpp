#ifndef    __inGameFlags__
#define    __inGameFlags__

struct inGameFlags{
    bool lockedout{false};
    bool holded{false};
    int holdedPiece{-1};
    bool jejoue{true};
    bool gameOver{false};
    bool goalReached{false};
    bool fisrtShuffle{true};
    int piecePositonInTheBag{0};								// store the N° of the holded piece
    int level{1};
    int nbLines{0};
	int score{0} ;
	sf::Time ellapsedPartyTime;
};
#endif
