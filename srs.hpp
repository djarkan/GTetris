#ifndef    __srs__
#define    __srs__

#include <array>

class srs {

public:
    srs();
    std::pair<int, int> getoffsetLeftRotation(int rotationNumber, int testNumber);
    std::pair<int, int> getoffsetRightRotation(int rotationNumber, int testNumber);
    std::pair<int, int> getoffsetLeftRotationI(int rotationNumber, int testNumber);
    std::pair<int, int> getoffsetRightRotationI(int rotationNumber, int testNumber);

private:
//rotation de pieces 3x3
//rotation vers la gauche                                       Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5     // my y  = 0 is the bottom so need to set to the Y opposite
    std::array<std::pair<int, int >, 20> m_rotationToTheLeft {{ {0, 0}, 	 { 1, 0}, 	{ 1,-1}, 	{ 0, 2}, 	{ 1, 2},
                                                                {0, 0},	     {-1, 0}, 	{-1, 1}, 	{ 0,-2}, 	{-1,-2},
                                                                {0, 0}, 	 {-1, 0}, 	{-1,-1}, 	{ 0, 2}, 	{-1, 2},
                                                                {0, 0}, 	 { 1, 0}, 	{ 1, 1}, 	{ 0,-2}, 	{ 1,-2} }};
//rotation vers la droite                                       Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5
    std::array<std::pair<int, int >, 20> m_rotationToTheRight {{ {0, 0},	 {-1, 0},	{-1,-1},	{ 0, 2},	{-1, 2},
                                                                 {0, 0},     { 1, 0},	{ 1, 1}, 	{ 0,-2},	{ 1,-2},
                                                                 {0, 0},     { 1, 0},	{ 1,-1},    { 0, 2},	{ 1, 2},
                                                                 {0, 0},     {-1, 0},	{-1, 1},	{ 0,-2},	{-1,-2} }};
//rotation de la piece I
//rotation vers la gauche                                       Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5
    std::array<std::pair<int, int >, 20> m_rotationLeftPieceI {{ {0, 0},	 {-1, 0},	{ 2, 0},	{-1, 2},	{ 2,-1},
                                                                 {0, 0},	 {-2, 0},	{ 1, 0},	{-2,-1},	{ 1, 2},
                                                                 {0, 0},	 { 1, 0},	{-2, 0},	{ 1,-2},	{-2, 1},
                                                                 {0, 0},	 { 2, 0},	{-1, 0},	{ 2, 1},	{-1,-2} }};


//rotation vers la droite                                       Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5
    std::array<std::pair<int, int >, 20> m_rotationRightPieceI {{ {0, 0},	 {-2, 0},	{ 1, 0},	{-2,-1},	{ 1, 2},
                                                                  {0, 0},	 {-1, 0},	{ 2, 0},	{-1, 2},	{ 2,-1},
                                                                  {0, 0},	 { 2, 0},	{-1, 0},	{ 2, 1},	{-1,-2},
                                                                  {0, 0},	 { 1, 0},	{-2, 0},	{ 1,-2},	{-2, 1} }};
};

#endif

/*  SRS point of ratations
Tetriminos 3x3 rotation

left rotation
            Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5

0>>3 	    {0, 0}, 	 { 1, 0}, 	{ 1, 1}, 	{ 0,-2}, 	{ 1,-2},
3>>2 	    {0, 0},	     {-1, 0}, 	{-1,-1}, 	{ 0, 2}, 	{-1, 2},
2>>1 	    {0, 0}, 	 {-1, 0}, 	{-1, 1}, 	{ 0,-2}, 	{-1,-2},
1>>0 	    {0, 0}, 	 { 1, 0}, 	{ 1,-1}, 	{ 0, 2}, 	{ 1, 2},

right rotation
            Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5

0>>1 	    {0, 0},	     {-1, 0},	{-1, 1},	{ 0,-2},	{-1,-2},
1>>2 	    {0, 0},	     { 1, 0},	{ 1,-1}, 	{ 0, 2},	{ 1, 2},
2>>3 	    {0, 0},	     { 1, 0},	{ 1, 1},    { 0,-2},	{ 1,-2},
3>>0 	    {0, 0},	     {-1, 0},	{-1,-1},	{ 0, 2},	{-1, 2};

rotation of Tetrimino I
left rotation
            Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5

0>>3 	    {0, 0},	     {-1, 0},	{ 2, 0},	{-1, 2},	{ 2,-1},
3>>2 	    {0, 0},	     {-2, 0},	{ 1, 0},	{-2,-1},	{ 1, 2},
2>>1 	    {0, 0},	     { 1, 0},	{-2, 0},	{ 1,-2},	{-2, 1},
1>>0 	    {0, 0},	     { 2, 0},	{-1, 0},	{ 2, 1},	{-1,-2};

right rotation
            Test 1 	     Test 2 	 Test 3 	 Test 4 	 Test 5

0>>1 	    {0, 0},	     {-2, 0},	{ 1, 0},	{-2,-1},	{ 1, 2},
1>>2 	    {0, 0},	     {-1, 0},	{ 2, 0},	{-1, 2},	{ 2,-1},
2>>3 	    {0, 0},	     { 2, 0},	{-1, 0},	{ 2, 1},	{-1,-2},
3>>0 	    {0, 0},	     { 1, 0},	{-2, 0},	{ 1,-2},	{-2, 1};

*/
