


bool canPlace(int arr[9][9], int row, int col, int n)       //this returns true if a given number is not found within a specific row, column, and grid 
{
    cout << "SOLVED SUDOKU PUZZLE" << endl;
    if(arr[row][col]!= 0)                                   //checks if current cell is not empty
        return false; 
    bool status = true; 
    int gridx = (col / 3) * 3;                              //calculates start of 3x3 grid
    int gridy = (row / 3) * 3;