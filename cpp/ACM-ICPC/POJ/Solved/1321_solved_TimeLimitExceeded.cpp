#include<iostream>

using namespace std;

const int board_size = 8;
char board[board_size][board_size];

int N, K;
int solutionNum;

void DFS(int startRow, int visitedColumn[], int chessNum)
{
	if (chessNum == 0)
	{
		solutionNum++;
		return;
	}

	if (N - startRow - chessNum < 0)
		return;
	int r;
	for (r = startRow; r <= N-chessNum; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (board[r][c] == '#'&&!visitedColumn[c])
			{
				visitedColumn[c] = 1;
				DFS(r+1, visitedColumn, chessNum - 1);  /*
														This is the very point to determine whether you would pass POJ or not.
														I used to write "DFS(r, visitedColumn, chessNum - 1);" , 
														and then no matter how hard I work on cutting branch 
														or using auxiliary array to save time, 
														it would always end up with "Time Limit Exceeded" although it's not "Wrong Answer".
														*/
				visitedColumn[c] = 0;
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	while (true)
	{
		cin >> N >> K;							/*
												Once I thought it was "cin" "cout" that led to "Time limit Exceeded", but in fact it wasn't.
												I\O Method		Memory	Time
												cin\cout		172K	32MS
												printf\scanf	88K		0MS
												*/
		//scanf("%d %d", &N, &K);
		if (N == -1)
			break;
		int n = N;
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				cin >> board[r][c];
			}
			//scanf("%s", board[r]);
		}
		N = n;
		solutionNum = 0;
		int visitedCol[board_size] = { 0 };
		if(N>0)
			DFS(0, visitedCol, K);
		cout << solutionNum << endl;
		//printf("%d\n", solutionNum);
	}
	fclose(stdin);
	return 0;
}
