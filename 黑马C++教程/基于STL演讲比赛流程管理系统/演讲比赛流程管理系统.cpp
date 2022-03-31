#include <iostream>
#include "speechManager.h"
using namespace std;

int main()
{
	//创建管理员对象
	SpeechManager sm;

	////测试
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << " 选手姓名：" << it->second.m_Name << " 分数：" << it->second.m_Score[0] << endl;
	//}

	int choice = 0;	//用于存储用户的输入
	srand((unsigned int)time(NULL));	//设置随机数种子
	while (true)
	{
		sm.show_Menu();

		cout << endl << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:		//开始比赛
			sm.startSpeech();
			break;
		case 2:		//查看往届比赛记录
			sm.showRecord();
			break;
		case 3:		//清空比赛记录
			sm.clearRecord();
			break;
		case 0:		//退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");	//清屏
			break;
		}
	}
	return 0;
}
