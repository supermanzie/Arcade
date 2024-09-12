#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int arrBoard[10][10];
int arrBoardEnemy[10][10];

//initializes the two boards as arrays
void setBoard() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            arrBoard[x][y] = 0;
        }
    }
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            arrBoardEnemy[x][y] = 0;
        }
    }
    //displays opening screen to player; prints initial board
    cout << "\t\t\t BATTLESHIP" << endl << endl;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cout << arrBoard[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << "'0' represents an unoccupied space." << endl << endl;
    cout << "'1' represents a space occupied by a ship." << endl << endl;
    cout << "'2' represents a ship that has been hit." << endl << endl;
}

void showBoard() { //a "show board" command used periodically and for testing
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cout << arrBoard[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void showEnemyBoard() { //a command for showing the enemy's board; used for testing
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cout << arrBoardEnemy[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

struct ship {//ship strucut; holds a few important variables for each "ship"
    string name;
    string playerStatus;
    int length;
    ship(string passinName, string passinPlayer, int passinLength) {//ship's lone constructor
        name = passinName;
        playerStatus = passinPlayer;
        length = passinLength;
    }
};
ship carrierPlayer = ship("carrier", "player", 5); //initializes the game's ships using a constructor
ship carrierEnemy = ship("carrier", "enemy", 5);
ship battleshipPlayer = ship("battleship", "player", 4);
ship battleshipEnemy = ship("battleship", "enemy", 4);
ship cruiserPlayer = ship("cruiser", "player", 3);
ship cruiserEnemy = ship("cruiser", "enemy", 3);
ship submarinePlayer = ship("submarine", "player", 3);
ship submarineEnemy = ship("submarine", "enemy", 3);
ship destroyerPlayer = ship("destroyer", "player", 2);
ship destroyerEnemy = ship("destroyer", "enemy", 2);;

int randomNumberGen() { //random number generator; 1 to 10 limit
    int ran;
    srand(time(0));
    ran = ((rand() % 10) + 1);
    return ran;
}

bool overlapTest(ship subShip, int x, int y, char direction) { //checks that the selected variables for a ship do not overlap with already-placed variables on either board
    if (subShip.playerStatus == "player") {
        for (int a = 0; a < subShip.length; a++) {
            if ((arrBoard[y + a - 1][x - 1] == 1) && (direction == 'V' || direction == 'v')) {
                return false;
            }
            else if ((arrBoard[y - 1][x + a - 1] == 1) && (direction == 'H' || direction == 'h')) {
                return false;
            }
        }
    }
    if (subShip.playerStatus == "enemy") {
        for (int a = 0; a < subShip.length; a++) {
            if ((arrBoardEnemy[y + a - 1][x - 1] == 1) && (direction == 'V' || direction == 'v')) {
                return false;
            }
            else if ((arrBoardEnemy[y - 1][x + a - 1] == 1) && (direction == 'H' || direction == 'h')) {
                return false;
            }
        }
    }
    return true;
}

bool limitCheck(ship subShip, int x, int y, char direction) {//checks that the submitted coordinates of a ship do not extend beyond the board before accepting them
    if (((x + subShip.length) > 11) && (direction == 'H' || direction == 'h')) {
        return false;
    }
    if (((y + subShip.length) > 11) && (direction == 'V' || direction == 'v')) {
        return false;
    }
    if ((x <= 0 || y <= 0)) {
        return false;
    }
    else {
        return true;
    }
}

ship coordinateSet(ship subShip, int x, int y, char direction) { //sets a ship's coordinates by updating the board
    while (1) {
        if (direction == 'H' || direction == 'h') {
            for (int iteration = 0; iteration < subShip.length; iteration++) {
                if (subShip.playerStatus == "player") {
                    arrBoard[y - 1][x + iteration - 1] = 1;
                }
                else if (subShip.playerStatus == "enemy") {
                    arrBoardEnemy[y - 1][x + iteration - 1] = 1;
                }
            }
            break;
        }
        else if (direction == 'V' || direction == 'v') {
            for (int iteration = 0; iteration < subShip.length; iteration++) {
                if (subShip.playerStatus == "player") {
                    arrBoard[y + iteration - 1][x - 1] = 1;
                }
                else if (subShip.playerStatus == "enemy") {
                    arrBoardEnemy[y + iteration - 1][x - 1] = 1;
                }
            }
            break;
        }
        else {
            cout << "Please, enter H or V: ";
            cin >> direction;
            continue;
        }
    }
    return subShip;
}

ship setPlayerCord(ship subShip) { //a function for taking user input in the setting of the player's ships' coordinates; runs the relevant tests, continues (infinitely) until those tests are passed
    int x;
    int y;
    char direction;
    while (1) {
        cout << "Now, set the starting x coordinate for your " << subShip.length << " unit " << subShip.name << ": ";
        cin >> x;
        cout << "Now, its corresponding y coordinate: ";
        cin >> y;
        cout << "Type H to set this ship horizontally (going rightwards). Type V to set it vertically (going downwards): ";
        cin >> direction;
        if (limitCheck(subShip, x, y, direction) == false) {
            cout << "Those coordinates go beyond the limits of the board!" << endl;
            continue;
        }
        if (overlapTest(subShip, x, y, direction) == false) {
            cout << "Those coordinates overlap with an already placed ship!" << endl;
            continue;
        }
        coordinateSet(subShip, x, y, direction);
        cout << endl;
        break;
    }
    showBoard();
    return subShip;
}

ship setEnemyCord(ship subShip) {//a function for setting the computer's ships; takes random numbers rather than user inputs, but runs the same tests in the same fashion
    int x;
    int y;
    char direction;
    while (1) {
        x = randomNumberGen();
        y = randomNumberGen();
        if (randomNumberGen() >= 5) {
            direction = 'H';
        }
        else {
            direction = 'V';
        }
        if (limitCheck(subShip, x, y, direction) == false) {
            continue;
        }
        if (overlapTest(subShip, x, y, direction) == false) {
            continue;
        }
        coordinateSet(subShip, x, y, direction);
        break;
    }
    return subShip;
}

void initializeGame() {//runs the set coordinates function for the player and then the computer
    carrierPlayer = setPlayerCord(carrierPlayer);
    battleshipPlayer = setPlayerCord(battleshipPlayer);
    cruiserPlayer = setPlayerCord(cruiserPlayer);
    submarinePlayer = setPlayerCord(submarinePlayer);
    destroyerPlayer = setPlayerCord(destroyerPlayer);

    cout << "Setting enemy coordinates..." << endl;
    carrierEnemy = setEnemyCord(carrierEnemy);
    battleshipEnemy = setEnemyCord(battleshipEnemy);
    cruiserEnemy = setEnemyCord(cruiserEnemy);
    submarineEnemy = setEnemyCord(submarineEnemy);
    destroyerEnemy = setEnemyCord(destroyerEnemy);
    cout << "Enemy coordinates set!" << endl;
}

int totalPlayerHits = 0;
int totalEnemyHits = 0;//each hit a player makes is tallied; the number of ship units on a board is constant, so calculating the maximum number of hits (in other words, the number of hits to win) is straightfoward.

void playerTurn() { //runs player's turn; takes user input then checks against enemy's board
    int x;
    int y;
    cout << "Please enter an x coordinate at which to fire at the enemy's ships: ";
    cin >> x;
    cout << "Now, a y coordinate: ";
    cin >> y;
    if (arrBoardEnemy[y - 1][x - 1] == 0) {//miss outcome
        cout << "You missed!" << endl;
    }
    else if (arrBoardEnemy[y - 1][x - 1] == 1) {//hit outcome
        totalPlayerHits = totalPlayerHits + 1;//plus one score
        arrBoardEnemy[y - 1][x - 1] = 2;
        cout << "You hit an enemy ship!" << endl << (17 - totalPlayerHits) << " occpuied enemy spaces remain." << endl;
    }
    else if (arrBoardEnemy[y - 1][x - 1] == 2) {//repeat hit outcome
        cout << "A ship was already struck at those coordinates!";
    }
}

void enemyTurn() {//runs computer's turn; takes random values and then checks against players's board
    cout << "The enemy is selecting coordinates..." << endl;
    while (1) {
        int x = randomNumberGen();
        int y = randomNumberGen();
        if (arrBoard[y - 1][x - 1] == 1) {//hit outcome
            totalEnemyHits = totalEnemyHits + 1;
            arrBoard[y - 1][x - 1] = 2;
            cout << endl;
            showBoard();
            cout << "The enemy has hit one of your ships!" << endl;
            break;
        }
        if (arrBoard[y - 1][x - 1] == 0) {//miss outcome
            cout << "The enemy missed!" << endl;
            break;
        }
        else if (arrBoard[y - 1][x - 1] == 2)//repeat hit outcome
            continue;
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------*/

//Connect four code
char c4board[6][7];
int c4turn = 1;
string c4player;
char c4piece;
int c4gameoverval;

//Gameboard Values
void c4gameval() {
    for (int c4rows = 0; c4rows < 6; c4rows++) {
        for (int c4cols = 0; c4cols < 7; c4cols++) {
            c4board[c4rows][c4cols] = '?';
        }
    }
}
//Gameboard that will get printed at the beginning and each time a move is made
void c4gameboard() {
    cout << "    1   2   3   4   5   6   7  " << endl;
    int c4boardcount;
    for (int c4c = 0; c4c < 6; c4c++) {
        c4boardcount = c4c + 1;
        cout << c4boardcount << " | " << c4board[c4c][0] << " | " << c4board[c4c][1] << " | " << c4board[c4c][2] << " | " << c4board[c4c][3] << " | " << c4board[c4c][4] << " | " << c4board[c4c][5] << " | " << c4board[c4c][6] << " | " << endl;
    }
}

//Player 1 Move
void c4p1turn() {
    int c4colnum = 8;
    int c4repeat = 1;
    int c4colplace;
    c4player = "P1";
    c4piece = 'X';
    cout << "Turn " << c4turn << endl;
    //move
    while ((c4turn % 2) == 1) {
        //column you want the piece to be placed into
        while (c4repeat > 0) {
            cout << "Which column do you want to place your piece(1-7)? ";
            cin >> c4colnum;
            while (c4colnum <= 0 || c4colnum >= 8) {
                cout << "Which column do you want to place your piece(1-7)? ";
                cin >> c4colnum;
            }
            c4repeat = 0;
        }
        c4colplace = c4colnum - 1;
        //check for open space in the column
        for (int c4rowcount = 5; c4rowcount >= 0; c4rowcount--) {
            if (c4board[c4rowcount][c4colplace] == '?') {
                c4board[c4rowcount][c4colplace] = c4piece;
                c4gameboard();
                cout << "Turn " << c4turn << " over" << endl;
                c4turn = c4turn + 1;
                break;
            }
        }
        //End Turn if column is acceptable for move
        if ((c4turn % 2) == 0) {
            break;
        }
        //Ask for another column if column is not acceptable for move
        c4repeat = 1;
        cout << "Choose another column" << endl;
    }
}

//Player 2 Move
void c4p2turn() {
    int c4colnum = 8;
    int c4repeat = 1;
    int c4colplace;
    c4player = "P2";
    c4piece = 'O';
    cout << "Turn " << c4turn << endl;
    //move
    while ((c4turn % 2) == 0) {
        //column you want the piece to be placed into
        while (c4repeat > 0) {
            cout << "Which column do you want to place your piece(1-7)? ";
            cin >> c4colnum;
            while (c4colnum <= 0 || c4colnum >= 8) {
                cout << "Which column do you want to place your piece(1-7)? ";
                cin >> c4colnum;
            }
            c4repeat = 0;
        }
        c4colplace = c4colnum - 1;
        //check for open space in the column
        for (int c4rowcount = 5; c4rowcount >= 0; c4rowcount--) {
            if (c4board[c4rowcount][c4colplace] == '?') {
                c4board[c4rowcount][c4colplace] = c4piece;
                c4gameboard();
                cout << "Turn " << c4turn << " over" << endl;
                c4turn = c4turn + 1;
                break;
            }
        }
        //End Turn if column is acceptable for move
        if ((c4turn % 2) == 1) {
            break;
        }
        //Ask for another column if column is not acceptable for move
        c4repeat = 1;
        cout << "Choose another column" << endl;
    }
}

//Gameover Scenarios: Return 1 if game is over, Return 0 if game is still ongoing
int c4gameover() {
    //Vertical Win
    for (int c4colcount = 0; c4colcount <= 6; c4colcount++) {
        for (int c4rowcount = 5; c4rowcount > 2; c4rowcount--) {
            if (c4board[c4rowcount][c4colcount] == c4piece && c4board[c4rowcount - 1][c4colcount] == c4piece && c4board[c4rowcount - 2][c4colcount] == c4piece && c4board[c4rowcount - 3][c4colcount] == c4piece) {
                cout << c4player << " wins" << endl;
                return 1;
            }
        }
    }
    //Horizontal Win
    for (int c4rowcount = 5; c4rowcount >= 0; c4rowcount--) {
        for (int c4colcount = 0; c4colcount < 4; c4colcount++) {
            if (c4board[c4rowcount][c4colcount] == c4piece && c4board[c4rowcount][c4colcount + 1] == c4piece && c4board[c4rowcount][c4colcount + 2] == c4piece && c4board[c4rowcount][c4colcount + 3] == c4piece) {
                cout << c4player << " wins" << endl;
                return 1;
            }
        }
    }
    //Downward Diagonal Win
    for (int c4colcount = 0; c4colcount < 4; c4colcount++) {
        for (int c4rowcount = 0; c4rowcount < 3; c4rowcount++) {
            if (c4board[c4rowcount][c4colcount] == c4piece && c4board[c4rowcount + 1][c4colcount + 1] == c4piece && c4board[c4rowcount + 2][c4colcount + 2] == c4piece && c4board[c4rowcount + 3][c4colcount + 3] == c4piece) {
                cout << c4player << " wins" << endl;
                return 1;
            }
        }
    }
    //Upward Diagonal Win
    for (int c4colcount = 6; c4colcount > 2; c4colcount--) {
        for (int c4rowcount = 0; c4rowcount < 3; c4rowcount++) {
            if (c4board[c4rowcount][c4colcount] == c4piece && c4board[c4rowcount + 1][c4colcount - 1] == c4piece && c4board[c4rowcount + 2][c4colcount - 2] == c4piece && c4board[c4rowcount + 3][c4colcount - 3] == c4piece) {
                cout << c4player << " wins" << endl;
                return 1;
            }
        }
    }
    //Tie
    if (c4turn == 43) {
        cout << "Its a tie";
        return 1;
    }
    return 0;
}

int battleshipmain() {
    setBoard();//sets boards
    initializeGame();//sets ship coordinates
    while (1) {//cycles through turns until victory state
        playerTurn();//runs player's turn
        if (totalPlayerHits == 17) {//checks for max score (17)
            cout << "You win!" << endl;
            break;//end state
        }
        enemyTurn();
        if (totalEnemyHits == 17) {//checks for max score (17)
            cout << "You lose!" << endl;
            break;//end state
        }
    }
    return 0;
}


int c4main() {
    cout << "Welcome to Connect Four" << endl;
    cout << "Player 1 is X and Player 2 is O" << endl;
    //Create values
    c4gameval();
    //Create board
    c4gameboard();
    c4gameoverval = 0;
    while (c4gameoverval == 0) {
        c4p1turn();
        c4gameoverval = c4gameover();
        //The game ends and P1 wins if the function above returns 1
        if (c4gameoverval == 1) {
            break;
        }
        c4p2turn();
        c4gameoverval = c4gameover();
        //The game ends and P2 wins if the function above returns 1
        if (c4gameoverval == 1) {
            break;
        }
    }
    return 0;
}

int main() {
    cout << "Welcome to T-13 Arcade" << endl;
    cout << "Press 0 to leave arcade" << endl;
    cout << "Press 1 for Battleship" << endl;
    cout << "Press 2 for Connect Four" << endl;
    int arcadegame;
    cout << "Selection: ";
    //game selection
    cin >> arcadegame;
    //Check for appropriate values
    while (arcadegame != 0 && arcadegame != 1 && arcadegame != 2) {
        cout << "Please make an appropriate selection (1 to leave, 2 for battleship, 3 for connect four): ";
        cin >> arcadegame;
    }
    //Battleship or Connect Four selection with choices after game
    while (arcadegame == 1 || arcadegame == 2) {
        if (arcadegame == 1) {
            battleshipmain();
            cout << "Would you like to (0) leave the arcade (1) play battleship or (2) play connect four" << endl;
            cin >> arcadegame;
            while (arcadegame != 0 && arcadegame != 1 && arcadegame != 2) {
                cout << "Please make an appropriate selection (0 to leave, 1 for battleship, 2 for connect four): ";
                cin >> arcadegame;
            }
        }
        else if (arcadegame == 2) {
            c4main();
            c4turn = 1;
            cout << "Would you like to (0) leave the arcade (1) play battleship or (2) play connect four" << endl;
            cin >> arcadegame;
            while (arcadegame != 0 && arcadegame != 1 && arcadegame != 2) {
                cout << "Please make an appropriate selection (0 to leave, 1 for battleship, 2 for connect four): ";
                cin >> arcadegame;
            }
        }
        //end loop if user is done playing
        if (arcadegame == 0) {
            break;
        }
    }
    //Leave arcade and end program
    if (arcadegame == 0) {
        cout << "Thank you for visiting T-13 Arcade!";
        return 0;
    }
    return 0;
}