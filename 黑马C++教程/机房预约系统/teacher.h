#pragma once
#include <vector>
#include "Identity.h"
#include "orderFile.h"

class Teacher :public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int empId, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

public:
	//ְ�����
	int m_EmpId;
};

