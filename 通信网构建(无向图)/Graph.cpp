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
			cout << "�������!" << endl;
			break;
		}
	} while (judge);


	/*cout << "Prim�㷨��" << endl;
	graph.PrimMinTree(&edge1[10]);*/
	/*for (int k = 1; k < i; k++)
	{
		cout << edge1[k].vex1.Code << "<------>" << edge1[k].vex2.Code << "\t" << edge1[k].weight << endl;
	}*/
	/*cout << "Kruskal�㷨��" << endl;
	graph.kruskalMinTree(&edge2[10]);*/
	/*for (int k = 1; k < i; k++)
	{
		cout << edge2[k].vex1.Code << "<------>" << edge2[k].vex2.Code << "\t" << edge2[k].weight << endl;
	}*/
	return 0;
}

void meau()
{
	cout << "\n--------------------�˵�---------------------\n" << endl;
	cout << "1.����ͼ  \t2.Prim�㷨\t3.Kruskal�㷨" << endl;
	cout << "4.��Ӷ���\t5.ɾ������\t6.���¶���" << endl;
	cout << "7.��ӱ�  \t8.ɾ����  \t9.���±�" << endl;
	cout << "0.�Ƴ�" << endl;
	cout << "��������ţ�0~9����";
}

void setGraph(Graph& graph)
{
	bool judge = false;
	int i, j;
	do {
		cout << "�����ĸ�����";
		cin >> i;
		while (getchar() != '\n');
		if (i < 2)
		{
			cout << "�������\n";
			judge = true;
		}
	} while (judge);
	graph.SetVexNum(i);
	graph.setVex();
	do {
		cout << "����ߵ�������";
		cin >> j;
		while (getchar() != '\n');
		if (j < i)
		{
			cout << "�������\n";
			judge = true;
		}
	} while (judge);
	graph.setEdges(j);
}

void setVexInGraph(Graph& graph)
{
	Vex svex;
	cout << "���붥����Ϣ��" << endl;
	cout << "���ƣ�";
	cin >> svex.Name;
	cout << "��ţ�";
	cin >> svex.Code;
	graph.InsertVex(svex);
}

void DeleteVexInGraph(Graph& graph)
{
	Vex svex;
	cout << "���붥����Ϣ��" << endl;
	cout << "���ƣ�";
	cin >> svex.Name;
	cout << "��ţ�";
	cin >> svex.Code;
	graph.DeleteVex(svex);
}

void UpdateVexInGraph(Graph& graph)
{
	Vex svex;
	cout << "���붥����Ϣ��" << endl;
	cout << "���ƣ�";
	cin >> svex.Name;
	cout << "��ţ�";
	cin >> svex.Code;
	graph.UpdateVex(svex);
}

void setEdgeInGraph(Graph& graph)
{
	Edge edge;
	cout << "����ߵ���Ϣ��" << endl;
	cout << "������  ������  Ȩֵ" << endl;
	cin >> edge.vex1.Code >> edge.vex2.Code >> edge.weight;
	graph.InsertEdge(edge);
}

void DeleteEdgeInGraph(Graph& graph)
{
	Edge edge;
	cout << "����ߵ���Ϣ��" << endl;
	cout << "������  ������  Ȩֵ" << endl;
	cin >> edge.vex1.Code >> edge.vex2.Code >> edge.weight;
	graph.DeleteEdge(edge);
}

void UpdateEdgeInGraph(Graph& graph)
{
	Edge edge;
	cout << "����ߵ���Ϣ��" << endl;
	cout << "������  ������  Ȩֵ" << endl;
	cin >> edge.vex1.Code >> edge.vex2.Code >> edge.weight;
	graph.UpdateEdge(edge);
}
