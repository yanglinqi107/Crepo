#include "orderFile.h"

OrderFile::OrderFile()
{
	ifstream ifs(ORDER_FILE, ios::in);

	string date;		//日期
	string interval;	//时间段
	string stuId;		//学生编号
	string stuName;		//学生姓名
	string roomId;		//机房编号
	string status;		//预约状态

	this->m_Size = 0;	//记录条数

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//cout << date << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl;
		//cout << status << endl;
		//cout << endl;

		map<string, string> m;
		subString(m, date);		//截取时间
		subString(m, interval);	//截取时间段
		subString(m, stuId);	//截取学生编号
		subString(m, stuName);	//截取学生姓名
		subString(m, roomId);	//截取机房编号
		subString(m, status);	//截取预约状态

		this->m_OrderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();

	//for (map<int, map<string, string>>::iterator it = m_OrderData.begin(); it != m_OrderData.end(); it++)
	//{
	//	cout << "条数：" << it->first << endl;
	//	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << "key = " << mit->first << " value = " << mit->second << endl;
	//	}
	//}
}

void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}

	ofstream ofs(ORDER_FILE, ios::trunc | ios::out);
	for (int i = 0; i < m_Size; i++)
	{
		ofs << "date:" << m_OrderData[i]["date"] << " ";
		ofs << "interval:" << m_OrderData[i]["interval"] << " ";
		ofs << "stuId:" << m_OrderData[i]["stuId"] << " ";
		ofs << "stuName:" << m_OrderData[i]["stuName"] << " ";
		ofs << "roomId:" << m_OrderData[i]["roomId"] << " ";
		ofs << "status:" << m_OrderData[i]["status"] << endl;
	}
}

void OrderFile::subString(map<string, string>& m, string s)
{
	string key;
	string value;

	int pos = s.find(":");
	if (pos != -1)
	{
		key = s.substr(0, pos);
		value = s.substr(pos + 1, s.size() - pos - 1);
		m.insert(make_pair(key, value));
	}
}
