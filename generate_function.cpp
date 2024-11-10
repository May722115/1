void generate_game(int level) {
    // Generate a complete Sudoku board
    vector<vector<int>> completeBoard = generateCompleteBoard();

    // Hollow out cells based on the difficulty level
    hollowOutCells(completeBoard, level);

    // Print the Sudoku board
    printBoard(completeBoard);
}
