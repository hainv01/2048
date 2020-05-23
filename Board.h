#include <stdlib.h>

int const Board_Size = 4;
int const Max = 11;

enum Direction{
    Up = 0,
    Left = 1,
    Down = 2,
    Right = 3,
    NoMove
};

int power(int a);
void CopyBoard(int source[Board_Size][Board_Size], int destination[Board_Size][Board_Size]);

class Board {
private:
    int board[Board_Size][Board_Size];
    int Empty = 0;
    int score = 0;
public:
    Board();
    int GetScore();
    int BonusScore(int num);
    int GetNumAt_xy(int x, int y);
    int Random(int min, int max);
    void PutNewNum();
    bool Move(int dir);
    bool Move_Up();
    bool Move_Left();
    bool Move_Down();
    bool Move_Right();
    bool CheckFull();
    bool CheckGameOver();
    bool CheckWin();
};