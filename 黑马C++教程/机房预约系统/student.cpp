#include "student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	//��ʼ������
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ��������Ϣ
	ifstream ifs(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		this->vCom.push_back(com);
	}
	ifs.close();
}

void Student::operMenu()
{
	cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

void Student::applyOrder()
{
	int date;			//����
	int interval = 0;	//ʱ���
	int room = 0;		//�������

	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;;
		}
		cout << "������������������" << endl;
	}

	cout << "������ѡ��Ļ����ţ�" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		bool flag = false;	//�ж��Ƿ�����ѭ��
		for (int i = 0; i < vCom.size(); i++)
		{
			if (room == vCom[i].m_ComId)
			{
				flag = true;
				break;
			}
		}
		if (flag) break;
		cout << "������������������" << endl;
	}
	cout << "ԤԼ�ɹ��������" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;
	ofs.close();
	system("pause");
	system("cls");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	int num = 0;	//��¼����ԤԼ����
	for (int i = 0; i < of.m_Size; i++)
	{
		//c_str(): stringת��C�����ַ��� const char*
		//atoi: const char* תint   
		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))	
		{
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
			cout << "ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����") << " ";
			cout << "�����ţ�" << of.m_OrderData[i]["roomId"] << " ";
			string status = "״̬��";	//1 �����	2 ԤԼ�ɹ�	-1 ԤԼʧ��	   0 ȡ��ԤԼ
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_OrderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else if (of.m_OrderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
			
			num++;
		}
	}
	if (num == 0)
	{
		cout << "��ԤԼ��¼" << endl;
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
		cout << "ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����") << " ";
		cout << "ѧ�ţ�" << of.m_OrderData[i]["stuId"] << " ";
		cout << "������" << of.m_OrderData[i]["stuName"] << " ";
		cout << "�����ţ�" << of.m_OrderData[i]["roomId"] << " ";
		string status = "״̬��";	//1 �����	2 ԤԼ�ɹ�	-1 ԤԼʧ��	   0 ȡ��ԤԼ
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_OrderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else if (of.m_OrderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ��" << endl;
	vector<int> v;	//�����ʾ�ؼ�¼��map�е��±���
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//���ж��������¼
		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))
		{
			//��ɸѡ״̬
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "�� ";
				cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
				cout << "ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����") << " ";
				cout << "�����ţ�" << of.m_OrderData[i]["roomId"] << " ";
				string status = "״̬��";	//1 �����	2 ԤԼ�ɹ�	-1 ԤԼʧ��	   0 ȡ��ԤԼ
				if (of.m_OrderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				else if (of.m_OrderData[i]["status"] == "-1")
				{
					status += "ԤԼʧ�ܣ����δͨ��";
				}
				else if (of.m_OrderData[i]["status"] == "0")
				{
					status += "ԤԼ��ȡ��";
				}
				cout << status << endl;
			}
		}
	}
	if (index == 1)
	{
		cout << "�޿�ȡ����¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "������Ҫȡ���ļ�¼��ţ�0������" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0) 
			{
				break; 
			}
			else
			{
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}
