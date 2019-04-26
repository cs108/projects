/*
"notSolved" version is kept.
*/
#include <iostream>

using namespace std;

//stack
const int sSize = 20000;
const int StrLen = 20;
char stack[sSize][StrLen];
int top = 0;



//que
const int qSize = 20000;
int que[qSize][5];
int front, rear;
#define QIN(x,y,t,fseq,sseq) que[rear][4]=sseq;que[rear][3]=fseq,que[rear][0]=x,que[rear][1]=y,que[rear++][2]=t,rear%=qSize
#define QOUT(x,y,t,gfseq,fseq) fseq=que[front][4],gfseq=que[front][3],x=que[front][0],y=que[front][1],t=que[front++][2],front%=qSize
#define QEMPTY (front%qSize==rear%qSize)


//auxiliary array
const int saSize = 20000;
char StrArr[saSize][StrLen];
int fseqArr[saSize]; //To record father seq. The index is self seq. 

int A = 0, B = 1;//pot index
int C;

int pot_cap[2];
int water_left[2];
const int max_visit_time = 20000;
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

void set(int a, int b)  //used for recover data
{
	water_left[A] = a;
	water_left[B] = b;
}


class node {
public:
	int fatherseq;
	char *op;
	//char Str[StrLen];
	int selfseq;
	node() {};
	node(int f, int s,char *o)
	{
		fatherseq = f;
		selfseq = s;
		op = o;
		for (int i = 0; i < StrLen; i++)
			StrArr[selfseq][i] = *(op + i);
	}
	void saveseq() 
	{
		fseqArr[selfseq] = fatherseq;
	}
};

int lastNodeSeq;

void BFS()
{
	bfs_succ = 0;
	front = 0;
	rear = 0;
	node *np = new node();
	np->fatherseq = NULL;
	np->op = "";
	np->selfseq = 0;
	QIN(0, 0, 0, np->fatherseq,np->selfseq);
	delete np;
	v[0][0] = 1;
	int seq = 0; 
	while (!QEMPTY)
	{
		int a, b, t, father,grandfather;
		QOUT(a, b, t, grandfather,father);
		//printf("QOUT(%d,%d,%d)\n", a, b, t);
		if (a == C || b == C)
		{
			bfs_succ = 1;
			T = t;
			lastNodeSeq = father;
			return;
		}
		int a2, b2;
		for (int i = 0; i < 6; i++)
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
				node *n = new node(father,seq, sp);
				n->saveseq();
				/*for (int i = 0; i < StrLen; i++)
				{
				StrArr[n->selfseq][i] = n->op[i];
				}*/
				QIN(a2, b2, t + 1, n->fatherseq,n->selfseq);
				delete n;
				//printf("fill a QIN(%d,%d,%d) seq=%d\n", a2, b2, t + 1,seq);
			}
		}
	}
}


void print()
{
	while (lastNodeSeq != 0)
	{
		for (int i = 0; i < StrLen; i++)
		{
			stack[top][i] = StrArr[lastNodeSeq][i];
		}
		top++;
		lastNodeSeq = fseqArr[lastNodeSeq];
	}
	while (top)
	{
		cout << stack[--top]<<endl;
	}
}


void print2()   //recursive version of print. looks cool without stack.
{
	int index = lastNodeSeq;
	if (lastNodeSeq = fseqArr[lastNodeSeq])
		print2();
	cout << StrArr[index]<<endl;
}


int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> pot_cap[A] >> pot_cap[B] >> C;
	BFS();
	if (bfs_succ)
	{
		cout << T << endl;
		print(); //or print2();
	}
	else
		cout << "impossible" << endl;
	//fclose(stdin);
}
