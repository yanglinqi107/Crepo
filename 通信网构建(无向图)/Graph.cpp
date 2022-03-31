#include "Graph.h"

void meau();
void setGraph(Graph& graph);
void setVexInGraph(Graph& graph);
void DeleteVexInGraph(Graph& graph);
void UpdateVexInGraph(Graph& graph);
void setEdgeInGraph(Graph& graph);
void DeleteEdgeInGraph(Graph& graph);
void UpdateEdgeInGraph(Graph& graph);

int main()
{
	int choice = -1;
	Graph graph;
	Edge edge1[10];
	Edge edge2[10];

	bool judge = true;
	do {
		meau();
		cin >> choice;
		while (getchar() != '\n');
		switch (choice)
		{
		case 1:setGraph(graph); break;
		case 2:cout << endl; graph.PrimMinTree(&edge1[10]); break;
		case 3:cout << endl; graph.kruskalMinTree(&edge2[10]); break;
		case 4:setVexInGraph(graph); break;
		case 5:DeleteVexInGraph(graph); break;
		case 6:UpdateVexInGraph(graph); break;
		case 7:setEdgeInGraph(graph); break;
		case 8:DeleteEdgeInGraph(graph); break;
		case 9:UpdateEdgeInGraph(graph); break;
		case 0:judge = false; break;
		default:
			cout << "输入错误!" << endl;
			break;
		}
	} while (judge);


	/*cout << "Prim算法：" << endl;
	graph.PrimMinTree(&edge1[10]);*/
	/*for (int k = 1; k < i; k++)
	{
		cout << edge1[k].vex1.Code << "<------>" << edge1[k].vex2.Code << "\t" << edge1[k].weight << endl;
	}*/
	/*cout << "Kruskal算法：" << endl;
	graph.kruskalMinTree(&edge2[10]);*/
	/*for (int k = 1; k < i; k++)
	{
		cout << edge2[k].vex1.Code << "<------>" << edge2[k].vex2.Code << "\t" << edge2[k].weight << endl;
	}*/
	return 0;
}

void meau()
{
	cout << "\n--------------------菜单---------------------\n" << endl;
	cout << "1.创建图  \t2.Prim算法\t3.Kruskal算法" << endl;
	cout << "4.添加顶点\t5.删除顶点\t6.更新顶点" << endl;
	cout << "7.添加边  \t8.删除边  \t9.更新边" << endl;
	cout << "0.推出" << endl;
	cout << "请输入序号（0~9）：";
}

void setGraph(Graph& graph)
{
	bool judge = false;
	int i, j;
	do {
		cout << "输入点的个数：";
		cin >> i;
		while (getchar() != '\n');
		if (i < 2)
		{
			cout << "输入错误！\n";
			judge = true;
		}
	} while (judge);
	graph.SetVexNum(i);
	graph.setVex();
	do {
		cout << "输入边的条数：";
		cin >> j;
		while (getchar() != '\n');
		if (j < i)
		{
			cout << "输入错误！\n";
			judge = true;
		}
	} while (judge);
	graph.setEdges(j);
}

void setVexInGraph(Graph& graph)
{
	Vex svex;
	cout << "输入顶点信息：" << endl;
	cout << "名称：";
	cin >> svex.Name;
	cout << "编号：";
	cin >> svex.Code;
	graph.InsertVex(svex);
}

void DeleteVexInGraph(Graph& graph)
{
	Vex svex;
	cout << "输入顶点信息：" << endl;
	cout << "名称：";
	cin >> svex.Name;
	cout << "编号：";
	cin >> svex.Code;
	graph.DeleteVex(svex);
}

void UpdateVexInGraph(Graph& graph)
{
	Vex svex;
	cout << "输入顶点信息：" << endl;
	cout << "名称：";
	cin >> svex.Name;
	cout << "编号：";
	cin >> svex.Code;
	graph.UpdateVex(svex);
}

void setEdgeInGraph(Graph& graph)
{
	Edge edge;
	cout << "输入边的信息：" << endl;
	cout << "顶点编号  顶点编号  权值" << endl;
	cin >> edge.vex1.Code >> edge.vex2.Code >> edge.weight;
	graph.InsertEdge(edge);
}

void DeleteEdgeInGraph(Graph& graph)
{
	Edge edge;
	cout << "输入边的信息：" << endl;
	cout << "顶点编号  顶点编号  权值" << endl;
	cin >> edge.vex1.Code >> edge.vex2.Code >> edge.weight;
	graph.DeleteEdge(edge);
}

void UpdateEdgeInGraph(Graph& graph)
{
	Edge edge;
	cout << "输入边的信息：" << endl;
	cout << "顶点编号  顶点编号  权值" << endl;
	cin >> edge.vex1.Code >> edge.vex2.Code >> edge.weight;
	graph.UpdateEdge(edge);
}
