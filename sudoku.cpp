#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int SIZE = 9;

int board[SIZE][SIZE];

vector<set<int>> possibleValues(SIZE, set<int>());

bool isValid(int x, int y, int num) {
    for (int i = 0; i < SIZE; ++i) {
        if (board[x][i] == num || board[i][y] == num || board[x / 3 * 3 + i / 3][y / 3 * 3 + i % 3] == num) {
            return false;
        }
    }
    return true;
}

bool isValidSudokuBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                int num = board[i][j];
                board[i][j] = 0; // Temporarily set the cell to 0 to check validity
                if (!isValid(i, j, num)) {
                    return false;
                }
                board[i][j] = num; // Restore the cell's value
            }
        }
    }
    return true;
}

void initializePossibleValues() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                for (int num = 1; num <= SIZE; ++num) {
                    if (isValid(i, j, num)) {
                        possibleValues[i].insert(num);
                    }
                }
            }
        }
    }
}

void displayBoard() {
    cout << "Sudoku Board:" << endl;
    cout << " -----------------------" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "| ";
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                cout << board[i][j] << " ";
            } else {
                cout << ". ";
            }
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0) cout << " -----------------------" << endl;
    }
}

bool solveSudoku(int row, int col) {
    if (row == SIZE) return true;

    int nextRow = col == SIZE - 1 ? row + 1 : row;
    int nextCol = (col + 1) % SIZE;

    if (board[row][col] != 0) {
        return solveSudoku(nextRow, nextCol);
    }

    for (int num : possibleValues[row]) {
        if (isValid(row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(nextRow, nextCol)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    cout << "Enter the Sudoku board (use 0 for empty cells):" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> board[i][j];
        }
    }

    if (!isValidSudokuBoard()) {
        cout << "Invalid Sudoku board! Please check the initial board configuration." << endl;
        return 1;
    }

    initializePossibleValues();
    displayBoard();

    if (solveSudoku(0, 0)) {
        cout << "\nSudoku solved successfully!" << endl;
        displayBoard();
    } else {
        cout << "\nNo solution found for the given Sudoku board!" << endl;
    }

    return 0;
}