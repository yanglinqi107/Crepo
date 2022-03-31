#pragma once
#define Maxsize 50
#define MAX_VERTEX_NUM 50
#define INFINITE 10000000
#define OK 1
#define ERROR 0


//定义Vex结构体，储存图的顶点信息
struct Vex
{
	int num = 0;	//景点编号
	char name[20] = { '\0' };  //景点名字
	char desc[1024] = { '\0' }; //景点介绍
};

//定义Edge结构体，储存图的边的信息
struct Edge
{
	int vex1, vex2;	//边的两个顶点
	int weight;		//权值
};

struct Graph
{
	int m_aAdjMatrix[Maxsize][Maxsize] = { 0 };	//邻接矩阵(不空00)
	Vex m_aVexs[Maxsize];			//顶点数组（0位不空）
	int m_nVexNum = 0;					//顶点个数
};

typedef struct Path
{
	int vexs[MAX_VERTEX_NUM] = { 0 };
	//保存一条路径
	Path* next;//下一条路径
}*PathList;

void Init(void);	//初始化图结构

int InsertVex(Graph& graph, Vex sVex);	//将顶点添加到顶点数组中

int InserEdge(Graph& graph, Edge sEdge);	//将边保存到邻接数组

Vex GetVex(Graph graph, int nVex);		//查询指定顶点信息

int FindEdge(Graph graph, int nVex, Edge aEdge[]);	//查询与指定顶点相连的边

void DFS(Graph graph, int nVex, bool bVisited[], int& nIndex, PathList& pList);	//深度优先搜索算法遍历图

void DFSTraverse(Graph graph, int nVex, PathList& pList);	//通过调用DFS()函数，得到深度优先搜索遍历结果

int FindShortPath(Graph graph, int nVexStart, int nVexEnd, Edge aPath[]);//通过Dijkstra算法求得v1到v2的最短路径

int FindMinTree(Graph graph, Edge aPath[]);	//通过Prim算法构建最小生成树
