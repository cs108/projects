/*
this is a simple dfs question
this file can be easily converted into c file
*/
#include<iostream>

using namespace std;

//stack of visit sequence
const int sSize = 26 * 26;
int stack[sSize][2];
int top = 0;
#define SPUSH(x,y) stack[top][0]=x,stack[top++][1]=y
#define SPOP(x,y) x=stack[--top][0],y=stack[top][1]

int v[26][26] = {};
int m[8][2] = { -1, -2, 1, -2, -2, -1, 2, -1, -2, 1, 2, 1, -1, 2, 1, 2 };//移动方向对x、y的影响
/*题目暗示了搜索方向的优先级，因而初次尝试时如下搜索顺序不符合题意
{
	2,-1,
	2,1,
	1,2,
	-1,2,
	-2,1,
	-2,-1,
	-1,-2,
	1,-2 };*/

int succ = 0;
int p, q;


bool allVisited()
{
	for (int i = 0; i < p; i++)
		for (int j = 0; j < q; j++)
			if (v[i][j] != 1)
				return false;
	return true;
}


void dfs(int x, int y)
{
	if (allVisited())
	{
		succ = 1;
		return;
	}

	for (int d = 0; d < 8; d++)  //try different searching direction if task not finished
	{
		int x2, y2;
		x2 = x + m[d][0];
		y2 = y + m[d][1];
		if (x2 >= 0 && y2 >= 0 && x2 < p&&y2 < q&&v[x2][y2]==0) //if this direction is leagal and not visited
		{
			SPUSH(x2, y2);
			v[x2][y2] = 1;
			dfs(x2, y2); //go deeper from this new start point
			if (!succ)   //if this direction didn't lead to a exact end
			{
				v[x2][y2] = 0;
				SPOP(x2, y2);
			}
		}
	}
}

void init()
{
	succ = 0;
	top = 0;
	for (int i = 0; i < p; i++)   //memset(v, 0, sizeof(v))
		for (int j = 0; j < q; j++)
			v[i][j] = 0;

}

int main()
{
	int t = 0;
	cin >> t;
	int count = 1;
	while (t--)
	{
		init();
		cin >> p >> q;
		int x = 0, y = 0;  //set root as (0,0)
		SPUSH(x, y);
		v[x][y] = 1;
		dfs(x, y);        //start dfs from root
		cout << "Scenario #" << count++ << ":" << endl;
		if (succ)
		{
			for (int i = 0; i < top;i++)
			{
				x = stack[i][0];
				y = stack[i][1];
				//cout << "("<<x<<","<< y<<") "<< endl;
				cout << char('A' + y) << char('1' + x);
			}
			cout << endl;
		}
		else
			cout << "impossible" << endl;
		cout << endl;
	}
	return 0;
}
