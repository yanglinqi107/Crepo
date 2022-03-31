#include "manager.h"

Manager::Manager()
{
}

Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//获取教师，学生的用户信息
	this->initVector();

	//初始化机房信息
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
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileName;	//操作文件名
	string tip;		//提示id号
	string errorTip;	//id重复错误提示

	ofstream ofs;	//文件操作对象
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//添加学生
		fileName = STUDENT_FILE;
		errorTip = "学号重复，请重新输入";
		tip = "请输入学号：";
	}
	else if (select == 2)
	{
		//添加老师
		fileName = TEACHER_FILE;
		errorTip = "职工号重复，请重新输入";
		tip = "请输入职工号：";
	}
	else
	{
		return;
	}

	int id;			//学号 或 职工号
	string name;	//用户名
	string pwd;		//密码
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		if (!checkRepeat(id, select)) break;
		cout << errorTip << endl;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	//写文件
	ofs.open(fileName, ios::out | ios::app);
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;
	ofs.close();

	//初始化学生，教师容器
	this->initVector();

	system("pause");
	system("cls");
}

void printStudent(Student& s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有教师" << endl;

	int select = 0;	//接收用户输入
	cin >> select;

	if (select == 1)
	{
		//查看学生
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		//查看教师
		cout << "所有教师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_ComId << " 机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	cout << "是否确定清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	//清空容器
	this->vStu.clear();
	this->vTea.clear();	
	//读取信息 学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "学生文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		this->vStu.push_back(s);
	}
	ifs.close();
	//cout << "学生数量：" << vStu.size() << endl;

	//读取信息 教师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "教师文件读取失败" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		this->vTea.push_back(t);
	}
	ifs.close();
	//cout << "教师数量：" << vTea.size() << endl;
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学生
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
		//检测教师
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

