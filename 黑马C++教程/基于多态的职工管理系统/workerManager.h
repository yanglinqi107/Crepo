#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager
{
public:
	
	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//���ְ��
	void Add_Emp();	

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//�����ļ�
	void save();

	//��������
	~WorkerManager();

	//���ݱ���ж�ְ���Ƿ���ڣ������򷵻������±꣬�����ڷ���-1
	int isExist(int id);

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;
};

