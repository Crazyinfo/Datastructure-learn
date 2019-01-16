#include<stdio.h>
#define PASS 1
#define MAX 20
#define MARKED -1
 
typedef struct Closedge
{
	int adjvex;
	int lowcost;
}closedge[MAX];

typedef struct ArcCell
{
	int adj;//表示顶点关系，用权值表示。32768时表示不相连 
}AdjMatrix[MAX][MAX];

typedef struct
{
	int vexs[MAX];//顶点向量 
	AdjMatrix edges;//邻接矩阵
	int numVertexes, numEdges;//图当前顶点数和弧数 
}MGraph;

//函数申明
int LocateVex(MGraph G, int v);//返回顶点所在位置 
MGraph CreateUDN();//邻接矩阵构造无向图 
int PrintMGraph(MGraph G);//打印邻接矩阵 
int Minimum(closedge closedge, MGraph G);//求辅助函数边权值最小的边序号 
void MiniSpanTree_Prime(MGraph G, int index);//构造无向图最小生成树 


int main()
{
	MGraph G;
	G = CreateUDN();
	PrintMGraph(G);
	printf("The Edges of the Minimum Spanning Tree is followed:\n");
	MiniSpanTree_Prime(G, G.vexs[0]); 
} 
 
int LocateVex(MGraph G, int v)
{
	int i;
	for(i=0; v!=G.vexs[i] && i<G.numVertexes; ++i);
	if(i>=G.numVertexes)
		return MARKED;
	return i;
}

//邻接矩阵创建无向图 
MGraph CreateUDN()
{
	MGraph G;
	int m, i, j;
	printf("Enter the number of Vertexes:");
	scanf("%d", &G.numVertexes);
	printf("Enter the number of Edges:");
	scanf("%d", &G.numEdges);	
	for(m=0; m<G.numVertexes; ++m)
	{
		printf("Enter the index of Vertex %d:", m+1);//输入顶点的下标 
		scanf("%d", &G.vexs[m]);//构造顶点向量 
	}
	for(i=0; i<G.numVertexes; ++i)//初始化邻接矩阵 
	{
		for(j=0; j<G.numVertexes; ++j)
		{
			G.edges[i][j].adj = 32768;
		}
	}
	int v1, v2;
	int weight, k;
	for(k=0; k<G.numEdges; ++k)//构造邻接矩阵 
	{
		printf("Enter the Vertex1 attaching the Edge%d:", k+1);//一条边连接的顶点下标 
		scanf("%d", &v1);
		printf("Enter the Vertex2 attaching the Edge%d:", k+1);//一条边连接的顶点下标 
		scanf("%d", &v2);
		printf("Enter the weight of Edge%d:", k+1);//该边权值的记录 
		scanf("%d", &weight); 
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);//确定v1、v2在G中的位置 
		G.edges[i][j].adj = weight;//弧的权值 
		G.edges[j][i].adj = G.edges[i][j].adj;//无向图无论从哪点出发两点间的权值相等 
	}
	return G;
}

int PrintMGraph(MGraph G)//打印邻接矩阵 
{
	int i,j;
	printf("  ");
	for(i=0; i<G.numVertexes; ++i)
		printf("%6d", G.vexs[i]);
	printf("\n");
	for(i=0; i<G.numVertexes; ++i)
	{
		printf("%d:", G.vexs[i]);
		for(j=0; j<G.numVertexes; ++j)
		{
			printf("%6d",G.edges[i][j].adj);
		}
		printf("|\n");
	}
	return 0;
}

int Minimum(closedge closedge, MGraph G)
{
	int min, i, k;
	for(i=0; i<G.numVertexes; i++)
	{
		if((closedge[i].lowcost!=0) && (closedge[i].lowcost!=32768))
		{
			min = closedge[i].lowcost;
			k = i;
			break;
		}
	}
	for(i=0; i<G.numVertexes; i++)
	{
		if((closedge[i].lowcost!=0) && (closedge[i].lowcost<min))
		{
			min = closedge[i].lowcost;
			k = i;
		}
	}
	return k;
}

void MiniSpanTree_Prime(MGraph G, int index)//index为出发点 
{
	int i, j, k;
	closedge closedge;
	k = LocateVex(G, index);
	for(j=0; j<G.numVertexes; ++j)//辅助函数初始化 
	{
		if(j!=k)
		{
			closedge[j].adjvex = index;
			closedge[j].lowcost = G.edges[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;
	for(i=1; i<G.numVertexes; ++i)
	{
		k = Minimum(closedge, G);
		printf("(%d, %d)\n", closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;
		for(j=0; j<G.numVertexes; ++j)
		{
			if(G.edges[k][j].adj<closedge[j].lowcost)
			{
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.edges[k][j].adj;
			}
		}
	}
	printf("\n");
}
