#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "Identity.h"
#include "computerRoom.h"

class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����˺�
	void addPerson();
	
	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void clearFile();

	//��ʼ������
	void initVector();

	//����ظ�	����1 ѧ�� �� ְ����	����2 ����
	bool checkRepeat(int id, int type);

public:
	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//������Ϣ����
	vector<ComputerRoom> vCom;
};

