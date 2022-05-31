#include "pieces.hpp"

thePieces::thePieces():m_allPieces  {
        -1,-1, 0,-1,            // piece 0 : L
         0, 0, 0,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 0,-1,-1,
        -1, 0,-1,-1,
        -1, 0, 0,-1,
        -1,-1,-1,-1,

        -1,-1,-1,-1,
         0, 0, 0,-1,
         0,-1,-1,-1,
        -1,-1,-1,-1,

         0, 0,-1,-1,
        -1, 0,-1,-1,
        -1, 0,-1,-1,
        -1,-1,-1,-1,

         1,-1,-1,-1,            // piece 1 : J
         1, 1, 1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 1, 1,-1,
        -1, 1,-1,-1,
        -1, 1,-1,-1,
        -1,-1,-1,-1,

        -1,-1,-1,-1,
         1, 1, 1,-1,
        -1,-1, 1,-1,
        -1,-1,-1,-1,

        -1, 1,-1,-1,
        -1, 1,-1,-1,
         1, 1,-1,-1,
        -1,-1,-1,-1,

        -1,-1,-1,-1,            // piece 2 : I
         2, 2, 2, 2,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1,-1, 2,-1,
        -1,-1, 2,-1,
        -1,-1, 2,-1,
        -1,-1, 2,-1,

        -1,-1,-1,-1,
        -1,-1,-1,-1,
         2, 2, 2, 2,
        -1,-1,-1,-1,

        -1, 2,-1,-1,
        -1, 2,-1,-1,
        -1, 2,-1,-1,
        -1, 2,-1,-1,

        -1, 3,-1,-1,            // piece 3 : T
         3, 3, 3,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 3,-1,-1,
        -1, 3, 3,-1,
        -1, 3,-1,-1,
        -1,-1,-1,-1,

        -1,-1,-1,-1,
         3, 3, 3,-1,
        -1, 3,-1,-1,
        -1,-1,-1,-1,

        -1, 3,-1,-1,
         3 ,3,-1,-1,
        -1, 3,-1,-1,
        -1,-1,-1,-1,

        -1, 4, 4,-1,            // piece 4 : O
        -1, 4, 4,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 4, 4,-1,
        -1, 4, 4,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 4, 4,-1,
        -1, 4, 4,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 4, 4,-1,
        -1, 4, 4,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 5, 5,-1,            // piece 5 : S
         5, 5,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 5,-1,-1,
        -1, 5, 5,-1,
        -1,-1, 5,-1,
        -1,-1,-1,-1,

        -1, 5, 5,-1,
         5, 5,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

         5,-1,-1,-1,
         5, 5,-1,-1,
        -1, 5,-1,-1,
        -1,-1,-1,-1,

         6, 6,-1,-1,            // piece 6 : Z
        -1, 6, 6,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 6,-1,-1,
         6, 6,-1,-1,
         6,-1,-1,-1,
        -1,-1,-1,-1,

        -1,-1,-1,-1,
         6, 6,-1,-1,
        -1, 6, 6,-1,
        -1,-1,-1,-1,

        -1,-1, 6,-1,
        -1, 6, 6,-1,
        -1, 6,-1,-1,
        -1,-1,-1,-1,

         7,-1, 7,-1,            // piece 7 : U
         7, 7, 7,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 7, 7,-1,
        -1, 7,-1,-1,
        -1, 7, 7,-1,
        -1,-1,-1,-1,

        -1,-1,-1,-1,
         7, 7, 7,-1,
         7,-1, 7,-1,
        -1,-1,-1,-1,

         7, 7,-1,-1,
        -1, 7,-1,-1,
         7, 7,-1,-1,
        -1,-1,-1,-1,

        -1, 8,-1,-1,            // piece 8 : mini L
        -1, 8, 8,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 8, 8,-1,
        -1, 8,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 8, 8,-1,
        -1,-1, 8,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1,-1, 8,-1,
        -1, 8, 8,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1, 9,-1,-1,            // piece 9 : croix
         9, 9, 9,-1,
        -1, 9,-1,-1,
        -1,-1,-1,-1,

        -1, 9,-1,-1,
         9, 9, 9,-1,
        -1, 9,-1,-1,
        -1,-1,-1,-1,

        -1, 9,-1,-1,
         9 ,9, 9,-1,
        -1, 9,-1,-1,
        -1,-1,-1,-1,

        -1, 9,-1,-1,
         9, 9, 9,-1,
        -1, 9,-1,-1,
        -1,-1,-1,-1,

        -1,10,-1,-1,            // piece 10 : simple block
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1,10,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1,10,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,

        -1,10,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1
     }
{

}

thePieces::~thePieces()
{

}

int thePieces::getBlock(int pieceNuber, int rotation, int x, int y)
{
 return m_allPieces[(pieceNuber * 4 * 4 * 4) + (rotation * 4 * 4) + (y * 4) + x];
}
