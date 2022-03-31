#pragma once
#include <vector>
#include <fstream>
#include "globalFile.h"
#include "computerRoom.h"
#include "Identity.h"
#include "orderFile.h"

class Student :public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();
	
	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

public:
	//ѧ��ѧ��
	int m_Id;

	//������Ϣ����
	vector<ComputerRoom> vCom;
};

