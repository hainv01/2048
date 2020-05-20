#include "Board.h"

int power(int a) {
    int p = 1;
    while (a--) {
        p *= 2;
    }
    return p;
}

void CopyBoard(int source[Board_Size][Board_Size], int destination[Board_Size][Board_Size]) {
    for (int i = 0; i < Board_Size; i++) {
        for (int j = 0; j < Board_Size; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

Board::Board() {
    for (int i = 0; i < Board_Size; i++) {
        for (int j = 0; j < Board_Size; j++) {
            board[i][j] = Empty;
        }
    }
    board[Random(0, 1)][Random(0,3)] = 1;
    board[Random(2, 3)][Random(0,3)] = 1;
}

int Board::GetScore() {
    return score;
}

int Board::GetNumAt_xy(int x,int y) {
    return power(board[x][y]);
}

int Board::Random(int min, int max) {
    return rand() % (max-min+1) + min;
}

int Board::BonusScore(int num) {
    return power(num);
}

void Board::PutNewNum() {
    int hash_map[Board_Size*Board_Size];
    int Empty_Num = 0;
    for (int i = 0; i < Board_Size; i++) {
        for (int j = 0; j < Board_Size; j++) {
            if (board[i][j] == Empty) {
                hash_map[Empty_Num++] = i * Board_Size + j;
            }
        }
    }
    int tmp = Random(0, Empty_Num-1);
    board[hash_map[tmp] / Board_Size][hash_map[tmp] % Board_Size] = Random(1, 2);
}

bool Board::Move(int dir) {
    bool CanMove = false;
    switch (dir) {
        case Up:
            CanMove = Move_Up();
            break;
        case Left:
            CanMove = Move_Left();
            break;
        case Down:
            CanMove = Move_Down();
            break;
        case Right:
            CanMove = Move_Right();
            break;
    }
    if (CanMove) {
        PutNewNum();
    }
    return CanMove;
}

bool Board::Move_Up() {
    bool flag = false;
    for (int j = 0; j < Board_Size; j++) {
        int i = 0, k = 1;
        while (k < Board_Size) {
            if (board[k][j] == Empty) {
                k++;
            }
            else if (board[i][j] == Empty) {
                board[i][j] = board[k][j];
                board[k++][j] = Empty;
                flag = true;
            }
            else if (board[i][j] == board[k][j]) {
                board[i++][j]++;
                score += BonusScore(board[i-1][j]);
                board[k++][j] = Empty;
                flag = true;
            }
            else if (i+1 != k) {
                board[++i][j] = board[k][j];
                board[k++][j] = Empty;
                flag = true;
            }
            else {
                i++;
                k++;
            }
        }
    }
    return flag;
}

bool Board::Move_Left() {
    bool flag = false;
	for (int i = 0; i < Board_Size ; i++) {
		int j = 0, k = 1;
		while (k < Board_Size) {
			if(board[i][k] == Empty) {
				k++;
			}
			else if (board[i][j] == Empty) {
				board[i][j] = board[i][k];
				board[i][k++] = Empty;
				flag = true;
			}
			else if (board[i][j] == board[i][k]) {
				board[i][j++]++;
				score += BonusScore(board[i][j-1]);
				board[i][k++] = Empty;
				flag = true;
			}
			else if (j+1 != k) {
				board[i][++j] = board[i][k];
				board[i][k++] = Empty;
				flag = true;
			}
			else {
				j++;
				k++;
			}
		}
	}
	return flag;
}

bool Board::Move_Down() {
    bool flag = false;
    for (int j = 0; j < Board_Size; j++) {
        int i = Board_Size-1, k = Board_Size-2;
        while (k >= 0) {
            if (board[k][j] == Empty) {
                k--;
            }
            else if (board[i][j] == Empty){
                board[i][j] = board[k][j];
                board[k--][j] = Empty;
                flag = true;
            }
            else if (board[i][j] == board[k][j]) {
                board[i--][j]++;
                score += BonusScore(board[i+1][j]);
                board[k--][j] = Empty;
                flag = true;
            }
            else if (i-1 != k) {
                board[--i][j] = board[k][j];
                board[k--][j] = Empty;
                flag = true;
            }
            else {
                i--;
                k--;
            }
            
        }
    }
    return flag;
}

bool Board::Move_Right() {
    bool flag = false;
    for (int i = 0; i < Board_Size; i++) {
        int j = Board_Size-1, k = Board_Size-2;
        while (k >= 0) {
            if (board[i][k] == Empty) {
                k--;
            }
            else if (board[i][j] == Empty){
                board[i][j] = board[i][k];
                board[i][k--] = Empty;
                flag = true;
            }
            else if (board[i][j] == board[i][k]) {
                board[i][j--]++;
                score += BonusScore(board[i][j+1]);
                board[i][k--] = Empty;
                flag = true;
            }
            else if (j-1 != k) {
                board[i][--j] = board[i][k];
                board[i][k--] = Empty;
                flag = true;
            }
            else {
                j--;
                k--;
            }
        }
    }
    return flag;
}

bool Board::CheckFull() {
    for (int i = 0; i < Board_Size; i++) {
        for (int j = 0; j < Board_Size; j++) {
            if (board[i][j] == Empty) {
                return false;
            }
        }
    }
    return true;
}

bool Board::CheckGameOver() {
    if (!CheckFull()) {
        return false;
    }
    int tmp[Board_Size][Board_Size];
    CopyBoard(board, tmp);
    if (Move_Up()) {
        CopyBoard(tmp, board);
        return false;
    }
    if (Move_Left()) {
        CopyBoard(tmp, board);
        return false;
    }
    if (Move_Down()) {
        CopyBoard(tmp, board);
        return false;
    }
    if (Move_Right()) {
        CopyBoard(tmp, board);
        return false;
    }
    return true;
}

bool Board::CheckWin() {
    for (int i = 0; i < Board_Size; i++) {
        for (int j = 0; j < Board_Size; j++) {
            if (board[i][j] == Max) {
                return true;
            }
        }
    }
    return false;
}