#pragma once
//#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
#include "struct.h"
using namespace std;

#define DEFAULT_SIZE 1000			// 缺省元素个数
#define DEFAULT_INFINITY 1000000	// 缺省无穷大



template<class T>
class SqList
{
private:
	T* data;	//保持不变，NULL不存在
	int length;	//实际存放元素的个数
	int listsize;//可以容纳的最大元素的个数

public:
	SqList()
	{
		data = new T[DEFAULT_SIZE];
		if (!data)
		{
			exit(OVERFLOW);
		}
		length = 0;
		listsize = DEFAULT_INFINITY;
	}

	~SqList()
	{
		if (data)
		{
			delete[] data;
		}
	}

	void InputList(int n)
	{
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			Input(data[i]);
			length++;
		}
		cout << endl;
	}
	int GetElem(int i, T& e) const	// 取顺序表中第i个元素的值	
	{
		if (i > length)
			return 0;
		else
		{
			e = data[i - 1];
		}
		return 1;
	}

	int InsertTail(const T& e)        // 在顺序表表尾插入元素
	{
		for (int i = 0; i < length; i++)
		{
			if (repetition(data[i], e))
			{
				return 0;
			}
		}
		data[length++] = e;
		return 1;
	}

	int Insert(int i, T e)	//在i的位置插入一个元素
	{
		if (i > length + 1)
			return 0;
		else
		{
			int j = length - 1;
			for (; j > i - 2; j--) {
				data[j + 1] = data[j];
			}
			data[j + 1] = e;
			length++;
		}
		return 1;
	}

	int Delete(int i, T& e)	//删除i位置的元素
	{
		if (i > length || length == 0)
		{
			return 0;
		}
		else
		{
			i--;
			e = data[i];
			for (; i < length; i++)
			{
				data[i] = data[i + 1];
			}
			length--;
		}
		return	1;
	}

	int Update(int i, T e)	//在i位置更新一个元素
	{
		if (i > length || length == 0)
			return 0;
		else
		{
			data[i - 1] = e;
		}
		return 1;
	}

	int Locate(T e)			//根据元素查找在线性表中的位置
	{
		for (int i = 0; i < length; i++)
		{
			if (data[i] == e)
			{
				return i + 1;
			}
		}
		return 0;
	}

	int GetLength() const		// 取顺序表长度		
	{
		return length;
	}

	bool IsEmpty() const		// 判断顺序表是否为空
	{
		if (length == 0) {
			return false;
		}
		return true;
	}

	void Clear()				// 将顺序表清空
	{
		if (length != 0) {
			length = 0;
		}
	}

	SqList<T>& operator =(const SqList<T>& sa) // 赋值语句重载
	{
		length = sa.GetLength();
		listsize = DEFAULT_INFINITY;
		for (int i = 0; i < length; i++)
			sa.GetElem(i + 1, data[i]);
		return *this;
	}
	template<typename T>
	void Input(T& e)
	{

	}
	void Input(Vex& e)
	{
		cout << "输入城市  编号：" << endl;
		cin >> e.Name >> e.Code;
	}

	void Input(Edge& e)
	{
		cout << "顶点1  顶点2  权值：" << endl;
		cin >> e.vex1.Code >> e.vex2.Code >> e.weight;
		/*cout << "输入第一个顶点编号：";
		cin >> e.vex1.Code;
		cout << "输入第二个顶点编号：";
		cin >> e.vex2.Code;
		cout << "输入两顶点间的权值：";
		cin >> e.weight;*/
	}

	template<typename T>
	bool repetition(T e1,T e2)
	{
		return false;
	}
	bool repetition(Vex e1,Vex e2)
	{
		if (strcmp(e1.Code, e2.Code) == 0 || strcmp(e1.Name, e2.Name) == 0)
		{
			return true;
		}
		return false;
	}

	/*bool repetition(Edge e1, Edge e2)
	{
		if(repetition(e1.vex1,e2.vex1)
		return false;
	}*/
};



