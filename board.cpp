#include "board.hpp"

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

void board::copyPieceInBoard(Piece& currentPiece, thePieces& thePieces)
{
    int boardBlock{-1};

    for(auto i = 0; i < 4; i++)
        for(auto j = 0; j < 4; j++) {
            boardBlock = thePieces.getBlock(currentPiece.current, currentPiece.rotation, j, i);
            if(boardBlock > -1)
                m_matrice[((currentPiece.y + i) * 10) + currentPiece.x + j] = boardBlock;
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
    bool lines = IsThereLines(pattern);
    bool clearedBoard{false};
    if(lines) { clearedBoard = IsThereClearBoard(pattern); }
    bool Tspin {false};
    if(pattern.TspinSearch){
        if(IsThereTspin(pattern, currentPiece)){
			Tspin = true;
        }
    }
    if((Tspin && !lines) || (pattern.nbLines > 0 && pattern.nbLines < 4)) { pattern.backToBack = -1; }
	if ( lines || Tspin) { pattern.combo++; }
	else { pattern.combo = -1; }
    return lines || Tspin || clearedBoard;
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
    switch(pattern.nbLines){
        case 1: pattern.singleLine = true;
                break;
        case 2: pattern.doubleLine = true;
                break;
        case 3: pattern.tripleLine = true;
                break;
        case 4: pattern.tetris = true;
                pattern.backToBack++;
                if(pattern.backToBack > 0) { pattern.backToBackFlag = true; }
                break;
        default: break;
        }
    return patternFound;
}

bool board::IsThereTspin(pattern& pattern, Piece& currentPiece)
{
    bool a = m_matrice[(currentPiece.y * 10) + currentPiece.x] != 11;
    bool b = m_matrice[(currentPiece.y * 10) + (currentPiece.x + 2)] != 11;
    bool c = m_matrice[((currentPiece.y + 2) * 10) + currentPiece.x] != 11;
    bool d = m_matrice[((currentPiece.y + 2) * 10) + (currentPiece.x + 2)] != 11;
    switch(currentPiece.rotation){
        case 0:
            pattern.miniTspin = (c && d) && (a || b);
            pattern.Tspin = (c || d) && (a && b);
            break;
        case 1:
            if(currentPiece.x < 0) {
                a = true;
                c = true;
            }
            pattern.miniTspin =  (a && c) && ( b || d);
            pattern.Tspin = ( a || c ) && b && d;
            break;
        case 2:
            pattern.miniTspin =  (a && b) && ( c || d);
            pattern.Tspin = ( a || b ) && (c && d);
            break;
        case 3:
            if(currentPiece.x == 8) {
                b = true;
                d = true;
            }
            pattern.miniTspin =  b && d  && ( a || c);
            pattern.Tspin = ( b || d ) &&  (a && c);
            break;
    }
   if(pattern.Tspin){
        pattern.miniTspin = false;
        switch(pattern.nbLines){
            case 1: pattern.TspinSingle = true;
                    pattern.singleLine = false;
                    pattern.Tspin = false;
                    break;
            case 2: pattern.TspinDouble = true;
                    pattern.doubleLine = false;
                    pattern.Tspin = false;
                    break;
            case 3: pattern.TspinTriple = true;
                    pattern.tripleLine = false;
                    pattern.Tspin = false;
                    break;
            default: break;
        }
        pattern.backToBack++;
        if(pattern.backToBack > 0) { pattern.backToBackFlag = true; }
    }
    if(pattern.miniTspin){
        switch(pattern.nbLines){
            case 1: pattern.miniTspinSingle = true;
                    pattern.singleLine = false;
                    pattern.miniTspin = false;
                    break;
            case 2: pattern.miniTspinDouble = true;
                    pattern.doubleLine = false;
                    pattern.miniTspin = false;
                    break;
        }
        pattern.backToBack++;
        if(pattern.backToBack > 0) { pattern.backToBackFlag = true; }
    }
	pattern.TspinSearch = false;
	return pattern.Tspin || pattern.miniTspin || pattern.TspinSingle ||  pattern.TspinDouble || pattern.TspinTriple	|| pattern.miniTspinSingle || pattern.miniTspinDouble;
}

bool board::IsThereClearBoard(pattern& pattern)
{
    for(auto i = 229; i >= 0; i--)
        if(m_matrice[i] != 11)
           return false;
    pattern.ClearBoard = true;
    return true;
}

void board::shiftBlocksAfterLines(const pattern& pattern)
{
    for(auto h = 0; h < pattern.nbLines; h++)
        for(auto j = 0; j < 10; j++)
            for(auto i = pattern.linesY[h]; i > 0; i--)
                m_matrice[(i * 10) + j] = m_matrice[((i - 1) * 10) + j];
}

void board::clearPattern(pattern& pattern)
{
    pattern.linesY.resize(0);
    pattern.nbLines = 0;
    pattern.singleLine = false;
    pattern.doubleLine = false;
    pattern.tripleLine = false;
    pattern.tetris = false;
    pattern.miniTspin = false;
    pattern.Tspin = false;
    pattern.ClearBoard = false;
    pattern.TspinSingle = false;
    pattern.TspinDouble = false;
    pattern.TspinTriple = false;
    pattern.miniTspinSingle = false;
    pattern.miniTspinDouble = false;
    pattern.backToBackFlag = false;
}

void board::insertBricks()
{
    for(auto i = 1; i < 23; i++) {
        for(auto j = 0; j < 10; j++) {
            m_matrice[j + (i * 10)] = m_matrice[j + (i * 10) + 10];
        }
    }
    for(auto i = 0; i < 10; i++) {
        m_matrice[220 + i] = 11;
    }
    randomInt randomInt;
    for(auto i = 0; i <= 9; i++) {
        m_matrice[220 + randomInt.randomInteger(0, 9)] = 12;
    }
}
