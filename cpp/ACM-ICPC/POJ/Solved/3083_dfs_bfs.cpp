#include<iostream>
#include<stdio.h>

using namespace std;

int R, C;
int v[40][40];
char maze[40][40];
int dir[4][2] = {0,-1,  -1,0,  0,1,  1,0};//r,c  left up  right down
int sr, sc;
int er, ec;
int dfs_succ;
int bfs_succ;
int currentDire;
int step;

//que
int que[1600][3];
int front = 0, rear = 0;
#define QIN(r,c,s) que[rear][0]=r,que[rear][1]=c,que[rear++][2]=s//*(que+rear++)={r,c,s}
#define QOUT(r,c,s) r=que[front][0],c=que[front][1],s=que[front++][2]
#define QEMPTY (front==rear)
#define QFULL ((rear-front)==1600)

void DFS(int r, int c, int spin)
{
	//if (step > 40)return;
	if (r == er&&c == ec)
	{
		dfs_succ = 1;
		cout << step;
		return;
	}
	if (!dfs_succ)
	{
		int r2 = r + dir[(currentDire + spin)%4][0];
		int c2 = c + dir[(currentDire + spin)%4][1];
		int r3 = r + dir[currentDire%4][0];
		int c3 = c + dir[currentDire%4][1];
		if (r2 < R&&r2 >= 0 && c2 < C&&c2 >= 0 && r3 < R&&r3 >= 0 && c3 < C&&c3 >= 0)
		{
			if (maze[r2][c2] != '#')//turn
			{
				step++;
//				printf("(%d,%d) %d\n", r, c, step);//
				currentDire = (currentDire + spin) % 4;
				DFS(r2, c2, spin);
			}
			else if (maze[r2][c2] == '#'&&maze[r3][c3] != '#')//go straight
			{
				step++;
//				printf("(%d,%d) %d\n", r, c, step);//
				DFS(r3, c3, spin);
			}
		}
		currentDire = (currentDire + 4-spin) % 4; //4 is the mod of direction sum, so +3 means -1
		DFS(r, c,  spin);

	}
}

void BFS()
{
	while (!QEMPTY)
	{
		int r, c, s;
		QOUT(r, c, s);
		for (int i = 0; i < 4; i++)
		{
			int r2 = r + dir[i][0];
			int c2 = c + dir[i][1];
			int s2 = s + 1;

//if (r2 == 6 && c2 == 1)
//				cout << endl;

			if (r2 < R&&r2 >= 0 && c2 < C&&c2 >= 0&&v[r2][c2]==0&&maze[r2][c2]!='#')
			{
//printf("(%d,%d) %d\n", r2, c2, s2);
				v[r2][c2] = 1;
				if (r2 == er&&c2 == ec)
				{
					dfs_succ = 1;
					step = s2;
					return;
				}
				QIN(r2, c2, s2);
			}
		}
	}
}

void clear()  //In fact,there's no need to clear maze[][],but if you don't, POJ would tell you TIME=16MS while TIME=0MS if you do
{
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
		{
			v[i][j] = 0;
			maze[i][j] = 0;
		}
}

int main()
{
//	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	
	while (T--)
	{
		clear();
		cin >> C >> R;
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				cin >> maze[i][j];
				if (maze[i][j] == 'S')
				{
					sr = i;
					sc = j;
				}
				if (maze[i][j] == 'E')
				{
					er = i;
					ec = j;
				}
			}
		}

		currentDire = 0;
		dfs_succ = 0;
		step = 1;
		DFS(sr, sc,  3);  //+3 means -1
		cout << " ";
		step = 1;
		dfs_succ = 0;
		DFS(sr, sc,  1);
		cout << " ";


		bfs_succ = 0;
		step = 1;
		front = 0;
		rear = 0;
		
		QIN(sr, sc, step);
		BFS();
		cout << step;
		cout << endl;
	}
//	fclose(stdin);
	return 0;
}

