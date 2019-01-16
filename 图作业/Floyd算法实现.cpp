#include <stdio.h> 
#include <stdlib.h> 
#define numV 3
#define MAX 32768
//将MAX近似为无穷大 

typedef struct       //邻接矩阵存储结构
{ 
	int edges[numV][numV]; 
	int Vertex, Edge;//分别表示图的顶点和边的个数 
}MGraph;


//函数申明 
MGraph *CreateMgraph(); //使用邻接矩阵创建无向图 
void Floyd(MGraph *mgraph);//实现算法，计算最短路径 
void Ppath(int path[][numV], int i, int j);//使用递归的思想，对最短路径经过的各顶点完整输出 
void Dispath(int A[][numV], int path[][numV], int n);//对形成的最短路径进行判断输出 
  
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
	int e=0;//对边进行计数 
	MGraph *mgraph=(MGraph *)malloc(sizeof(MGraph)); 
	//为方便起见，以ppt上图形为准直接输入矩阵 
	int matrix[numV][numV]=  
	{
		{0, 4, 11}, 
		{6, 0, 2}, 
    	{3, MAX, 0}
	};
	//将矩阵赋值给邻接矩阵 
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
				//检查A(i,j)A(i,k) + A(k,j)>A(i,k) + A(k,j)是否成立,若成立则更新最短路径 
				{ 
					A[i][j] = A[i][k]+A[k][j]; 
					path[i][j] = k; 
				} 
			} 
		} 
	} 
  
	Dispath(A, path, mgraph->Vertex); 
} 
  
void Ppath(int path[][numV], int i, int j) //输出在最短路径上的顶点 
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
			if(A[i][j]==MAX) printf("%d-%d have no path", i, j);//判断两点间是否无路径可达 
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
