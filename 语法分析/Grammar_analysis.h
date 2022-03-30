#pragma once
#include <vector>
#include <iostream>
#include "Lexical_analysis.h"
using namespace std;

typedef struct LFOUT
{
	LFOUT(SymbolType ty, string s)
	{
		type = ty;
		str = s;
	}
	SymbolType type;
	string str;
}LFOUT;

class Grammar_analysis
{
#define GETWORD next_Word();		//读word
#define MYERROR print_ERROR();		//报错
#define PRINTL print_lexcial();		//打印当前word的symbolType和save
#define PRINTG(gram) print_gram(gram);	//打印语法分析出的语法成分
#define RESERVE save_print();			

public:
	Grammar_analysis(Lexical_analysis& l_a, ofstream& ofs) :lexical_analysis(l_a), fout(ofs) {};
	void grammarAnalyze();

	void print_lexcial() { fout << now_symbolType << " " << now_save << endl; };
	void print_gram(string gram) { fout << gram << endl; };
	int next_Word();
	void print_ERROR() { fout << "错误" << endl; exit(0); };
	void save_print() { reserve.push_back(LFOUT(lexical_analysis.symbolType, lexical_analysis.save)); };
	void print_reserve() 
	{ 
		for (int i = 0; i < reserve.size(); i++)
		{
			fout << reserve[i].type << " " << reserve[i].str << endl;
		}
		reserve.clear();
	};

private:
	ofstream& fout;         //输出文件
	Lexical_analysis& lexical_analysis;

	vector<LFOUT> reserve;
	SymbolType now_symbolType;		//当前word的前一个word的symbolType
	string now_save;				//保存前一个word

	int is_CX();				//程序
	int is_CLSM();				//常量说明
	int is_CLDY();				//常量定义
	int is_ZS();				//整数
	int is_WFHZS();				//无符号整数
	int is_BLSM(bool& flag);	//变量说明
	int is_BLDY();				//变量定义
	int is_YFHZHSDY();			//有返回值函数定义
	int is_WFHZHSDY();			//无返回值函数定义
	int is_CSB();				//参数表	
	int is_FHYJ();				//复合语句
	int is_YJL();				//语句列
	int is_YJ();				//语句
	int is_TJYJ();				//条件语句
	int is_TJ();				//条件
	int is_BDS();				//表达式
	int is_X();					//项
	int is_YZ();				//因子
	int is_ZF();				//字符
	int is_JFYSF();				//加法运算符
	int is_CFYSF();				//乘法运算符
	int is_ZM();				//字母
	int is_SZ();				//数字
	int is_YFHZHSDYYJ();		//有返回值函数调用语句
	int is_ZCSB();				//值参数表
	int is_GXYSF();				//关系运算符
	int is_XHYJ();				//循环语句
	int is_BC();				//步长
	int is_WFHZHSDYYJ();		//无返回值函数调用语句
	int is_FZYJ();				//赋值语句
	int is_DYJ();				//读语句
	int is_XYJ();				//写语句
	int is_REYJ();				//返回语句
	int is_ZHS();				//主函数
	int is_ZFC();				//字符串
};

