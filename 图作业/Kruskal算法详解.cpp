//��Դhttps://blog.csdn.net/ppalive_/article/details/47761015 
#include <stdio.h>
#include <stdlib.h>
 
#define MAXEDGE 10
#define MAXVEX 6
 
//�����ʾͼ
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
 
//�������� 
int Find(int *parent,int f);//
int IsCompleted(int *parent);//�ж��Ƿ�������������
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
    for(i=0;i<G->numVertexes;++i)  //һά����(ͼ�и������)��ʼ��{0,1,2,3,4,5}  
        G->vex[i]=i;  
    G->edges=(Edge*)malloc(sizeof(Edge)*MAXEDGE);
	if(!G->edges)  return 0;
	//�����������(���ߵ�Ȩֵ��С��������)ֱ������
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
	while(parent[f]!=-1) //���f��parent[f]�Ƿ�����(���߼�Ӽ���������)��(�ڱ��Ӽ���)ͬһ�����
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
	if(n==MAXVEX-1)  //��С���������ص���n���ڵ���n-1����
		return 1;
	else
		return 0;
}
 
void MiniSpanTree_Kruskal(MGraph *G)
{
	int i,n,m;
	int parent[MAXVEX];  //�жϱ����֮���Ƿ��γɻ�·,Ԫ��ֵparent[i]��0ʱ��ʾ���i��parent[i]֮��ı���ȷ��Ϊ��������ĳһ����
 
	for(i=0;i<G->numVertexes;++i)
		parent[i]=-1;
		//parent[i]=0;
 
	for(i=0;i<G->numEdges;++i)
	{
		n=Find(parent,G->edges[i].v1);
		m=Find(parent,G->edges[i].v2);
 
		//if(n!=m && parent[n]!=m)
		if(n!=m) //�жϽ��edges[i].a��edges[i].b�Ƿ�����(���߼�Ӽ���������)��(�ڱ��Ӽ���)ͬһ����㣬
		//������edges[i].a����edges[i].b��������һ�����X����(���߼������)�����������жϣ������������γɻ�·
		{
			parent[n]=m;
			printf("(%d,%d)  %d\n",G->edges[i].v1,G->edges[i].v2,G->edges[i].weight);
		}
		//�ж��Ƿ�������������
		if(IsCompleted(parent))
			break;
	}
}

