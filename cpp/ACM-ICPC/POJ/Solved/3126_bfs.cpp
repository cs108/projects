#include<iostream>

using namespace std;

const int qSize = 1000;
int que[qSize][2];
int front = 0, rear = 0;
#define QIN(x,step) que[rear][0]=x,que[rear++][1]=step,rear%=qSize
#define QOUT(x,step) x=que[front][0],step=que[front++][1],front%=qSize
#define QEMPTY (front%qSize==rear%qSize)

int src, dst;
int bfs_succ;
int STEP;

bool isPrime(int x) {
	bool result = true;
	if (x == 2)
		return result;
	
	if(!(x&1))return false;
				/*
				I added sentence "if(!(x&1))return false;" after I saw how Python standard lib judge prime,
				and I think that would really save a lot of time when you deal with big number.
				But then I submitted on POJ only to find that the TIME is still the same.
				Well, numbers in POJ test case are too small to let this sentence make a different.
				All numbers POJ test case provides are four-digit primes as it says.
				*/
	
	for (int i = 2; i*i <= x; i++)
	{
		if (x%i == 0)
		{
			result = false;
			break;
		}
	}
	return result;
}


void BFS()
{
	int v[10000] = { 0 };
	front = 0;
	rear = 0;
	QIN(src, 0);
	v[src] = 1;
	bfs_succ = 0;
	while (!QEMPTY)
	{
		int num, step;
		QOUT(num, step);

		//printf("QOUT(%d,%d)\n", num, step);
		if (num == dst)
		{
			bfs_succ = 1;
			STEP = step;
			return;
		}
		int n;
		int bit[4];
		for (int i = 0; i < 4; i++)
		{
			int mod = 1;
			for (int j = i; j > 0; j--)
				mod *= 10;
			bit[i] = (num / mod) % 10;
		}
		
		//change bits
		for (int i = 0; i < 4; i++)
		{
			int bit2[4];
			for (int l = 0; l < 4; l++)
				bit2[l] = bit[l];
			for (int j = 0; j < 10; j++)
			{
				if (i == 3 && j == 0)
					continue;
				bit2[i] = j;

				//I was trapped by a coding mistake for a long while: n = bit2[0] + bit2[1] * 10 + bit[2] * 100 + bit2[3] * 1000;
				n = bit2[0] + bit2[1] * 10 + bit2[2] * 100 + bit2[3] * 1000;

				if (v[n] == 0 && isPrime(n))
				{
					v[n] = 1;
					QIN(n, step + 1);
					//if (n == 1733 || n == 3733 || n== 3739 || n == 3779 || n == 8779 || n == 8179)
					//printf("QIN(%d,%d)\n", n, step + 1);
				}
			}
		}
	}
}

int main()
{
	//		freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> src >> dst;
		BFS();
		if (bfs_succ)
			cout << STEP << endl;
		else
			cout << "Impossible" << endl;
	}
	//		fclose(stdin);
	return 0;
}
