/*
Simple data structure implimentarion.
*/
#include<iostream>

using namespace std;

//stack
const int maxSize = 1000;
int stack[maxSize];
int top = 0;
#define PUSH(x) stack[top++]=x
#define POP stack[--top]
#define SFULL (top==maxSize)
#define SEMPTY (top==0)


//queue
const int qSize = 1000;
int que[qSize];
int front = 0;
int rear = 0;
#define QIN(x) que[rear++%qSize]=x
#define QOUT que[front++%qSize]
#define QFULL (rear%qSize-front%qSize==qSize-1)
#define QEMPTY (rear%qSize==front%qSize)



int main()
{
	//ios::sync_with_stdio(false);
	for (int i = 0; i < 10; i++)
		PUSH(i);
	while (!SEMPTY)
		cout << POP << endl;
	char a=getchar();

	for (int i = 0; i < 10; i++)
		QIN(i);
	while (!QEMPTY)
	{
		cout << QOUT << endl;
	}
	cout << "???" << endl;
	
	char c;
	while ((c = getchar()) == '\n'); //previous getchar() has left a '\n' in the input buffer
	cout << '\''<<c <<'\''<< endl;
	return 0;
}
