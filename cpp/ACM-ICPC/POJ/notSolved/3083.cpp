/*
Hard to fix this source code.
I'd rather write a new solution than fix it.
*/
#include<iostream>
#include<stdio.h>

using namespace std;

const int Size = 40;
//que
const int qSize = 40 * 40;
int que[qSize][2];
int front, rear;
#define QIN(x,y) que[rear][0]=x,que[rear++]=y
#define QOUT(x,y) x=que[front][0],y=que[front++][0]
#define QEMPTY (front==rear)

char maze[Size][Size];
int w, h;
int v[Size][Size];
int prio;
const int L = 0, R = 1;
int dfs_succ,dfs_end;
int px,py,pd,step;//previous
int currentDirection;//0:lft  1:up  2:rht  3:dwn

/*int dir[2][4][2] = { 
	{-1,0,  0,1,  0,-1, 1,0},//prio==L
	{1,0,  0,1,  0,-1, -1,0}//prio==R
};*/

//int lft[2]{ -1,0 }, rht[2] = { 1,0 }, up[2] = { 0,-1 }, dwn[2] = { 0,1 };
#define lft {-1,0} 
#define rht {1,0}
#define up {0,-1}
#define dwn {0,1}

int dir[2][4][4][2] = {
	{
		{dwn,  lft,  rht,  up},
		{lft,  up,  dwn,  rht},
		{up,  rht,  lft,  dwn},
		{rht,  dwn,  up,  lft}
	},
	{
		{up,  lft,  rht,  dwn},
		{rht,  up,  dwn,  lft},
		{dwn,  rht,  lft,  up},
		{lft,  dwn,  up,  rht}
	}
};

void DFS(int x,int y,int d,int pri) //x:w,y:h
{
	if (dfs_succ == 1)
		return;
	for (int i = 0; i < 4; i++)
	{
		int x2 = x + dir[pri][currentDirection][i][0];
		int y2 = y + dir[pri][currentDirection][i][1];
		int d2 = d + 1;
		if (x2 >= 0 && x2 < w&&y2 >= 0 && y2 < h&&v[y2][x2] <v[y][x]&&maze[y2][x2]!='#'&&dfs_succ==0&&dfs_end==0)
		{
printf("(%d,%d)", y2, x2);
if (x2 == 5 && y2 == 1)
{
	cout << endl;
}
			v[y2][x2] += 1;
			if (dir[pri][currentDirection][i][0] == -1 && dir[pri][currentDirection][i][1] == 0)
				currentDirection = 0;
			else if (dir[pri][currentDirection][i][0] == 0 && dir[pri][currentDirection][i][1] == -1)
				currentDirection = 1;
			else if (dir[pri][currentDirection][i][0] == 1 && dir[pri][currentDirection][i][1] == 0)
				currentDirection = 2;
			else if (dir[pri][currentDirection][i][0] == 0 && dir[pri][currentDirection][i][1] == 1)
				currentDirection = 3;

//if (x2 == 6 && y2 == 3)
//	cout << "???";
			if (maze[y2][x2] == 'E')
			{
				dfs_succ = 1;
				step = d2;
				return;
			}
			DFS(x2, y2, d2, pri);
		}
		else
		{
			if(i==3&& maze[x2][y2] == '#')
				if (dfs_end == 0)
				{
					dfs_end = 1;
					px = x;
					py = y;
					pd = d;
					//v[y][x] += 1;
				}
			if(!(x2 >= 0 && x2 < w&&y2 >= 0 && y2 < h&&v[x2][y2] <v[y][x]&& maze[x2][y2] != '#'))
				if(i==3)
					if (dfs_end == 0)
					{
						dfs_end = 1;
						px = x;
						py = y;
						pd = d;
						//v[y][x] += 1;
					}
		}
	}
}

void clearv()
{
	for (int x = 0; x < Size; x++)
		for (int y = 0; y < Size; y++)
			v[x][y] = 0;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	int x, y;
	while (T--)
	{
		cin >> w >> h;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cin >> maze[i][j];
				if (maze[i][j] == 'S')
				{
					x = j;
					y = i;
				}
			}
		}

		dfs_succ = 0;
		step = 0;
		px = x;
		py = y;
		pd = 1;
		
		clearv();
		while (!dfs_succ)
		{
			currentDirection = 0;
			v[py][px] += 1;
			dfs_end = 0;
			DFS(px, py, pd, L);
		}
		cout << step;

		dfs_succ = 0;
		step = 0;
		px = x;
		py = y;
		pd = 1;
		clearv();
		while (!dfs_succ)
		{
			currentDirection = 2;
			v[py][px] += 1;
			dfs_end = 0;
			DFS(x, y, 1, R);
		}
		cout <<" "<< step<<endl;


	}
	fclose(stdin);
	return 0;
}

