#pragma once
#include"Lexical_analysis.h"
#include<iostream>
using namespace std;

class  Grammar_analysis
{
public:
	Grammar_analysis(Lexical_analysis & lexical, ofstream & ofs):lexical_analysis(lexical), fout(ofs) {};

	bool X_add();
	bool X_mult();
	bool X_rel();
	bool X_str();
	bool X_s();
	bool TempM();
	bool X_c_exp();
	bool X_c_def();
	bool TempA();
	bool TempB();
	bool X_nf_int();
	bool X_int();
	bool X_head();
	bool X_b_exp();
	bool X_b_def();
	bool TempC();
	bool X_bl();
	bool X_yfh();
	bool X_wfh();
	bool X_fh();
	bool X_csb();
	bool TempD();
	bool X_main();
	bool X_bd();
	bool X_x();
	bool X_yz();
	bool X_yj();
	bool X_fz();
	bool X_tjy();
	bool X_tj();
	bool X_xh();
	bool X_bc();
	bool X_yfd();
	bool X_wfd();
	bool X_zc();
	bool TempH();
	bool X_yjl();
	bool X_ryj();
	bool TempQ();
	bool X_wyj();
	bool X_ret();

private:
	ofstream& fout;         //Êä³öÎÄ¼þ
	Lexical_analysis& lexical_analysis;

};

 Grammar_analysis(Lexical_analysis& lexical, ofstream& ofs):: Grammer_analysis(Lexical_analysis& lexical, ofstream& ofs)()
{
		
}

 Grammar_analysis(Lexical_analysis& lexical, ofstream& ofs)::~ Grammer_analysis(Lexical_analysis& lexical, ofstream& ofs)()
{
}