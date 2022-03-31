#include "manager.h"

Manager::Manager()
{
}

Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ȡ��ʦ��ѧ�����û���Ϣ
	this->initVector();

	//��ʼ��������Ϣ
	ifstream ifs(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		this->vCom.push_back(com);
	}
	ifs.close();
}

void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileName;	//�����ļ���
	string tip;		//��ʾid��
	string errorTip;	//id�ظ�������ʾ

	ofstream ofs;	//�ļ���������
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//���ѧ��
		fileName = STUDENT_FILE;
		errorTip = "ѧ���ظ�������������";
		tip = "������ѧ�ţ�";
	}
	else if (select == 2)
	{
		//�����ʦ
		fileName = TEACHER_FILE;
		errorTip = "ְ�����ظ�������������";
		tip = "������ְ���ţ�";
	}
	else
	{
		return;
	}

	int id;			//ѧ�� �� ְ����
	string name;	//�û���
	string pwd;		//����
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		if (!checkRepeat(id, select)) break;
		cout << errorTip << endl;
	}

	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	//д�ļ�
	ofs.open(fileName, ios::out | ios::app);
	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;
	ofs.close();

	//��ʼ��ѧ������ʦ����
	this->initVector();

	system("pause");
	system("cls");
}

void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "ְ���ţ�" << t.m_EmpId << " ������" << t.m_Name << " ���룺" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴���н�ʦ" << endl;

	int select = 0;	//�����û�����
	cin >> select;

	if (select == 1)
	{
		//�鿴ѧ��
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		//�鿴��ʦ
		cout << "���н�ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_ComId << " �������������" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	//�������
	this->vStu.clear();
	this->vTea.clear();	
	//��ȡ��Ϣ ѧ��
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ѧ���ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		this->vStu.push_back(s);
	}
	ifs.close();
	//cout << "ѧ��������" << vStu.size() << endl;

	//��ȡ��Ϣ ��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ʦ�ļ���ȡʧ��" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		this->vTea.push_back(t);
	}
	ifs.close();
	//cout << "��ʦ������" << vTea.size() << endl;
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//���ѧ��
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else	
	{
		//����ʦ
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

