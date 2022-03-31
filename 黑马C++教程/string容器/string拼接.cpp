#include <iostream>
using namespace std;

/*
* `string& operator+=(const char* str);`                   //����+=������
* `string& operator+=(const char c);`                         //����+=������
* `string& operator+=(const string& str);`                //����+=������
* `string& append(const char *s); `                               //���ַ���s���ӵ���ǰ�ַ�����β
* `string& append(const char *s, int n);`                 //���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
* `string& append(const string &s);`                           //ͬoperator+=(const string& str)
* `string& append(const string &s, int pos, int n);`	//�ַ���s�д�pos��ʼ��n���ַ����ӵ��ַ�����β
*/

void test01()
{
	string s1 = "��";
	s1 += "������Ϸ";
	cout << "s1 = " << s1 << endl;

	s1 += ':';
	cout << "s1 = " << s1 << endl;

	string s2 = "LOL DNF";
	s1 += s2;
	cout << "s1 = " << s1 << endl;

	string s3 = "I";
	s3.append(" love");
	cout << "s3 = " << s3 << endl;

	s3.append(" game dowfjelw", 5);
	cout << "s3 = " << s3 << endl;

	s3.append(s2);
	cout << "s3 = " << s3 << endl;

	s3.append(s2, 0, 3);
	cout << "s3 = " << s3 << endl;
}

int main()
{
	test01();
	return 0;
}