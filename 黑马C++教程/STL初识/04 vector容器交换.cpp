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
	cout << "v的容量：" << v.capacity() << endl;	//10000+
	cout << "v的大小：" << v.size() << endl;		//10000

	v.resize(3);
	vector<int> v2(v);
	cout << "v2的容量：" << v2.capacity() << endl;	//3
	cout << "v2的大小：" << v2.size() << endl;		//3
}

int main()
{
	test01();
	return 0;
}