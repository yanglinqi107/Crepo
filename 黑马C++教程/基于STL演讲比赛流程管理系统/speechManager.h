#pragma once
#include <map>
#include <deque>
#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "speaker.h"
using namespace std;

//演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//初始化成员属性
	void initSpeech();

	//创建12名选手
	void createSpeaker();

	//开始比赛 比赛整个流程的控制函数
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届得分
	void showRecord();	

	//菜单功能
	void show_Menu();

	//清空记录
	void clearRecord();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();

public:
	//成员属性
	//保存第一轮比赛选手编号
	vector<int> v1;

	//第一轮晋级选手编号
	vector<int> v2;

	//胜出的前三名选手编号
	vector<int> vVictory;

	//存放编号，具体对应选手
	map<int, Speaker> m_Speaker;

	//存放比赛轮数
	int m_Index;

	//文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;
};

