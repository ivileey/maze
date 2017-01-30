#include<stack>
#include<iostream>
#include<time.h>
#define random(x)(rand()%x)
using namespace std;
struct point
{
	int x;
	int y;
};
void ProduceRoute(int row, int column, int x, int y, int x1, int y1);
void CreatMaze(int row, int column);
void CreatMaze1(int row, int column);
/*int Maze1[6][16] =
{ 
0,1,0,0,0,1,1,1,0,1,0,1,1,0,1,0,
0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,1,
1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,1,
0,0,0,1,1,1,0,0,0,0,1,0,1,0,1,0,
0,1,1,0,0,0,0,0,1,0,1,0,1,0,1,1,
0,0,0,0,1,1,0,0,1,0,0,0,1,0,1,1
};(1,1)(6,14)*/
int **Maze; //初始化迷宫
stack<point> st;
point move1[4] = { {-1,0},{1,0},{0,-1},{0,1} };//上下左右
void ProduceMaze(int &row,int &column,int &x,int &y,int &x1,int &y1)
{
	srand((unsigned)time(0));
	row = 10;//random(10)+1;
	column = 10;//random(10)+1;
	x = random(row) + 1;
	if (x == 1 || x == row)
		y = random(row) + 1;
	else
	{
		int i = random(2);
		if (i == 0)
			y = 1;
		else y = column;
	}                                                                                                                      
	                                                                                                                                                                               
	x1 = random(row) + 1;
	if (x1 == 1 || x1 == row)
		y1 = random(row) + 1;
	else
	{
		int i = random(2);
		if (i == 0)
			y1 = 1;
		else y1 = column;
	}
	Maze = new int*[row + 2];
 	for (int i = 0; i < row + 2; i++)
		Maze[i] = new int[column + 2];
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++)
		{
				Maze[i][j] = 1;
		}
	CreatMaze(row, column);
	ProduceRoute(row, column, x, y, x1, y1);
	CreatMaze1(row, column);
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++)
		{
			if (Maze[i][j] != 0)
				Maze[i][j] = random(2);
		}				
	Maze[x][y] = 0;
	Maze[x1][y1] = 0;
}
void ProduceRoute(int row, int column, int x, int y, int x1, int y1)
{
	srand((unsigned)time(0));
	stack<point> q;
	point temp;
	temp.x = x;
	temp.y = y;
	q.push(temp);
	point move2[4];
	for (int j = 0; j < 4; j++)
	{
		move2[j] = move1[j];
	}
	while (!q.empty())
	{
		temp = q.top();
		if (Maze[temp.x - 1][temp.y] == 0 && Maze[temp.x + 1][temp.y] == 0 && Maze[temp.x][temp.y - 1] == 0 && Maze[temp.x][temp.y + 1] == 0)
		{
			q.pop();
		}
		for (int j = 0; j < 4; j++)
		{
			int i = random(4);
			point k = move2[i];
			move2[i] = move2[j];
			move2[j] = k;
		}
		for (int j = 0; j < 4; j++)
		{
			if (temp.x + move2[j].x == x1&&temp.y + move2[j].y == y1)
			{
				Maze[temp.x][temp.y] = 0;
				goto result;
			}
			if (Maze[temp.x + move2[j].x][temp.y + move2[j].y] != 0)
			{
				Maze[temp.x][temp.y] = 0;
				temp.x += move2[j].x;
				temp.y += move2[j].y;
				q.push(temp);
			}
		}
	}
result:cout << "已成功生成路径" << endl;
}
void CreatMaze(int row, int column)
{
	int i,j;
	for (i = 0; i < row + 2; i++)
		Maze[i][0] = Maze[i][column + 1] = 0;
	for (i = 0; i < column + 2; i++)
		Maze[0][i] = Maze[row + 1][i] = 0;
	/*for (j = 1; j <= row; j++)
		for (i = 1; i <= column; i++)
			Maze[j][i] = Maze1[j - 1][i - 1];
		//	cin >> Maze[i][j];*/
}
void CreatMaze1(int row, int column)
{
	int i, j;
	for (i = 0; i < row + 2; i++)
		Maze[i][0] = Maze[i][column + 1] = 1;
	for (i = 0; i < column + 2; i++)
		Maze[0][i] = Maze[row + 1][i] = 1;
}
/*bool MazePath(int row, int column, int x, int y, int x1, int y1)//递归算法
{
	Maze[x][y] = 1;
	point temp;
	temp.x = x;
	temp.y = y;
	st.push(temp);
	for (int i = 0; i < 4; i++)
	{
		if (x + move1[i].x == x1&&y + move1[i].y == y1)
		{
			point now;
			now.x = x1;
			now.y = y1;
			st.push(now);
			return true;
		}
		if (Maze[x + move1[i].x][y + move1[i].y] == 0)
		{
			if (MazePath(row, column, x + move1[i].x, y + move1[i].y, x1, y1))
				return true;
		}
	}
	st.pop();
	return false;
}*/
bool MazePath(int row, int column, int x, int y, int x1, int y1)//栈
{
	if (x == x1&&y == y1)
		return true;
	stack<point> q;
	point now;
	bool judge;
	now.x = x;
	now.y = y;
	q.push(now);
	while (!q.empty())
	{
		now = q.top();
		if (Maze[now.x][now.y] == 0)
		{
			st.push(now);
			Maze[now.x][now.y] = -1;
		}
		judge = true;
		for (int i = 0; i < 4; i++)
		{
			if (now.x + move1[i].x == x1&&now.y + move1[i].y == y1)
			{
				point temp;
				temp.x = x1;
				temp.y = y1;
				st.push(temp);
				return true;
			}
			if (Maze[now.x + move1[i].x][now.y + move1[i].y] == 0)
			{
				point temp;
				temp.x = now.x + move1[i].x;
				temp.y = now.y + move1[i].y;
				q.push(temp);
				judge = false;
			}
		}
		if (judge)
		{
			q.pop();
			st.pop();
		}
	}
	return false;
}
void Print()
{
	stack<point> q1;
	point temp;
	while (!st.empty())
	{
		temp = st.top();
		q1.push(temp);
		st.pop();
	}
	while (!q1.empty())
	{
		temp = q1.top();
		cout << "(" << temp.x << "," << temp.y << ")" << " ";
		q1.pop();
	}
	cout << endl;
}
void PrintMaze(int row, int column,int x,int y,int x1,int y1)
{
	cout << "The Maze is " << row << "*" << column << endl;
	cout << "The First is (" << x << "," << y << ")" << endl;
	cout << "The End is (" << x1 << "," << y1 << ")" << endl;
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= column; j++)
			cout << Maze[i][j] << " ";
		cout << endl;
	}
}
int main()
{
	int row, column;
	int x, y, x1, y1;
	ProduceMaze(row, column, x, y, x1, y1);
	PrintMaze(row, column, x, y, x1, y1);
	if (MazePath(row,column,x,y,x1,y1))
	{
		cout << "已找到路径" << endl;
		Print();
	}
	else cout << "未能找到路径,请重新生成" << endl;
	system("pause");
	return 0;
}
 