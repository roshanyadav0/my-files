#include <iostream>
using namespace std;

const int N = 9;

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num || grid[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(int grid[N][N]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    int grid[N][N] = {0};  // Initialize all cells to 0

    cout << "Enter the number of cells you want to fill: ";
    int numCells;
    cin >> numCells;

    cout << "Enter cell positions (row col) and values:\n";
    cout << "Example: To fill row 1, column 2 with value 5, enter: 1 2 5\n";
    
    for (int i = 0; i < numCells; ++i) {
        int row, col, value;
        cin >> row >> col >> value;
        
        if (row >= 0 && row < N && col >= 0 && col < N) {
            grid[row][col] = value;
        } else {
            cout << "Invalid cell position! Skipping...\n";
        }
    }

    if (solveSudoku(grid)) {
        cout << "Sudoku puzzle solved:\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "No solution exists for the given Sudoku puzzle.\n";
    }
    
    return 0;
}

