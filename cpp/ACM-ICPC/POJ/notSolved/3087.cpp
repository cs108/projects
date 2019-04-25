/*
Pass test case given by POJ but failed to be Accepted.
Something wrong but don't know yet.
Maybe there's something wrong with visited().
*/

/*
sample_input.txt:
2
4
AHAH
HAHA
HHAAAAHH
3
CDE
CDE
EEDDCC
*/

#include<iostream>

using namespace std;

const int size1 = 100;
const int size2 = 200;
char S1[size1], S2[size1], S12[size2];
char dst[size2];
char v[100][size2] = {0};
int vtail = 0;


int C, N;

void shuffle()
{
	//new s12
	for (int i = 0, j = 0; i < C; i ++,j+=2)
	{
		S12[j] = S2[i];
	}
	for (int i = 0, j = 1; i < C; i++, j += 2)
	{
		S12[j] = S1[i];
	}

	//new s1
	for (int i = 0; i < C; i++)
	{
		S1[i] = S12[i];
	}

	//new s2
	for (int i = 0; i < C; i++)
	{
		S2[i] = S12[C + i];
	}


}

bool visited()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (v[i][j] != S1[j] || v[i][C + j] != S2[j])
				return false;
			else if(j==C-1)
				return true;
		}	
	}
	return false;
}

void visit()
{
	for (int i = 0; i < C; i++)
		v[vtail][i] = S1[i];
	for (int i = 0; i < C; i++)
		v[vtail][i + C] = S2[i];
	vtail++;
}

bool hitDst()
{
	for (int i = 0; i < 2 * C; i++)
	{
		if (S12[i] != dst[i])
			return false;
	}
	return true;
}

int findSolution()
{
	int mix = 0;
	int found = -1;
	while (!visited())
	{
		visit();
		shuffle();
		mix++;
		if (hitDst())
		{
			found = 1;
			break;
		}
	}
	return ((found==-1)?found:mix);
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> N;
	int t = 1;
	while (N--)
	{
		vtail = 0;
		cin >> C;
		for (int i = 0; i < C; i++)
			cin >> S1[i];
		for (int i = 0; i < C; i++)
			cin >> S2[i];
		for (int i = 0; i < 2 * C; i++)
			cin >> dst[i];

		cout << t++ << " " << findSolution()<<endl;
	}
	fclose(stdin);
	return 0;
}
