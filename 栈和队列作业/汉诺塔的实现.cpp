#include<stdio.h>
#include<stdlib.h>

#define MAX 100
//目标：借助Y将X上的盘子全部移动到Z上 

//定义结构体
typedef struct
{
	char name; 
	int stack[MAX];
	int top;
}qhanoi, *Point;

//函数申明 
void Initiateqs(Point G);  //初始化栈 
int PushStack(Point L,int n);  //入栈函数 
int PopStack(Point L,int m);  //出栈函数
void GotoHanoi(int n, Point Num1, Point Num2, Point Num3);  //开始执行汉诺塔的移动 
void HanoiPrint(int n,char x,char y,char z);  //打印汉诺塔的移动 
void MoveHanoi(int x, Point Out, Point In);  //移动汉诺塔 
void MovePrint(int n,char x,char y);  //打印移动汉诺塔的过程 

int main()
{
	int m;
	printf("Pease input the number(1~100) of disks on X:");
	scanf("%d",&m);
	//判断输入的数字是否在1~100之间 
	while(m<1||m>100)
	{
		printf("please enter a number that matches its conditon:");
		scanf("%d",&m);
	}
	Point X,Y,Z;//定义三个栈指针，分别代表三个塔座 
	//为每个栈指针分配空间，并进行初始化
	X = (qhanoi *)malloc(sizeof(qhanoi));
	Initiateqs(X);
	X->name = 'X';
	
	Y = (qhanoi *)malloc(sizeof(qhanoi));
	Initiateqs(Y);
	Y->name = 'Y';
	
	Z = (qhanoi *)malloc(sizeof(qhanoi));
	Initiateqs(Z);
	Z->name = 'Z';
	
	PushStack(X, m);//为第一个栈存入相应的数据，即把所有盘子先放在X塔座 
	printf("The step to move %d disks:\n",m);
	GotoHanoi(m, X, Y, Z);
	HanoiPrint(m, X->name,Y->name,Z->name);
}

//初始化栈
void Initiateqs(Point G) //G为参数 
{
	G->top = 0;
}

//入栈
int PushStack(Point L,int n)
{
	L->stack[L->top]=n;
	L->top++;
}

//出栈
int PopStack(Point L,int m)
{

	m=L->stack[L->top];
	L->top--;
}

//移动汉诺塔 
void MoveHanoi(int x, Point Out, Point In)
{
	PopStack(Out, x);
	PushStack(In,x);
}

//打印移动过程函数
int k=1;
void MovePrint(int n,char x,char y)
{
	printf("%5d:  Move NO.%d from %c to %c.\n", k, n, x, y);
	k++;
}

//汉诺塔开始执行移动 
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

//递归打印移动过程函数
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
