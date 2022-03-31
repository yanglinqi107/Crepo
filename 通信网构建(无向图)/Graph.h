#pragma once

#include "SqList.h"
#include "struct.h"

class Graph
{
private:
	int AdjMatrix[numMAX][numMAX] = { 0 };	//�ڽӾ���
	SqList<Vex> Vexs;				//��ļ���
	SqList<Edge> Edges;				//�ߵļ���
	int VexNum;						//��ĸ���
public:
	Graph()
	{
		VexNum = 0;
	}

	~Graph()
	{

	}

	bool InsertVex(Vex svex)	//����һ������
	{
		Vexs.InsertTail(svex);
		return true;
	}

	bool DeleteVex(Vex svex)	//ɾ��һ������
	{
		int i = Vexs.Locate(svex);
		if (i == 0)
		{
			return false;
		}
		Vexs.Delete(i, svex);
		return true;
	}

	bool UpdateVex(Vex svex)	//����һ������
	{
		int i;
		cout << "Ԫ�ظ��µ�λ�ã�";
		cin >> i;
		if (Vexs.Update(i, svex) == 0)
		{
			return false;
		}
		return true;
	}

	bool InsertEdge(Edge sedge)		//����һ����
	{
		int n = VexNum * (VexNum - 1) / 2 + VexNum;
		if (Edges.GetLength() < n)
		{
			Edges.InsertTail(sedge);
			return true;
		}
		return false;
	}

	bool DeleteEdge(Edge sedge)		//ɾ��һ����
	{
		int i = Edges.Locate(sedge);
		if (i == 0)
		{
			return false;
		}
		Edges.Delete(i, sedge);
		return true;
	}

	bool UpdateEdge(Edge sedge)		//����һ����
	{
		int i;
		cout << "Ԫ�ظ��µ�λ�ã�";
		cin >> i;
		if (Edges.Update(i, sedge) == 0)
		{
			return false;
		}
		return true;
	}

	Edge GetEdge(char* vex1Code, char* vex2Code)	//��ȡһ����
	{
		Edge e;
		int n = Edges.GetLength();
		for (int i = 1; i <= n; i++)
		{
			Edges.GetElem(i, e);
			if (strcmp(e.vex1.Code, vex1Code) == 0)
			{
				return e;
			}
		}
	}

	Vex GetVex(char* vex1Code)		//��ȡһ������
	{
		Vex e;
		int n = Vexs.GetLength();
		for (int i = 1; i <= n; i++)
		{
			Vexs.GetElem(i, e);
			if (strcmp(e.Code, vex1Code) == 0)
			{
				return e;
			}
		}
	}

	void SetVexNum(int i)		//���õ�ĸ���
	{
		if (i > 0)
		{
			VexNum = i;
		}
	}

	void setVex()					//���ö��㼯��
	{
		Vexs.InputList(VexNum);
	}

	void setEdges(int i)			//���ñ߼���
	{
		Edges.InputList(i);
		setAdjMatrix();
	}

	void setAdjMatrix()				//�����ڽӾ���
	{
		Vex v;
		Edge e;
		int n = Edges.GetLength();
		int m = Vexs.GetLength();
		int x = 0, y = 0;
		for (int i = 1; i <= n; i++)
		{
			Edges.GetElem(i, e);
			for (int j = 1; j <= m; j++)
			{
				Vexs.GetElem(j, v);
				if (strcmp(e.vex1.Code, v.Code) == 0)
				{
					strcpy_s(e.vex1.Name, v.Name);
					x = j;
				}
				if (strcmp(e.vex2.Code, v.Code) == 0)
				{
					strcpy_s(e.vex2.Name, v.Name);
					y = j;
				}
			}
			if (x != y)
			{
				AdjMatrix[x][y] = e.weight;
				AdjMatrix[y][x] = e.weight;
			}
		}
	}

	/*bool judgecConnect()
	{
		int sum;
		for (int i = 1; i <= VexNum; i++)
		{
			sum = 0;
			for (int j = 1; j < VexNum; j++)
			{
				sum = +AdjMatrix[i][j];
			}
			if (sum == 0)
			{
				return false;
			}
		}
		return true;
	}*/

	int GetVexNum() { return VexNum; }			//���ض���ĸ���

	int PrimMinTree(Edge aPath[])
	{
		int vex[numMAX] = { 0 };		//�ж�ĳ�������Ƿ���ӣ�1Ϊ�����
		int v[numMAX] = { 0 };			//��������ӵĶ���
		int vexnum = 1;
		int edgenum = 0;
		int temp;
		Vex v1, v2;
		v[1] = 1;
		vex[1] = 1;
		int i = 1, j = 1, k = 1, r1, r2;
		while (vexnum < VexNum)
		{
			r1 = r2 = 0;
			temp = DEFAULT_INFINITY;
			while (v[j] != 0)
			{
				for (k = 1; k <= VexNum; k++)
				{
					if (vex[k] == 0 && AdjMatrix[v[j]][k] != 0)
					{
						if (temp > AdjMatrix[v[j]][k])
						{
							temp = AdjMatrix[v[j]][k];
							r1 = v[j];
							r2 = k;
						}
					}
				}
				j++;
			}
			j = 1;
			if (temp != DEFAULT_INFINITY)
			{
				edgenum++;
				//Vexs.GetElem(r1, aPath[edgenum].vex1);
				Vexs.GetElem(r1, v1);

				//Vexs.GetElem(r2, aPath[edgenum].vex2);
				Vexs.GetElem(r2, v2);

				//aPath[edgenum].weight = temp;

				cout << v1.Code << "<----->" << v2.Code << "  " << temp << endl;
				vex[r2] = 1;
				v[++vexnum] = r2;
			}
			else
			{
				break;
			}
		}
		return 0;
	}

	int kruskalMinTree(Edge aPath[])
	{
		Vex v1, v2;
		int edge[40][4] = { 0 };		//���ڽӾ����еķ���ֵ��С���󴢴�
		int num = 0;
		for (int i = 1; i <= VexNum; i++)
		{
			for (int j = 1; j < i; j++)
			{
				if (AdjMatrix[i][j] != 0)
				{
					edge[num + 1][1] = AdjMatrix[i][j];
					edge[num + 1][2] = i;
					edge[num + 1][3] = j;
					num++;
				}
			}
		}
		for (int i = 1; i < num - 1; i++)
		{
			for (int j = 1; j <= num - i; j++)
			{
				if (edge[j][1] > edge[j + 1][1])
				{
					edge[0][1] = edge[j][1];
					edge[0][2] = edge[j][2];
					edge[0][3] = edge[j][3];
					edge[j][1] = edge[j + 1][1];
					edge[j][2] = edge[j + 1][2];
					edge[j][3] = edge[j + 1][3];
					edge[j + 1][1] = edge[0][1];
					edge[j + 1][2] = edge[0][2];
					edge[j + 1][3] = edge[0][3];
				}
			}
		}
		int edgenum = 0;
		int v[20][10] = { 0 };	//
		int i = 1;
		while (edgenum < VexNum && i <= num)
		{
			int xjudge = 0, yjudge = 0;
			for (int a = 1; a < 10; a++)
			{
				if (v[edge[i][2]][a] == 1)
				{
					xjudge = a;
				}
				if (v[edge[i][3]][a] == 1)
				{
					yjudge = a;
				}
			}
			int sum = xjudge + yjudge;
			if (sum == 0)
			{
				int a = 1;
				while (v[0][a] != 0)
				{
					a++;
				}
				v[0][a] = 1;
				v[edge[i][2]][a] = v[edge[i][3]][a] = 1;
				edgenum++;
			}
			else if (xjudge == yjudge)
			{
				i++;
				continue;
			}
			else if (sum == xjudge || sum == yjudge)
			{
				v[edge[i][2]][sum] = v[edge[i][3]][sum] = 1;
				edgenum++;
			}
			else if (sum > xjudge && sum > yjudge)
			{
				for (int a = 1; a < 20; a++)
				{
					if (v[a][xjudge] == 1)
					{
						v[a][yjudge] = 1;
					}
				}
				v[0][xjudge] = 0;
				edgenum++;
			}
			Vexs.GetElem(edge[i][2], v1);
			Vexs.GetElem(edge[i][3], v2);
			cout << v1.Code << "<----->" << v2.Code << "  " << edge[i][1] << endl;
			i++;
		}
		return 0;
	}
};
		//int edgenum = 0;
		//int v[numMAX] = { 0 };	//ÿ��һ���ߣ������������Ӧ�����ݼ�1���������ж�����
		//int i = 1;
		//while (edgenum < VexNum && i <= num)
		//{
		//	int vexnum = 0;		//����ӵı������ж���ĸ���
		//	if (v[edge[i][2]] < 2 && v[edge[i][3]] < 2)
		//	{
		//		/*Vexs.GetElem(edge[i][2], aPath[edgenum].vex1);
		//		Vexs.GetElem(edge[i][3], aPath[edgenum].vex2);*/

		//		
		//		//aPath[edgenum].weight = edge[i][1];


		//		v[edge[i][2]]++;
		//		v[edge[i][3]]++;
		//		edgenum++;

		//		for (int j = 1; j <= VexNum; j++)	//��������ӵĶ���
		//		{
		//			if (v[j] != 0)
		//			{
		//				vexnum++;
		//			}
		//		}
		//		if (vexnum <= edgenum)				//��ӵĶ���С�ڵ��ڱ����γɻ�·��������ӵı�ȥ��
		//		{
		//			v[edge[i][2]]--;
		//			v[edge[i][3]]--;
		//			edgenum--;
		//			continue;
		//		}
		//		Vexs.GetElem(edge[i][2], v1);
		//		Vexs.GetElem(edge[i][3], v2);
		//		cout << v1.Code << " " << v2.Code << " " << edge[i][1] << endl;
		//	}
		//	i++;
		//} 
	


