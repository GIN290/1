#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define EASY_COUNT 10
void InitBoard(char board[ROWS][COLS],int rows,int cols,char set);
void DisplayBoard(char board[ROWS][COLS],int row,int col);//[][]中还是ROWS是因为传过来的数组并没有改变只能不全部显示
void SetMine(char board[ROWS][COLS],int row,int col);
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);
int getminecount(char mine[ROWS][COLS], int x, int y);