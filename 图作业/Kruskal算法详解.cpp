//来源https://blog.csdn.net/ppalive_/article/details/47761015 
#include <stdio.h>
#include <stdlib.h>
 
#define MAXEDGE 10
#define MAXVEX 6
 
//数组表示图
typedef struct{
	int v1;
	int v2;
	int weight;
}Edge;


typedef struct mgraph
{
	int numVertexes;
	int numEdges;
	int *vex;
	Edge *edges;
}MGraph;
 
//函数申明 
int Find(int *parent,int f);//
int IsCompleted(int *parent);//判断是否已生成生成树
void MiniSpanTree_Kruskal(MGraph *G);// 

int main()  
{  
    MGraph *G=(struct mgraph*)malloc(sizeof(struct mgraph));  
    int i,j;  
    int t=0;  
    G->numVertexes=7;
	G->numEdges=9;
    G->vex=(int*)malloc(sizeof(int)*G->numVertexes);  
    if(!G->vex) return 0;  
    for(i=0;i<G->numVertexes;++i)  //一维数组(图中各结点编号)初始化{0,1,2,3,4,5}  
        G->vex[i]=i;  
    G->edges=(Edge*)malloc(sizeof(Edge)*MAXEDGE);
	if(!G->edges)  return 0;
	//简单起见，数组(按边的权值从小到大排序)直接输入
	G->edges[0].v1=0; G->edges[0].v2=5; G->edges[0].weight=10;
	G->edges[1].v1=2; G->edges[1].v2=3; G->edges[1].weight=12;
	G->edges[2].v1=1; G->edges[2].v2=6; G->edges[2].weight=14;
	G->edges[3].v1=1; G->edges[3].v2=2; G->edges[3].weight=16;
	G->edges[4].v1=6; G->edges[4].v2=3; G->edges[4].weight=18;
	G->edges[5].v1=3; G->edges[5].v2=4; G->edges[5].weight=22;
	G->edges[6].v1=4; G->edges[6].v2=6; G->edges[6].weight=24;
	G->edges[7].v1=4; G->edges[7].v2=5; G->edges[7].weight=25;
	G->edges[8].v1=0; G->edges[8].v2=1; G->edges[8].weight=28;
  
    MiniSpanTree_Kruskal(G);
    return 0;
}


int Find(int *parent,int f)
{
	while(parent[f]!=-1) //结点f与parent[f]是否连接(或者间接即多跳连接)着(在边子集中)同一个结点
		f=parent[f];
	return f;
}
 
int IsCompleted(int *parent)
{
	int i;
	int n=0;
	for(i=0;i<MAXVEX;++i)
	{
		if(parent[i]!=-1)
			++n;
	}
	if(n==MAXVEX-1)  //最小生成树的特点是n各节点有n-1条边
		return 1;
	else
		return 0;
}
 
void MiniSpanTree_Kruskal(MGraph *G)
{
	int i,n,m;
	int parent[MAXVEX];  //判断边与边之间是否形成环路,元素值parent[i]非0时表示结点i与parent[i]之间的边已确定为生成树的某一条边
 
	for(i=0;i<G->numVertexes;++i)
		parent[i]=-1;
		//parent[i]=0;
 
	for(i=0;i<G->numEdges;++i)
	{
		n=Find(parent,G->edges[i].v1);
		m=Find(parent,G->edges[i].v2);
 
		//if(n!=m && parent[n]!=m)
		if(n!=m) //判断结点edges[i].a与edges[i].b是否连接(或者间接即多跳连接)着(在边子集中)同一个结点，
		//假设结点edges[i].a与结点edges[i].b都跟量外一个结点X相连(或者间接相连)，如若不加判断，则三个结点会形成回路
		{
			parent[n]=m;
			printf("(%d,%d)  %d\n",G->edges[i].v1,G->edges[i].v2,G->edges[i].weight);
		}
		//判断是否已生成生成树
		if(IsCompleted(parent))
			break;
	}
}

