// #include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define _MAXSIDES 25

int SIDE;
int MINES;

int main(){
    cout << "hello world";
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