#ifndef    __board__
#define    __board__

#include <array>
#include <vector>
#include "pieces.h"

struct pattern {
    int nbLines{0};
    std::vector<int> linesY;
    bool miniTspin{false};
    bool Tspin{false};
    bool ClearBoard{false};
    int backToBack{0};
	int combo{0};
    bool TspinSearch{false};
};

class board{
public:
    board();
    ~board();
    void clearBoard();
    int getBlockToDraw(int index);
    bool putNewPieceInBoard(currentPiece& currentPiece, thePieces& thePieces);
    bool testMovement(int virtualX, int virtualY, int virtualRotation,int pieceNumber, thePieces& thePieces);
    void superRotationSystem(currentPiece& currentPiece, int virtualRotation, thePieces& thePieces);
    void copyPieceInBoard(currentPiece& currentPiece, thePieces& thePieces);
    bool patternSearch(pattern& pattern, currentPiece& currentPiece);
    void shiftBlocksAfterLines(const pattern& pattern);
    void clearPattern(pattern& pattern);
    void IsThereClearBoard(pattern& pattern);

    void  printMatrice(); //pour test

private:
    bool IsThereLines(pattern& pattern);
    bool IsThereTspin(pattern& pattern, currentPiece& currentPiece);

    std::array<int, 10 * 23> m_matrice;
};
#endif
