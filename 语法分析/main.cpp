#include "Lexical_analysis.h"
#include "Grammar_analysis.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream fin;
	fin.open("testfile.txt");
	ofstream fout;
	fout.open("output.txt");
	if (!fin.is_open() || !fout.is_open()) {
		cerr << "err: cannot open file: "<< endl;
		cerr << "Please check the path and file name." << endl;
		return 0;
	}
	Lexical_analysis &lexical_analysis = Lexical_analysis::initialLexicalanalysis(fin, fout);	//初始化词法分析对象，读文件，写文件
	Grammar_analysis grammar_analysis(lexical_analysis, fout);
	//while (lexical_analysis.getSymbol() != FINISH) {		//判断文件中读入的字符是否是-1，判断文件是否读完
		//lexical_analysis.nextSymbol();
		//grammar_analysis.grammarAnalyze();
	//}
	grammar_analysis.grammarAnalyze();
	//grammar_analysis.stringAnalysis();
	//grammar_analysis.intAnalysis();
	return 0;
}