#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::endl;


/* 
    Vector of vectors as a 2d array for a tic tac toe board
 */

const char x = 'X', o = 'O', empty = '-';
int board[3][3];
char currentPlayer;

void clearBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = empty;
        }
    }
    currentPlayer = x;
}

void swapPlayer()
{
    if (currentPlayer == x)
    {
        currentPlayer = o;
    }
    else
    {
        currentPlayer = x;
    }
}

void putMark()          
{   
    bool goodInput = false;
    int i = 0, j = 0;
    cout << "Enter your move. Row first then column. " << endl;
    cin >> i >> j;

    while (!goodInput)
    {
        if (currentPlayer == x)
        {
            if ((i >= 0) && (i < 3) && (board[i][j] != 'O') && (board[i][j] != 'X'))
            {
                board[i][j] = currentPlayer;
                swapPlayer();
                goodInput = true;
            }
            else
            {
                cout << "bad input, try again. " << endl;
                cout << "Enter your move. Row first then column. " << endl;
                cin >> i >> j;
            }
        }
        else
        {
            if (i >= 0 && i < 3 && board[i][j] != 'X' && board[i][j] != 'O')
            {
                board[i][j] = currentPlayer;
                swapPlayer();
                goodInput = true;
            }
            else
            {
                cout << "bad input, try again. " << endl;
                cout << "Enter your move. Row first then column. " << endl;
                cin >> i >> j;
            }
        }
    }

}

void displayBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch(board[i][j])
            {
                case x: cout << 'X';
                break;

                case o: cout << 'O';
                break;

                case empty: cout << ' ';
                break;
            }
            if (j < 2)
                cout << "|";
        }
        if (i < 2)
            cout << "\n-+-+-\n";
    }
}

int main()
{
    clearBoard();
    displayBoard();

    for (int i = 0; i < 5; i++)
    {
        putMark();
        displayBoard();
    }

    return 0;
}