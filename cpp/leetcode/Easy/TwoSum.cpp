#include<stdio.h>
#include<malloc.h>
#include<iostream>

/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
	*returnSize = 2;
	int *returnArray = (int *)malloc(sizeof(int) * 2);
	for (int i = 0; i < numsSize - 1; i++)
	{
		for (int j = i + 1; j < numsSize; j++)
		{
			if (*(nums + i) + *(nums + j) == target)
			{
				*returnArray = i;
				*(returnArray + 1) = j;
				return returnArray;
			}
		}
	}
	return returnArray; // I don't think this line is needed referring to the problem description. However, I was forced to write this line to get rid of "compile error".
}


int main()
{
	int nums[] = {2,7,11,15};
	int numsSize = 4;
	int target = 9;
	int *returnArray=nullptr;
	int *returnSize = new int;
	returnArray = twoSum(nums,numsSize, target, returnSize);
	delete returnSize;

	std::cout << *returnArray << '\n' << *(returnArray + 1) << std::endl;
	free(returnArray);
	return 0;
}

