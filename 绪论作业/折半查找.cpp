#include<stdio.h>

int SearchInt(int *num, int down, int up, int target);

int main()
{
	int num[10] = {2,4,6,8,10,12,14,16,18,20};//1~20ż��˳��� 
	int target;
	printf("Please enter an even number(1~20) to search its postion:\n");
	scanf("%d", &target);
	while(target)//��target����Ϊ0ʱ�˳�ѭ����������
	{
		if(target<=20&&target>0&&target%2==0)//�ж���������Ƿ����������������Ϊ�ַ���ʱtargetĬ�ϵ���1���ų�
		{
			int m = SearchInt(num, 0, 10, target);
			printf("Its index is %d\n\n", m);//������������������±� 
		}
		else
		{
			printf("It does not meet the conditions\n\n");
			fflush(stdin);//�������������ֹ����ѭ�� 
		}
		scanf("%d", &target);
	}
	return 0;
}


//���Һ��� 
int SearchInt(int *num, int down, int up, int target)//����˳����Լ���ʼ�±���ܸ�����Ҫ���ҵ��� 
{
	int middle;
	while(1)	
	{
		middle = (up + down)/2;//���ַ�ȡ�м�ֵ 
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
