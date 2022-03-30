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
#define GETWORD next_Word();		//��word
#define MYERROR print_ERROR();		//����
#define PRINTL print_lexcial();		//��ӡ��ǰword��symbolType��save
#define PRINTG(gram) print_gram(gram);	//��ӡ�﷨���������﷨�ɷ�
#define RESERVE save_print();			

public:
	Grammar_analysis(Lexical_analysis& l_a, ofstream& ofs) :lexical_analysis(l_a), fout(ofs) {};
	void grammarAnalyze();

	void print_lexcial() { fout << now_symbolType << " " << now_save << endl; };
	void print_gram(string gram) { fout << gram << endl; };
	int next_Word();
	void print_ERROR() { fout << "����" << endl; exit(0); };
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
	ofstream& fout;         //����ļ�
	Lexical_analysis& lexical_analysis;

	vector<LFOUT> reserve;
	SymbolType now_symbolType;		//��ǰword��ǰһ��word��symbolType
	string now_save;				//����ǰһ��word

	int is_CX();				//����
	int is_CLSM();				//����˵��
	int is_CLDY();				//��������
	int is_ZS();				//����
	int is_WFHZS();				//�޷�������
	int is_BLSM(bool& flag);	//����˵��
	int is_BLDY();				//��������
	int is_YFHZHSDY();			//�з���ֵ��������
	int is_WFHZHSDY();			//�޷���ֵ��������
	int is_CSB();				//������	
	int is_FHYJ();				//�������
	int is_YJL();				//�����
	int is_YJ();				//���
	int is_TJYJ();				//�������
	int is_TJ();				//����
	int is_BDS();				//���ʽ
	int is_X();					//��
	int is_YZ();				//����
	int is_ZF();				//�ַ�
	int is_JFYSF();				//�ӷ������
	int is_CFYSF();				//�˷������
	int is_ZM();				//��ĸ
	int is_SZ();				//����
	int is_YFHZHSDYYJ();		//�з���ֵ�����������
	int is_ZCSB();				//ֵ������
	int is_GXYSF();				//��ϵ�����
	int is_XHYJ();				//ѭ�����
	int is_BC();				//����
	int is_WFHZHSDYYJ();		//�޷���ֵ�����������
	int is_FZYJ();				//��ֵ���
	int is_DYJ();				//�����
	int is_XYJ();				//д���
	int is_REYJ();				//�������
	int is_ZHS();				//������
	int is_ZFC();				//�ַ���
};

