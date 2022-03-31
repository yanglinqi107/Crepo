#pragma once
using namespace std;

class Date								/*����Ҫ��--������Date*/
{
public:
	Date(int y = 2000, int m = 1, int d = 1)						//��Ĭ�ϲ����Ĺ��캯��,Ĭ������Ϊ2000.1.1������Ҫ��2��
	{
		year = y;
		month = m;
		day = d;
	}
	void SetDate(int y, int m, int d);								//�˹��趨���ڣ�����Ҫ��1���������ݳ�Ա��
		                                     /*��ȡ��Щ���ݳ�Ա�ĳ�Ա����������Ҫ��1��*/
	int GetYear() { return year; }									//��ȡ�꣨����Ҫ��1��

	int GetMonth() { return month; }								//��ȡ�£�����Ҫ��1��

	int GetDay() { return day; }									//��ȡ�գ�����Ҫ��1��
												
	friend int IsLeagl(int year, int mon, int day);				    //�ж��������Ƿ�Ϸ������Ϸ��򷵻ظ��µ�����������Ҫ��3������£��ս�λ���⣩	

	friend int IsLeapYear(int year);							    //�ж��Ƿ�Ϊ���꣨����Ҫ��3:��
	
	Date operator+(int days);								        //�������ڼ�����days��õ������ڣ�����Ҫ��4������+��ʵ�ּ�n�죩
	
	Date operator-(int days);								        //�������ڼ�ȥ����days��õ������ڣ�����Ҫ��4������-��ʵ�ּ�n�죩
	
	Date operator++();										        //����ǰ������������Ҫ��4������++��ʵ�ּ�1�죩
			
	Date operator--();									            //����ǰ���Լ�������Ҫ��4������--��ʵ�ּ�1�죩
	
	int operator-(Date& b);                                         //���������������������ڼ������
	
	void Print()												   //��ʾ����
	{
		cout << year << "." << month << "." << day << endl;
	}
	
private:															//����Ҫ��1���������ꡢ�¡��յ���Ϣ�����ݳ�Ա��
	int year;															//��
	int month;															//��
	int day;															//��
};

class DateTime :public Date					/*���Ҫ��1--ʱ����DateTime(���м̳�)*/
{
public:
	DateTime(int h = 0, int min = 0, int s = 0);						//��ʼ������

	void SetDateTime(int y, int m, int d, int h, int min, int s);		//�����꣬�£��գ�ʱ���룬��
	
	DateTime operator++();												//ʱ������

	void Print();														//ʱ����ʾ
	
private:														/*����ʱ���֣��룻�̳��꣬�£���*/
	int hour;															//ʱ
	int minute;                                                         //��
	int second;															//��	
};

class CDate :public Date			     /*���Ҫ��2--������CDate*/
{
public:
	CDate() :Date(2000, 1, 2) {}									//��ʼ��Date���꣬�£���Ϊ2000.1.2�����꣬�����գ��Դ�Ϊ��׼

	void Y_Calendar();												//��ʾһ�������
	
	void M_Calendar();												//��ʾһ�µ�����
	
private:
	const char* p_zodiac[12] = { "��","��","��","��","��","��","��","��","��","ţ","��","��" };   //��¼ʮ����Ф
};

int IsLeagl(int year, int mon, int day);

int IsLeapYear(int year);

