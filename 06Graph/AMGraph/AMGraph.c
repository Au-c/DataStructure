/*
* 章节六·图
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

#define MVNum 100 // 最大顶点数
#define INF 32767 // 无穷数
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))
typedef char VexTexType; // 假设顶点数据类型为字符型
typedef int EdgeType; // 假设边的数据类型为整型
typedef int ArcType; // 假设边上的权值为整型

/*邻接矩阵*/
typedef struct {
	VexTexType Vex[MVNum]; // 顶点集
	EdgeType Edge[MVNum][MVNum]; // 边集邻接矩阵
	int vexnum; // 顶点数
	int edgenum; // 边数
}Graph;

/*边*/
typedef struct edge{
	VexTexType start; // 边的始点
	VexTexType end; // 边的终点
	ArcType lowcost; // 边上的权值
}Edge;
/*
 * tools: 读取一个输入字符
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
* 获取顶点在顶点集中的位置
*/
static LocateVex(Graph* G, char ch)
{
	for (int i = 0; i < G->vexnum; i++) {
		return ch == G->Vex[i] ? i : -1;
	}
}

/*
*创建无向图·用户输入
*/
Graph* CreateUDN(Graph* G)
{
	char start, end;
	int v = 0, e = 0;
	int i, j, weight = 0, p1, p2;
	// 输入"顶点数"和"边数"
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
	// 初始化边集邻接矩阵
	for (i = 0; i < G->vexnum; i++) {
		for (int j = 0; j < G->vexnum; j++) {
			G->Edge[i][j] = i == j ? 0 : INF;
		}
	}
	// 往邻接矩阵填入信息
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
* 创建无向图·示例图
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
	// 初始化顶点集
	for (i = 0; i < G->vexnum; i++)
		G->Vex[i] = Vex[i];

	// 初始化边集
	for (i = 0; i < G->vexnum; i++)
		for (j = 0; j < G->vexnum; j++) {
			G->Edge[i][j] = Edge[i][j];
			// 统计边的数量
			if (i != j && G->Edge[i][j] != INF)
				G->edgenum++;
		}
	G->edgenum /= 2;

	return G;
}

/*
* 最小生成树·Prim 算法
*/
void Prim(Graph* G, int v0)
{
	// 构建辅助数组
	bool isJoin[MVNum] = { false }; // 记录该顶点是否加入了U集
	int lowCast[MVNum] = { 0 }; // 存放顶点如果加入到U集的最小权值
	VexTexType u[MVNum] = { 0 }; // U集, 收纳已经加入最小生成树中的顶点
	int i, w;
	int miniCost = 0; // 最小代价之合
	int count = 0;// 工具中间数,用来记录往最终素组(U集)中已经填入了几个顶点

	// 初始化辅助数组
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
		// 求下一个顶点
		for (w = 0; w < G->vexnum; w++) {
			if (!isJoin[w] && lowCast[w] < minDis) {
				minDis = lowCast[w];
				nextVex = w;
			}
		}
		isJoin[nextVex] = true;
		u[count++] = G->Vex[nextVex];
		miniCost += minDis;
		// 更新 lowCast
		for (w = 0; w < G->vexnum; w++) {
			if (!isJoin[w] && G->Edge[nextVex][w] < lowCast[w]) {
				lowCast[w] = G->Edge[nextVex][w];
			}
		}
	}
	// 打印
	printf("\n******************** Prim ********************\n");
	printf("\n源点：%c\n", G->Vex[v0]);
	printf("最小生成树为:  ");
	for (i = 0; i < G->vexnum; i++) {
		printf("%c", u[i]);
	}
	printf("\n最小代价为:  %d", miniCost);
}

/*
* 获取图的所有边
* return: 一个包含所有边的数组
*/
Edge* getEdges(Graph* G)
{
	int i, j;
	int index = 0;
	Edge *edges;
	edges = (Edge*)malloc(G->edgenum * sizeof(Edge));
	// 取邻接矩阵上三角区
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
* 将边按照权值从小到大排列
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
* 最小生成树·Kruskal 算法
* 有时间补上
*/

/*
* 最短路径·Dijkstra 算法
*/
void Dijkstra(Graph* G, int v0)
{
	// 创建辅助数组
	bool final[MVNum] = { false };
	int dis[MVNum] = { 0 };
	int path[MVNum] = { 0 };
	int i, w;
	// 辅助数组初始化
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
	printf("\n源点：%c\n", G->Vex[v0]);
	for (i = 0; i < G->vexnum; i++) {
		printf("%c 到 %c 的最短路径为: %d\n", G->Vex[v0], G->Vex[i], dis[i]);
	}
}

/*
* 最短路径·Floyd 算法
*/
void Floyd(Graph* G)
{
	int dis[MVNum][MVNum] = { 0 };
	int path[MVNum][MVNum] = { 0 };
	int i, j, k;
	// 初始化辅助数组
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
	// 打印结果
	printf("\n******************** Floyd ********************\n");
	printf("\ndis表如下: \n");
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			printf("%2d  ", dis[i][j]);
		}
		printf("\n");
	}
	printf("\npath表如下: \n");
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

	// 创建无向图·用户输入
	// G = CreateUDN(G);
	// 创建无向图·示例图
	G = createUDN_Display();
	Prim(G, 5);
	Floyd(G);
	Dijkstra(G, 2);
}