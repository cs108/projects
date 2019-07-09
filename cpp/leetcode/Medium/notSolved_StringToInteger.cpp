/*
Message from leetcode:
'''
Runtime Error Message:
Line 61: Char 7: runtime error: signed integer overflow: 2147483640 + 8 cannot be represented in type 'int' (solution.c)  

Last executed input:
"-2147483648"
'''
*/

#include<stdio.h>
#include<iostream>

int myAtoi(char * str) {

	void prepare(int* prepared, char bigNumArray[], char smallNumArray[], int* maxLength, int* MAX, int* MIN);
	bool available(char *str);
	void getNumFromStr(char *str, char numArray[], char* sign, int* numLength,int* maxLenth);

	static int prepared = 0;
	static int MAX, MIN;
	static char bigNumArray[32] = { 0 };
	static char smallNumArray[32] = { 0 };
	static char *sBiggestNum = bigNumArray;
	static char *sSmallestNum = smallNumArray;
	static int maxLength;
	
	prepare(&prepared,bigNumArray,smallNumArray,&maxLength,&MAX,&MIN);

	if (!available(str))
		return 0;

	char numArray[32] = { 0 };
	char sign;
	int numLength;
	getNumFromStr(str, numArray, &sign,&numLength,&maxLength);

	if (numLength > maxLength)
	{
		if (sign == '-')
			return MIN;
		else
			return MAX;
	}

	if (numLength == maxLength)
	{
		char *M;
		int m;
		if (sign == '-')
		{
			M = smallNumArray;
			m = MIN;
		}
		else
		{
			M = bigNumArray;
			m = MAX;
		}
		int i;
		for (i = 0;i<numLength;i++)
		{
			if (numArray[i] > M[numLength-1-i])
				return m;
		}
		if (i == -1)
			return m;
	}

	int num = 0;
	for (int i = 0; i <numLength ; i++)
	{
		num *= 10;
		num += numArray[i] - '0';
	}
	if (sign == '-')
		num = 0 - num;
	return num;
}

void prepare(int* prepared, char bigNumArray[], char smallNumArray[], int* maxLength, int* MAX, int* MIN)
{
	if (!*prepared)
	{
		*prepared = 1;
		int big, small;
		unsigned l = 1;
		for (int i = 0; i < 31; i++)
		{
			l *= 2;
		}
		big = l - 1;
		small = 0 - big - 1;
		*MAX = big;
		*MIN = small;
		int i;
		for (i = 0; big > 0; i++)
		{
			bigNumArray[i] = '0' + big % 10;
			big /= 10;
		}
		bigNumArray[i] = 0;
		*maxLength = i;

		for (i = 0; i<32; i++)
		{
			smallNumArray[i] = bigNumArray[i];
		}
		smallNumArray[0] += 1;
	}
}

bool available(char *str)
{
	if (str == NULL)
		return false;
	if (*str == 0)
		return false;
	if (*str == ' ')
		return available(str + 1);
	if (*str == '+' || *str == '-')
		if (*(str + 1) >= '0'&&*(str + 1) <= '9')
			return true;
		else
			return false;
	if (*str >= '0'&&*str <= '9')
		return true;
	return false;
}

void getNumFromStr(char *str, char numArray[], char* sign, int* numLength,int* maxLength)
{
	int i;
	for (i = 0; str[i] == ' '; i++);
	if (str[i] == '-')
	{
		*sign = '-';
		i++;
	}
	else
	{
		*sign = '+';
		if (str[i] == '+')
			i++;
	}

	//delete leading zeros
	while (str[i]=='0')
	{
		i++;
	}

	int j;
	for (j = 0; ; i++, j++)
	{
		if (j > *maxLength)
			break;
		if (str[i] >= '0'&&str[i] <= '9')
			numArray[j] = str[i];
		else
			break;
	}
	*numLength = j;
}

int main()
{
	char str[5][100] = { "-2147483648" ,"   -42" ,"4193 with words" ,"words and 987" ,"-91283472332" };
	for (int i = 0; i < 5; i++)
	{
		std::cout << str[i] << std::endl
			<<myAtoi(str[i])<<std::endl;
	}
	return 0;
}
