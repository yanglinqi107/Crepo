#include<iostream>
#include"Date.h"
using namespace std;

void Date::SetDate(int y, int m, int d)								//�����趨����
{
	year = y;
	month = m;
	day = d;
}
Date Date::operator+(int days)									//�������ڼ�����days��õ�������
{
	day = day + days;                                           //����day��������days
										
	while (day > IsLeagl(year, month, 1))			/*����IsLeagl������month���������ж����Ӻ����day�Ƿ������month��������Ϊѭ������*/
	{
		++month;												//��day������month������������month��1
		if (month > 12)											//�ж����������month�Ƿ����12
		{
			++year;												//��month����12������year��1
			month = 1;											//��month��λ��Ϊ1
			day = day - 31;										//��day��ȥԭ����month��12�µ�����31
		}
		else
			day = day - IsLeagl(year, month - 1, 1);			//���������monthС�ڵ���12����day��ȥԭ����month������������IsLeagl,��month���1
	}
	return *this;
}
Date Date::operator-(int days)									//�������ڼ�ȥ����days��õ�������
{
	day = day - days;											//����day��ȥ����days
	while (day < 1)										        //�ж���day�Ƿ�С��1��Ϊѭ������
	{
		--month;												//��dayС�ڣ�����month��1
		if (month < 1)											//�жϼ�1�����month�Ƿ�С��1
		{
			--year;												//��monthС��1������year��1����month��Ϊ12
			month = 12;
		}
		day = day + IsLeagl(year, month, 1);					//�Լ�����´��ڵ���1����day���ϸ���month������������IsLeagl
	}
	return *this;
}
Date Date::operator++()											//����ǰ������
{
	if (++day > IsLeagl(year, month, 1))						//�ж���day�������Ƿ������month������������IsLeagl
	{
		day = 1;												//��day������month����������day��λΪ1,��month��1
		if (++month > 12)										//�ж����Ӻ����month�Ƿ����12
		{
			month = 1;											//��month����12����month��λΪ1����year��1
			++year;												
		}
	}
	return *this;
}
Date Date::operator--()											//����ǰ���Լ�
{
	if (--day < 1)												//�ж���day�Լ����Ƿ�С��1
	{
		if (--month < 1)										//��day�Լ���С��1���ж���month�Լ����Ƿ�С��1
		{
			--year;												//��month�Լ���С��1����year�Լ�����month��Ϊ12����day��Ϊ��month������������IsLeagl
			month = 12;
			day = IsLeagl(year, month, 10);
		}
		day = IsLeagl(year, month, 1);							//��day�Լ���С��1����month�Լ���С��1����day��Ϊ��month������������IsLeagl
	}
	return *this;
}
int Date::operator-(Date& b)                                   //������������������
{
	int days = 0;											   //��¼��������������
	int days1 = 0, days2 = 0;								   //��¼��month��day����year�ĵڼ���
	int n = 0;												   //���ж�����
	int y = year - b.year;									   //��y���������ж�����,�Ƚ�����ݵĴ�С
	int Y;	

	for (int i = 1; i < month; ++i)							   //������month��day����year�ĵڼ��죬����2019.2.1��2019��ĵ�31��
		days1 += IsLeagl(year, i, 1);							
	days1 += day;

	for (int i = 1; i < b.month; ++i)						   //������b.month��b.day����b.year�ĵڼ���
		days2 += IsLeagl(b.year, i, 1);
	days2 += b.day;

	if (y > 0)												   //��С����ݸ�ֵ��y,�����ݸ�ֵ��Y
	{
		y = b.year;
		Y = year;
		n = 1;												   //���������year���ڼ������b.year��n��Ϊ1
	}
	else													   //���������yearС�ڵ��ڼ������b.year��n����
	{
		y = year;
		Y = b.year;
	}
	while (y < Y)											  //�������������������
	{
		if (IsLeapYear(y) == 0)								  //����IsLeapYear�ж�year��b.year֮���Ƿ������꣬�У�days��366���ޣ�days��365
			days += 365;
		if (IsLeapYear(y) == 1)
			days += 366;
		++y;
	}
	if (days == 0)										      //daysΪ0����year����b.year���
		return days2 - days1;								  //�����ȣ�����ڼ���֮�Ϊ�������������,days��������
	if (n == 1)											 //nΪ1����year����b.year��days=�������������days+���ڴ��year��days1-����С��b.year��days2
	{
		days = days + days1 - days2;						
		return -days;										  //days��Ϊ��������-days
	}
	days = days + days2 - days1;		   //n���䣬��days��Ϊ0����yearС��b.year��days=�������������days+���ڴ��b.year��days2-����С��year��days1

	return days;								//days��Ϊ��������days
}/*����ֵdays�����������ж������ڵĴ�С��ϵ������Date(С)-Date(��)������Date(��)-Date(С)�������ж���ʼ�����Ƿ�С�ڸ߿����ڣ�����ȷ�������������*/


DateTime::DateTime(int h, int min, int s) :Date(2000, 1, 1)       //��ʼ��Ϊ2000.1.1 0:0:0
{
	hour = h;
	minute = min;
	second = s;
}
void DateTime::SetDateTime(int y, int m, int d, int h, int min, int s)    //�����趨ʱ��
{
	Date::SetDate(y, m, d);
	hour = h;
	minute = min;
	second = s;
}
DateTime DateTime::operator++()											  //ʱ������
{
	if (++second > 59)													//�ж���second�������Ƿ����59��������second��λΪ0
	{
		second = 0;						
		if (++minute > 59)												//��second��λ���minute����������minute���������59����minute��λΪ0
		{
			minute = 0;
			if (++hour > 23)											//��minute��λ��ʱhour��������ʱhour���������23��ʱhour��λΪ0
			{
				hour = 0;
				Date::operator++();									   //ʱhour��λ�������operator++���������յ�����
			}
		}
	}
	return  *this;
}
void DateTime::Print()												   //��ʾʱ��
{
	Date::Print();
	cout << hour << ":" << minute << ":" << second << endl;
}


void CDate::Y_Calendar()											  //��ʾһ�������
{
	int y = 2000, m = 1, d = 1;										  //yΪ�꣬mΪ�£�dΪ��	
	cout << "������ݣ�";											  //��ʾ����
	cin >> y;
	int z = (y - 2000) % 12;										  //���������ݺͻ�׼�����2000��������12ȡ��,����ֵ��z,z����ȷ����Ф
	if (z < 0)														  //��yС����2000ʱ��zС��0,����12
		z = z + 12;
	Date b(y, m, d);												  //�趨��������󲢳�ʼ��Ϊ��y.1.1
	int week = Date::operator-(b) % 7;								  //���׼����2000.1.1����������������7ȡ�࣬����ֵ��week��week����ȷ������
	if (week < 0)													  //y.1.1С��2000.1.1ʱ��weekΪ��������7
		week += 7;
	cout << "\n\t\t\t" << y << "(" << p_zodiac[z] << "��)" << endl;   //�����ݺ���Ф
	for (m = 1; m <= 12; ++m)										  //��mС�ڵ���12��ѭ������
	{
		cout << " " << m << "��" << endl;							  //�����m
		cout << "\t��\tһ\t��\t��\t��\t��\t��\n";					  //�������
		for (d = 1; d <= IsLeagl(y, m, 1); ++d)						  //��dС�ڵ�����m������ʱ����d����
		{
			week = week % 7;										 //week������������
			if (d == 1)												 //��dΪ1��ÿ�µĵ�һ�죬����β���У��Ű沢��Ӧ�����ڣ����week��\t
			{
				for (int i = 0; i < week; ++i)
					cout << "\t  ";
			}
			cout << "\t" << d;
			if (week == 6)											//weekΪ6,����ʱ��d��Ӧ����������	
				cout << endl;
			++week;													 //week������d����
		}
		cout << endl;												//ÿ��β����
	}
}
void CDate::M_Calendar()
{
	int y = 2000, m = 1, d = 1;										//yΪ�꣬mΪ�£�dΪ��
loop:cout << "���루�� �£���";										//��ʾ����
	cin >> y >> m;
	if (m < 0 || m > 12)											//�ж��·��Ƿ���󣬴���������
	{
		cout << "�������ڴ���";
		goto loop;
	}
	int z = (y - 2000) % 12;										//���������ݺͻ�׼�����2000��������12ȡ��,����ֵ��z,z����ȷ����Ф
	if (z < 0)														//��yС����2000ʱ��zС��0,����12
		z = z + 12;													
	Date b(y, m, d);												//�趨��������󲢳�ʼ��Ϊ��y.��m.1
	int week = Date::operator-(b) % 7;								//���׼����2000.1.1����������������7ȡ�࣬����ֵ��week��week����ȷ������
	if (week < 0)													//y.1.1С��2000.1.1ʱ��weekΪ��������7
		week += 7;
	cout << "\n\t\t\t" << y << "(" << p_zodiac[z] << "��)" << m << "��" << endl;//������,��Ф���·�
	cout << "\t��\tһ\t��\t��\t��\t��\t��\n";						//�������
	for (d = 1; d <= IsLeagl(y, m, 1); ++d)						  //��dС�ڵ�����m������ʱ����d����
	{
		week = week % 7;										 //week������������
		if (d == 1)												 //��dΪ1��ÿ�µĵ�һ�죬����β���У��Ű沢��Ӧ�����ڣ����week��\t
		{
			for (int i = 0; i < week; ++i)
				cout << "\t  ";
		}
		cout << "\t" << d;
		if (week == 6)											//weekΪ6,����ʱ��d��Ӧ����������	
			cout << endl;
		++week;													 //week������d����
	}
	cout << endl;
}
