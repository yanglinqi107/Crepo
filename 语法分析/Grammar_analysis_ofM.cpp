#include"Grammar_analysis_ofM.h"
#include<iostream>
#include<fstream>
using namespace std;

bool X_add() {

}





void test() {
	ifstream fin;
	fin.open("testfile.txt");
	ofstream fout;
	fout.open("output.txt");
	if (!fin.is_open() || !fout.is_open()) {
		cerr << "err: cannot open file: " << endl;
		cerr << "Please check the path and file name." << endl;
		return;
	}
	Lexical_analysis& lexical_analysis = Lexical_analysis::initialLexicalanalysis(fin, fout);	//��ʼ���ʷ��������󣬶��ļ���д�ļ�
	Grammer_analysis grammar_analysis(lexical_analysis, fout);
	while (lexical_analysis.getSymbol() != FINISH) {		//�ж��ļ��ж�����ַ��Ƿ���-1���ж��ļ��Ƿ����
		lexical_analysis.nextSymbol();
}