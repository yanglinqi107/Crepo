#include<cmath>
#include "SqStack.h"
using namespace std;

void Transfer(char* equation, SqStack<char>& sqChar);			//将输入的中缀表达式变为后缀表达式并存入字符栈中

int Priority(char str);											//返回运算符的优先级

void Calculate(SqStack<char>& sqChar);							//计算后缀表达式

int main() 
{
	SqStack<int> sqInt;
	SqStack<char> sqChar;
	char* p = new char[20];
	string equa;
	int i = 0;
	cout << "输入一个算式（没有空格，以=结束）：" << endl;
	do {
		cin >> p[i];
		i++;
	} while (p[i - 1] != '=');
	cout << "后缀表达式：";
	Transfer(p, sqChar);
	Calculate(sqChar);
	if (p)
	{
		delete[] p;
	}
	return 0;
}

void Calculate(SqStack<char>& schar)			//计算后缀表达式
{
	SqStack<int> sint;
	char e;
	int back, front;
	int num = 0;
	while (!schar.isEmpty())
	{
		schar.pop(e);
		if (e >= '0' && e <= '9')				//对char数字处理为int,存入整型栈中
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
				sint.pop(back);						//取栈顶的两个数进行计算
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
				sint.push(num);						//将计算得到的数压入栈中
			}
		}
	}
	sint.getTop(num);
	cout << endl << num;
}

void Transfer(char* equation, SqStack<char>& sqChar)				//将输入的中缀表达式变为后缀表达式并存入字符栈中
{
	SqStack<char> s1;							
	SqStack<char> s2;
	int i = 0;
	char e;
	while (equation[i] != '=')
	{
		if (equation[i] >= '0' && equation[i] <= '9')				//数字直接进栈
		{
			s1.push(equation[i]);
		}
		else {
			if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')
			{
				s1.push(' ');										//不同的数字用空格隔开
				while(true) 
				{
					s2.getTop(e);
					if (s2.isEmpty() || e == '(')					
					{
						s2.push(equation[i]);
						break;
					}
					else if (Priority(equation[i]) > Priority(e))	//比较优先级
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
		s1.push(e);						//处理得到的后缀表达式存在字符栈s1中
	}
	while (!s1.isEmpty())				//栈后进先出，将s1倒置存入s2
	{
		s1.pop(e);
		s2.push(e);
	}
	sqChar = s2;						//调用赋值语句重载，将s2赋给sqChar用于计算
	while (!s2.isEmpty())				//输出后缀表达式
	{
		s2.pop(e);
		cout << e;
	}
}

int Priority(char str)							//返回运算符的优先级
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


