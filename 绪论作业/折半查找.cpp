#include<stdio.h>

int SearchInt(int *num, int down, int up, int target);

int main()
{
	int num[10] = {2,4,6,8,10,12,14,16,18,20};//1~20偶数顺序表 
	int target;
	printf("Please enter an even number(1~20) to search its postion:\n");
	scanf("%d", &target);
	while(target)//当target输入为0时退出循环结束程序
	{
		if(target<=20&&target>0&&target%2==0)//判断输入的数是否符合条件，当输入为字符串时target默认等于1已排除
		{
			int m = SearchInt(num, 0, 10, target);
			printf("Its index is %d\n\n", m);//输出符合条件的数的下标 
		}
		else
		{
			printf("It does not meet the conditions\n\n");
			fflush(stdin);//清除缓冲区，防止无限循环 
		}
		scanf("%d", &target);
	}
	return 0;
}


//查找函数 
int SearchInt(int *num, int down, int up, int target)//传入顺序表，以及起始下标和总个数、要查找的数 
{
	int middle;
	while(1)	
	{
		middle = (up + down)/2;//二分法取中间值 
		if(target == num[middle])
		{
			return middle;
		}
		else if(target > num[middle])
		{
			down = middle + 1;
		}
		else if(target < num[middle])
		{
			up = middle - 1;
		}
	}
}
