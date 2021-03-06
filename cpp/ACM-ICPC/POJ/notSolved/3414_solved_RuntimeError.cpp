/*
I ran it on my computer with visual studio 2015 and there was nothing wrong using test case given by POJ.
But when I submitted it to POJ, it told me that "nullptr" is not defined.
So I changed all "nullptr" into "NULL" and submitted again, only to be told that there was Runtime Error.
I guess the C++ compiler that POJ use is out of date, which even wouldn't recognize "nullptr".


I constructed the code and used array rather than object to store data the day after, 
and there was no more Runtime Error found by POJ.
I decide to upload that solution which was Accepted by POJ meanwhile keep this file.
*/

/*
Sample Input
3 5 4
Sample Output
6
FILL(2)
POUR(2,1)
DROP(1)
POUR(2,1)
FILL(2)
POUR(2,1)
*/
#include <iostream>

using namespace std;

//stack
const int sSize = 2000;
const int StrLen = 20;
char stack[sSize][StrLen];
int top = 0;





//que
const int qSize = 1000;
int que[qSize][4];
int front, rear;
#define QIN(x,y,t,addr) que[rear][3]=addr,que[rear][0]=x,que[rear][1]=y,que[rear++][2]=t,rear%=qSize
#define QOUT(x,y,t,addr) addr=que[front][3],x=que[front][0],y=que[front][1],t=que[front++][2],front%=qSize
#define QEMPTY (front%qSize==rear%qSize)



int A = 0, B = 1;//pot index
int C;

int pot_cap[2];
int water_left[2];
const int max_visit_time = 100;
int v[max_visit_time][max_visit_time];
int bfs_succ;
int T;

void FILL(int i)
{
	water_left[i] = pot_cap[i];
}

void DROP(int i)
{
	water_left[i] = 0;
}
void POUR(int i, int j)
{
	int water_to_fill_j = pot_cap[j] - water_left[j];
	if (water_to_fill_j >= water_left[i])
	{
		water_left[j] += water_left[i];
		water_left[i] = 0;
	}
	else if (water_to_fill_j < water_left[i])
	{
		water_left[i] -= (pot_cap[j] - water_left[j]);
		water_left[j] = pot_cap[j];
	}
}

void set(int a, int b)  //used for recover
{
	water_left[A] = a;
	water_left[B] = b;
}


class node {
public:
	node *father;
	char *op;
	char Str[StrLen];
	node *self()
	{
		return this;
	};
	node() {};
	node(node *f, char *o)
	{
		father = f;
		//self = s;
		op = o;
		for (int i = 0; i < StrLen; i++)
			Str[i] = *(op + i);
	}

};

node *lastNode;

void BFS()
{
	bfs_succ = 0;
	front = 0;
	rear = 0;
	node *np = new node();
	np->father = NULL;
	np->op = "";
	//np->self = np;
	QIN(0, 0, 0, int(np->self()));
	v[0][0] = 1;
	int seq = 0; //not in use.only used to test
	while (!QEMPTY)
	{
		int a, b, t, father;
		QOUT(a, b, t, father);
		//printf("QOUT(%d,%d,%d)\n", a, b, t);
		if (a == C || b == C)
		{
			bfs_succ = 1;
			T = t;
			lastNode = (node *)father;
			return;
		}
		int a2, b2;
		for (int i = 0; i < 6; i++)  //6 kinds of action
		{
			seq++;
			set(a, b);
			char *sp;
			switch (i)
			{
			case 0:FILL(A); sp = "FILL(1)"; break;
			case 1:FILL(B); sp = "FILL(2)"; break;
			case 2:DROP(A); sp = "DROP(1)"; break;
			case 3:DROP(B); sp = "DROP(2)"; break;
			case 4:POUR(A, B); sp = "POUR(1,2)"; break;
			case 5:POUR(B, A); sp = "POUR(2,1)"; break;
			}
			a2 = water_left[A];
			b2 = water_left[B];
			if (v[a2][b2] == 0)
			{
				v[a2][b2] = 1;
				node *n = new node((node *)father, sp);   //never delete --> memory leak
				QIN(a2, b2, t + 1, int(n->self()));
				//printf("fill a QIN(%d,%d,%d) seq=%d\n", a2, b2, t + 1,seq);
			}
		}
	}
}


int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> pot_cap[A] >> pot_cap[B] >> C;
	BFS();
	if (bfs_succ)
	{
		cout << T << endl;
		while (lastNode->father != NULL)
		{
			for (int i = 0; i < StrLen; i++)
			{
				stack[top][i] = lastNode->Str[i];
			}
			top++;
			lastNode = lastNode->father;
		}
		while (top != 0)
		{
			cout << stack[--top] << endl;
		}
	}
	else
		cout << "impossible" << endl;



	//fclose(stdin);
}
