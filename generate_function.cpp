#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <cmath>
#include <cstring>
#include <ctime>
#include <bitset>
#include "generate_function.h"

int resultNum = 0;
int answer[9][9] = {0};
int tempSudoku[9][9] = {0};
int copy[9][9] = {0};

bool checkvalid(int numberboard[][9], int number, int row, int col);
bool generateboard(int numberboard[][9], int row, int col);
bool hasSingleSolution(int sudoku[][9], int level);
void removeElements(int sudoku[][9], int sudoku_copy[][9], int count, int level);
void solve(int data[][9], int sudoku_copy[][9], int level);
void analyse(int data[][9]);
int check(int data[][9]);
int* findLessCandidatesPos(int data[][9]);
void printByRow(int data[][9], int sudoku_copy[][9]);
void binaryToInt(int data[][9]);

int main() {
    srand(time(0));
    int sudoku[9][9] = {0};
    int sudoku_copy[9][9] = {0};
    int level;

    // Prompt the user to input the difficulty level
    std::cout << "Enter the difficulty level (1 for 20 filled spaces, 2 for 35 filled spaces): ";
    std::cin >> level;

    // Generate a single Sudoku puzzle with the desired number of filled spaces
    generateboard(sudoku, 0, 0);
    std::memcpy(sudoku_copy, sudoku, sizeof(sudoku));

    if (level == 1) {
        removeElements(sudoku, sudoku_copy, 20, 1);
    } else if (level == 2) {
        removeElements(sudoku, sudoku_copy, 35, 2);
    }

    return 0;
}

bool checkvalid(int numberboard[][9], int number, int row, int col) {
    // check for columns
    for (int i = 0; i < 9; i++) {
        if (numberboard[row][i] == number) {
            return false;
        }
    }

    // check for rows
    for (int i = 0; i < 9; i++) {
        if (numberboard[i][col] == number) {
            return false;
        }
    }

    // check for 3x3 matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (numberboard[(row / 3 * 3) + i][(col / 3 * 3) + j] == number) {
                return false;
            }
        }
    }

    return true;
}

// generate full number board
bool generateboard(int numberboard[][9], int row, int col) {
    // check whether all rows are filled
    if (row == 8 && col == 9) {
        return true;
    }

    // check whether all columns in the row are filled
    if (col == 9) {
        row++;
        col = 0;
    }

    // check whether the position is filled
    if (numberboard[row][col] != 0) {
        return generateboard(numberboard, row, col + 1);
    }

    // fill the number in a row
    for (int i = 1; i <= 9; i++) {
        // randomly generating a number
        int number = rand() % 9 + 1;

        // check if the number is valid and fill it in the position
        if (checkvalid(numberboard, number, row, col)) {
            numberboard[row][col] = number;

            // check whether next valid number exists, repeat previous step if not
            if (generateboard(numberboard, row, col + 1)) {
                return true;
            }

            numberboard[row][col] = 0;
        }
    }

    return false;
}

bool hasSingleSolution(int sudoku[][9], int level) {
    int tempSudoku[9][9];
    std::memcpy(tempSudoku, sudoku, sizeof(tempSudoku));
    int tempSudoku_copy[9][9];
    std::memcpy(tempSudoku_copy, sudoku, sizeof(tempSudoku_copy));

    resultNum = 0;
    solve(tempSudoku, tempSudoku_copy, level);
    return resultNum == 1;
}

void removeElements(int sudoku[][9], int sudoku_copy[][9], int count, int level) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int removedCount = 0;

    while (removedCount < count) {
        int row = gen() % 9;
        int col = gen() % 9;

        if (sudoku[row][col] != 0) {
            sudoku_copy[row][col] = sudoku[row][col];
            sudoku[row][col] = 0;

            if (hasSingleSolution(sudoku, level)) {
                removedCount++;
            } else {
                sudoku[row][col] = sudoku_copy[row][col];
            }
        }
    }
}

void solve(int data[][9], int sudoku_copy[][9], int level) {
    analyse(data);
    int result = check(data);

    if (result == 0) {
        resultNum++;
        int emptyCount = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (sudoku_copy[i][j] == 0) {
                    emptyCount++;
                }
                answer[i][j] = data[i][j];
            }
        }
        if (level == 1 && emptyCount == 20) {
            binaryToInt(answer);
            printByRow(answer, sudoku_copy);
        } else if (level == 2 && emptyCount == 35) {
            binaryToInt(answer);
            printByRow(answer, sudoku_copy);
        }
    } else if (result == 1) {
        int* position = findLessCandidatesPos(data);
        int pv = data[position[0]][position[1]];
        int pvcount = __builtin_popcount(pv);

        for (int i = 0; i < pvcount; i++) {
            int testV = 1 << (31 - __builtin_clz(pv));
            pv ^= testV;
            int copy[9][9];
            std::memcpy(copy, data, sizeof(data[0]) * 9);
            copy[position[0]][position[1]] = testV;
            solve(copy, sudoku_copy, level);
        }
    }
}
void analyse(int data[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] == 0) {
                int rowMask = 0, colMask = 0, subGridMask = 0;

                for (int k = 0; k < 9; k++) {
                    if (data[i][k] != 0) {
                        rowMask |= (1 << (data[i][k] - 1));
                    }
                    if (data[k][j] != 0) {
                        colMask |= (1 << (data[k][j] - 1));
                    }
                    int subGridRow = (i / 3) * 3 + k / 3;
                    int subGridCol = (j / 3) * 3 + k % 3;
                    if (data[subGridRow][subGridCol] != 0) {
                        subGridMask |= (1 << (data[subGridRow][subGridCol] - 1));
                    }
                }

                data[i][j] = ~(rowMask | colMask | subGridMask) & 0x1FF;
            } else {
                data[i][j] = 1 << (data[i][j] - 1);
            }
        }
    }
}

int check(int data[][9]) {
    int emptyCount = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] == 0) {
                emptyCount++;
            }
        }
    }

    if (emptyCount == 0) {
        return 0;
    } else if (emptyCount > 0 && std::bitset<9>(data[findLessCandidatesPos(data)[0]][findLessCandidatesPos(data)[1]]).count() == 1) {
        return 1;
    } else {
        return -1;
    }
}

int* findLessCandidatesPos(int data[][9]) {
    static int position[2] = {0};
    int minCandidates = 10;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] == 0) {
                int candidates = __builtin_popcount(data[i][j]);
                if (candidates < minCandidates) {
                    minCandidates = candidates;
                    position[0] = i;
                    position[1] = j;
                }
            }
        }
    }

    return position;
}

void printByRow(int data[][9], int sudoku_copy[][9]) {
    std::cout << "------------ Question -----------" << std::endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku_copy[i][j] == 0) {
                std::cout << ". ";
            } else {
                std::cout << sudoku_copy[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void binaryToInt(int data[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] != 0) {
                data[i][j] = (int)(log2(data[i][j]) + 1);
            }
        }
    }
}
