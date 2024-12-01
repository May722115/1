#ifndef GENERATE_HARD_H
#define GENERATE_HARD_H

bool checkvalid(int numberboard[][9], int number, int row, int col);
bool generateboard(int numberboard[][9], int row, int col);
bool checkremain(int numberboard[][9], int row, int col);
void removehard(int numberboard[][9]);
void formgameboard(vector<string> &board);
void formatting(vector<string> &board, int numberboard[][9]);
void storeanswer(int numberboard[][9]);

#endif
