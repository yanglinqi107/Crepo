#pragma once
#ifndef __STACK_H__
#define __STACK_H__
#include<stdio.h>
#include<malloc.h>
#include<iostream>
#define MaxSize 100

template<class ElemType>
class Stack
{
private:
	typedef struct
	{
		ElemType* data[MaxSize];
		int Top;//栈顶指针
	}SqStack;
	SqStack* S;
public:
	Stack()
	{
		S = new SqStack;
		S->Top = -1;
	}
	~Stack()
	{
		if (S)
		{
			delete S;
		}
	}
	bool Push(ElemType* e)//将元素e压入栈中
	{
		if (S->Top < 99)
		{	
			S->data[++S->Top] = e;
			return true;
		}
		return false;
	}
	bool Pop(ElemType*& e)//栈顶元素出栈赋值给e
	{
		if (S->Top == -1)
			return false;
		else
		{
			e = S->data[S->Top--];
			return true;
		}
	}
	bool GetTop(ElemType*& e)//将栈顶元素赋值给e，并不进行出栈操作
	{
		if (S->Top == -1)
			return false;
		else
		{
			e = S->data[S->Top];
			return true;
		}
	}
	bool StackEmpty()//判断栈是否为空
	{
		if (S->Top == -1)
			return true;
		else
			return false;
	}
	int GetNum()//得到栈顶指针
	{
		return S->Top;
	}
	ElemType* GetElement(int suf)//得到栈中指针为suf的元素
	{
		if (suf >= 0 && suf <= S->Top)
		{
			return S->data[suf];
		}
		else
			return NULL;
	}
};
#endif //!__STACK_H__

