#include<iostream>
#include"Date.h"
using namespace std;

int TimePrint(Date& a, Date& b);				//高考倒计时显示

int main()
{
	Date date1, date2;							//两个日期类对象（起始日期和高考日期）
	CDate time;									//日历类对象，用于日历的输出
	int y, m, d;								//储存输入的年 月 日
	int days = 0;								//储存对日期所要加，减的天数
										/*起始日期和高考日期的输入（基本要求5）*/
	cout << "备战高考！" << endl;
loop:cout << "输入起始时间（年 月 日）：";		//提示输入
	cin >> y >> m >> d;
	while (IsLeagl(y, m, d) == 0) /*调用IsLeagl判断输入的日期是否合法，不合法则重输*/
	{
		cout << "日期不合法，请重新输入：";
		cin >> y >> m >> d;
	};
	date1.SetDate(y, m, d);								//将日期类对象date1设为输入的起始日期

	cout << "输入高考时间（年 月 日）：";		//提示输入
	cin >> y >> m >> d;
	while (IsLeagl(y, m, d) == 0) /*调用IsLeagl判断输入的日期是否合法，不合法则重输*/
	{
		cout << "日期不合法，请重新输入：";
		cin >> y >> m >> d;
	}
	date2.SetDate(y, m, d);							//将日期类对象date2设为输入的高考时间

	if (TimePrint(date1, date2) == 1)				/*调用TimePrint显示高考倒计时*/
	{
		cout << "时间错误！\n\n";                   //函数返回值为1，即起始日期大于高考日期，错误
		goto loop;									//跳到loop重新输入起始日期和高考日期
	}
										/*设置菜单供用户操作*/
	int n;
	do
	{
		n = -1;
		cout << "1.对起始时间增加\n" << "2.对起始时间减少\n" <<"3.显示日历\n"<< "0.退出\n" << "输入操作序号(0-3)：";     //显示菜单
		cin >> n;
		while (getchar() != '\n');
		switch (n) 
		{
			case 1:										//增加起始时间
			{
				cout << "输入所加天数：";               //提示输入
				cin >> days;
				if (days == 1)							//增加天数为1，调用Date operator++()自增
					++date1;
				if (days > 1 || days == 0)				//增加天数大于1，调用Date operator+(int days)
					date1 = date1 + days;
				if (days < 0)							//输入天数小于0，返回菜单
				{
					cout << "天数错误！" << endl;
					break;
				}
				TimePrint(date1, date2);				//调用int TimePrint(Date& a, Date& b)显示起始时间改变后的高考倒计时
				break;
			}
			case 2:										//减少起始时间
			{
				cout << "输入所减天数：";				//提示输入
				cin >> days;
				if (days == 1)							//减少天数为1，调用Date operator--()自减
					--date1;
				if (days > 1 || days == 0)				//减少天数大于1，调用Date operator-(int days)
					date1 = date1 - days;
				if (days < 0)							//输入天数小于0，返回菜单
				{
					cout << "天数错误！" << endl;
					break;
				}
				TimePrint(date1, date2);
				break;
			}
			case 3:										//日历显示
			{
				int nselect;
				cout << "1.年历\n" << "2.月历\n" << "输入操作序号（1-2）：";  //小菜单
				cin >> nselect;
				if(nselect==1)										//输入1，调用void Y_Calendar()
					time.Y_Calendar();
				if (nselect == 2)									//输入2，调用void M_Calendar()
					time.M_Calendar();
				break;												//输入其他不做处理，返回主菜单
			}
			case 0:														
			{
				cout << "退出！\n";								    //输入0，退出主菜单，调试结束
				break;
			}
			default:
			{
				cout << "输入序号错误！" << endl;
			}
		}
	} while (n != 0);
	return 0;
}
int IsLeagl(int year, int mon, int day)												//判断时间是否合法，不合法返回0，若合法则返回该月份的天数
{
	if (year < 0 || mon <= 0 || mon>12 || day <= 0 || day > 31)
		return 0;
	if (1 == mon || 3 == mon || 5 == mon || 7 == mon || 8 == mon || 10 == mon || 12 == mon)		//判断月份是否为大月
	{
		if (day > 31)																//若为大月，判断天数是否超过31天，超过则返回0
			return 0;																
		return 31;																	//返回大月的天数31
	}
	if (4 == mon || 6 == mon || 9 == mon || 11 == mon)											//判断月份是否为小月
	{
		if (day > 30)																//若为小月，判断天数是否超过30天，超过则返回0
			return 0;
		return 30;																	//返回小月的天数30
	}
	if (IsLeapYear(year))															//调用int IsLeapYear(int year)判断是否为闰年
	{
		if (2 == mon && day > 29)									//若为闰年且为2月,天数大于29返回0
			return 0;
		return 29;														//返回闰年2月天数29
	}
	else
	{
		if (2 == mon && day > 28)							//若不为闰年，但是2月，天数大于28返回0
			return 0;
		return 28;											//返回非闰年2月的天数28
	}
}
int IsLeapYear(int year)													//判断闰年
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))  //非百年能整除4，或整百年能整除400
		return 1;
	return 0;
}
int TimePrint(Date& a, Date& b)										//高考倒计时显示（基本要求5）
{
	cout << endl;
	cout << "起始时间：";
	a.Print();														//显示起始日期
	cout << "高考时间：";
	b.Print();														//显示高考日期
	int days = a - b;								/*调用重载- 函数计算两日期相差天数即高考倒计时，并通过函数返回天数的正负判断起始日期是否小于高考日期*/
	if (days < 0)										//days<0 即 起始日期大于高考日期 函数返回1
		return 1;
	cout << "距高考还剩" << days << "天" << endl;       //起始日期小于高考日期，输出剩余天数，函数返回0
	cout << endl;
	return 0;										  
}

