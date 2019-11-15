#include "board.h"
#include <algorithm>

#include <iostream>

board::board()
{

}

board::~board()
{

}

void board::clearBoard()
{
    std::fill( m_matrice.begin(), m_matrice.end(), 11);
}

int board::getBlockToDraw(int index)
{
    return m_matrice[index];
}

bool board::putNewPieceInBoard(Piece& currentPiece, thePieces& thePieces)
{
    currentPiece.rotation = 0;
    currentPiece.x = 3;
    switch (currentPiece.current) {
        case 9:
            currentPiece.y = 0;
            break;
        case 10:
            currentPiece.y = 2;
            break;
        default:
            currentPiece.y = 1;
            break;
    }
    if(testMovement(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.current, thePieces)) {
        currentPiece.y++;
        return true;
    }
    else
        return false;
}

bool board::testMovement(int virtualX, int virtualY, int virtualRotation, int pieceNumber, thePieces& thePieces)
{
    int boardBock{-1};

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) {
            boardBock = thePieces.getBlock(pieceNumber, virtualRotation, j, i);
            if(boardBock != -1)
                if(virtualX + j < 0 || virtualX + j > 9 || virtualY + i >= 23 || m_matrice[((virtualY + i) * 10) + virtualX + j] != 11)
                    return false;
        }
    return true;
}

void board::superRotationSystem(Piece& currentPiece, int virtualRotation, thePieces& thePieces)
{
    int offset{1};
    if(currentPiece.rotation == 1 || currentPiece.rotation == 3) {                    // SRS point 1 & 2
        if(currentPiece.current == 2) {
            if(testMovement(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces) == false && currentPiece.rotation == 1)
                offset = 2;
            else
                if(!testMovement(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.current, thePieces) && currentPiece.rotation == 3)
                    offset = 2;
        }
        if(testMovement(currentPiece.x + offset, currentPiece.y, virtualRotation, currentPiece.current, thePieces)) {
            currentPiece.x += offset;
            currentPiece.rotation = virtualRotation;
            return;
        }
        else
            if(testMovement(currentPiece.x - offset, currentPiece.y, virtualRotation, currentPiece.current, thePieces)) {
                currentPiece.x -= offset;
                currentPiece.rotation = virtualRotation;
                return;
            }
            else {                                                                     // SRS point 4 & 5
                if(currentPiece.current == 2)
                    offset = 3;
                else
                    offset = 2;
                if(testMovement(currentPiece.x, currentPiece.y - offset, virtualRotation, currentPiece.current, thePieces)) {
                    currentPiece.y -= offset;
                    currentPiece.rotation = virtualRotation;
                    return;
                }
            }
    }
    else
        if(currentPiece.rotation == 0 || currentPiece.rotation == 2) {                   // SRS point 3
            if(currentPiece.current == 2 && currentPiece.rotation == 2)
                offset = 2;
            if(testMovement(currentPiece.x, currentPiece.y - offset, virtualRotation, currentPiece.current, thePieces)) {
                currentPiece.y -= offset;
                currentPiece.rotation = virtualRotation;
                return;
            }
        }
}

void board::copyPieceInBoard(Piece& currentPiece, thePieces& thePieces)
{
    int boardBock{-1};

    for(auto i = 0; i < 4; i++)
        for(auto j = 0; j < 4; j++) {
            boardBock = thePieces.getBlock(currentPiece.current, currentPiece.rotation, j, i);
            if(boardBock > -1)
                m_matrice[((currentPiece.y + i) * 10) + currentPiece.x + j] = boardBock;
        }
}

void  board::printMatrice()
{
    for(auto i = 0; i < 23; i++) {                     // 0 au lieu de 2  temporaire IDEM
        for(auto j = 0; j < 10; j++) {
           int  block = getBlockToDraw((i*10) + j);
            std::cout << block << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

bool board::patternSearch(pattern& pattern, Piece& currentPiece)
{
    bool patternFound{false};

    if(IsThereLines(pattern))
        patternFound = true;
    if(pattern.TspinSearch)
        if(IsThereTspin(pattern, currentPiece))
			patternFound = true;
    if(pattern.nbLines > 0 && pattern.nbLines < 4 && pattern.Tspin == false)
        pattern.backToBack = 0;
    else
        if(pattern.nbLines > 3 || pattern.Tspin)
            pattern.backToBack++;
	if (patternFound)
		pattern.combo++;
	else
		pattern.combo = 0;
    return patternFound;
}

bool board::IsThereLines(pattern& pattern)
{
    bool patternFound{false};
    int counter{0};

    for(int i = 0; i < 23; i++) {                                                    // search lines
        for(int j = 0; j < 10; j++)
            if(m_matrice[(i * 10) + j] != 11)
                counter++;
        if(counter == 10) {
            patternFound = true;
            pattern.nbLines++;
            pattern.linesY.push_back(i);
        }
        counter = 0;
    }
    return patternFound;
}

bool board::IsThereTspin(pattern& pattern, Piece& currentPiece)
{
std::cout << "recherche si Tsipn" << std::endl;
    bool a = m_matrice[(currentPiece.y * 10) + currentPiece.x] != 11;
    bool b = m_matrice[(currentPiece.y * 10) + (currentPiece.x + 2)] != 11;
    bool c = m_matrice[((currentPiece.y + 2) * 10) + currentPiece.x] != 11;
    bool d = m_matrice[((currentPiece.y + 2) * 10) + (currentPiece.x + 2)] != 11;
    switch(currentPiece.rotation){
        case 0:
            pattern.Tspin = c && d && (a || b);
            pattern.miniTspin = (c || d) && a && b;
            break;
        case 1:
            pattern.Tspin =  a && c && ( b || d);
            pattern.miniTspin = ( a || c ) && b && d;
            break;
        case 2:
            pattern.Tspin =  a && b && ( c || d);
            pattern.miniTspin = ( a || b ) && c && d;
            break;
        case 3:
            pattern.Tspin =  b && d  && ( a || c);
            pattern.miniTspin = ( b || d ) &&  a && c;
            break;
    }
	pattern.TspinSearch = false;
std::cout << currentPiece.x << " : " << currentPiece.y << std::endl;
std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl << "d: " << d << std::endl;
std::cout << "Tspin: " << pattern.Tspin << std::endl << "miniTspin: " << pattern.miniTspin << std::endl;
	return(pattern.Tspin || pattern.miniTspin);
}

void board::IsThereClearBoard(pattern& pattern)
{
    for(int i = 229; i >= 0; i--)
        if(m_matrice[i] != 11)
           return;
    pattern.ClearBoard = true;
}

void board::shiftBlocksAfterLines(const pattern& pattern)
{
    for(int h = 0; h < pattern.nbLines; h++)
        for(int j = 0; j < 10; j++)
            for(int i = pattern.linesY[h]; i > 0; i--)
                m_matrice[(i * 10) + j] = m_matrice[((i - 1) * 10) + j];
}

void board::clearPattern(pattern& pattern)
{
    for(int i  = 0; i < pattern.nbLines; i++)
        pattern.linesY.pop_back();
    pattern.nbLines = 0;
    pattern.miniTspin = false;
    pattern.Tspin = false;
    pattern.ClearBoard = false;
}
