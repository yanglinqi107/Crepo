#include<iostream>
#include"Date.h"
using namespace std;

void Date::SetDate(int y, int m, int d)								//自主设定日期
{
	year = y;
	month = m;
	day = d;
}
Date Date::operator+(int days)									//返回日期加天数days后得到的日期
{
	day = day + days;                                           //用日day加上天数days
										
	while (day > IsLeagl(year, month, 1))			/*调用IsLeagl返回月month的天数，判断增加后的日day是否大于月month的天数作为循环条件*/
	{
		++month;												//日day大于月month的天数，则月month增1
		if (month > 12)											//判断自增后的月month是否大于12
		{
			++year;												//月month大于12，则年year增1
			month = 1;											//月month进位变为1
			day = day - 31;										//日day减去原来月month即12月的天数31
		}
		else
			day = day - IsLeagl(year, month - 1, 1);			//自增后的月month小于等于12，日day减去原有月month的天数，调用IsLeagl,月month需减1
	}
	return *this;
}
Date Date::operator-(int days)									//返回日期减去天数days后得到的日期
{
	day = day - days;											//用日day减去天数days
	while (day < 1)										        //判断日day是否小于1作为循环条件
	{
		--month;												//日day小于，则月month减1
		if (month < 1)											//判断减1后的月month是否小于1
		{
			--year;												//月month小于1，则年year减1，月month变为12
			month = 12;
		}
		day = day + IsLeagl(year, month, 1);					//自减后的月大于等于1，日day加上该月month的天数，调用IsLeagl
	}
	return *this;
}
Date Date::operator++()											//日期前置自增
{
	if (++day > IsLeagl(year, month, 1))						//判断日day自增后是否大于月month的天数，调用IsLeagl
	{
		day = 1;												//日day大于月month的天数，日day进位为1,月month增1
		if (++month > 12)										//判断增加后的月month是否大于12
		{
			month = 1;											//月month大于12，月month进位为1，年year增1
			++year;												
		}
	}
	return *this;
}
Date Date::operator--()											//日期前置自减
{
	if (--day < 1)												//判断日day自减后是否小于1
	{
		if (--month < 1)										//日day自减后小于1，判断月month自减后是否小于1
		{
			--year;												//月month自减后小于1，年year自减，月month变为12，日day变为月month的天数，调用IsLeagl
			month = 12;
			day = IsLeagl(year, month, 10);
		}
		day = IsLeagl(year, month, 1);							//日day自减后小于1，月month自减后不小于1，日day变为月month的天数，调用IsLeagl
	}
	return *this;
}
int Date::operator-(Date& b)                                   //返回两日期相差的天数
{
	int days = 0;											   //记录两日期相差的天数
	int days1 = 0, days2 = 0;								   //记录月month日day是年year的第几天
	int n = 0;												   //作判断条件
	int y = year - b.year;									   //以y的正负作判断条件,比较两年份的大小
	int Y;	

	for (int i = 1; i < month; ++i)							   //计算月month日day在年year的第几天，例：2019.2.1是2019年的第31天
		days1 += IsLeagl(year, i, 1);							
	days1 += day;

	for (int i = 1; i < b.month; ++i)						   //计算月b.month日b.day在年b.year的第几天
		days2 += IsLeagl(b.year, i, 1);
	days2 += b.day;

	if (y > 0)												   //将小的年份赋值给y,大的年份赋值给Y
	{
		y = b.year;
		Y = year;
		n = 1;												   //被减数年份year大于减数年份b.year，n变为1
	}
	else													   //被减数年份year小于等于减数年份b.year，n不变
	{
		y = year;
		Y = b.year;
	}
	while (y < Y)											  //计算两个年份相差的天数
	{
		if (IsLeapYear(y) == 0)								  //调用IsLeapYear判断year和b.year之间是否有闰年，有：days加366；无：days加365
			days += 365;
		if (IsLeapYear(y) == 1)
			days += 366;
		++y;
	}
	if (days == 0)										      //days为0即年year和年b.year相等
		return days2 - days1;								  //年份相等，该年第几天之差即为两日期相差天数,days正负不定
	if (n == 1)											 //n为1，即year大于b.year，days=两年份相差的天数days+日期大的year的days1-日期小的b.year的days2
	{
		days = days + days1 - days2;						
		return -days;										  //days必为正，返回-days
	}
	days = days + days2 - days1;		   //n不变，且days不为0，即year小于b.year，days=两年份相差的天数days+日期大的b.year的days2-日期小的year的days1

	return days;								//days必为正，返回days
}/*返回值days的正负用于判断两日期的大小关系，正：Date(小)-Date(大)；负：Date(大)-Date(小)；用于判断起始日期是否小于高考日期，用于确定日历类的星期*/


DateTime::DateTime(int h, int min, int s) :Date(2000, 1, 1)       //初始化为2000.1.1 0:0:0
{
	hour = h;
	minute = min;
	second = s;
}
void DateTime::SetDateTime(int y, int m, int d, int h, int min, int s)    //自主设定时间
{
	Date::SetDate(y, m, d);
	hour = h;
	minute = min;
	second = s;
}
DateTime DateTime::operator++()											  //时间自增
{
	if (++second > 59)													//判断秒second自增后是否大于59，是则秒second进位为0
	{
		second = 0;						
		if (++minute > 59)												//秒second进位则分minute自增，若分minute自增后大于59，分minute进位为0
		{
			minute = 0;
			if (++hour > 23)											//分minute进位则时hour自增，若时hour自增后大于23，时hour进位为0
			{
				hour = 0;
				Date::operator++();									   //时hour进位，则调用operator++进行年月日的自增
			}
		}
	}
	return  *this;
}
void DateTime::Print()												   //显示时间
{
	Date::Print();
	cout << hour << ":" << minute << ":" << second << endl;
}


void CDate::Y_Calendar()											  //显示一年的日历
{
	int y = 2000, m = 1, d = 1;										  //y为年，m为月，d为日	
	cout << "输入年份：";											  //提示输入
	cin >> y;
	int z = (y - 2000) % 12;										  //将输入的年份和基准的年份2000相减后除于12取余,并赋值给z,z用于确定生肖
	if (z < 0)														  //年y小于年2000时，z小于0,加上12
		z = z + 12;
	Date b(y, m, d);												  //设定日期类对象并初始化为年y.1.1
	int week = Date::operator-(b) % 7;								  //与基准日期2000.1.1相减的相差天数除于7取余，并赋值给week，week用于确定星期
	if (week < 0)													  //y.1.1小于2000.1.1时，week为负，加上7
		week += 7;
	cout << "\n\t\t\t" << y << "(" << p_zodiac[z] << "年)" << endl;   //输出年份和生肖
	for (m = 1; m <= 12; ++m)										  //月m小于等于12做循环条件
	{
		cout << " " << m << "月" << endl;							  //输出月m
		cout << "\t日\t一\t二\t三\t四\t五\t六\n";					  //输出星期
		for (d = 1; d <= IsLeagl(y, m, 1); ++d)						  //日d小于等于月m的天数时，日d自增
		{
			week = week % 7;										 //week做换行条件，
			if (d == 1)												 //日d为1即每月的第一天，因月尾换行，排版并对应上星期，输出week个\t
			{
				for (int i = 0; i < week; ++i)
					cout << "\t  ";
			}
			cout << "\t" << d;
			if (week == 6)											//week为6,即此时日d对应周六，换行	
				cout << endl;
			++week;													 //week跟随日d自增
		}
		cout << endl;												//每月尾换行
	}
}
void CDate::M_Calendar()
{
	int y = 2000, m = 1, d = 1;										//y为年，m为月，d为日
loop:cout << "输入（年 月）：";										//提示输入
	cin >> y >> m;
	if (m < 0 || m > 12)											//判断月份是否错误，错误则重输
	{
		cout << "输入日期错误！";
		goto loop;
	}
	int z = (y - 2000) % 12;										//将输入的年份和基准的年份2000相减后除于12取余,并赋值给z,z用于确定生肖
	if (z < 0)														//年y小于年2000时，z小于0,加上12
		z = z + 12;													
	Date b(y, m, d);												//设定日期类对象并初始化为年y.月m.1
	int week = Date::operator-(b) % 7;								//与基准日期2000.1.1相减的相差天数除于7取余，并赋值给week，week用于确定星期
	if (week < 0)													//y.1.1小于2000.1.1时，week为负，加上7
		week += 7;
	cout << "\n\t\t\t" << y << "(" << p_zodiac[z] << "年)" << m << "月" << endl;//输出年份,生肖和月份
	cout << "\t日\t一\t二\t三\t四\t五\t六\n";						//输出星期
	for (d = 1; d <= IsLeagl(y, m, 1); ++d)						  //日d小于等于月m的天数时，日d自增
	{
		week = week % 7;										 //week做换行条件，
		if (d == 1)												 //日d为1即每月的第一天，因月尾换行，排版并对应上星期，输出week个\t
		{
			for (int i = 0; i < week; ++i)
				cout << "\t  ";
		}
		cout << "\t" << d;
		if (week == 6)											//week为6,即此时日d对应周六，换行	
			cout << endl;
		++week;													 //week跟随日d自增
	}
	cout << endl;
}
