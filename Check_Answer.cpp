// Function to check if a number is valid in the current position
bool check(vector<vector<int>>& board, int row, int col, int num) {
    // Check row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 sub-grid
    int subRow = (row / 3) * 3;
    int subCol = (col / 3) * 3;
    for (int i = subRow; i < subRow + 3; i++) {
        for (int j = subCol; j < subCol + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}
