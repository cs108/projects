/*
Cut branch "(N - startRow - chessNum < 0)" in DFS;
added a auxiliary array "visitablePosition";
added "reverse_mode" to do DFS in a faster way;
but Still Time Limit Exceeded.
*/
#include<iostream>

using namespace std;

const int board_size = 8;
char board[board_size][board_size];

int N, K;
int solutionNum;
int visitablePosition[board_size][board_size];

int reverse_mode = 0;

void DFS(int startRow,int visitedColumn[],int chessNum)
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
		for (int i = 0; i < N; i++)
		{
			int c = visitablePosition[r][i];
			if (c == -1)
				break;

			if (reverse_mode == 0)
			{
				if (visitedColumn[c] == 0)
				{
					int v[board_size];
					for (int i = 0; i < N; i++)
					{
						v[i] = visitedColumn[i];
					}
					v[c] = 1;
					DFS(r, v, chessNum - 1);
				}
			}
			else
			{
				DFS(r, visitedColumn, chessNum - 1);
			}

		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	while (true)
	{
		cin >> N >> K;
		if (N == -1)
			break;

		reverse_mode = 0;
		if (K > N / 2&&K<N)
		{
			K = N - K;
			reverse_mode = 1;
		}
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				visitablePosition[r][c] = -1;  //to store visitable column of each row
			}
		}

		for (int r = 0,top=0; r < N; r++,top=0)
		{
			for (int c = 0; c < N; c++)
			{
				cin >> board[r][c];
				if (board[r][c] == '#')
				{
					visitablePosition[r][top++] = c;
				}
			}
		}
		solutionNum = 0;
		int visitedCol[board_size] = { 0 };
		if(N>0)
			DFS(0, visitedCol, K);
		cout << solutionNum << endl;
	}
	//fclose(stdin);
	return 0;
}
