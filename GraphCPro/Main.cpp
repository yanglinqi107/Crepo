#include<iostream>
#include"Graph.h"
#include"Tourism.h"

using namespace std;


int main(void)
{
	/*int a[10] = { -1};
	fill(a, a + 10, -1);
	cout << a[0] << a[1] << a[9]*/;

	Graph graph;
	bool judge = true;
	int choice;
	while (judge)
	{
		cout << "====== 景区信息管理系统 ======" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入操作编号（0~5）：";
		cin >> choice;
		//while (getchar() != '\0');
		switch (choice)
		{
		case 1:CreateGraph(graph); break;
		case 2:GetSpotInfo(graph); break;
		case 3:TravelPath(graph); break;
		case 4:FindShortPath(graph); break;
		case 5:DesignPath(graph); break;
		case 0:cout << "退出！" << endl; judge = false; break;
		default:
			cout << "输入错误！请重试\n" << endl;
			break;
		}
	}

	return 0;
}