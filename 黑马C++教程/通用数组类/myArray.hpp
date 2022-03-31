#pragma once
#include <iostream>
using namespace std;

template <class T>
class MyArray
{
public:
	//构造函数
	MyArray(int capacity)
	{
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}
	//拷贝构造
	MyArray(const MyArray& arr)
	{
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[this->m_Capacity];
		for (int i = 0; i < this->m_Capacity; ++i)
		{
			//如果T为对象，而且还包含指针，必须需要重载 = 操作符，因为这个等号不是 构造 而是赋值，
			// 普通类型可以直接= 但是指针类型需要深拷贝
			pAddress[i] = arr.pAddress[i];
		}
	}
	//重载= 运算符 防止浅拷贝问题
	MyArray& operator=(const MyArray& arr)
	{
		~MyArray();

		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[this->m_Capacity];

		for (int i = 0; i < this->m_Size; ++i)
		{
			this->pAddress = arr.pAddress[i];
		}
		return *this;
	}
	//重载[] 运算符
	T& operator[](int index)
	{
		return this->pAddress[index];	//不考虑越界，用户自己去处理
	}
	//尾插法
	void Push_back(const T& val)
	{
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}
	//尾删法
	void Pop_back()
	{
		if (this->m_Size == 0)
		{
			return;
		}
		this->m_Size--;
	}
	//获取数组的容量
	int getCapacity()
	{
		return this->m_Capacity;
	}
	//获取数组大小
	int getSize()
	{
		return this->m_Size;
	}
	//析构函数
	~MyArray()
	{
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
	}
private:
	T* pAddress;	//指向堆空间，存储数据
	int m_Capacity;	//容量
	int m_Size;		//大小
};