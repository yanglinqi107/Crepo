#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include"Tourism.h"
#include"Graph.h"

using namespace std;

//读取文件，创建景区景点图
void CreateGraph(Graph& graph)
{
	cout << endl << "====== 创建景区景点图 ======" << endl;
	Vex vex;
	Edge edge;
	//char num;
	int num;
	ifstream infile("Vex.txt");
	infile >> num;
	//cout << num << endl;
	cout << "顶点数目：" << num << endl;
	cout << "----- 顶点 -----" << endl;

	for (int i = 0; i < num; i++)
	{
		infile >> vex.num;
		infile >> vex.name;
		infile >> vex.desc;
		//cout << vex.num << "\t" << vex.name << "\t" << vex.desc << endl;
		cout << vex.num << "-" << vex.name << endl;
		InsertVex(graph, vex);
	}
	infile.clear();
	infile.close();

	cout << "----- 边 -----" << endl;
	infile.open("Edge.txt");
	while (infile.peek() != EOF)
	{
		infile >> edge.vex1;
		infile >> edge.vex2;
		infile >> edge.weight;
		//cout << edge.vex1 << "\t" << edge.vex2 << "\t" << edge.weight << endl;
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << endl;
		InserEdge(graph, edge);
	}
	infile.clear();
	infile.close();
	
	cout << "====== 景点图生成完毕 ======\n" << endl;

	system("pause");
	system("cls");

	//FILE* fp;

	//fopen_s(&fp, "E:\\Vex.txt", "r");
	//if (!fp)
	//{
	//	cerr << "文件打开失败1！" << endl;
	//	return;
	//}

	////1初始化图
	//Init();
	//while (!feof(fp))
	//{
	//	fread(&num, sizeof(int), 1, fp);	//读取顶点个数
	//	cout << num << endl;
	//}
	////2设置图的顶点
	//for (int i = 0; i < num - 48; i++)
	//{
	//	fread(&vex, sizeof(Vex), 1, fp);
	//	cout << vex.num << "\t" << vex.name << "\t" << vex.desc << endl;
	//	InsertVex(graph, vex);
	//}
	//fclose(fp);

	//fopen_s(&fp, "E:\\Edge.txt", "r");
	//if (!fp)
	//{
	//	cerr << "打开文件失败2！" << endl;
	//	return;
	//}
	////3设置图的边
	//while (!feof(fp))
	//{
	//	fread(&edge, sizeof(Edge), 1, fp);
	//	cout << edge.vex1 << "\t" << edge.vex2 << "\t" << edge.weight << endl;
	//	InserEdge(graph, edge);
	//}
	//fclose(fp);
}

//查询指定景点信息，显示到相邻景点的距离
void GetSpotInfo(Graph graph)
{
	cout << endl << "====== 查询景点信息 ======" << endl;
	if (graph.m_nVexNum == 0) {
		cout << "请先创建图！\n" << endl;
		return;
	}

	int v = 0;		//储存景点编码

	
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	cout << "请输入想要查询的景点编号：";
	cin >> v;

	if (v < 0 || v >= graph.m_nVexNum)
	{
		cout << "输入错误！\n" << endl;
		return;
	}
	Edge* aEdge=NULL;

	//取得指定顶点信息
	Vex vex = GetVex(graph, v);
	cout << vex.name << endl << vex.desc << endl;
	cout << "----- 周边景区 -----" << endl;
	//查询所有与指定顶点相连的边的信息
	FindEdge(graph, v, aEdge);
	cout << endl;

	system("pause");
	system("cls");
}

//调用DFSTraverse()函数，实现旅游景点导航功能
void TravelPath(Graph graph)
{
	cout << endl << "====== 旅游景点导航 ======" << endl;

	if (graph.m_nVexNum == 0)
	{
		cout << "请先创建图！\n" << endl;
		return;
	}

	PathList pList = NULL;		//遍历得到的结果
	//pList = new Path;
	pList = (PathList)malloc(sizeof(Path));
	PathList pHead = pList;

	int nVex = 0;		//储存景点编码

	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	cout << "请输入起始点编号：";
	cin >> nVex;
	if (nVex < 0 || nVex >= graph.m_nVexNum)
	{
		cout << "输入错误！\n" << endl;
		return;
	}
	cout << "导游路线为：" << endl;
	DFSTraverse(graph, nVex, pList);

	pList = pHead;
	int i = 1;
	while (pList->next != NULL)
	{
		int j = 0;
		//cout<<"路线"<<i<<graph.m_aVexs[pList->vexs[j]].name<<"->"
		cout << "路线" << i << "：";
		while (j < graph.m_nVexNum - 1)
		{
			cout << graph.m_aVexs[pList->vexs[j]].name << "->";
			j++;
		}
		cout << graph.m_aVexs[pList->vexs[j]].name << endl;
		i++;
		pList = pList->next;
	}
	cout << endl;

	//PathList p = pList;
	while (pHead != NULL)
	{
		pList = pHead;
		pHead = pHead->next;
		free(pList);
	}

	system("pause");
	system("cls");

	//delete pList;
}

// 通过调用FindShortPath(Graph, int, int, Edge)函数查询两个景点间的最短路径和距离
void FindShortPath(Graph graph)
{
	cout << endl << "====== 搜索最短路径 ======" << endl;

	if (graph.m_nVexNum == 0)
	{
		cout << "请先创建图！\n" << endl;
		return;
	}

	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}

	int nVexStart, nVexEnd;
	cout << "请输入起点的编号：";
	cin >> nVexStart;
	if (nVexStart < 0 || nVexStart >= graph.m_nVexNum)
	{
		cout << "输入错误！\n" << endl;
		return;
	}

	cout << "请输入终点的编号：";
	cin >> nVexEnd;
	if (nVexEnd < 0 || nVexEnd >= graph.m_nVexNum || nVexEnd == nVexStart)
	{
		cout << "输入错误！\n" << endl;
		return;
	}
	int i = 0;
	Edge aPath[Maxsize];
	int num = FindShortPath(graph, nVexStart, nVexEnd, aPath);
	int dist = 0;
	cout << "最短路线为：";
	for (i = 0; i < num; i++)
	{
		cout << graph.m_aVexs[aPath[i].vex1].name << "->";
		dist += aPath[i].weight;
	}
	cout << graph.m_aVexs[nVexEnd].name << endl;
	//dist += aPath[i].weight;
	cout << "最短距离为：" << dist << endl << endl;

	system("pause");
	system("cls");
}

//通过调用Graph.cpp文件中的FindMinTree()方法查询铺设电路规划图
void DesignPath(Graph graph)
{
	cout << "\n===== 铺设电路规划 =====" << endl;
	if (graph.m_nVexNum == 0)
	{
		cout << "请先创建图！\n" << endl;
		return;
	}

	cout << "在以下两个景点之间铺设电路：" << endl;

	Edge aPath[Maxsize];
	int pnum = FindMinTree(graph, aPath);
	int Snumdist = 0;

	for (int i = 0; i < pnum; i++)
	{
		cout << graph.m_aVexs[aPath[i].vex1].name << " - " << graph.m_aVexs[aPath[i].vex2].name << "\t" << aPath[i].weight << endl;
		Snumdist += aPath[i].weight;
	}
	cout << "铺设电路的总长度为：" << Snumdist << endl << endl;

	system("pause");
	system("cls");
}