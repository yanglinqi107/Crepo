#pragma once
// ANSI C++��׼��ͷ�ļ�
#include <cstring>					// ��׼������
#include <iostream>					// ��׼������
using namespace std;
#define DEFAULT_SIZE 100

// ˳��ջģ����
template<class ElemType>
class SqStack
{
protected:
	// ˳��ջ�����ݳ�Ա:
	int top;										// ջ��ָ�� 
	int maxSize;									// ջ��������� 
	ElemType* data;									// Ԫ�ش洢�ռ�
public:
	//  ˳��ջ�ķ������������ر���ϵͳĬ�Ϸ�������:
	SqStack(int size = DEFAULT_SIZE)				// ���캯��
	{
		data = new ElemType[size];
		if (!data)
		{
			exit(OVERFLOW);
		}
		top = 0;
		maxSize = size;
	}

	virtual ~SqStack()							// ��������
	{
		if (data) {
			delete[] data;
		}
	}

	int getLength() const;							// ��ջ�ĳ���	
	
	bool isEmpty() const;							// �ж�ջ�Ƿ�Ϊ��
	
	void clear()									// ��ջ���
	{
		top = 0;
	}

	void traverse(void (*Visit)(const ElemType&)) const;	// ����ջ
	
	int push(const ElemType e);				    // ��ջ

	int getTop(ElemType& e) const;			    // ȡ��Ԫ��
	
	int pop(ElemType& e);					    // ��ջ
	
	SqStack(const SqStack<ElemType>& s)		// ���ƹ��캯��
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

	SqStack<ElemType>& operator =(const SqStack<ElemType>& s); // ��ֵ�������
};

template<class ElemType>
int SqStack<ElemType>::getLength() const							// ��ջ�ĳ���	
{
	return top;
}

template<class ElemType>
bool SqStack<ElemType>::isEmpty() const							// �ж�ջ�Ƿ�Ϊ��
{
	if (top == 0) {
		return true;
	}
	return false;
}

template<class ElemType>
void SqStack<ElemType>::traverse(void (*Visit)(const ElemType&)) const	// ����ջ
{
	for (int i = top; i > 0; i--)
	{
		(*Visit)(data[i]);
	}
}

template<class ElemType>
int SqStack<ElemType>::push(const ElemType e)				    // ��ջ
{
	data[++top] = e;
	return 0;
}
template<class ElemType>
int SqStack<ElemType>::getTop(ElemType& e) const				    // ȡ��Ԫ��
{
	if (top == 0) {
		return 0;
	}
	e = data[top];
	return 1;
}
template<class ElemType>
int SqStack<ElemType>::pop(ElemType& e)					    // ��ջ
{
	if (top == 0) {
		return 0;
	}
	e = data[top--];
	return 1;
}

template<class ElemType>
SqStack<ElemType>& SqStack<ElemType>::operator =(const SqStack<ElemType>& s) // ��ֵ�������
{
	top = s.getLength();
	for (int i = top; i > 0; i--)
	{
		data[i] = s.data[i];
	}
	return *this;
}



