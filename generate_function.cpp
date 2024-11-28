#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <cmath>

int resultNum = 0;
int answer[9][9] = {0};

bool checkvalid(int numberboard[][9], int number, int row, int col) {
    //check for columns
    for (int i = 0; i < 9; i++) {
        if (numberboard[row][i] == number) {
            return false;
        }
    }

    //check for rows
    for (int i = 0; i < 9; i++) {
        if (numberboard[i][col] == number) {
            return false;
        }
    }

    //check for 3x3 matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (numberboard[(row / 3 * 3) + i][(col / 3 * 3) + j] == number) {
                return false;
            }
        }
    }
    return true;
}

//generate full number board
bool generateboard(int numberboard[][9], int row, int col) {
    //check whether all rows are filled
    if (row == 8 && col == 9) {
        return true;
    }

    //check whether all colunms in the row are filled
    if (col == 9) {
        row++;
        col = 0;
    }

    //check whether the position is filled
    if (numberboard[row][col] != 0) {
        return generateboard(numberboard, row, col + 1);
    }

    //fill the number in a row
    for (int i = 1; i <= 9; i++) {
        //randomly generateing a number
        int number = rand() % 9 + 1;
        //check if the number if valid and fill it in the position
        if (checkvalid(numberboard, number, row, col)) {
            numberboard[row][col] = number;
            //check whether next valid number exists, repeat previous step if not
            if (generateboard(numberboard, row, col + 1)) {
                return true;
            }
            numberboard[row][col] = 0;
        }
    }
    return false;
}

void removeElements(int sudoku[][9], int count) {
    // 实现移除元素的逻辑
    std::random_device rd;
    std::mt19937 gen(rd());
    int removedCount = 0;

    while (removedCount < count) {
        int row = gen() % 9;
        int col = gen() % 9;

        if (sudoku[row][col] != 0) {
            int temp = sudoku[row][col];
            sudoku[row][col] = 0;

            // 检查数独是否仍然有唯一解
            int tempSudoku[9][9];
            std::memcpy(tempSudoku, sudoku, sizeof(sudoku));
            resultNum = 0;
            solve(tempSudoku); // 假设 solve 方法用于解决数独并更新 resultNum

            // 如果有多个解，则恢复该数字
            if (resultNum > 1) {
                sudoku[row][col] = temp;
            } else {
                removedCount++;
            }
        }
    }
}

void solve(int data[][9]) {
    // 实现解决数独的逻辑
    if (resultNum > 1) {
        return;
    }

    analyse(data);
    int result = check(data);

    if (result == 1) {
        int* position = findLessCandidatesPos(data);
        int pv = data[position[0]][position[1]];
        int pvcount = __builtin_popcount(pv);

        for (int i = 0; i < pvcount; i++) {
            int testV = 1 << (31 - __builtin_clz(pv));
            pv ^= testV;
            int copy[9][9];
            memcpy(copy, data, sizeof(data));
            copy[position[0]][position[1]] = testV;

            if (i > 0) {
                return;
            }

            solve(copy);
        }
    } else if (result == 0) {
        resultNum++;
        std::cout << "------------------------------------Solution " << resultNum << "---------------------" << std::endl;
        answer = data;
        binaryToInt(answer);
        printByRow(answer);
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
    } else if (emptyCount > 0 && Integer.bitCount(data[findLessCandidatesPos(data)[0]][findLessCandidatesPos(data)[1]]) == 1) {
        return 1;
    } else {
        return -1;
    }
}

int* findLessCandidatesPos(int data[][9]) {
    int[] position = new int[2];
    int minCandidates = 10;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] == 0) {
                int candidates = Integer.bitCount(data[i][j]);
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

void printByRow(int data[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] == 0) {
                std::cout << ". ";
            } else {
                std::cout << data[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void binaryToInt(int data[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i][j] != 0) {
                data[i][j] = (int) (log2(data[i][j]) + 1);
            }
        }
    }
}

int main() {
    int sudoku[9][9] = {0};
    int level = 1;

    generateboard(sudoku, 0, 0);
    answer = sudoku;

    if (level == 1) {
        removeElements(sudoku, 20);
    } else if (level == 2) {
        removeElements(sudoku, 35);
    }

    solve(sudoku);

    if (resultNum > 1) {
        // 重新生成
        generateboard(sudoku, 0, 0);
        answer = sudoku;
    }

    // 返回最终结果
    return 0;
} 
