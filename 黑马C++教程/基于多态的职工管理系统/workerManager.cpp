#include "workerManager.h"

WorkerManager::WorkerManager()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڵ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	ifs.close();

	//3���ļ����ڲ�������
	this->m_FileIsEmpty = false;
	this->m_EmpNum = get_EmpNum();
	//cout << "ְ������Ϊ��" << this->m_EmpNum << endl;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݣ�����������
	this->init_Emp();
}

void WorkerManager::Show_Menu()
{
	cout << "************************************************" << endl;
	cout << "************* ��ӭʹ��ְ������ϵͳ *************" << endl;
	cout << "***************  0.�˳��������  ***************" << endl;
	cout << "***************  1.����ְ����Ϣ  ***************" << endl;
	cout << "***************  2.��ʾְ����Ϣ  ***************" << endl;
	cout << "***************  3.ɾ����ְְ��  ***************" << endl;
	cout << "***************  4.�޸�ְ����Ϣ  ***************" << endl;
	cout << "***************  5.����ְ����Ϣ  ***************" << endl;
	cout << "***************  6.���ձ������  ***************" << endl;
	cout << "***************  7.��������ĵ�  ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "���������ְ����������" << endl;
	int addNum = 0;		//�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;	//�¿ռ����� = ԭ����¼������ + ��������
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//��ԭ���ռ��µ����ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		//�����������
		for (int i = 0; i < addNum; i++)
		{
			int id;	//ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��

			while (true)
			{
				cout << "�������" << i + 1 << "����ְ�����" << endl;
				cin >> id;
				int idExist = this->isExist(id);
				if (idExist == -1) break;
				cout << "ְ�����Ѵ��ڣ�������" << endl;
			}

			cout << "�������" << i + 1 << "����ְ������" << endl;
			cin >> name;

			cout << "��ѡ��ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			//��������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//������ְ������
		this->m_EmpNum = newSize;
		//�������ļ�
		this->save();
		//�����ļ���ʶ
		this->m_FileIsEmpty = false;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else
	{
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ���ڻ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{

		for (int i = 0; i < this->m_EmpNum; ++i)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//���������
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�����Ϊ��" << endl;
	}
	else
	{
		cout << "������ɾ��ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1)
		{
			cout << "ְ��������" << endl;
		}
		else  //ְ������
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; ++i)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;	//���������м�¼����
			//ͬ�������ļ�
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�����Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1)
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
		else
		{
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "���ҵ���Ϣ���£�" << endl;
			this->m_EmpArray[index]->showInfo();
			cout << "�������µ�ְ���ţ�" << endl;
			cin >> newId;
			cout << "�������µ�������" << endl;
			cin >> newName;
			cout << "�������µĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			delete this->m_EmpArray[index];
			this->m_EmpArray[index] = worker;
			//�����ļ�
			this->save();
			cout << "�޸ĳɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�����Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//��Ų���
			int id;
			cout << "���������ְ���ı�ţ�" << endl;
			cin >> id;
			int index = this->isExist(id);
			if (index != -1)   //����
			{
				cout << "���ҵ���Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//��������
			string name;
			cout << "���������ְ����������" << endl;
			cin >> name;
			bool flag = false;	//�Ƿ���ҵ��ı�־��Ĭ��Ϊ�ҵ�
			for (int i = 0; i < this->m_EmpNum; ++i)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҵ���Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "�������" << endl;
		}
	}
	//���������
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�����Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1������ְ���������" << endl;
		cout << "2������ְ����Ž���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; ++i)
		{
			int minOrMax = i;	//���� ��Сֵ�����ֵ���±�
			for (int j = i + 1; j < this->m_EmpNum; ++j)
			{
				if (select == 1)	//����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = this->m_EmpArray[i];
				this->m_EmpArray[i] = temp;
			}
		}
		cout << "����ɹ���������Ϊ��" << endl;
		//�������ļ�
		this->save();
		//չʾ����ְ����Ϣ
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File()
{
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);	//ɾ���ļ������´���
		ofs.close();
		
		if (this->m_EmpArray != NULL);
		{
			for (int i = 0; i < this->m_EmpNum; ++i)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	if (!ofs.is_open())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	//��ÿ���˵�����д���ļ�
	for (int i = 0; i < this->m_EmpNum; ++i)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

int WorkerManager::isExist(int id)
{
	for (int i = 0; i < this->m_EmpNum; ++i)
	{
		if (id == this->m_EmpArray[i]->m_Id) return i;
	}
	return -1;
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		switch (dId)
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
