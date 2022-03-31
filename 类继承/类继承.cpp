#include <iostream>
using namespace std;
class Employee
{
public:
	Employee(int n, const char* pn)
	{
		number = n;
		strcpy_s(name, pn);
		salary = 0;
	}
	void Sersalary(double s) { salary = s; }
	int getnumber() { return number; }
	void print()
	{
		cout << "ְԱ��ţ�" << number << endl;
		cout << "���֣�" << name << endl;
		cout << "нˮ��" << salary << endl;
	}
private:
	int number;
	char name[10];
	double salary;
};
class Salesman :public Employee
{
public:
	Salesman(int n, const char* pn) :Employee(n, pn) { commrate = 0.005; sales = 0; }
	void Setrate(double rate) { commrate = rate; }
	double pay()
	{
		cout << "�������۶";
		cin >> sales;
		double s = commrate * sales;
		Employee::Sersalary(s);
		return s;
	}
	void print() 
	{
		Employee::print();
		cout << "���۶" << sales << endl;
		cout << "��ɱ�����" << commrate << endl;
	}
private:
	double commrate, sales;
};
class Salesmanager :public Salesman
{
public:
	Salesmanager(int n, const char* pn) :Salesman(n, pn) { monthlypay = 4000; Employee::Sersalary(0.002); }
	void pay() { double s = monthlypay + Salesman::pay(); Employee::Sersalary(s); }
	void print() { Salesman::print(); cout << "��н��" << monthlypay << endl; }
private:
	double monthlypay;
};
int main()
{
	Salesman sman[4] = { Salesman(1,"С��"),Salesman(2,"����"), Salesman(3,"����"),Salesman(4,"����") };
	Salesmanager smanager[2] = { Salesmanager(5,"����"),Salesmanager(6,"��ʣ") };
	for(int i = 0; i < 4; i++)
	{
		sman[i].pay();
		sman[i].print();
		cout << endl;
	}
	smanager[0].pay();
	smanager[0].print();
	cout << endl;
	smanager[1].pay();
	smanager[1].print();
	return 0;
}


