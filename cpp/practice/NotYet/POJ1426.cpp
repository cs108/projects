/*
I tried to create a class named bigInt to solve POJ1426 but failed to make it as what I wanted.
*/
#include<iostream>

using namespace std;

const int BITS = 100;

class bigInt {
	 unsigned int a[BITS];

public:
	bigInt()
	{
		for (int i = 0; i < BITS; a[i++] = 0);
	}

	bool ok()
	{
		int result = true;
		for (int i = 0; i < BITS; i++)
			if (!(a[i] == 1 || a[i] == 0))
				result = false;
		return result;
	}

	bigInt operator*(int n)  //a=b*a ; n is going to be that b
	{
		int b[10] = { 0 }; //yes,that b
		int bLength;
		if (n < 10)
		{
			bLength = 1;
			b[0] = n;
		}
		else
		{
			for (int i = 0; n != 0; b[i] = n % 10, n /= 10,bLength++);
		}
		unsigned int c[BITS][BITS] = { 0 }; //middle result of b*a
		unsigned int carry[BITS + 10] = { 0 };
		for (int ia = 0; ia < BITS; ia++)//ia : index of a
		{



			for (int ib = 0; ib < bLength; ib++)//ib : index of b
			{
				c[ia][ib] = a[ia] * b[ib] % 10;
				carry[ia + 1] += a[ia] * b[ib] / 10;
			}
		}
		for (int is = 0; is < BITS; is++)// is : index of sum
		{
			int s = 0;
			for (int ia = 0; ia <= is; ia++)
			{
				s +=c[ia][is - ia] + carry[is];
			}
			a[is] = s % 10;
			if (s / 10)
				carry[is + 1] += s / 10;
		}
		return *this;
	}

	bigInt operator++(int)
	{
		if (a[0] + 1 < 10)
			a[0] += 1;
		else
		{
			int carry[BITS + 10] = { 0 };
			a[0] = 0;
			carry[1] = 1;
			for (int i = 1; i < BITS; i++)
			{
				a[i] = carry[i] + a[i];
				carry[i + 1] += a[i] / 10;
				a[i] %= 10;
			}
		}
		return *this;
	}

	void print()
	{
		int start = 0;
		for (int i = BITS-1; i >= 0; i--)
		{
			if (a[i])
			{
				start = i;
				break;
			}
		}
		for (int i = start; i >= 0; i--)
			cout << a[i];
	}
};


int main()
{
	bigInt b;
	b++;
	for (int i = 1; i < 10; i++)
	{
		cout << "#" << i << ":" << endl;
		b=b*i;

		b.print();
		cout << endl;
	}

}
