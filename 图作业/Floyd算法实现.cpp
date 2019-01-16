#include <stdio.h> 
#include <stdlib.h> 
#define numV 3
#define MAX 32768
//��MAX����Ϊ����� 

typedef struct       //�ڽӾ���洢�ṹ
{ 
	int edges[numV][numV]; 
	int Vertex, Edge;//�ֱ��ʾͼ�Ķ���ͱߵĸ��� 
}MGraph;


//�������� 
MGraph *CreateMgraph(); //ʹ���ڽӾ��󴴽�����ͼ 
void Floyd(MGraph *mgraph);//ʵ���㷨���������·�� 
void Ppath(int path[][numV], int i, int j);//ʹ�õݹ��˼�룬�����·�������ĸ������������ 
void Dispath(int A[][numV], int path[][numV], int n);//���γɵ����·�������ж���� 
  
int main() 
{ 
	MGraph *mgraph; 
  
	printf("The graph is:\n"); 
	mgraph=CreateMgraph(); 
	printf("The shortest path between is:\n"); 
	Floyd(mgraph); 
   
	return 0; 
} 
  
MGraph *CreateMgraph() 
{ 
	int i,j; 
	int e=0;//�Ա߽��м��� 
	MGraph *mgraph=(MGraph *)malloc(sizeof(MGraph)); 
	//Ϊ�����������ppt��ͼ��Ϊ׼ֱ��������� 
	int matrix[numV][numV]=  
	{
		{0, 4, 11}, 
		{6, 0, 2}, 
    	{3, MAX, 0}
	};
	//������ֵ���ڽӾ��� 
	for(i=0;i<numV;i++) 
	{ 
		for(j=0;j<numV;j++) 
		{ 
			mgraph->edges[i][j]=matrix[i][j]; 
			if(matrix[i][j]!=0 && matrix[i][j]!=MAX) e++; 
		} 
  	} 
	mgraph->Vertex = numV; 
	mgraph->Edge = e; 
  
	printf("Vertexes=%d\nEdges=%d\n",mgraph->Vertex,mgraph->Edge); 
	for(i=0;i<numV;i++) 
	{ 
		for(j=0;j<numV;j++) 
		{ 
			if(mgraph->edges[i][j] != MAX) printf("%3d",mgraph->edges[i][j]); 
			else printf("%3c",'&'); 
		} 
	printf("\n"); 
	} 
  
	return mgraph; 
} 
  
void Floyd(MGraph *mgraph) 
{ 
	int A[numV][numV], path[numV][numV]; 
	int i, j, k; 
  
	for(i=0;i<mgraph->Vertex;i++) 
	{ 
		for(j=0;j<mgraph->Vertex;j++) 
		{ 
			A[i][j]=mgraph->edges[i][j]; 
			path[i][j]=-1; 
		} 
	} 
  
	for(k=0; k<mgraph->Vertex; k++) 
	{ 
		for(i=0; i<mgraph->Vertex; i++) 
		{ 
			for(j=0; j<mgraph->Vertex; j++) 
			{ 
				if(A[i][k]!=MAX && A[k][j]!=MAX && A[i][j]>A[i][k]+A[k][j]) 
				//���A(i,j)A(i,k) + A(k,j)>A(i,k) + A(k,j)�Ƿ����,��������������·�� 
				{ 
					A[i][j] = A[i][k]+A[k][j]; 
					path[i][j] = k; 
				} 
			} 
		} 
	} 
  
	Dispath(A, path, mgraph->Vertex); 
} 
  
void Ppath(int path[][numV], int i, int j) //��������·���ϵĶ��� 
{ 
	int k; 
  
	k = path[i][j]; 
	if(k==-1) return; 
	Ppath(path, i, k); 
	printf("%d,", k); 
	Ppath(path, k, j); 
} 

void Dispath(int A[][numV], int path[][numV], int n)
{ 
	int i, j; 
	for(i=0; i<n; i++) 
	{ 
		for(j=0; j<n; j++) 
		{
			if(A[i][j]==MAX) printf("%d-%d have no path", i, j);//�ж�������Ƿ���·���ɴ� 
			else
			{
				printf("Vertex%d To Vertex%d Is %d  ***the path is ", i, j, A[i][j]); 
				printf("%d,", i); 
				Ppath(path, i, j); 
				printf("%d\n", j); 	
			} 
		} 
	} 
}
