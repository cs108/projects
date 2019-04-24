/*
Simple BFS.
I wouldn't think it would pass POJ but eventually it did! Crazy.
If input number is too large,then you may change qSize to adjust.
But this file wouldn't work if input number is big enough since cpp is using bits-limited data type unlike Python.
So if the input number is big, you'd better design a new solution.
*/
#include<iostream>

using namespace std;

const int qSize = 1000000;  //If qSize is not big enough, rear will hit front easily and cause a fake QEMPTY. 
unsigned long long que[qSize];
int front, rear;
#define QIN(x) que[rear++]=x,rear%=qSize
#define QOUT(x) x=que[front++],front%=qSize
#define QEMPTY (front%qSize==rear%qSize)

unsigned long long m, n;

void BFS()
{
//int count = 0;
	front = 0; 
	rear = 0;
	QIN(1);
//cout << "QIN "<<1<<endl;
	while (!QEMPTY)
	{
//count++;
		QOUT(m);
//if(m==111110011111)
//  cout << "QOUT " << m << endl;
		if ((long long)(m%n) == 0)
			return;
		QIN(m * 10);
//cout << "QIN " << m * 10 << endl;
		QIN(m * 10 + 1);
//cout << "QIN " << m * 10+1 << endl;
/*		if ((m * 10) % n == 0)
		{
			m *= 10;
			return;
		}
		else
		{
			QIN(m * 10);
cout << "QIN " << m * 10 << endl;
		}
		if (!(m & 1))
		{
			if (++m%n == 0)
				return;
			else
			{
				QIN(m);
cout << "QIN " << m << endl;
			}
		}*/
/*if (!(count % 50))
		{
			cout << " ";
			system("cls");
		}*/
	}
}

int main()
{
	while (true)
	{
		cin >> n;
		if (n == 0)
			break;
		BFS();
		cout << m << endl;
//printf("%lld %% %lld = %lld\n", m, n, (long long) m%n);
	}
	return 0;
}
