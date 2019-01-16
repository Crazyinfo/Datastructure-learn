#include<stdio.h>
#include<stdlib.h>

#define goon 1
#define sum1 4
#define sum2 5 

//AH = 1 - 10x 6 + 2x 8 +7x 14
//BH = - x 4 + 10x 6 - 3x 10 + 8x 14 +4x 18


//����ṹ�� 
typedef struct TwoPolynomial
{
	int index;
	int ratio;
	struct TwoPolynomial *next;
}TP, *Point;


//���� 
Point CreateList(Point L, int *index, int *ratio, int n);  //�Ը��������ݴ�����Ԫ����ʽ�����������ָ����ϵ�������ڱ��� 
Point AddPolynomial(Point L1, Point L2);  //��������Ԫ����ʽ�ϲ�����L1λ��׼
void PrintList(Point P);  //��ӡ���� 


int main()
{
	Point L1;  //������һ����Ԫ����ʽ  
	int index_1[4] = {14, 8, 6, 0};
	int ratio_1[4] = {7, 2, -10, 1};
	L1 = CreateList(L1, index_1, ratio_1, sum1);

	Point L2;  //�����ڶ�����Ԫ����ʽ
	int index_2[5] = {18, 14, 10, 6, 4};
	int ratio_2[5] = {4, 8, -3, 10, -1};
	L2 = CreateList(L2, index_2, ratio_2, sum2);
	
	printf("The first two element polynomial is:\n");
	PrintList(L1);
	printf("The second two element polynomial is:\n");
	PrintList(L2);

	Point L3;  //����L3����������AddPolynomial���ص�L1                                           
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
	while(i<n)  //ͷ�巨 
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
	Point pa,pb,pc,pd;  //pc���Ϊpa����һ��Ԫ�أ�pd���ڱ�ǵ�ַ��Ȼ���ͷ�ָ��ĵ�ַ 
	pa = L1->next;
	pb = L2->next;
	pc = L1;
	if(pa == NULL)  //��L1�������κ�Ԫ��ʱ 
	{
		return L2;
	}
	while(goon)
	{
		if(pa == NULL)  //��������L1�����һ��Ԫ��ʱ 
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
			if((pb->index) == (pa->index))  //��Ԫ�ص�ָ�����ʱ 
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
					pc = pa; //ʼ�ձ���pcָ��ǰ�Ƚ�Ԫ�ص�ǰһ��ָ�룬����ϵ��֮�����Ϊ0ʱɾȥԪ��
					pa = pa->next;
				}
				L2 = L2->next;
				pb = pb->next;
				
			}
			else if(pb->index > pa->index)  //��L1��ָ������L2��ָ��ʱ 
			{			
				L2->next = pb->next;  //ʼ�ձ���L2ָ��ȽϽڵ��ǰһ��ͷָ�룬�൱��L2�Ƚ���һ��Ԫ�ؼ�ɾȥһ��Ԫ��
				pb->next = pa->next;
				pa->next = pb;
				pc = pb; 
				pa = pb->next;
				pb = L2->next;
			}
			else if(pb->index < pa->index)  //��L1��ָ��С��L2��ָ��ʱ 
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
		printf("X��%d�η���ϵ��Ϊ%d\n", k->index, k->ratio);
		k = k->next;
	}
	printf("\n");
}
