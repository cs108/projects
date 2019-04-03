/*
这个项目用来回应c++笔试题目“将输入的字符的二进制ASCII码反过来输出”，
并且将应用域拓展至中文字符亦适用。

经验教训：
1.头一回用unsigned char来达到我的目的。
2.右移“operator1>>operator2”任一操作数为负的情况都未被c标准所定义，因而结果取决于编译系统的具体实现。
  当operator1为负数时，由于visual studio 2015会将此表达式编译为shr，因而无论右移多少次，其结果都不会是0，
  倒是可能移的次数多了变成了-1，怎么移都是-1。
*/
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

class character
{
public:
	character(char c)
	{
		for (int i = 0; i < 4; i++)
		{
			ca[i] = i == 0 ? c : 0;
			ia[i] = 0;
		}
	}

	character(char a[])
	{
		for (int i = 0; i < 4; i++)
		{
			ia[i] = 0;
			ca[i] = a[i];
		}
	}

	void reverse();
	void toInt();
	void print();
	void printInt();
	int getLastIndex();

	void display();
private:
	char ca[4]; 
	unsigned char ia[4];//used to declare as unsigned int and get something wrong
};

void character::print() 
{
	for (int i = 0; i < 4 && ca[i] != 0; i++)
		cout << ca[i];
	cout << endl;
}

void character::toInt()
{
	for (int i = 0; i < 4; i++)
	{
		if (ca[i] < 0)
			ia[i] = unsigned char(ca[i]);
		else
			ia[i] = ca[i];
	}
}


void character::printInt()
{
	for (int i = 0; i <= getLastIndex(); i++)
		cout <<bitset<sizeof(ia[i])*8>(ia[i]) ;
	cout << endl;
}

void character::reverse()
{
	int l = getLastIndex();
	char temp[4] = { 0,0,0,0 };
	for (int i = l; i >= 0; i--)
	{
		for (int bits=8; bits; ca[i] >>= 1,bits--)
		{
			if (ca[i] == -1)
			{
				temp[l - i] <<= 1;
				temp[l - i]++;
				break;
			}
			temp[l - i] <<=1;
			if (ca[i] & 1)
			{
				temp[l - i]++;
			}
		}
	}
	for (int i = l; i >= 0; i--)
		ca[i] = temp[i];
}

int character::getLastIndex()
{
	int i = 3;
	for (; i >= 0; i--)
	{
		if (ca[i])
			return i;
	}
	return 0;
}

void character::display()
{
	print();
	toInt();
	printInt();
	reverse();
	toInt();
	printInt();
}

void Test1()
{
	cout << "Test1 begins:" << endl;
	character *c = new character('\0');
	c->display();
	cout << "Test1 finished." << endl;
}

void Test2()
{
	cout << "Test2 begins:" << endl;
	character *c = new character('g');
	c->display();
	cout << "Test2 finished." << endl;
}

void Test3()
{
	cout << "Test3 begins:" << endl;
	character *c = new character('$');
	c->display();
	cout << "Test3 finished." << endl;
}

void Test4()
{
	cout << "Test4 begins:" << endl;
	character *c = new character("狗");
	c->display();
	cout << "Test4 finished." << endl;
}

void Test5()
{
	cout << "Test5 begins:" << endl;
	character *c = new character('狗');
	c->display();
	cout << "Test5 finished." << endl;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	return 0;
}
