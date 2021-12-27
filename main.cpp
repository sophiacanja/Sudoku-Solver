#include <iostream>
#include <vector> 
#include <string>

using namespace std; 

void printSudokuBoard(int arr[9][9])                       //prints out the 2D array declared in main
{
    cout << "--------------------------" << endl;

    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            cout << arr[row][col] << " "; 
        }
        cout << endl;
    }

    cout << "--------------------------" << endl;
}


bool canPlace(int arr[9][9], int row, int col, int n)       //this returns true if a given number is not found within a specific row, column, and grid 
{
    
    if(arr[row][col]!= 0)                                   //checks if current cell is not empty
        return false; 
    bool status = true; 
    int gridx = (col / 3) * 3;                              //calculates start of 3x3 grid
    int gridy = (row / 3) * 3;
    for(int i = 0; i < 9; i++){                             //checks to see if a number is repeated within the row or the column 
        if(arr[row][i] == n || arr[i][col] == n){  
            status = false;
            break;
        }
        if(arr[gridy + i / 3][gridx + i % 3] == n){         //checks if number is repeated within each grid
            status = false; 
            break;
        }
    }
    return status;
    
}

vector<int> findPlaceables(int arr[9][9], int r, int c)     //creates a vector that stores all possible solutions for one cell
{
    vector<int> cps = {};
    for( int i = 1; i <=9; i++){
        if(canPlace(arr, r, c, i))                          //checks if number i can be placed in a cell
        cps.push_back(i);                                   //stores number into vector
    }
    return cps;
}

void copyArr(int arr[9][9], int duplicate[9][9])            //creates a duplicate of the 9x9 array
{
    for(int x = 0; x < 9; x++)
        for( int y = 0; y < 9; y++)
            duplicate[x][y] = arr[x][y];
}

void nextEmpty(int arr[9][9], int row, int col, int &nextRow, int &nextCol)     //finds next available empty cell 
{
    int index = 9 * 9; 
    for(int i = row * 9 + col + 1; i < 9 * 9; i++){
        if(arr[i / 9][i % 9]==0){
            index = i;
            break;
        }
    }
    nextRow = index / 9;
    nextCol = index % 9;
}
bool solveSudoku(int arr[9][9], int row, int col)           //uses recursion to solve sudoku puzzle 
{
    if(row > 8)                                             //checks if all rows are filled and puzzle is completed
        return true;

    if(arr[row][col] != 0){                                 //checks if current cell is filled      
        int nextCol, nextRow; 
        nextEmpty(arr, row, col, nextRow, nextCol);         //calls method to find next available cell 
        return solveSudoku(arr, nextRow, nextCol);          //uses recursion to evaluate the next available cell
    }

    vector<int> placeables = findPlaceables(arr, row, col);
    
    if (placeables.size() == 0)                             //checks if row is full 
        return false;

    bool status = false; 

    for(int i = 0; i < placeables.size(); i++){             //loops through all placeables 
        int n = placeables[i];                              //sets first value in vector as n
        int arrCpy[9][9];
        copyArr(arr, arrCpy);                               //copies array to test out the different variations
        arrCpy[row][col] = n;                               //sets n as a possible solution to a specific cell
        int nextCol, nextRow;
        nextEmpty(arrCpy, row, col, nextRow, nextCol);      //finds the next empty cell
        if(solveSudoku(arrCpy, nextRow, nextCol))           //uses recursion to evaluate the right values for all 0-8 rows
        {
            copyArr(arrCpy, arr);                           //when all the rows are filled, it sets the copied array to the original array
            status = true;
            break;
        }
    }
    
    return status;
}


int main() 
{
    
     int board[9][9] = {
        {5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
    };


    printSudokuBoard(board); 
    solveSudoku(board, 0, 0);
    printSudokuBoard(board);

    return 0;
}


