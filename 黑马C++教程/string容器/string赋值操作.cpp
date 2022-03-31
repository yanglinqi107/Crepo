//#include <iostream>
//using namespace std;
//
///*
//* `string& operator=(const char* s);`             //char*类型字符串 赋值给当前的字符串
//* `string& operator=(const string &s);`         //把字符串s赋给当前的字符串
//* `string& operator=(char c);`                          //字符赋值给当前的字符串
//* `string& assign(const char *s);`                  //把字符串s赋给当前的字符串
//* `string& assign(const char *s, int n);`     //把字符串s的前n个字符赋给当前的字符串
//* `string& assign(const string &s);`              //把字符串s赋给当前字符串
//* `string& assign(int n, char c);`                  //用n个字符c赋给当前字符串
//*/
//
//void test01()
//{
//	string s1;
//	s1 = "hello world";
//	cout << "s1 = " << s1 << endl;
//
//	string s2;
//	s2 = s1;
//	cout << "s2 = " << s2 << endl;
//
//	string s3;
//	s3 = 'a';
//	cout << "s3 = " << s3 << endl;
//
//	string s4;
//	s4.assign("hello C++");
//	cout << "s4 = " << s4 << endl;
//
//	string s5;
//	s5.assign("hello C++", 5);
//	cout << "s5 = " << s5 << endl;
//
//	string s6;
//	s6.assign(s5);
//	cout << "s6 = " << s6 << endl;
//
//	string s7;
//	s7.assign(10, 'w');
//	cout << "s7 = " << s7 << endl;
//
//}
//
//int main()
//{
//	test01();
//	return 0;
//}