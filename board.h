#ifndef    __board__
#define    __board__

#include <array>
#include <vector>
#include "pieces.h"
#include "7-bag.h"

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
    int backToBack{-1};
	int combo{-1};
};

class board{
public:
    board();
    ~board();
    void clearBoard();
    int getBlockToDraw(int index);
    bool putNewPieceInBoard(Piece& currentPiece, thePieces& thePieces);
    bool testMovement(int virtualX, int virtualY, int virtualRotation,int pieceNumber, thePieces& thePieces);
    void superRotationSystem(Piece& currentPiece, int virtualRotation, thePieces& thePieces);
    void copyPieceInBoard(Piece& currentPiece, thePieces& thePieces);
    bool patternSearch(pattern& pattern, Piece& currentPiece);
    void shiftBlocksAfterLines(const pattern& pattern);
    void clearPattern(pattern& pattern);
    void IsThereClearBoard(pattern& pattern);
    bool IsTherePattern(pattern& pattern);
    void insertBricks(randomizer& random);

    void  printMatrice(); //pour test

private:
    bool IsThereLines(pattern& pattern);
    bool IsThereTspin(pattern& pattern, Piece& currentPiece);

    std::array<int, 10 * 23> m_matrice;
};
#endif
