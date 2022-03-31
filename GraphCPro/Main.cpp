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
		cout << "====== ������Ϣ����ϵͳ ======" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "�����������ţ�0~5����";
		cin >> choice;
		//while (getchar() != '\0');
		switch (choice)
		{
		case 1:CreateGraph(graph); break;
		case 2:GetSpotInfo(graph); break;
		case 3:TravelPath(graph); break;
		case 4:FindShortPath(graph); break;
		case 5:DesignPath(graph); break;
		case 0:cout << "�˳���" << endl; judge = false; break;
		default:
			cout << "�������������\n" << endl;
			break;
		}
	}

	return 0;
}