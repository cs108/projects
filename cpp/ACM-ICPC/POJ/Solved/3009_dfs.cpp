/*
This question asks for steps of valid shortest path, so BFS may be a better choice.
But since there is max-times limit, DFS would work efficiently enough as well.
*/
#include<iostream>

using namespace std;

int R, C; //row,columm
const int vacant_square = 0, block = 1, start = 2, goal = 3;
const int max_time = 10;

int current_shortest_time;
int dfs_succ;

const int map_size = 20;
int dir[4][2] = {0,-1, -1,0, 0,1, 1,0};//left up right down {r:0,c:1}

void DFS(int r, int c, int time, int (*m)[map_size])
{
//printf("\ntime = %d r = (%d,%d)\t",time,r,c);
	if (time >= current_shortest_time)
		return;
	int map[map_size][map_size];
	for (int tr = 0; tr < R; tr++)
	{
		for (int tc = 0; tc < C; tc++)
		{
			map[tr][tc] = *(*(m + tr) + tc);  //**m   *(*(m + tr) + tc);
//cout<< map[tr][tc] <<" ";
		}
	}

	for (int i = 0; i < 4; i++)  //change i to change direction
	{
//cout << "dir = " << i << endl;
		for (int r2=r+dir[i][0],c2=c+dir[i][1];r2>=0&&c2>=0&&r2<R&&c2<C; r2 += dir[i][0], c2 += dir[i][1])  //(r2,c2):front 1 step square
		{
			if (map[r2][c2] == goal)
			{
				if (time >= max_time)
					return;
				current_shortest_time = current_shortest_time < time + 1 ? current_shortest_time : time + 1;
				dfs_succ = 1;
				return;
			}
			if (map[r2][c2] == block)
			{
				break;
			}
			else 
			{
				int r3 = r2 + dir[i][0];
				int c3 = c2 + dir[i][1];
													//I wrote "if (r3<0 || r3>R || c3<0 || c3>C)" and of course failed
													//This is really a deadly mistake but not hard to avoid
				if (r3<0 || r3>=R || c3<0 || c3>=C)  //(r3,c3):front 2 step square    
				{
					break;
				}
				if (map[r3][c3] == block)
				{
					map[r3][c3] = vacant_square;
					DFS(r3 - dir[i][0], c3 - dir[i][1], time + 1, map);
					map[r3][c3] = block;
					break;
				}
				if (map[r3][c3] == goal)
				{
//cout << "reach goal" << endl;
					if (time >= max_time)
						return;
					current_shortest_time = current_shortest_time < time + 1 ? current_shortest_time : time + 1;
					dfs_succ = 1;
					return;
				}
			}
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	int map[map_size][map_size];
	int r, c;
	int type;
	while (true)
	{
		cin >> C >> R;
		if (C + R == 0)
			break;
		for (int tr = 0; tr < R; tr++)
		{
			for (int tc = 0; tc < C; tc++)
			{
				cin>>type;
				map[tr][tc] = type;
				if (type == start)
				{
					r = tr;
					c = tc;
				}
			}
		}
		dfs_succ = 0;
		current_shortest_time = 11;
		DFS(r, c, 0,map);
		if (dfs_succ)
			cout << current_shortest_time << endl;
		else
			cout << -1 << endl;
	}
	//fclose(stdin);
	return 0;
}
