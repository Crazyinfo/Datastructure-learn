#include<stdio.h>
#include<stdlib.h>

#define goon 1
#define sum1 4
#define sum2 5 

//AH = 1 - 10x 6 + 2x 8 +7x 14
//BH = - x 4 + 10x 6 - 3x 10 + 8x 14 +4x 18


//定义结构体 
typedef struct TwoPolynomial
{
	int index;
	int ratio;
	struct TwoPolynomial *next;
}TP, *Point;


//函数 
Point CreateList(Point L, int *index, int *ratio, int n);  //以给出的数据创建二元多项式，用数组接收指数和系数，便于遍历 
Point AddPolynomial(Point L1, Point L2);  //将两个二元多项式合并，以L1位基准
void PrintList(Point P);  //打印函数 


int main()
{
	Point L1;  //创建第一个二元多项式  
	int index_1[4] = {14, 8, 6, 0};
	int ratio_1[4] = {7, 2, -10, 1};
	L1 = CreateList(L1, index_1, ratio_1, sum1);

	Point L2;  //创建第二个二元多项式
	int index_2[5] = {18, 14, 10, 6, 4};
	int ratio_2[5] = {4, 8, -3, 10, -1};
	L2 = CreateList(L2, index_2, ratio_2, sum2);
	
	printf("The first two element polynomial is:\n");
	PrintList(L1);
	printf("The second two element polynomial is:\n");
	PrintList(L2);

	Point L3;  //定义L3，用来接收AddPolynomial返回的L1                                           
	L3 = AddPolynomial(L1, L2);
	printf("Combined two element polynomials:\n");
	PrintList(L3);
}


Point CreateList(Point L, int *index, int *ratio, int n)
{
	int i = 0; 
	L = (TP *)malloc(sizeof(TP));
	L->next = NULL;
	Point p;
	p = (TP *)malloc(sizeof(TP));
	while(i<n)  //头插法 
	{
		p->index = index[i];
		p->ratio = ratio[i];
		p->next = L->next;
		L->next = p;
		p = (TP *)malloc(sizeof(TP));
		i++;
	}
	return L;
}


Point AddPolynomial(Point L1, Point L2)
{
	Point pa,pb,pc,pd;  //pc标记为pa的上一个元素，pd用于标记地址，然后释放指向的地址 
	pa = L1->next;
	pb = L2->next;
	pc = L1;
	if(pa == NULL)  //当L1本身不含任何元素时 
	{
		return L2;
	}
	while(goon)
	{
		if(pa == NULL)  //当遍历到L1的最后一个元素时 
		{
			if(pb != NULL)
			{
				pc->next = pb;
				return L1;
			} 
			else
			{
				pa->next= pb; 
				return L1;
			} 
		}
		else
		{
			if((pb->index) == (pa->index))  //当元素的指数相等时 
			{
				pa->ratio += pb->ratio;
				if(pa->ratio == 0)
				{
					pd = pa;
					pc->next = pa->next;
					pa = pc->next;
					free(pd);
				}
				else
				{
					pc = pa; //始终保持pc指向当前比较元素的前一个指针，便于系数之和相加为0时删去元素
					pa = pa->next;
				}
				L2 = L2->next;
				pb = pb->next;
				
			}
			else if(pb->index > pa->index)  //当L1的指数大于L2的指数时 
			{			
				L2->next = pb->next;  //始终保持L2指向比较节点的前一个头指针，相当于L2比较完一个元素即删去一个元素
				pb->next = pa->next;
				pa->next = pb;
				pc = pb; 
				pa = pb->next;
				pb = L2->next;
			}
			else if(pb->index < pa->index)  //当L1的指数小于L2的指数时 
			{
				L2->next = pb->next;
				pc->next = pb;
				pb->next = pa;
				pa = pb;
				pb = L2->next;
			}
		}
	}
}


void PrintList(Point P)
{
	Point k;
	k = P->next;
	while(k!=NULL)
	{
		printf("X的%d次方的系数为%d\n", k->index, k->ratio);
		k = k->next;
	}
	printf("\n");
}
