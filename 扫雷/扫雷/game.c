#include"game.h"
void InitBoard(char board[ROWS][COLS],int rows,int cols,char set)
{
	int i,j;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
			board[i][j] = set;
	}
}
void DisplayBoard(char board[ROWS][COLS],int row,int col)
{
	int i,j;
	//��ӡ�к�
	for(i=0;i<=row;i++)
	{
		printf("%d ",i);
	}
	printf("\n");
	for(i=1;i<=row;i++)
	{
		//��ӡ�к�
		printf("%d ",i);
		for(j=1;j<=col;j++)
		printf("%c ",board[i][j]);
		printf("\n");
	}
}
void SetMine(char board[ROWS][COLS],int row,int col)
{
	int count = EASY_COUNT;
	while(count)
	{
		int x = rand()%row+1;//1����9
		int y = rand()%col+1;
		if(board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
int getminecount(char mine[ROWS][COLS], int x, int y)//������
{
	return mine[x - 1][y] +//�ַ������ֲ�ͬ���
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1]-8*'0';
}
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
	int x=0,y=0;
	int win=0;
	while(win<row*col-EASY_COUNT)
	{
		printf("�������Ų��׵�����:>");
		scanf("%d%d",&x,&y);
		if(x>=1&&x<=row && y>=1&&y<=col)
		{
			//����Ϸ�
			//1.����
			if(mine[x][y] == '1')
			{
				printf("���ź����㱻ը���ˣ�\n");
				DisplayBoard(mine,row,col);
				break;
			}
			//2.û����
			else
			{
				int count=getminecount(mine,x,y);	
				show[x][y] = count + '0';
				DisplayBoard(show,row,col);
				win++;
				
			}
		}
		else
		{
			printf("�Ƿ����꣬���������룡\n");
		}
	}
	if(win == row*col-EASY_COUNT)
	{
		printf("��ϲ�㣬���׳ɹ�\n");
		DisplayBoard(mine,row,col);
	}
}