#pragma once
using namespace std;

class Date								/*基本要求--日期类Date*/
{
public:
	Date(int y = 2000, int m = 1, int d = 1)						//带默认参数的构造函数,默认日期为2000.1.1（基本要求2）
	{
		year = y;
		month = m;
		day = d;
	}
	void SetDate(int y, int m, int d);								//人工设定日期（基本要求1：设置数据成员）
		                                     /*读取这些数据成员的成员函数（基本要求1）*/
	int GetYear() { return year; }									//读取年（基本要求1）

	int GetMonth() { return month; }								//读取月（基本要求1）

	int GetDay() { return day; }									//读取日（基本要求1）
												
	friend int IsLeagl(int year, int mon, int day);				    //判断年月日是否合法，若合法则返回该月的天数（基本要求3：解决月，日进位问题）	

	friend int IsLeapYear(int year);							    //判断是否为闰年（基本要求3:）
	
	Date operator+(int days);								        //返回日期加天数days后得到的日期（基本要求4：重载+，实现加n天）
	
	Date operator-(int days);								        //返回日期减去天数days后得到的日期（基本要求4：重载-，实现减n天）
	
	Date operator++();										        //日期前置自增（基本要求4：重载++，实现加1天）
			
	Date operator--();									            //日期前置自减（基本要求4：重载--，实现减1天）
	
	int operator-(Date& b);                                         //两日期相减，计算出两日期间的天数
	
	void Print()												   //显示日期
	{
		cout << year << "." << month << "." << day << endl;
	}
	
private:															//基本要求1：（描述年、月、日等信息的数据成员）
	int year;															//年
	int month;															//月
	int day;															//日
};

class DateTime :public Date					/*提高要求1--时间类DateTime(公有继承)*/
{
public:
	DateTime(int h = 0, int min = 0, int s = 0);						//初始化数据

	void SetDateTime(int y, int m, int d, int h, int min, int s);		//设置年，月，日，时，秒，分
	
	DateTime operator++();												//时间自增

	void Print();														//时间显示
	
private:														/*描述时，分，秒；继承年，月，日*/
	int hour;															//时
	int minute;                                                         //分
	int second;															//秒	
};

class CDate :public Date			     /*提高要求2--日历类CDate*/
{
public:
	CDate() :Date(2000, 1, 2) {}									//初始化Date的年，月，日为2000.1.2（龙年，星期日）以此为基准

	void Y_Calendar();												//显示一年的日历
	
	void M_Calendar();												//显示一月的日历
	
private:
	const char* p_zodiac[12] = { "龙","蛇","马","羊","猴","鸡","狗","猪","鼠","牛","虎","兔" };   //记录十二生肖
};

int IsLeagl(int year, int mon, int day);

int IsLeapYear(int year);

