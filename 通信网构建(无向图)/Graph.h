#pragma once

#include "SqList.h"
#include "struct.h"

class Graph
{
private:
	int AdjMatrix[numMAX][numMAX] = { 0 };	//邻接矩阵
	SqList<Vex> Vexs;				//点的集合
	SqList<Edge> Edges;				//边的集合
	int VexNum;						//点的个数
public:
	Graph()
	{
		VexNum = 0;
	}

	~Graph()
	{

	}

	bool InsertVex(Vex svex)	//插入一个顶点
	{
		Vexs.InsertTail(svex);
		return true;
	}

	bool DeleteVex(Vex svex)	//删除一个顶点
	{
		int i = Vexs.Locate(svex);
		if (i == 0)
		{
			return false;
		}
		Vexs.Delete(i, svex);
		return true;
	}

	bool UpdateVex(Vex svex)	//更新一个顶点
	{
		int i;
		cout << "元素更新的位置：";
		cin >> i;
		if (Vexs.Update(i, svex) == 0)
		{
			return false;
		}
		return true;
	}

	bool InsertEdge(Edge sedge)		//插入一条边
	{
		int n = VexNum * (VexNum - 1) / 2 + VexNum;
		if (Edges.GetLength() < n)
		{
			Edges.InsertTail(sedge);
			return true;
		}
		return false;
	}

	bool DeleteEdge(Edge sedge)		//删除一条边
	{
		int i = Edges.Locate(sedge);
		if (i == 0)
		{
			return false;
		}
		Edges.Delete(i, sedge);
		return true;
	}

	bool UpdateEdge(Edge sedge)		//更新一条边
	{
		int i;
		cout << "元素更新的位置：";
		cin >> i;
		if (Edges.Update(i, sedge) == 0)
		{
			return false;
		}
		return true;
	}

	Edge GetEdge(char* vex1Code, char* vex2Code)	//获取一条边
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

	Vex GetVex(char* vex1Code)		//获取一个顶点
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

	void SetVexNum(int i)		//设置点的个数
	{
		if (i > 0)
		{
			VexNum = i;
		}
	}

	void setVex()					//设置顶点集合
	{
		Vexs.InputList(VexNum);
	}

	void setEdges(int i)			//设置边集合
	{
		Edges.InputList(i);
		setAdjMatrix();
	}

	void setAdjMatrix()				//设置邻接矩阵
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

	int GetVexNum() { return VexNum; }			//返回顶点的个数

	int PrimMinTree(Edge aPath[])
	{
		int vex[numMAX] = { 0 };		//判断某个顶点是否添加，1为已添加
		int v[numMAX] = { 0 };			//保存已添加的顶点
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
		int edge[40][4] = { 0 };		//将邻接矩阵中的非零值从小到大储存
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
		//int v[numMAX] = { 0 };	//每加一条边，其两个顶点对应的数据加1，用于做判断条件
		//int i = 1;
		//while (edgenum < VexNum && i <= num)
		//{
		//	int vexnum = 0;		//以添加的边所含有顶点的个数
		//	if (v[edge[i][2]] < 2 && v[edge[i][3]] < 2)
		//	{
		//		/*Vexs.GetElem(edge[i][2], aPath[edgenum].vex1);
		//		Vexs.GetElem(edge[i][3], aPath[edgenum].vex2);*/

		//		
		//		//aPath[edgenum].weight = edge[i][1];


		//		v[edge[i][2]]++;
		//		v[edge[i][3]]++;
		//		edgenum++;

		//		for (int j = 1; j <= VexNum; j++)	//计算以添加的顶点
		//		{
		//			if (v[j] != 0)
		//			{
		//				vexnum++;
		//			}
		//		}
		//		if (vexnum <= edgenum)				//添加的顶点小于等于边则形成回路，将刚添加的边去掉
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
	


