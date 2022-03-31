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
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//添加账号
	void addPerson();
	
	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void clearFile();

	//初始化容器
	void initVector();

	//检测重复	参数1 学号 或 职工号	参数2 类型
	bool checkRepeat(int id, int type);

public:
	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//机房信息容器
	vector<ComputerRoom> vCom;
};

