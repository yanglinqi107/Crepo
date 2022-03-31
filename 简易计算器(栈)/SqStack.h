#pragma once
// ANSI C++标准库头文件
#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
using namespace std;
#define DEFAULT_SIZE 100

// 顺序栈模板类
template<class ElemType>
class SqStack
{
protected:
	// 顺序栈的数据成员:
	int top;										// 栈顶指针 
	int maxSize;									// 栈的最大容量 
	ElemType* data;									// 元素存储空间
public:
	//  顺序栈的方法声明及重载编译系统默认方法声明:
	SqStack(int size = DEFAULT_SIZE)				// 构造函数
	{
		data = new ElemType[size];
		if (!data)
		{
			exit(OVERFLOW);
		}
		top = 0;
		maxSize = size;
	}

	virtual ~SqStack()							// 析构函数
	{
		if (data) {
			delete[] data;
		}
	}

	int getLength() const;							// 求栈的长度	
	
	bool isEmpty() const;							// 判断栈是否为空
	
	void clear()									// 将栈清空
	{
		top = 0;
	}

	void traverse(void (*Visit)(const ElemType&)) const;	// 遍历栈
	
	int push(const ElemType e);				    // 入栈

	int getTop(ElemType& e) const;			    // 取顶元素
	
	int pop(ElemType& e);					    // 出栈
	
	SqStack(const SqStack<ElemType>& s)		// 复制构造函数
	{
		data = new ElemType[DEFAULT_SIZE];
		if (!data) {
			exit(OVERFLOW);
		}
		maxSize = DEFAULT_SIZE;
		top = s.getLength();
		for (int i = top; i > 0; i--)
		{
			data[i] = s.data[i];
		}
	}

	SqStack<ElemType>& operator =(const SqStack<ElemType>& s); // 赋值语句重载
};

template<class ElemType>
int SqStack<ElemType>::getLength() const							// 求栈的长度	
{
	return top;
}

template<class ElemType>
bool SqStack<ElemType>::isEmpty() const							// 判断栈是否为空
{
	if (top == 0) {
		return true;
	}
	return false;
}

template<class ElemType>
void SqStack<ElemType>::traverse(void (*Visit)(const ElemType&)) const	// 遍历栈
{
	for (int i = top; i > 0; i--)
	{
		(*Visit)(data[i]);
	}
}

template<class ElemType>
int SqStack<ElemType>::push(const ElemType e)				    // 入栈
{
	data[++top] = e;
	return 0;
}
template<class ElemType>
int SqStack<ElemType>::getTop(ElemType& e) const				    // 取顶元素
{
	if (top == 0) {
		return 0;
	}
	e = data[top];
	return 1;
}
template<class ElemType>
int SqStack<ElemType>::pop(ElemType& e)					    // 出栈
{
	if (top == 0) {
		return 0;
	}
	e = data[top--];
	return 1;
}

template<class ElemType>
SqStack<ElemType>& SqStack<ElemType>::operator =(const SqStack<ElemType>& s) // 赋值语句重载
{
	top = s.getLength();
	for (int i = top; i > 0; i--)
	{
		data[i] = s.data[i];
	}
	return *this;
}



