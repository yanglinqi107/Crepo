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
		int Top;//ջ��ָ��
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
	bool Push(ElemType* e)//��Ԫ��eѹ��ջ��
	{
		if (S->Top < 99)
		{	
			S->data[++S->Top] = e;
			return true;
		}
		return false;
	}
	bool Pop(ElemType*& e)//ջ��Ԫ�س�ջ��ֵ��e
	{
		if (S->Top == -1)
			return false;
		else
		{
			e = S->data[S->Top--];
			return true;
		}
	}
	bool GetTop(ElemType*& e)//��ջ��Ԫ�ظ�ֵ��e���������г�ջ����
	{
		if (S->Top == -1)
			return false;
		else
		{
			e = S->data[S->Top];
			return true;
		}
	}
	bool StackEmpty()//�ж�ջ�Ƿ�Ϊ��
	{
		if (S->Top == -1)
			return true;
		else
			return false;
	}
	int GetNum()//�õ�ջ��ָ��
	{
		return S->Top;
	}
	ElemType* GetElement(int suf)//�õ�ջ��ָ��Ϊsuf��Ԫ��
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

