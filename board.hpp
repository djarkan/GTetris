#ifndef    __board__
#define    __board__

#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include "pieces.hpp"
#include "pattern.hpp"
#include "randomint.hpp"

class board{
public:
    board();
    ~board();
    void clearBoard();
    int getBlockToDraw(int index);
    bool putNewPieceInBoard(Piece& currentPiece, thePieces& thePieces);
    bool testMovement(int virtualX, int virtualY, int virtualRotation,int pieceNumber, thePieces& thePieces);
    void copyPieceInBoard(Piece& currentPiece, thePieces& thePieces);
    bool patternSearch(pattern& pattern, Piece& currentPiece);
    void shiftBlocksAfterLines(const pattern& pattern);
    void clearPattern(pattern& pattern);
    bool IsThereClearBoard(pattern& pattern);
    bool IsTherePattern(pattern& pattern);
    void insertBricks();

    void  printMatrice(); //pour test

private:
    bool IsThereLines(pattern& pattern);
    bool IsThereTspin(pattern& pattern, Piece& currentPiece);

    std::array<int, 10 * 23> m_matrice;
};
#endif
