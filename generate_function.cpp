 public static int[][] generateFunction(int level) {
    int[][] sudoku = new int[9][9];
    int[][] answer = new int[9][9];
    int resultNum = 0;
    long startTime = System.nanoTime();

    // 生成一个完整的数独
    generateSudoku(sudoku);
    answer = copyArray(sudoku);

    // 根据难度级别挖空
    if (level == 1) {
        removeElements(sudoku, 20);
    } else if (level == 2) {
        removeElements(sudoku, 40);
    }

    // 解决数独
    solve(sudoku);

    // 如果找到两个解,则重新生成
    if (resultNum > 1) {
        return generateFunction(level);
    }

    // 返回最终结果
    return answer;
}

private static void solve(int[][] data) {
    if (resultNum > 1) {
        return;
    }

    analyse(data);
    int result = check(data);

    if (result == 1) {
        int[] position = findLessCandidatesPos(data);
        int pv = data[position[0]][position[1]];
        int pvcount = Integer.bitCount(pv);

        for (int i = 0; i < pvcount; i++) {
            int testV = 1 << ((int) (Math.log(Integer.highestOneBit(pv)) / Math.log(2)));
            pv ^= testV;
            int[][] copy = copyArray(data);
            copy[position[0]][position[1]] = testV;

            if (i > 0) {
                return;
            }

            solve(copy);
        }
    } else if (result == 0) {
        resultNum++;
        System.out.println("------------------------------------Solution " + (resultNum) + "---------------------"
                + (System.nanoTime() - startTime) / 1000000.0 + "ms---");
        answer = data;
        binaryToInt(answer);
        printByRow(answer);
    }
}

private static void analyse(int[][] data) {
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
            }
        }
    }
}

private static int check(int[][] data) {
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

private static int[] findLessCandidatesPos(int[][] data) {
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
