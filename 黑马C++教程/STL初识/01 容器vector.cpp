//#include <iostream>
//#include <vector>
//#include <algorithm>	//标准算法头文件
//using namespace std;
//
//void myPrint(int val)
//{
//	cout << val << endl;
//}
//
//int main()
//{
//	//创建vector容器对象，并且通过模板参数指定容器中存放的数据的类型
//	vector<int> v;
//	//向容器中放数据
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	//cout << typeid(v.begin()).name() << endl;
//
//	//通过迭代器访问容器中的数据
//
//	//每一个容器都有自己的迭代器，迭代器是用来遍历容器中的元素
//	//v.begin()返回迭代器，这个迭代器指向容器中第一个数据
//	//v.end()返回迭代器，这个迭代器指向容器元素的最后一个元素的下一个位置
//	//vector<int>::iterator 拿到vector<int>这种容器的迭代器类型
//	vector<int>::iterator itBegin = v.begin();
//	vector<int>::iterator itEnd = v.end();
//	//第一种遍历方式
//	while (itBegin != itEnd)
//	{
//		cout << *itBegin << endl;
//		itBegin++;
//	}
//
//	//第二种遍历方式
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << endl;
//	}
//
//	//第三种遍历方式，使用STL提供的遍历算法
//	for_each(v.begin(), v.end(), myPrint);
//
//	return 0;
//}
//
