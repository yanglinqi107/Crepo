#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include "globalFile.h"
using namespace std;

class OrderFile
{
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();

	//��string��":"�ָ��key��value������map��
	void subString(map<string, string>& m, string s);

public:
	//��¼ԤԼ����
	int m_Size;

	//��¼����ԤԼ��Ϣ������  key�Ǽ�¼����   value�Ǿ����¼��ֵ�Ե���Ϣ
	map<int, map<string, string>> m_OrderData;
};

