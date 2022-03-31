#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include "globalFile.h"
using namespace std;

class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//将string按":"分割成key和value，放入map中
	void subString(map<string, string>& m, string s);

public:
	//记录预约条数
	int m_Size;

	//记录所有预约信息的容器  key是记录条数   value是具体记录键值对的信息
	map<int, map<string, string>> m_OrderData;
};

