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
		cout << "职员编号：" << number << endl;
		cout << "名字：" << name << endl;
		cout << "薪水：" << salary << endl;
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
		cout << "输入销售额：";
		cin >> sales;
		double s = commrate * sales;
		Employee::Sersalary(s);
		return s;
	}
	void print() 
	{
		Employee::print();
		cout << "销售额：" << sales << endl;
		cout << "提成比例：" << commrate << endl;
	}
private:
	double commrate, sales;
};
class Salesmanager :public Salesman
{
public:
	Salesmanager(int n, const char* pn) :Salesman(n, pn) { monthlypay = 4000; Employee::Sersalary(0.002); }
	void pay() { double s = monthlypay + Salesman::pay(); Employee::Sersalary(s); }
	void print() { Salesman::print(); cout << "底薪：" << monthlypay << endl; }
private:
	double monthlypay;
};
int main()
{
	Salesman sman[4] = { Salesman(1,"小明"),Salesman(2,"张三"), Salesman(3,"李四"),Salesman(4,"王二") };
	Salesmanager smanager[2] = { Salesmanager(5,"麻子"),Salesmanager(6,"狗剩") };
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


