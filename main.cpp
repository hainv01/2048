#include <iostream>
#include <fstream>
#include <time.h>

#include "Board.h"

using namespace std;

void GetBestScore(int &BestScore);

void UpdataBestScore(int &Score, int &BestScore);

void ShowBoard(Board GameBoard);

int main() {
    srand(time(0));
    int BestScore;
    int Score;
    bool retry = true;
    while (retry == true) {
        Board GameBoard;
        GetBestScore(BestScore);
        while (!GameBoard.CheckWin() && !GameBoard.CheckGameOver()) {
            Score = GameBoard.GetScore();
            UpdataBestScore(Score, BestScore);
            cout << "Score: " << Score << "\tBest " << BestScore << '\n';
            ShowBoard(GameBoard);
            printf("Enter move (W,A,S,D) : ");
            char dir;
            cin >> dir;
            switch(dir) {
                case 'w' :
                    GameBoard.Move(Up);
                    break;
                case 'a' :
                    GameBoard.Move(Left);
                    break;
                case 's' :
                    GameBoard.Move(Down);
                    break;
                case 'd' :
                    GameBoard.Move(Right);
                    break;
                default :
                    cout << "Invalid Move\n";
            }
            cout << "\n\n--------------------------------------\n\n";
        }
        if (GameBoard.CheckGameOver()) {
            cout << "Game Over\n";
        }
        else {
            cout << "You Win\n";
        }
        ShowBoard(GameBoard);
        Score = GameBoard.GetScore();
        cout << "Final Score " << Score << '\n';
        ofstream file("BestScore.txt", ios::out);
        if (file.is_open()) {
            UpdataBestScore(Score, BestScore);
            file << BestScore;
            file.close();
        }
        while (true) {
            cout << "Press r to retry x to exit ";
            char opt;
            cin >> opt;
            if (opt == 'r') break;
            else if (opt == 'x') {
                retry = false;
                break;
            }
            else {
                continue;
            }
        }
    }
}

void GetBestScore(int &BestScore) {
    ifstream file("BestScore.txt");
    if (file.is_open()) {
        file >> BestScore;
        file.close();
    }
}

void UpdataBestScore(int &Score, int &BestScore) {
    if (Score > BestScore) {
        BestScore = Score;
    }
}

void ShowBoard(Board GameBoard) {
    for (int i = 0; i < Board_Size; i++) {
        for (int j = 0; j < Board_Size; j++) {
            int tmp = GameBoard.GetNumAt_xy(i, j);
            if (tmp == 1) {
                cout << "-\t";
            }
            else {
                cout << tmp << '\t';
            }
        }
        cout << '\n';
    }
}