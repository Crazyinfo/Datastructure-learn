#include<stdio.h>
#include<stdlib.h>

#define MAX 100
//Ŀ�꣺����Y��X�ϵ�����ȫ���ƶ���Z�� 

//����ṹ��
typedef struct
{
	char name; 
	int stack[MAX];
	int top;
}qhanoi, *Point;

//�������� 
void Initiateqs(Point G);  //��ʼ��ջ 
int PushStack(Point L,int n);  //��ջ���� 
int PopStack(Point L,int m);  //��ջ����
void GotoHanoi(int n, Point Num1, Point Num2, Point Num3);  //��ʼִ�к�ŵ�����ƶ� 
void HanoiPrint(int n,char x,char y,char z);  //��ӡ��ŵ�����ƶ� 
void MoveHanoi(int x, Point Out, Point In);  //�ƶ���ŵ�� 
void MovePrint(int n,char x,char y);  //��ӡ�ƶ���ŵ���Ĺ��� 

int main()
{
	int m;
	printf("Pease input the number(1~100) of disks on X:");
	scanf("%d",&m);
	//�ж�����������Ƿ���1~100֮�� 
	while(m<1||m>100)
	{
		printf("please enter a number that matches its conditon:");
		scanf("%d",&m);
	}
	Point X,Y,Z;//��������ջָ�룬�ֱ������������ 
	//Ϊÿ��ջָ�����ռ䣬�����г�ʼ��
	X = (qhanoi *)malloc(sizeof(qhanoi));
	Initiateqs(X);
	X->name = 'X';
	
	Y = (qhanoi *)malloc(sizeof(qhanoi));
	Initiateqs(Y);
	Y->name = 'Y';
	
	Z = (qhanoi *)malloc(sizeof(qhanoi));
	Initiateqs(Z);
	Z->name = 'Z';
	
	PushStack(X, m);//Ϊ��һ��ջ������Ӧ�����ݣ��������������ȷ���X���� 
	printf("The step to move %d disks:\n",m);
	GotoHanoi(m, X, Y, Z);
	HanoiPrint(m, X->name,Y->name,Z->name);
}

//��ʼ��ջ
void Initiateqs(Point G) //GΪ���� 
{
	G->top = 0;
}

//��ջ
int PushStack(Point L,int n)
{
	L->stack[L->top]=n;
	L->top++;
}

//��ջ
int PopStack(Point L,int m)
{

	m=L->stack[L->top];
	L->top--;
}

//�ƶ���ŵ�� 
void MoveHanoi(int x, Point Out, Point In)
{
	PopStack(Out, x);
	PushStack(In,x);
}

//��ӡ�ƶ����̺���
int k=1;
void MovePrint(int n,char x,char y)
{
	printf("%5d:  Move NO.%d from %c to %c.\n", k, n, x, y);
	k++;
}

//��ŵ����ʼִ���ƶ� 
void GotoHanoi(int n, Point Num1, Point Num2, Point Num3)
{
	if(n == 1)
	{
		MoveHanoi(1, Num1, Num3);
	}
	else
	{
		GotoHanoi(n-1, Num1, Num3, Num2);
		MoveHanoi(n, Num1, Num3);
		GotoHanoi(n-1, Num2, Num1, Num3);
	}
}

//�ݹ��ӡ�ƶ����̺���
void HanoiPrint(int n,char x,char y,char z)
{
	if(n==1)
		MovePrint(1,x,z);
	else
	{
		HanoiPrint(n-1,x,z,y);
		MovePrint(n,x,z);
		HanoiPrint(n-1,y,x,z);
	}
}
