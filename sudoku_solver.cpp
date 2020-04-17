#include <iostream>
using namespace std;

#define N 9

/* Searches the grid to find an entry that is
still unassigned. If found, the reference
parameters row, col will be set the location
that is unassigned, and true is returned.
If no unassigned entries remain, false is returned. */
bool FindEmpty(int grid[N][N],int &row, int &col){
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}
/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
bool UsedInRow(int grid[N][N], int row, int num){
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num){
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow,int boxStartCol, int num){
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] == num)
                return true;
    return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool isValid(int grid[N][N], int row,int col, int num){
    /* Check if 'num' is not already placed in
    current row, current column and current 3x3 box */
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row % 3 ,
                      col - col % 3, num) &&
            grid[row][col] == 0;
}

bool SolveSudoku(int grid[N][N]){
    int row, col;

    // If there is no blank space left, we solved it
    if (!FindEmpty(grid, row, col))
    return true; // success!

    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++){
        // if looks promising
        if (isValid(grid, row, col, num)){
            // make tentative assignment
            grid[row][col] = num;

            // return, if success, yay!
            if (SolveSudoku(grid))
                return true;

            // failure, unmake & try again
            grid[row][col] = 0;
        }
    }
    return false; // this triggers backtracking
}




/* A utility function to print grid */
void printGrid(int grid[N][N]){
    for (int row = 0; row < N; row++)
    {
    for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

int main(){
    //TODO: add user input
    int grid[N][N] = {{8, 0, 0, 0, 1, 0, 0, 0, 0},
                      {8, 3, 0, 0, 0, 0, 2, 0, 0},
                      {0, 0, 0, 9, 5, 0, 7, 0, 4},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    if (SolveSudoku(grid) == true)
        printGrid(grid);
    else
        cout << "Solution does not exist!" << endl;

    return 0;
}
