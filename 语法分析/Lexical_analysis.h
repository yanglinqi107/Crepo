#ifndef LEXICAL_ANALYSIS__H
#define LEXICAL_ANALYSIS__H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ofstream;

//ö������
enum SymbolType {               
    ILLEGAL,            // �Ƿ��ַ�
    FINISH,             // �ļ���β

    IDENFR,     // ��ʶ��
    INTCON,     // ��������
    CHARCON,    // �ַ�����
    STRCON,     // �ַ���

    CONSTTK,    //const�ؼ���
    INTTK,      //int�ؼ���
    CHARTK,     //char�ؼ���
    VOIDTK,     //void�ؼ���
    MAINTK,     //main�ؼ���
    IFTK,       //if�ؼ���
    ELSETK,     //else�ؼ���
    DOTK,       //do�ؼ���
    WHILETK,    //while�ؼ���
    FORTK,      //for�ؼ���
    SCANFTK,    //scanf�ؼ���
    PRINTFTK,   //printf�ؼ���
    RETURNTK,   //return�ؼ���

    PLUS,       //�Ӻ� +
    MINU,       //���� -
    MULT,       //�˺� *
    DIV,        //���� /
    LSS,        //С�ں� <
    LEQ,        //С�ڵ��ں� <=
    GRE,        //���ں� >
    GEQ,        //���ڵ��ں� >=
    EQL,        //���ں� ==
    NEQ,        //���Ⱥ� !=
    ASSIGN,     //��ֵ�� =
    SEMICN,     //�ֺ� ;
    COMMA,      //���� ,
    LPARENT,    //��Բ���� (
    RPARENT,    //��԰���� )
    LBRACK,     //������ [
    RBRACK,     //�ҷ����� ]
    LBRACE,     //������� {
    RBRACE      //�Ҽ����� }
};

class Lexical_analysis
{
public:
    static Lexical_analysis& initialLexicalanalysis(ifstream& file, ofstream& ofs); //��̬���������ɲ����ؾ�̬Lexical_analysis����
	void nextSymbol();
    void nextString();
    void nextChar();
	//void nextNum();
	SymbolType getSymbol();
private:
	ifstream &sourceFile;   //�����ļ�
	SymbolType symbolType;  //ö�ٱ������ʵ�����
	ofstream& fout;         //����ļ�
	friend class Grammar_analysis;  //��Ԫ�࣬�﷨����
	string save;    
	Lexical_analysis(ifstream& file,ofstream& ofs);     //�вι��캯��
	Lexical_analysis(const Lexical_analysis&);          //���ƹ��캯��
	Lexical_analysis& operator  = (const Lexical_analysis&);    
};


using std::ostream;
ostream& operator<< (ostream& ofs, SymbolType st);


#endif