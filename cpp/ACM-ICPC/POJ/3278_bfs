#include <iostream>

using namespace std;

//que
const int qSize = 100001;
int que[qSize][2] = { 0 };
int front, rear;
#define QIN(x,t) que[rear%qSize][0]=x,que[rear%qSize][1]=t,rear++
#define QOUT(x,t) x=que[front%qSize][0],t=que[front%qSize][1],front++
#define QEMPTY (front%qSize==rear%qSize)

int N, K, T;
const int MIN = 0, MAX = 100001;
int shortest = MAX;
int v[MAX] = { 0 };


void bfs(int x, int t)
{
	if (t >= shortest)
		return;
	if (x == K)
	{
		T = t;
		shortest = shortest <= T ? shortest : T;
		return;
	}

	if (x<MIN&&x>MAX)
		return;

	int x2, t2;
	int newNodeNum = 0;
	//action 1
	x2 = x + 1;
	t2 = t;
	if (x2 <= MAX)
	{
		t2++;
		QIN(x2, t2);
		newNodeNum++;
	}
	//action 2
	x2 = x - 1;
	t2 = t;
	if (x2 >= MIN)
	{
		t2++;
		QIN(x2, t2);
		newNodeNum++;
	}
	//action 3
	x2 = x * 2;
	t2 = t;
	if (x2 <= MAX)
	{
		t2++;
		QIN(x2, t2);
		newNodeNum++;
	}

	while (newNodeNum--)
	{

		QOUT(x2, t2);
		if (!v[x2])
		{
			v[x2] = 1;
			bfs(x2, t2);
		}
	}
}

int main()
{
	cin >> N >> K;
	if (N >= MIN&&N <= MAX&&K >= MIN&&K <= MAX)
	{
		bfs(N, 0);
	}
	cout << shortest << endl;
	return 0;
}
