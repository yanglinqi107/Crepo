#pragma once
#define Maxsize 50
#define MAX_VERTEX_NUM 50
#define INFINITE 10000000
#define OK 1
#define ERROR 0


//����Vex�ṹ�壬����ͼ�Ķ�����Ϣ
struct Vex
{
	int num = 0;	//������
	char name[20] = { '\0' };  //��������
	char desc[1024] = { '\0' }; //�������
};

//����Edge�ṹ�壬����ͼ�ıߵ���Ϣ
struct Edge
{
	int vex1, vex2;	//�ߵ���������
	int weight;		//Ȩֵ
};

struct Graph
{
	int m_aAdjMatrix[Maxsize][Maxsize] = { 0 };	//�ڽӾ���(����00)
	Vex m_aVexs[Maxsize];			//�������飨0λ���գ�
	int m_nVexNum = 0;					//�������
};

typedef struct Path
{
	int vexs[MAX_VERTEX_NUM] = { 0 };
	//����һ��·��
	Path* next;//��һ��·��
}*PathList;

void Init(void);	//��ʼ��ͼ�ṹ

int InsertVex(Graph& graph, Vex sVex);	//��������ӵ�����������

int InserEdge(Graph& graph, Edge sEdge);	//���߱��浽�ڽ�����

Vex GetVex(Graph graph, int nVex);		//��ѯָ��������Ϣ

int FindEdge(Graph graph, int nVex, Edge aEdge[]);	//��ѯ��ָ�����������ı�

void DFS(Graph graph, int nVex, bool bVisited[], int& nIndex, PathList& pList);	//������������㷨����ͼ

void DFSTraverse(Graph graph, int nVex, PathList& pList);	//ͨ������DFS()�������õ�������������������

int FindShortPath(Graph graph, int nVexStart, int nVexEnd, Edge aPath[]);//ͨ��Dijkstra�㷨���v1��v2�����·��

int FindMinTree(Graph graph, Edge aPath[]);	//ͨ��Prim�㷨������С������
