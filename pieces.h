#ifndef   __thePieces__
#define   __thePieces__

#include <array>

struct Piece {                                                                   // Piece information: coord in board, kind of piece
        int x{0};
        int y{0};
        int current{-1};
        int rotation{0};
};

class thePieces{
public:
    thePieces();
    ~thePieces();
    int getBlock(int pieceNuber, int rotation, int x, int y);

private:
    std::array<const int, 11*4*4*4> m_allPieces;
};
#endif // __thePieces__

