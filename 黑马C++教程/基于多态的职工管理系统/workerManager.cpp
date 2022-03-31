#include "workerManager.h"

WorkerManager::WorkerManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	ifs.close();

	//3、文件存在并有数据
	this->m_FileIsEmpty = false;
	this->m_EmpNum = get_EmpNum();
	//cout << "职工人数为：" << this->m_EmpNum << endl;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据，存至数组中
	this->init_Emp();
}

void WorkerManager::Show_Menu()
{
	cout << "************************************************" << endl;
	cout << "************* 欢迎使用职工管理系统 *************" << endl;
	cout << "***************  0.退出管理程序  ***************" << endl;
	cout << "***************  1.增加职工信息  ***************" << endl;
	cout << "***************  2.显示职工信息  ***************" << endl;
	cout << "***************  3.删除离职职工  ***************" << endl;
	cout << "***************  4.修改职工信息  ***************" << endl;
	cout << "***************  5.查找职工信息  ***************" << endl;
	cout << "***************  6.按照编号排序  ***************" << endl;
	cout << "***************  7.清空所有文档  ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;		//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;	//新空间人数 = 原来记录的人数 + 新增人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来空间下的数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		//批量添加数据
		for (int i = 0; i < addNum; i++)
		{
			int id;	//职工编号
			string name; //职工姓名
			int dSelect; //部门选择

			while (true)
			{
				cout << "请输入第" << i + 1 << "个新职工编号" << endl;
				cin >> id;
				int idExist = this->isExist(id);
				if (idExist == -1) break;
				cout << "职工号已存在，请重输" << endl;
			}

			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;

			cout << "请选择职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			//将创建的职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更新新空间指向
		this->m_EmpArray = newSpace;
		//更新新职工人数
		this->m_EmpNum = newSize;
		//保存至文件
		this->save();
		//更新文件标识
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else
	{
		cout << "输入错误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Show_Emp()
{
	//判断文件是否存在或为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{

		for (int i = 0; i < this->m_EmpNum; ++i)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或数据为空" << endl;
	}
	else
	{
		cout << "请输入删除职工的编号：" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1)
		{
			cout << "职工不存在" << endl;
		}
		else  //职工存在
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; ++i)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;	//更新数组中记录人数
			//同步更新文件
			this->save();

			cout << "删除成功" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或数据为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1)
		{
			cout << "修改失败，查无此人" << endl;
		}
		else
		{
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查找到信息如下：" << endl;
			this->m_EmpArray[index]->showInfo();
			cout << "请输入新的职工号：" << endl;
			cin >> newId;
			cout << "请输入新的姓名：" << endl;
			cin >> newName;
			cout << "请输入新的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			//更新文件
			this->save();
			cout << "修改成功" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或数据为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//编号查找
			int id;
			cout << "请输入查找职工的编号：" << endl;
			cin >> id;
			int index = this->isExist(id);
			if (index != -1)   //存在
			{
				cout << "查找到信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			//姓名查找
			string name;
			cout << "请输入查找职工的姓名：" << endl;
			cin >> name;
			bool flag = false;	//是否查找到的标志，默认为找到
			for (int i = 0; i < this->m_EmpNum; ++i)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找到信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入错误！" << endl;
		}
	}
	//任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或数据为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照职工编号升序" << endl;
		cout << "2、按照职工编号降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; ++i)
		{
			int minOrMax = i;	//声明 最小值或最大值的下标
			for (int j = i + 1; j < this->m_EmpNum; ++j)
			{
				if (select == 1)	//升序
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
		cout << "排序成功！排序结果为：" << endl;
		//保存至文件
		this->save();
		//展示所有职工信息
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File()
{
	cout << "确认清空吗？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);	//删除文件后重新创建
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
		cout << "清空成功！" << endl;
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
		cout << "文件打开失败！" << endl;
		return;
	}
	//将每个人的数据写入文件
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
