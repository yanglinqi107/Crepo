#include <iostream>
#include <vector>
using namespace std;

void test01()
{
	vector<int> v;
	for (int i = 0; i < 10000; i++)
	{
		v.push_back(i);
	}
	cout << "v��������" << v.capacity() << endl;	//10000+
	cout << "v�Ĵ�С��" << v.size() << endl;		//10000

	v.resize(3);
	vector<int> v2(v);
	cout << "v2��������" << v2.capacity() << endl;	//3
	cout << "v2�Ĵ�С��" << v2.size() << endl;		//3
}

int main()
{
	test01();
	return 0;
}