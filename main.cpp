// #include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define _MAXSIDES 25
#define _BEGINNER 1
#define _BEGINNER_SIDES 9
#define _BEGINNER_MINES 4
#define _INTERMEDIATE 2
#define _INTERMEDIATE_SIDES 16
#define _INTERMEDIATE_MINES 40
#define _ADVANCED 3
#define _ADVANCED_SIDES 24
#define _ADVANCED_MINES 99

int DIFFICULTY;
int SIDE;
int MINES;

void chooseDifficulty();
void createBoard();

int main(){
    chooseDifficulty();
    createBoard();
}

void chooseDifficulty(){
    int level;

    cout << "Enter the difficulty level" << endl;
    cout << "Beginner:      1" << endl;
    cout << "Intermediate:  2" << endl;
    cout << "Advanced:      3" << endl;

    cin >> level;
    
    switch (level)
    {
    case 1:
        SIDE = _BEGINNER_SIDES;
        MINES = _BEGINNER_MINES;
        break;
    case 2:
        SIDE = _BEGINNER_SIDES;
        MINES = _BEGINNER_MINES;
        break;
    case 3:
        SIDE = _BEGINNER_SIDES;
        MINES = _BEGINNER_MINES;
        break;
    
    default:
        break;
    }
}

void printBoard(char myBoard[][_MAXSIDES]){
    int i,j;
    printf("    ");

    for(i = 0; i < SIDE; i++){
        printf("%d ", i);
        printf("\n\n");
    }

    for(i = 0; i < SIDE; i++){
        printf("%d  ", i);

        for(j = 0; j < SIDE; j++){
            printf("%c ", myBoard[i][j]);
            printf("\n");
        }
    }
}