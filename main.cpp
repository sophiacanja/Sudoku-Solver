#include <iostream>
#include <vector> 
#include <string>

using namespace std; 

void printSudokuBoard(int arr[9][9])                //prints out the 2D array declared in main
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
        if(canPlace(arr, r, c, i))
        cps.push_back(i);
    }
    return cps;
}

void copyArr(int arr[9][9], int duplicate[9][9])      //creates a duplicate of the 9x9 array
{
    for(int y = 0; y < 9; y++)
        for( int x = 0; x < 9; x++)
            duplicate[y][x] = arr[y][x];
}

void nextEmpty(int arr[9][9], int row, int col, int &nextRow, int &nextCol)
{
    int index = 9*9; 
    for(int i = row * 9 + col + 1; i < 9*9; i++){
        if(arr[i / 9][i % 9]==0){
            index = i;
            break;
        }
    }
    nextRow = index / 9;
    nextCol = index % 9;
}
bool solveSudoku(int arr[9][9], int row, int col) 
{
    if(row > 8)                                 //checks if all rows are filled
        return true;

    if(arr[row][col] != 0){                     
        int nextCol, nextRow; 
        nextEmpty(arr, row, col, nextRow, nextCol);
        return solveSudoku(arr, nextRow, nextCol);
    }

    vector<int> placeables = findPlaceables(arr, row, col);
    
    if (placeables.size() == 0)                 //checks if row is full 
        return false;

    bool status = false; 

    for(int i = 0; i < placeables.size(); i++){
        int n = placeables[i]; 
        int arrCpy[9][9];
        copyArr(arr, arrCpy);
        arrCpy[row][col] = n; 
        int nextCol, nextRow;
        nextEmpty(arrCpy, row, col, nextRow, nextCol);
        if(solveSudoku(arrCpy, nextRow, nextCol))
        {
            copyArr(arrCpy, arr);
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
    solveSudoku(board, 0,0);
    printSudokuBoard(board);

    return 0;
}


