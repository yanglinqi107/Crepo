#pragma once
//#include <cstring>					// ��׼������
#include <iostream>					// ��׼������
#include "struct.h"
using namespace std;

#define DEFAULT_SIZE 1000			// ȱʡԪ�ظ���
#define DEFAULT_INFINITY 1000000	// ȱʡ�����



template<class T>
class SqList
{
private:
	T* data;	//���ֲ��䣬NULL������
	int length;	//ʵ�ʴ��Ԫ�صĸ���
	int listsize;//�������ɵ����Ԫ�صĸ���

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
	int GetElem(int i, T& e) const	// ȡ˳����е�i��Ԫ�ص�ֵ	
	{
		if (i > length)
			return 0;
		else
		{
			e = data[i - 1];
		}
		return 1;
	}

	int InsertTail(const T& e)        // ��˳����β����Ԫ��
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

	int Insert(int i, T e)	//��i��λ�ò���һ��Ԫ��
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

	int Delete(int i, T& e)	//ɾ��iλ�õ�Ԫ��
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

	int Update(int i, T e)	//��iλ�ø���һ��Ԫ��
	{
		if (i > length || length == 0)
			return 0;
		else
		{
			data[i - 1] = e;
		}
		return 1;
	}

	int Locate(T e)			//����Ԫ�ز��������Ա��е�λ��
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

	int GetLength() const		// ȡ˳�����		
	{
		return length;
	}

	bool IsEmpty() const		// �ж�˳����Ƿ�Ϊ��
	{
		if (length == 0) {
			return false;
		}
		return true;
	}

	void Clear()				// ��˳������
	{
		if (length != 0) {
			length = 0;
		}
	}

	SqList<T>& operator =(const SqList<T>& sa) // ��ֵ�������
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
		cout << "�������  ��ţ�" << endl;
		cin >> e.Name >> e.Code;
	}

	void Input(Edge& e)
	{
		cout << "����1  ����2  Ȩֵ��" << endl;
		cin >> e.vex1.Code >> e.vex2.Code >> e.weight;
		/*cout << "�����һ�������ţ�";
		cin >> e.vex1.Code;
		cout << "����ڶ��������ţ�";
		cin >> e.vex2.Code;
		cout << "������������Ȩֵ��";
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



