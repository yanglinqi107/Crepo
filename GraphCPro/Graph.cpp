#include<iostream>
#include"Graph.h"

using namespace std;

void Init(void)	//初始化图结构
{

}

int InsertVex(Graph& graph, Vex sVex)	//将顶点添加到顶点数组中
{
	graph.m_aVexs[graph.m_nVexNum++] = sVex;
	//cout << graph.m_aVexs[graph.m_nVexNum - 1].num << graph.m_aVexs[graph.m_nVexNum - 1].name << graph.m_aVexs[graph.m_nVexNum - 1].desc << endl;
	return OK;
}

int InserEdge(Graph& graph, Edge sEdge)	//将边保存到邻接数组
{
	graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	//cout << graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] << endl;
	return OK;
}

Vex GetVex(Graph graph, int nVex)		//查询指定顶点信息
{
	return graph.m_aVexs[nVex];
}

int FindEdge(Graph graph, int nVex, Edge aEdge[])	//查询与指定顶点相连的边
{
	for (int i = 0; i < graph.m_nVexNum; ++i)
	{
		if (graph.m_aAdjMatrix[nVex][i] != 0)
			cout << graph.m_aVexs[nVex].name << "->" << graph.m_aVexs[i].name << " " << graph.m_aAdjMatrix[nVex][i] << endl;
	}
	return OK;
}

void DFS(Graph graph, int nVex, bool bVisited[], int& nIndex, PathList& pList)	//深度优先搜索算法遍历图
{
	/*PathList pNode = NULL;
	pNode = (PathList)malloc(sizeof(Path));
	pList = pNode;*/
	bVisited[nVex] = true;//改为已访问
	pList->vexs[nIndex++] = nVex;//访问顶点nVex
	if (nIndex >= graph.m_nVexNum)
	{
		pList->next = (PathList)malloc(sizeof(Path));
		//p->next = NULL;
		for (int i = 0; i < graph.m_nVexNum ; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		//pNode->next = pRail;
		pList = pList->next;
		pList->next = NULL;
	}
	else
	{
		for (int w = 0; w < graph.m_nVexNum; w++)	//搜索v的所有邻接点
		{
			if (graph.m_aAdjMatrix[nVex][w] != 0 && !bVisited[w])
			{
				//cout << w;
				DFS(graph, w, bVisited, nIndex, pList);	//递归调用DFS
				//cout << w;
				bVisited[w] = false;	//回溯，恢复状态
				nIndex--;//回溯
			}
		}
	}
}

void DFSTraverse(Graph graph, int nVex, PathList& pList)	//通过调用DFS()函数，得到深度优先搜索遍历结果
{
	int nIndex = 0;						//记录遍历的深度
	bool aVisited[MAX_VERTEX_NUM] = { false };	//用来记录某个顶点是否被遍历过
	DFS(graph, nVex, aVisited, nIndex, pList);
}

int FindShortPath(Graph graph, int nVexStart, int nVexEnd, Edge aPath[])  //通过Dijkstra算法求得v1到v2的最短路径
{
	int dist[Maxsize];			//储存最短距离
	fill(dist, dist + Maxsize, INFINITE);	//赋初值为无穷

	int path[Maxsize];			//保存路径
	fill(path, path + Maxsize, -1);		

	int S[Maxsize] = { 0 };		

	int smallnum = nVexStart;
	int i;
	for (i = 0; i < graph.m_nVexNum; i++)
	{
		if (graph.m_aAdjMatrix[nVexStart][i] != 0)
		{
			/*if (graph.m_aAdjMatrix[nVexStart][i] < small)
			{
				small = graph.m_aAdjMatrix[nVexStart][i];
				smallnum = i;
			}*/
			dist[i] = graph.m_aAdjMatrix[nVexStart][i];
			path[i] = nVexStart;
		}
	}
	//dist[nVexStart] = 0;
	S[nVexStart] = 1;
	

	for (i = 0; i < graph.m_nVexNum; i++)
	{
		int small = INFINITE;
		for (int j = 0; j < graph.m_nVexNum; ++j)
		{
			if (!S[j] && dist[j] < small)
			{
				small = dist[j];
				smallnum = j;
			}
		}
		S[smallnum] = 1;
		int w;
		for (w = 0; w < graph.m_nVexNum; w++)
		{
			if (!S[w] && graph.m_aAdjMatrix[smallnum][w] != 0 &&
				dist[smallnum] + graph.m_aAdjMatrix[smallnum][w] < dist[w])
			{
				dist[w] = graph.m_aAdjMatrix[smallnum][w] + dist[smallnum];
				path[w] = smallnum;
			}
		}
	}

	int vpath[Maxsize];
	fill(vpath, vpath + Maxsize, -1);
	int pathnum = 0;
	//vpath[0] = nVexEnd;
	i = nVexEnd;
	while (i != nVexStart)
	{
		//cout << i;
		vpath[pathnum++] = i;
		i = path[i];
	}
	vpath[pathnum++] = nVexStart;
	//cout << nVexStart;
	i = 0;
	//int num = pathnum;
	aPath[0].vex1 = vpath[--pathnum];
	for (; pathnum > 1; pathnum--)
	{
		aPath[i].vex2 = vpath[pathnum - 1];
		aPath[i].weight = graph.m_aAdjMatrix[aPath[i].vex1][aPath[i].vex2];
		aPath[++i].vex1 = vpath[pathnum - 1];
	}
	aPath[i].vex2 = nVexEnd;
	aPath[i].weight = graph.m_aAdjMatrix[aPath[i].vex1][aPath[i].vex2];

	return i + 1;
}

int FindMinTree(Graph graph, Edge aPath[])	//通过Prim算法构建最小生成树
{
	int path[Maxsize];	//保存最小生成树的路径
	int num = 0;	//已添加的顶点数量
	fill(path, path + Maxsize, -1);
	bool isAdd[Maxsize] = { false };

	int pnum = 0;	//记录路径的数量
	path[num++] = 0;
	isAdd[0] = true;
	int small = INFINITE;		//记录生成过程中的最小边
	int lnode, rnode;					//存放过程中的顶点

	while (num < graph.m_nVexNum) 
	{
		small = INFINITE;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < graph.m_nVexNum; j++)
			{
				if (graph.m_aAdjMatrix[path[i]][j] != 0 &&
					graph.m_aAdjMatrix[path[i]][j] < small && !isAdd[j])
				{
					lnode = path[i];
					rnode = j;
					small = graph.m_aAdjMatrix[path[i]][j];
				}
			}
		}
		path[num++] = rnode;
		isAdd[rnode] = true;
		aPath[pnum].vex1 = lnode;
		aPath[pnum].vex2 = rnode;
		aPath[pnum].weight = graph.m_aAdjMatrix[lnode][rnode];
		pnum++;
	}
	return pnum;
}



