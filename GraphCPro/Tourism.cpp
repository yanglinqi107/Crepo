#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include"Tourism.h"
#include"Graph.h"

using namespace std;

//��ȡ�ļ���������������ͼ
void CreateGraph(Graph& graph)
{
	cout << endl << "====== ������������ͼ ======" << endl;
	Vex vex;
	Edge edge;
	//char num;
	int num;
	ifstream infile("Vex.txt");
	infile >> num;
	//cout << num << endl;
	cout << "������Ŀ��" << num << endl;
	cout << "----- ���� -----" << endl;

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

	cout << "----- �� -----" << endl;
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
	
	cout << "====== ����ͼ������� ======\n" << endl;

	system("pause");
	system("cls");

	//FILE* fp;

	//fopen_s(&fp, "E:\\Vex.txt", "r");
	//if (!fp)
	//{
	//	cerr << "�ļ���ʧ��1��" << endl;
	//	return;
	//}

	////1��ʼ��ͼ
	//Init();
	//while (!feof(fp))
	//{
	//	fread(&num, sizeof(int), 1, fp);	//��ȡ�������
	//	cout << num << endl;
	//}
	////2����ͼ�Ķ���
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
	//	cerr << "���ļ�ʧ��2��" << endl;
	//	return;
	//}
	////3����ͼ�ı�
	//while (!feof(fp))
	//{
	//	fread(&edge, sizeof(Edge), 1, fp);
	//	cout << edge.vex1 << "\t" << edge.vex2 << "\t" << edge.weight << endl;
	//	InserEdge(graph, edge);
	//}
	//fclose(fp);
}

//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
void GetSpotInfo(Graph graph)
{
	cout << endl << "====== ��ѯ������Ϣ ======" << endl;
	if (graph.m_nVexNum == 0) {
		cout << "���ȴ���ͼ��\n" << endl;
		return;
	}

	int v = 0;		//���澰�����

	
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	cin >> v;

	if (v < 0 || v >= graph.m_nVexNum)
	{
		cout << "�������\n" << endl;
		return;
	}
	Edge* aEdge=NULL;

	//ȡ��ָ��������Ϣ
	Vex vex = GetVex(graph, v);
	cout << vex.name << endl << vex.desc << endl;
	cout << "----- �ܱ߾��� -----" << endl;
	//��ѯ������ָ�����������ıߵ���Ϣ
	FindEdge(graph, v, aEdge);
	cout << endl;

	system("pause");
	system("cls");
}

//����DFSTraverse()������ʵ�����ξ��㵼������
void TravelPath(Graph graph)
{
	cout << endl << "====== ���ξ��㵼�� ======" << endl;

	if (graph.m_nVexNum == 0)
	{
		cout << "���ȴ���ͼ��\n" << endl;
		return;
	}

	PathList pList = NULL;		//�����õ��Ľ��
	//pList = new Path;
	pList = (PathList)malloc(sizeof(Path));
	PathList pHead = pList;

	int nVex = 0;		//���澰�����

	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	cout << "��������ʼ���ţ�";
	cin >> nVex;
	if (nVex < 0 || nVex >= graph.m_nVexNum)
	{
		cout << "�������\n" << endl;
		return;
	}
	cout << "����·��Ϊ��" << endl;
	DFSTraverse(graph, nVex, pList);

	pList = pHead;
	int i = 1;
	while (pList->next != NULL)
	{
		int j = 0;
		//cout<<"·��"<<i<<graph.m_aVexs[pList->vexs[j]].name<<"->"
		cout << "·��" << i << "��";
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

// ͨ������FindShortPath(Graph, int, int, Edge)������ѯ�������������·���;���
void FindShortPath(Graph graph)
{
	cout << endl << "====== �������·�� ======" << endl;

	if (graph.m_nVexNum == 0)
	{
		cout << "���ȴ���ͼ��\n" << endl;
		return;
	}

	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}

	int nVexStart, nVexEnd;
	cout << "���������ı�ţ�";
	cin >> nVexStart;
	if (nVexStart < 0 || nVexStart >= graph.m_nVexNum)
	{
		cout << "�������\n" << endl;
		return;
	}

	cout << "�������յ�ı�ţ�";
	cin >> nVexEnd;
	if (nVexEnd < 0 || nVexEnd >= graph.m_nVexNum || nVexEnd == nVexStart)
	{
		cout << "�������\n" << endl;
		return;
	}
	int i = 0;
	Edge aPath[Maxsize];
	int num = FindShortPath(graph, nVexStart, nVexEnd, aPath);
	int dist = 0;
	cout << "���·��Ϊ��";
	for (i = 0; i < num; i++)
	{
		cout << graph.m_aVexs[aPath[i].vex1].name << "->";
		dist += aPath[i].weight;
	}
	cout << graph.m_aVexs[nVexEnd].name << endl;
	//dist += aPath[i].weight;
	cout << "��̾���Ϊ��" << dist << endl << endl;

	system("pause");
	system("cls");
}

//ͨ������Graph.cpp�ļ��е�FindMinTree()������ѯ�����·�滮ͼ
void DesignPath(Graph graph)
{
	cout << "\n===== �����·�滮 =====" << endl;
	if (graph.m_nVexNum == 0)
	{
		cout << "���ȴ���ͼ��\n" << endl;
		return;
	}

	cout << "��������������֮�������·��" << endl;

	Edge aPath[Maxsize];
	int pnum = FindMinTree(graph, aPath);
	int Snumdist = 0;

	for (int i = 0; i < pnum; i++)
	{
		cout << graph.m_aVexs[aPath[i].vex1].name << " - " << graph.m_aVexs[aPath[i].vex2].name << "\t" << aPath[i].weight << endl;
		Snumdist += aPath[i].weight;
	}
	cout << "�����·���ܳ���Ϊ��" << Snumdist << endl << endl;

	system("pause");
	system("cls");
}