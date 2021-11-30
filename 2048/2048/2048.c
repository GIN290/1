#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 4
#define COL 4
#define SCORE 2048
void menu()
{
	printf("****************************************\n");
	printf("************     2048     **************\n");
	printf("****  1. play   ****  0. exit   ********\n");
	printf("****************************************\n");
}
struct spot
{
	int row;
	int col;
};
int fine_null(int(*board)[COL],int* i,int* j)
{
	struct spot null[ROW*COL];
	int x,y,num=0,n;
	srand((unsigned int)time(NULL));
	for(x=0;x<ROW;x++)
	{
		for(y=0;y<COL;y++)
		{
			if(board[x][y] == 0)
			{				
				null[num].row = x;
				null[num].col = y;
				num++;
			}
		}
	}
	if(num == 0) return 0;
	n = rand()%num;//0——num-1
	*i = null[n].row;
	*j = null[n].col;
	return num;
}
int Setboard(int (*board)[COL])
{
	int i=-1,j;
	srand((unsigned int)time(NULL));
	fine_null(board,&i,&j);
	if(-1 == i) return 0;//没生成随机数
	board[i][j] = (rand()%2+1)*2;//2/4
	return 1;
}
void DispalyBoard(int (*board)[COL],int row,int col)
{
	int i,j;
	printf("   --     --     --     --    \n");
	for(i=0;i<row;i++)
	{
		printf("|");
		for(j=0;j<col;j++)
		{
			if(board[i][j] == 0)
				printf("      ");
			else
				printf(" %4d ",board[i][j]);
			printf("|");
		}
		printf("\n");
		printf("   --     --     --     --    \n");
	}
}
int point(int n)
{
	if(n==1)
		return 0;
	else
		return(1+point(n/2));
}
void up(int(*board)[COL],int* mark)
{
	int i,j,h,k,l;	
	for (j = 0; j < COL; j++) 
	{	//j代表列
		for (i = 0; i < ROW-1; i++) 
		{
			if (board[i][j] != 0) 
			{
				//如果这个格子不等于零就检测能否合并
				for (h = i+1; h < ROW; h++) 
				{
					if (board[h][j] != 0) 
					{
						if (board[h][j] == board[i][j]) 
						{
							//相等的话就合并，然后并到hj的格子里
							(*mark)+=point(board[i][j]);
							board[i][j] *= 2;
							board[h][j] = 0;
							//之后要忽略掉已经合并的格子
							i = h; //这里要特别注意一下，不知道是不是到了外层循环结束了之后自动给他减一
							break;
						}
						else 
						{
							break;
						}
					}
				}
			}
		}
	}
		//这里要进行紧凑操作，逐行扫描
	for (j = 0; j < COL; j++) 
	{
		for (k = 0; k < ROW-1; k++)
		{
			//找到一个为0的格子之后把不为0的最近的格子值赋值上来，然后被赋值的格子变0
			//一直检查完为止，最后一行是不用检查的，因为最后一行为0也没有格子可以上移
			if (board[k][j] == 0) 
			{
				//找最近的不为0的格子
				for (l = k + 1; l < ROW; l++) 
				{
					if (board[l][j] != 0) 
					{
						board[k][j] = board[l][j];
						board[l][j] = 0;
						break;
					}
				}
			}
		}
	}
}
void down(int(*board)[COL],int* mark)
{
	int i,j,k,h;	
	for (j = 0; j < COL; j++) 
	{	//j代表列
		for (i = ROW-1; i > 0; i--) 
		{
			if (board[i][j] != 0) 
			{
				//如果这个格子不等于零就检测能否合并
				for (h = i-1; h >= 0; h--) 
				{
					if (board[h][j] != 0) 
					{
						if (board[h][j] == board[i][j]) 
						{
							//相等的话就合并，然后并到hj的格子里
							(*mark)+=point(board[i][j]);
							board[i][j] *= 2;
							board[h][j] = 0;
							//之后要忽略掉已经合并的格子
							i = h; //这里要特别注意一下，不知道是不是到了外层循环结束了之后自动给他减一
							break;
						}
						else 
						{
							break;
						}
					}
				}
			}
		}
	}
	for (j = 0; j < 4; j++) 
	{
		for (i = ROW-1; i > 0; i--) 
		{
			if (board[i][j] == 0) 
			{
				for ( k = i - 1; k >= 0; k--) 
				{
					if (board[k][j] != 0) 
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						break;
					}
				}
			}
		}
	}

}
void left(int(*board)[COL],int* mark)
{
	//左移操作
	int i,j,k;
	for (i = 0; i < 4; i++) 
	{
		for (j = 3; j > 0; j--) 
		{
			if (board[i][j] != 0) 
			{
				for (k = j - 1; k >= 0; k--) 
				{
					if (board[i][k] != 0) 
					{
						//要找第一个不等于0的格子
						if (board[i][k] == board[i][j]) 
						{
							(*mark)+=point(board[i][j]);
							board[i][k] *= 2;
							board[i][j] = 0;
							j = k;
							break;
						}
						else 
						{
							break;
						}
					}
				}
			}
		}
	}
	//进行紧凑处理
	for (i = 0; i < 4; i++) 
	{
		for (j = 0; j < 3; j++) 
		{
			if (board[i][j] == 0) 
			{
				for (k = j + 1; k < 4; k++) 
				{
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}
void right(int(*board)[COL],int* mark)
{
		//右移操作
	int i,j,k;
	for (i = 0; i < 4; i++) 
	{
		for (j = 0; j < 3; j++) 
		{
			if (board[i][j] != 0) 
			{
				for (k = j + 1; k < 4; k++) 
				{
					if (board[i][k] != 0) 
					{
						if (board[i][k] == board[i][j]) 
						{
							(*mark)+=point(board[i][j]);
							board[i][k] *= 2;
							board[i][j] = 0;
							j = k;
							break;
						}
						else 
						{
							break;
						}
					}
				}
			}
		}
	}
	//进行紧凑处理
	for (i = 0; i < 4; i++) 
	{
		for (j = 3; j > 0; j--) 
		{
			if (board[i][j] == 0) 
			{
				for (k = j - 1; k >= 0; k--) 
				{
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}
int is_same(int(*board)[COL])
{
	int i,j;
	int x,y;
	int bigboard[ROW+2][COL+2]={0};
	for(x=1,i=0;i<ROW;i++,x++)
		for(y=1,j=0;j<COL;j++,y++)
			bigboard[x][y]=board[i][j];
	for(i=1;i<=ROW;i++)
	{
		for(j=1;j<=COL;j++)
		{
			if(bigboard[i][j] == bigboard[i-1][j] || bigboard[i][j] == bigboard[i][j-1]
			||bigboard[i][j] == bigboard[i+1][j] || bigboard[i][j] == bigboard[i][j+1])
				return 0;
		}
	}
	return 1;//任一个元素和周围四个都不相同
}
int is_win(int(*board)[COL])
{
	int i,j;
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(board[i][j] == SCORE)
				return 1;//合成了2048赢了
		}
	}
	if(fine_null(board,&i,&j) == 0)
	{
		if(is_same(board) == 1)
		{
			return 0;//输了
		}
	}
	return 2;//不输也不赢
}
void move(int(*board)[COL],int* mark)
{
	char ch;
	scanf("%c",&ch);
	getchar();
	switch(ch)
	{
	case 'w':
		up(board,mark);
		
		
		break;
	case 's':
		down(board,mark);
		
		break;
	case 'a':
		left(board,mark);
		
		break;
	case 'd':
		right(board,mark);
		
		break;
	default:
		printf("输入错误!\n");
		break;
	}
}
void game()
{
	int board[ROW][COL] = {0};//初始化数组
	int mark = 0;
	//DispalyBoard(board,ROW,COL);//打印数组
	Setboard(board);//生成一个2或者4的随机数
	DispalyBoard(board,ROW,COL);//打印数组
	while(1)
	{
		move(board,&mark);
		printf("当前得分为:>%d\n",mark);
		Setboard(board);
		DispalyBoard(board,ROW,COL);
		if(is_win(board) == 1)
		{
			printf("恭喜你赢了！！！\n");
			break;
		}
		else if(is_win(board) == 0)
		{
			printf("抱歉你输了！\n");
			break;
		}

	}
}
int main()
{
	int input;
	do
	{
		menu();
		printf("请输入:");
		scanf("%d",&input);
		getchar();
		switch(input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出\n");
			break;
		default:
			printf("输入错误，请重新输入！\n");
			break;
		}
	}while(input);
	return 0;
}