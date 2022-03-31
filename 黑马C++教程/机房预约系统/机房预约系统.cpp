#include <iostream>
#include <fstream>
#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
using namespace std;

//登录功能	参数1 操作文件名	参数2 操作身份类型
void LoginIn(string fileName, int type);

//管理员用户交互界面
void managerMenu(Identity*& manager);

//学生用户交互界面
void studentMenu(Identity*& student);

//教师用户交互界面
void teacherMenu(Identity*& teacher);

int main()
{
	int select = 0;	//接收用户输入的选择

	while (true)
	{
		cout << "======================  欢迎来到传智播客机房预约系统  ====================="
			<< endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";
		cin >> select;

		switch (select)
		{
		case 1:		//学生身份
			LoginIn(STUDENT_FILE, select);
			break;
		case 2:		//老师身份
			LoginIn(TEACHER_FILE, select);
			break;
		case 3:		//管理员身份
			LoginIn(ADMIN_FILE, select);
			break;
		case 0:		//退出系统
			cout << "欢迎下一次使用" << endl;
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}

void LoginIn(string fileName, int type)
{
	//父类指针，用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;

	if (type == 1)	//学生登录
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)	//教师登录
	{
		cout << "请输入您的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId;	//文件中读取的id
		string fName;	//文件中读取的姓名
		string fPwd;	//文件中读取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户信息做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份子菜单
				studentMenu(person);
				ifs.close();
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId;	//文件中读取的id
		string fName;	//文件中读取的姓名
		string fPwd;	//文件中读取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户信息做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份子菜单
				teacherMenu(person);
				ifs.close();
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName;	//文件中读取的姓名
		string fPwd;	//文件中读取的密码
		while (ifs >> fName && ifs >> fPwd)
		{
			//与用户信息做对比
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员身份子菜单
				ifs.close();
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
}

void managerMenu(Identity*& manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();

		//将父类指针 转为子类指针 ，调用子类里其它接口
		Manager* man = (Manager*)manager;

		//接收用户选项
		int select = 0;
		cin >> select;

		if (select == 1)	//添加账号
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2)	//查看账号
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)		//查看机房
		{
			//cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4)		//清空预约
		{
			//cout << "清空预约" << endl;
			man->clearFile();
		}
		else		//默认注销登录
		{
			delete manager;	//销毁堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学生子菜单
		student->operMenu();

		Student* stu = (Student*)student;

		int select = 0;
		cin >> select;	//接收用户选择

		if (select == 1)	//申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2)	//查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3)	//查看所有预约
		{
			stu->showAllOrder();
		}
		else if (select == 4)	//取消预约
		{
			stu->cancelOrder();
		}
		else		//注销登录
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//调用子菜单界面
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;

		int select = 0;	//接收用户选择
		cin >> select;

		if (select == 1)	//查看所有预约
		{
			tea->showAllOrder();
		}
		else if (select == 2)	//审核预约
		{
			tea->validOrder();
		}
		else			//注销登录
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
