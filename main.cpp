// #include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <string.h>

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
#define _MINECHAR 'x'
#define _EMPTYCHAR '-'

int DIFFICULTY;
int SIDE;
int MINES;
char** gameBoard;
char** playerBoard;
bool gameOver;
bool playerWin;
int turns;

struct coord
{
    int x;
    int y;
};

//prototypes
void chooseDifficulty();
void createBoards();
void deleteBoards();
void fillBoard();
void printBoard();
void printGameBoard();
void update();
coord convertToCoord(int);
void removeElemFromVector(int, vector<int>&);
coord getSelection();
bool isCoordMine(coord);
bool isCoordMine(int, int);
void updatePlayerBoard(coord);
coord stringToCoord(char*);

int main(){
    bool playAgain = true;
    while(playAgain){
        char ans[1];
        gameOver = false;
        playerWin = false;
        turns = 0;

        chooseDifficulty();
        createBoards();
        fillBoard();

        while(!gameOver){
            update();
        }
        if(playerWin){
            printf("\n\n");
            printf("Congrats! You won!");
        }
        else{
            printBoard();
            printf("\n");
            printGameBoard();
            printf("\n\n");
            printf("OH NO! You exploded. Try again.\n");
        }

        printf("play again? (y/n)\n");
        scanf("%s", ans);


        if(*ans == 'n' || *ans == 'N'){
            playAgain = false;
        }
    }
    deleteBoards();
    
}

void update(){
    turns++;
    printBoard();
    coord selection = getSelection();
    if(isCoordMine(selection)){
        gameOver = true;
    }
    updatePlayerBoard(selection);
}

coord convertToCoord(int n){
    coord c;
    c.x = n / SIDE; 
    c.y = n % SIDE;
    return c;
}

coord getSelection(){
    char str[10];
    coord selection;
    if(turns == 1){
        printf("(i.e. 1, 15. All coordinates should be enter as x,y. Must include \",\" for separation and have no whitespace separation)");
    }
    printf("\nPlease enter a coordinate: ");

    scanf("%s", str);
    selection = stringToCoord(str);

    return selection;
}

coord stringToCoord(char* str){
    coord c;
    c.x,c.y = 0;
    string num;
    num.empty();
    
    char* token = strtok(str, ",");
    c.x = stoi(token);
    
    token = strtok(NULL, ",");
    c.y = stoi(token);

    return c;
}

bool isCoordMine(coord c){
    bool isMine = false;
    if(gameBoard[c.x][c.y] == _MINECHAR){
        isMine = true;
    }
    return isMine;
}

bool isCoordMine(int x, int y){
    bool isMine = false;
    if(x < 0 || y < 0 || x > SIDE - 1 || y > SIDE - 1){
        return isMine;
    }
    if(gameBoard[x][y] == _MINECHAR){
        isMine = true;
    }
    return isMine;
}

void updatePlayerBoard(coord c){
    if(isCoordMine(c)){
        playerBoard[c.x][c.y] = _MINECHAR;
        return;
    }

    int numOfMines = 0;
    if(isCoordMine(c.x - 1, c.y - 1)){
        numOfMines++;
    }
    if(isCoordMine(c.x, c.y - 1)){
        numOfMines++;
    }
    if(isCoordMine(c.x + 1, c.y - 1)){
        numOfMines++;
    }
    if(isCoordMine(c.x - 1, c.y)){
        numOfMines++;
    }
    if(isCoordMine(c.x + 1, c.y)){
        numOfMines++;
    }
    if(isCoordMine(c.x - 1, c.y + 1)){
        numOfMines++;
    }
    if(isCoordMine(c.x, c.y + 1)){
        numOfMines++;
    }
    if(isCoordMine(c.x + 1, c.y + 1)){
        numOfMines++;
    }
    playerBoard[c.x][c.y] = to_string(numOfMines)[0];

    for(int i = 0; i < SIDE; i++){
        for(int j = 0; j < SIDE; j++){
            if(playerBoard[i][j] == _EMPTYCHAR){
                break;
            }
            else if ((i == SIDE - 1 && j == SIDE - 1) && playerBoard[i][j] != _EMPTYCHAR){
                gameOver = true;
                playerWin = true;
            }
        }
    }
}

void removeElemFromVector(int n, vector<int>& v){
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); it++){
        if(*it == n){
            break;
        }
    }
    if(it == v.end() && *it != n){
        return;
    }
    v.erase(it);
}

void createBoards(){
    gameBoard = new char*[SIDE];

    for(int i = 0; i < SIDE; i++){
        gameBoard[i] = new char[SIDE];
    }
    
    playerBoard = new char*[SIDE];

    for(int i = 0; i < SIDE; i++){
        playerBoard[i] = new char[SIDE];
    }

}

void deleteBoards(){
    delete gameBoard;
    delete playerBoard;
}

void fillBoard(){
    srand(time(0));
    int minesCount = 0;

    //fill a vector with elements 0-SIDE
    vector<int> spots = vector<int>(SIDE * SIDE);
    vector<int>::iterator it = spots.begin();
    int n = 0;
    for(it; it != spots.end(); it++){
        *it = n;
        n++;
    }

    //initialize game board with empty spaces
    for (int i = 0; i < SIDE; i++){
        for(int j = 0; j < SIDE; j++){
            gameBoard[i][j] = _EMPTYCHAR;
        }
    }

    for (int i = 0; i < MINES; i++){
        //get a random number from the vector
        int randSpot = rand() % spots.size();
        //convert number to x, y coord
        coord randomCoord = convertToCoord(randSpot);
        //set that coord to mine
        gameBoard[randomCoord.x][randomCoord.y] = _MINECHAR;

        //delete number from vector
        removeElemFromVector(randSpot, spots);

        minesCount++;
    }
    
    // initialize player board with empty spaces
    for (int i = 0; i < SIDE; i++){
        for(int j = 0; j < SIDE; j++){
            playerBoard[i][j] = _EMPTYCHAR;
        }
    }
    
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
        SIDE = _INTERMEDIATE_SIDES;
        MINES = _INTERMEDIATE_MINES;
        break;
    case 3:
        SIDE = _ADVANCED_SIDES;
        MINES = _ADVANCED_MINES;
        break;
    
    default:
        break;
    }
    printf("\n");
}

void printBoard(){
    int i,j;
    printf("   ");

    for(i = 0; i < SIDE; i++){
        printf("%*d", 3, i);
    }
    
    printf("\n\n");

    for(i = 0; i < SIDE; i++){
        printf("%-*d", 3, i);

        for(j = 0; j < SIDE; j++){
            printf("%*c", 3, playerBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void printGameBoard(){
    int i,j;
    printf("   ");

    for(i = 0; i < SIDE; i++){
        printf("%*d", 3, i);
    }
    
    printf("\n\n");

    for(i = 0; i < SIDE; i++){
        printf("%-*d", 3, i);

        for(j = 0; j < SIDE; j++){
            printf("%*c", 3, gameBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}