/*
* �½�����ͼ
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

#define MVNum 100 // ��󶥵���
#define INF 32767 // ������
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))
typedef char VexTexType; // ���趥����������Ϊ�ַ���
typedef int EdgeType; // ����ߵ���������Ϊ����
typedef int ArcType; // ������ϵ�ȨֵΪ����

/*�ڽӾ���*/
typedef struct {
	VexTexType Vex[MVNum]; // ���㼯
	EdgeType Edge[MVNum][MVNum]; // �߼��ڽӾ���
	int vexnum; // ������
	int edgenum; // ����
}Graph;

/*��*/
typedef struct edge{
	VexTexType start; // �ߵ�ʼ��
	VexTexType end; // �ߵ��յ�
	ArcType lowcost; // ���ϵ�Ȩֵ
}Edge;
/*
 * tools: ��ȡһ�������ַ�
 */
static char read_char()
{
	char ch;
	do {
		ch = getchar();
	} while (!isLetter(ch));
	return ch;
}

/*
* ��ȡ�����ڶ��㼯�е�λ��
*/
static LocateVex(Graph* G, char ch)
{
	for (int i = 0; i < G->vexnum; i++) {
		return ch == G->Vex[i] ? i : -1;
	}
}

/*
*��������ͼ���û�����
*/
Graph* CreateUDN(Graph* G)
{
	char start, end;
	int v = 0, e = 0;
	int i, j, weight = 0, p1, p2;
	// ����"������"��"����"
	printf("input the vertex number: ");
	// scanf("%d", &v);
	printf("input the edge number: ");
	// scanf("%d", &e);
	if (v < 1 || e < 1 || e > v * (v - 1)) {
		printf("input error: invalid parameters!\n");
		return NULL;
	}
	if ((G = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(G, 0, sizeof(Graph));
	G->vexnum = v;
	G->edgenum = e;
	for (i = 0; i < G->vexnum; i++) {
		printf("vertex_%d: ", i);
		G->Vex[i] = read_char();
	}
	// ��ʼ���߼��ڽӾ���
	for (i = 0; i < G->vexnum; i++) {
		for (int j = 0; j < G->vexnum; j++) {
			G->Edge[i][j] = i == j ? 0 : INF;
		}
	}
	// ���ڽӾ���������Ϣ
	for (i = 0; i < G->vexnum; i++) {
		printf("edge_%d: ", i);
		start = read_char();
		end = read_char();
		// scanf("%d", &weight);
		p1 = LocateVex(G, start);
		p2 = LocateVex(G, end);
		if (p1 == -1 || p2 == -1) {
			printf("input error: invalid edge!\n");
			free(G);
			return NULL;
		}
		G->Edge[p1][p2] = weight;
		G->Edge[p2][p1] = weight;
	}
	return G;
}

/*
* ��������ͼ��ʾ��ͼ
*/
Graph* createUDN_Display()
{
	char Vex[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	int Edge[][9] = {
		/*A*//*B*//*C*//*D*//*E*//*F*//*G*/
		/*A*/ {   0,  12, INF, INF, INF,  16,  14},
		/*B*/ {  12,   0,  10, INF, INF,   7, INF},
		/*C*/ { INF,  10,   0,   3,   5,   6, INF},
		/*D*/ { INF, INF,   3,   0,   4, INF, INF},
		/*E*/ { INF, INF,   5,   4,   0,   2,   8},
		/*F*/ {  16,   7,   6, INF,   2,   0,   9},
		/*G*/ {  14, INF, INF, INF,   8,   9,   0} };
	int vlen = LENGTH(Vex);
	int i, j;
	Graph* G;
	if ((G = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(G, 0, sizeof(Graph));
	G->vexnum = vlen;
	// ��ʼ�����㼯
	for (i = 0; i < G->vexnum; i++)
		G->Vex[i] = Vex[i];

	// ��ʼ���߼�
	for (i = 0; i < G->vexnum; i++)
		for (j = 0; j < G->vexnum; j++) {
			G->Edge[i][j] = Edge[i][j];
			// ͳ�Ʊߵ�����
			if (i != j && G->Edge[i][j] != INF)
				G->edgenum++;
		}
	G->edgenum /= 2;

	return G;
}

/*
* ��С��������Prim �㷨
*/
void Prim(Graph* G, int v0)
{
	// ������������
	bool isJoin[MVNum] = { false }; // ��¼�ö����Ƿ������U��
	int lowCast[MVNum] = { 0 }; // ��Ŷ���������뵽U������СȨֵ
	VexTexType u[MVNum] = { 0 }; // U��, �����Ѿ�������С�������еĶ���
	int i, w;
	int miniCost = 0; // ��С����֮��
	int count = 0;// �����м���,������¼����������(U��)���Ѿ������˼�������

	// ��ʼ����������
	for (i = 0; i < G->vexnum; i++) {
		isJoin[i] = false;
		lowCast[i] = G->Edge[v0][i];
	}
	isJoin[v0] = true;
	u[0] = G->Vex[v0];
	count++;

	// Prim
	for (i = 0; i < G->vexnum; i++) {
		if (i == v0) {
			continue;
		}
		int minDis = INF;
		int nextVex;
		// ����һ������
		for (w = 0; w < G->vexnum; w++) {
			if (!isJoin[w] && lowCast[w] < minDis) {
				minDis = lowCast[w];
				nextVex = w;
			}
		}
		isJoin[nextVex] = true;
		u[count++] = G->Vex[nextVex];
		miniCost += minDis;
		// ���� lowCast
		for (w = 0; w < G->vexnum; w++) {
			if (!isJoin[w] && G->Edge[nextVex][w] < lowCast[w]) {
				lowCast[w] = G->Edge[nextVex][w];
			}
		}
	}
	// ��ӡ
	printf("\n******************** Prim ********************\n");
	printf("\nԴ�㣺%c\n", G->Vex[v0]);
	printf("��С������Ϊ:  ");
	for (i = 0; i < G->vexnum; i++) {
		printf("%c", u[i]);
	}
	printf("\n��С����Ϊ:  %d", miniCost);
}

/*
* ��ȡͼ�����б�
* return: һ���������бߵ�����
*/
Edge* getEdges(Graph* G)
{
	int i, j;
	int index = 0;
	Edge *edges;
	edges = (Edge*)malloc(G->edgenum * sizeof(Edge));
	// ȡ�ڽӾ�����������
	for (i = 0; i < G->edgenum; i++) {
		for (j = i+1; j < G->edgenum; j++) {
			if (G->Edge[i][j] < INF) {
				edges[index].start = G->Edge[i];
				edges[index].end = G->Edge[j];
				edges[index].lowcost = G->Edge[i][j];
				index++;
			}
		}
	}
	return edges;
}

/*
* ���߰���Ȩֵ��С��������
*/
void SortEdge(Edge *edges, int edgenum)
{
	Edge temp;
	for (int i = 0; i < edgenum; i++) {
		if (edges[i].lowcost > edges[i + 1].lowcost) {
			temp = edges[i];
			edges[i] = edges[i + 1];
			edges[i + 1] = temp;
		}
	}
}

/*
* ��С��������Kruskal �㷨
* ��ʱ�䲹��
*/

/*
* ���·����Dijkstra �㷨
*/
void Dijkstra(Graph* G, int v0)
{
	// ������������
	bool final[MVNum] = { false };
	int dis[MVNum] = { 0 };
	int path[MVNum] = { 0 };
	int i, w;
	// ���������ʼ��
	for (i = 0; i < G->vexnum; i++) {
		final[i] = false;
		dis[i] = G->Edge[v0][i];
		path[i] = dis[i] < INF ? v0 : -1;
	}
	final[v0] = true;
	dis[v0] = 0;

	// Dijkstra
	for (i = 1; i < G->vexnum; i++) {
		int minDis = INF;
		int nextVex;

		for (w = 0; w < G->vexnum; w++) {
			if (!final[w] && dis[w] < minDis) {
				minDis = dis[w];
				nextVex = w;
			}
		}
		final[nextVex] = true;

		for (w = 0; w < G->vexnum; w++) {
			if (!final[w] && G->Edge[nextVex][w] + minDis < dis[w]) {
				dis[w] = G->Edge[nextVex][w] + minDis;
				path[w] = nextVex;
			}
		}
	}
	printf("\n******************** Dijkstra ********************\n");
	printf("\nԴ�㣺%c\n", G->Vex[v0]);
	for (i = 0; i < G->vexnum; i++) {
		printf("%c �� %c �����·��Ϊ: %d\n", G->Vex[v0], G->Vex[i], dis[i]);
	}
}

/*
* ���·����Floyd �㷨
*/
void Floyd(Graph* G)
{
	int dis[MVNum][MVNum] = { 0 };
	int path[MVNum][MVNum] = { 0 };
	int i, j, k;
	// ��ʼ����������
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			dis[i][j] = G->Edge[i][j];
			path[i][j] = G->Edge[i][j] < INF ? i : -1;
		}
	}
	// Floyd
	for (k = 0; k < G->vexnum; k++) {
		for (i = 0; i < G->vexnum; i++) {
			for (j = 0; j < G->vexnum; j++) {
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
	// ��ӡ���
	printf("\n******************** Floyd ********************\n");
	printf("\ndis������: \n");
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			printf("%2d  ", dis[i][j]);
		}
		printf("\n");
	}
	printf("\npath������: \n");
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			printf("%2d  ", path[i][j]);
		}
		printf("\n");
	}
}

void main()
{
	Graph* G;

	// ��������ͼ���û�����
	// G = CreateUDN(G);
	// ��������ͼ��ʾ��ͼ
	G = createUDN_Display();
	Prim(G, 5);
	Floyd(G);
	Dijkstra(G, 2);
}