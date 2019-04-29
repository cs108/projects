/*
Use "printf()" "scanf()" rather than "cin" "cout" still doesn't work.
*/
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
	for (r = startRow; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (board[r][c] == '#'&&!visitedColumn[c])
			{
				visitedColumn[c] = 1;
				DFS(r, visitedColumn, chessNum - 1);
				visitedColumn[c] = 0;
			}
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	while (true)
	{
		//cin >> N >> K;
		scanf("%d %d", &N, &K);
		if (N == -1)
			break;
		int n = N;
		for (int r = 0; r < N; r++)
		{
			/*for (int c = 0; c < N; c++)
			{
				cin >> board[r][c];
			}*/
			scanf("%s", board[r]);
		}
		N = n;
		solutionNum = 0;
		int visitedCol[board_size] = { 0 };
		if(N>0)
			DFS(0, visitedCol, K);
		//cout << solutionNum << endl;
		printf("%d\n", solutionNum);
	}
	//fclose(stdin);
	return 0;
}
