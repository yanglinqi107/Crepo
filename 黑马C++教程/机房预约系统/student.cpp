#include "student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
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
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Student::applyOrder()
{
	int date;			//日期
	int interval = 0;	//时间段
	int room = 0;		//机房编号

	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入选择的机房号：" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		bool flag = false;	//判断是否跳出循环
		for (int i = 0; i < vCom.size(); i++)
		{
			if (room == vCom[i].m_ComId)
			{
				flag = true;
				break;
			}
		}
		if (flag) break;
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "预约成功，审核中" << endl;

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
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	int num = 0;	//记录自身预约条数
	for (int i = 0; i < of.m_Size; i++)
	{
		//c_str(): string转成C风格的字符串 const char*
		//atoi: const char* 转int   
		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))	
		{
			cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
			cout << "时段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
			cout << "机房号：" << of.m_OrderData[i]["roomId"] << " ";
			string status = "状态：";	//1 审核中	2 预约成功	-1 预约失败	   0 取消预约
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_OrderData[i]["status"] == "-1")
			{
				status += "预约失败，审核未通过";
			}
			else if (of.m_OrderData[i]["status"] == "0")
			{
				status += "预约已取消";
			}
			cout << status << endl;
			
			num++;
		}
	}
	if (num == 0)
	{
		cout << "无预约记录" << endl;
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
		cout << "时段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
		cout << "学号：" << of.m_OrderData[i]["stuId"] << " ";
		cout << "姓名：" << of.m_OrderData[i]["stuName"] << " ";
		cout << "机房号：" << of.m_OrderData[i]["roomId"] << " ";
		string status = "状态：";	//1 审核中	2 预约成功	-1 预约失败	   0 取消预约
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_OrderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else if (of.m_OrderData[i]["status"] == "0")
		{
			status += "预约已取消";
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
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
	}
	cout << "审核中或预约成功的记录可以取消" << endl;
	vector<int> v;	//存放显示地记录在map中的下标编号
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断是自身记录
		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))
		{
			//在筛选状态
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、 ";
				cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
				cout << "时段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
				cout << "机房号：" << of.m_OrderData[i]["roomId"] << " ";
				string status = "状态：";	//1 审核中	2 预约成功	-1 预约失败	   0 取消预约
				if (of.m_OrderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				else if (of.m_OrderData[i]["status"] == "-1")
				{
					status += "预约失败，审核未通过";
				}
				else if (of.m_OrderData[i]["status"] == "0")
				{
					status += "预约已取消";
				}
				cout << status << endl;
			}
		}
	}
	if (index == 1)
	{
		cout << "无可取消记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "请输入要取消的记录序号，0代表返回" << endl;
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
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}
