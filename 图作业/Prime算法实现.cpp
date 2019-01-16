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
	int adj;//��ʾ�����ϵ����Ȩֵ��ʾ��32768ʱ��ʾ������ 
}AdjMatrix[MAX][MAX];

typedef struct
{
	int vexs[MAX];//�������� 
	AdjMatrix edges;//�ڽӾ���
	int numVertexes, numEdges;//ͼ��ǰ�������ͻ��� 
}MGraph;

//��������
int LocateVex(MGraph G, int v);//���ض�������λ�� 
MGraph CreateUDN();//�ڽӾ���������ͼ 
int PrintMGraph(MGraph G);//��ӡ�ڽӾ��� 
int Minimum(closedge closedge, MGraph G);//����������Ȩֵ��С�ı���� 
void MiniSpanTree_Prime(MGraph G, int index);//��������ͼ��С������ 


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

//�ڽӾ��󴴽�����ͼ 
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
		printf("Enter the index of Vertex %d:", m+1);//���붥����±� 
		scanf("%d", &G.vexs[m]);//���춥������ 
	}
	for(i=0; i<G.numVertexes; ++i)//��ʼ���ڽӾ��� 
	{
		for(j=0; j<G.numVertexes; ++j)
		{
			G.edges[i][j].adj = 32768;
		}
	}
	int v1, v2;
	int weight, k;
	for(k=0; k<G.numEdges; ++k)//�����ڽӾ��� 
	{
		printf("Enter the Vertex1 attaching the Edge%d:", k+1);//һ�������ӵĶ����±� 
		scanf("%d", &v1);
		printf("Enter the Vertex2 attaching the Edge%d:", k+1);//һ�������ӵĶ����±� 
		scanf("%d", &v2);
		printf("Enter the weight of Edge%d:", k+1);//�ñ�Ȩֵ�ļ�¼ 
		scanf("%d", &weight); 
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);//ȷ��v1��v2��G�е�λ�� 
		G.edges[i][j].adj = weight;//����Ȩֵ 
		G.edges[j][i].adj = G.edges[i][j].adj;//����ͼ���۴��ĵ����������Ȩֵ��� 
	}
	return G;
}

int PrintMGraph(MGraph G)//��ӡ�ڽӾ��� 
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

void MiniSpanTree_Prime(MGraph G, int index)//indexΪ������ 
{
	int i, j, k;
	closedge closedge;
	k = LocateVex(G, index);
	for(j=0; j<G.numVertexes; ++j)//����������ʼ�� 
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
