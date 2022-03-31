#include<iostream>
#include"Date.h"
using namespace std;

int TimePrint(Date& a, Date& b);				//�߿�����ʱ��ʾ

int main()
{
	Date date1, date2;							//���������������ʼ���ں͸߿����ڣ�
	CDate time;									//����������������������
	int y, m, d;								//����������� �� ��
	int days = 0;								//�����������Ҫ�ӣ���������
										/*��ʼ���ں͸߿����ڵ����루����Ҫ��5��*/
	cout << "��ս�߿���" << endl;
loop:cout << "������ʼʱ�䣨�� �� �գ���";		//��ʾ����
	cin >> y >> m >> d;
	while (IsLeagl(y, m, d) == 0) /*����IsLeagl�ж�����������Ƿ�Ϸ������Ϸ�������*/
	{
		cout << "���ڲ��Ϸ������������룺";
		cin >> y >> m >> d;
	};
	date1.SetDate(y, m, d);								//�����������date1��Ϊ�������ʼ����

	cout << "����߿�ʱ�䣨�� �� �գ���";		//��ʾ����
	cin >> y >> m >> d;
	while (IsLeagl(y, m, d) == 0) /*����IsLeagl�ж�����������Ƿ�Ϸ������Ϸ�������*/
	{
		cout << "���ڲ��Ϸ������������룺";
		cin >> y >> m >> d;
	}
	date2.SetDate(y, m, d);							//�����������date2��Ϊ����ĸ߿�ʱ��

	if (TimePrint(date1, date2) == 1)				/*����TimePrint��ʾ�߿�����ʱ*/
	{
		cout << "ʱ�����\n\n";                   //��������ֵΪ1������ʼ���ڴ��ڸ߿����ڣ�����
		goto loop;									//����loop����������ʼ���ں͸߿�����
	}
										/*���ò˵����û�����*/
	int n;
	do
	{
		n = -1;
		cout << "1.����ʼʱ������\n" << "2.����ʼʱ�����\n" <<"3.��ʾ����\n"<< "0.�˳�\n" << "����������(0-3)��";     //��ʾ�˵�
		cin >> n;
		while (getchar() != '\n');
		switch (n) 
		{
			case 1:										//������ʼʱ��
			{
				cout << "��������������";               //��ʾ����
				cin >> days;
				if (days == 1)							//��������Ϊ1������Date operator++()����
					++date1;
				if (days > 1 || days == 0)				//������������1������Date operator+(int days)
					date1 = date1 + days;
				if (days < 0)							//��������С��0�����ز˵�
				{
					cout << "��������" << endl;
					break;
				}
				TimePrint(date1, date2);				//����int TimePrint(Date& a, Date& b)��ʾ��ʼʱ��ı��ĸ߿�����ʱ
				break;
			}
			case 2:										//������ʼʱ��
			{
				cout << "��������������";				//��ʾ����
				cin >> days;
				if (days == 1)							//��������Ϊ1������Date operator--()�Լ�
					--date1;
				if (days > 1 || days == 0)				//������������1������Date operator-(int days)
					date1 = date1 - days;
				if (days < 0)							//��������С��0�����ز˵�
				{
					cout << "��������" << endl;
					break;
				}
				TimePrint(date1, date2);
				break;
			}
			case 3:										//������ʾ
			{
				int nselect;
				cout << "1.����\n" << "2.����\n" << "���������ţ�1-2����";  //С�˵�
				cin >> nselect;
				if(nselect==1)										//����1������void Y_Calendar()
					time.Y_Calendar();
				if (nselect == 2)									//����2������void M_Calendar()
					time.M_Calendar();
				break;												//�����������������������˵�
			}
			case 0:														
			{
				cout << "�˳���\n";								    //����0���˳����˵������Խ���
				break;
			}
			default:
			{
				cout << "������Ŵ���" << endl;
			}
		}
	} while (n != 0);
	return 0;
}
int IsLeagl(int year, int mon, int day)												//�ж�ʱ���Ƿ�Ϸ������Ϸ�����0�����Ϸ��򷵻ظ��·ݵ�����
{
	if (year < 0 || mon <= 0 || mon>12 || day <= 0 || day > 31)
		return 0;
	if (1 == mon || 3 == mon || 5 == mon || 7 == mon || 8 == mon || 10 == mon || 12 == mon)		//�ж��·��Ƿ�Ϊ����
	{
		if (day > 31)																//��Ϊ���£��ж������Ƿ񳬹�31�죬�����򷵻�0
			return 0;																
		return 31;																	//���ش��µ�����31
	}
	if (4 == mon || 6 == mon || 9 == mon || 11 == mon)											//�ж��·��Ƿ�ΪС��
	{
		if (day > 30)																//��ΪС�£��ж������Ƿ񳬹�30�죬�����򷵻�0
			return 0;
		return 30;																	//����С�µ�����30
	}
	if (IsLeapYear(year))															//����int IsLeapYear(int year)�ж��Ƿ�Ϊ����
	{
		if (2 == mon && day > 29)									//��Ϊ������Ϊ2��,��������29����0
			return 0;
		return 29;														//��������2������29
	}
	else
	{
		if (2 == mon && day > 28)							//����Ϊ���꣬����2�£���������28����0
			return 0;
		return 28;											//���ط�����2�µ�����28
	}
}
int IsLeapYear(int year)													//�ж�����
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))  //�ǰ���������4����������������400
		return 1;
	return 0;
}
int TimePrint(Date& a, Date& b)										//�߿�����ʱ��ʾ������Ҫ��5��
{
	cout << endl;
	cout << "��ʼʱ�䣺";
	a.Print();														//��ʾ��ʼ����
	cout << "�߿�ʱ�䣺";
	b.Print();														//��ʾ�߿�����
	int days = a - b;								/*��������- ������������������������߿�����ʱ����ͨ���������������������ж���ʼ�����Ƿ�С�ڸ߿�����*/
	if (days < 0)										//days<0 �� ��ʼ���ڴ��ڸ߿����� ��������1
		return 1;
	cout << "��߿���ʣ" << days << "��" << endl;       //��ʼ����С�ڸ߿����ڣ����ʣ����������������0
	cout << endl;
	return 0;										  
}

