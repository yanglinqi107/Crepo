#include<cmath>
#include "SqStack.h"
using namespace std;

void Transfer(char* equation, SqStack<char>& sqChar);			//���������׺���ʽ��Ϊ��׺���ʽ�������ַ�ջ��

int Priority(char str);											//��������������ȼ�

void Calculate(SqStack<char>& sqChar);							//�����׺���ʽ

int main() 
{
	SqStack<int> sqInt;
	SqStack<char> sqChar;
	char* p = new char[20];
	string equa;
	int i = 0;
	cout << "����һ����ʽ��û�пո���=��������" << endl;
	do {
		cin >> p[i];
		i++;
	} while (p[i - 1] != '=');
	cout << "��׺���ʽ��";
	Transfer(p, sqChar);
	Calculate(sqChar);
	if (p)
	{
		delete[] p;
	}
	return 0;
}

void Calculate(SqStack<char>& schar)			//�����׺���ʽ
{
	SqStack<int> sint;
	char e;
	int back, front;
	int num = 0;
	while (!schar.isEmpty())
	{
		schar.pop(e);
		if (e >= '0' && e <= '9')				//��char���ִ���Ϊint,��������ջ��
		{
			num = ((int)e - 48) * 10;
			char f;
			do {
				schar.getTop(f);
				if (f >= '0' && f <= '9')
				{
					schar.pop(e);
					num = (num + ((int)e - 48)) * 10;
				}
			} while (f >= '0' && f <= '9');
			sint.push(num / 10);
		}
		else {
			if (e == ' ')
			{

			}
			else
			{
				sint.pop(back);						//ȡջ�������������м���
				sint.pop(front);
				switch (e)
				{
				case'*':num = front * back; break;
				case'/':num = front / back; break;
				case'+':num = front + back; break;
				case'-':num = front - back; break;
				default:
					break;
				}
				sint.push(num);						//������õ�����ѹ��ջ��
			}
		}
	}
	sint.getTop(num);
	cout << endl << num;
}

void Transfer(char* equation, SqStack<char>& sqChar)				//���������׺���ʽ��Ϊ��׺���ʽ�������ַ�ջ��
{
	SqStack<char> s1;							
	SqStack<char> s2;
	int i = 0;
	char e;
	while (equation[i] != '=')
	{
		if (equation[i] >= '0' && equation[i] <= '9')				//����ֱ�ӽ�ջ
		{
			s1.push(equation[i]);
		}
		else {
			if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')
			{
				s1.push(' ');										//��ͬ�������ÿո����
				while(true) 
				{
					s2.getTop(e);
					if (s2.isEmpty() || e == '(')					
					{
						s2.push(equation[i]);
						break;
					}
					else if (Priority(equation[i]) > Priority(e))	//�Ƚ����ȼ�
					{
						s2.push(equation[i]);
						break;
					}
					else
					{
						s2.pop(e);
						s1.push(e);
					}
				}
			}
			else if (equation[i] == '(')
			{
				s2.push(equation[i]);
			}
			else if(equation[i] == ')')
			{
				do {
					if (!s2.pop(e))
						exit(0);
					if (e != '(')
					{
						s1.push(e);
					}
				} while (e != '(');
			}
		}
		i++;
	}
	while(!s2.isEmpty())
	{
		s2.pop(e);
		s1.push(e);						//����õ��ĺ�׺���ʽ�����ַ�ջs1��
	}
	while (!s1.isEmpty())				//ջ����ȳ�����s1���ô���s2
	{
		s1.pop(e);
		s2.push(e);
	}
	sqChar = s2;						//���ø�ֵ������أ���s2����sqChar���ڼ���
	while (!s2.isEmpty())				//�����׺���ʽ
	{
		s2.pop(e);
		cout << e;
	}
}

int Priority(char str)							//��������������ȼ�
{
	switch (str)
	{
	case'*':return 2; break;
	case'/':return 2; break;
	case'+':return 1; break;
	case'-':return 1; break;
	case'(':return 0; break;
	default:
		break;
	}
	exit(0);
}


