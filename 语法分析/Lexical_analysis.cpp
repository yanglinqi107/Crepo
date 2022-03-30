#include "Lexical_analysis.h"
#include <ctype.h>
#include <map>
#include <string>
#include <iostream>
#include<fstream>

using namespace std;
using std::ofstream;

static string strGot;   //��̬ȫ�ֱ������ַ���
static char ch;         //��̬ȫ�ֱ������ַ�
static map<string, SymbolType> reservedWords;   //�����֣�map��STL��һ���������������ṩһ��һ��hash���������ֵ�

//����
Lexical_analysis &Lexical_analysis::initialLexicalanalysis(ifstream &file,ofstream &ofs) {
    static Lexical_analysis theLexical_analysis(file,ofs);
    return theLexical_analysis;
}

//���캯��
Lexical_analysis::Lexical_analysis(ifstream &file,ofstream &ofs) : sourceFile(file),fout(ofs),save("") {
    ch = sourceFile.get();
    //fout.open("output.txt");
//�����ֱ�      ʹ��map���������ؼ��ֺ�ö���е�int�Ͷ�Ӧ key-value
#define INSERT_RES(str, type)    \
        reservedWords.insert(pair<string, SymbolType>(str, type))   // ����꣬��������
    INSERT_RES("const", CONSTTK);
    INSERT_RES("int", INTTK);
    INSERT_RES("char", CHARTK);
    INSERT_RES("void", VOIDTK);
    INSERT_RES("main", MAINTK);
    INSERT_RES("if", IFTK);
    INSERT_RES("else", ELSETK);
    INSERT_RES("do", DOTK);
    INSERT_RES("while", WHILETK);
    INSERT_RES("for", FORTK);
    INSERT_RES("scanf", SCANFTK);
    INSERT_RES("printf", PRINTFTK);
    INSERT_RES("return", RETURNTK);
#undef  INSERT_RES
}

SymbolType Lexical_analysis::getSymbol() {
    return symbolType;
}

#define GET     ch = sourceFile.get()   // ����꣬�򻯴��ļ��ж�ȡһ���ַ��Ĳ���
#define PEEK    ch = sourceFile.peek()  // ����꣬�򻯲鿴�ļ�����һ���ַ��Ĳ���
#define ADD(c)  save.append(1, c)     // ����꣬�����ַ�����β����ַ��Ĳ���


//�ʷ���������
void Lexical_analysis::nextSymbol() {
    while (isspace(ch)) {           // isspace ��� ch �Ƿ��ǿ��ַ���
        GET;
    }
    // ���ã��� ���� ʶ�����������save�ַ�����
    if (isdigit(ch)) {              //isdigit �ж��ַ��Ƿ������� 
        symbolType = INTCON;        //�򽫴ʷ�������� ö�ٱ��� ��Ϊ ��������
		save.clear();               //����ַ��� save  
		ADD(ch);                    //����ǰ�ַ��ӵ� save �ַ�����
        for (GET; isdigit(ch); GET) {   //�������ļ��ж��ַ��������ַ�����save�ַ�����ֱ����������
			ADD(ch);
        }
    } else if (isalpha(ch) || ch == '_') {      //�ж϶�����ַ� �Ƿ� ����ĸ���»���
        strGot.clear();                         //���strGot��save
		save.clear();
        ADD(ch);                                //����ǰ�ַ��ӵ� save �ַ�����     
        for (GET; isalpha(ch) || isdigit(ch)|| ch == '_'; GET) {  //�������ļ��ж��ַ��������ַ�����save�ַ�����ֱ������ ���֡���ĸ���»���
            ADD(ch);
        }
        map<string, SymbolType>::iterator it = reservedWords.find(save);    //����ȡ���ı����ֺͱ����ֱ��еı����ֶԱ�
        if (it == reservedWords.end()) {                    //����ҵ����ñ���������Ϊ��ʶ�������û��Զ���ı�������
            symbolType = IDENFR;
        } else {
            symbolType = it->second;                        //���򣬱���������Ϊ�����ֱ���key��Ӧ��valueֵ
        }
    } else {                                //��������ַ��������֣���ĸ���»���
		save.clear();                       //���save�ַ���
        ADD(ch);                            // �ȰѴ��жϵ��ַ������ַ���

        switch (ch) {                       //�ж�����ַ�
            case '+':
				symbolType = PLUS;
                break;
            case '-':
				symbolType = MINU;
                break;
            case '*':
                symbolType = MULT;
                break;
            case '/':
                symbolType = DIV;
                break;
            case '<':
                PEEK;                       //peek  Ԥ��ȡ��һ���ַ�           
                if (ch == '=') {            //�ж���һ���ַ��Ƿ��ǵȺ� = 
                    GET;                    //��ȡ��һ���ַ�������save
					ADD(ch);
                    symbolType = LEQ;
                } else {
                    symbolType = LSS;
                }
                break;
            case '>':
                PEEK;                       //peek  Ԥ��ȡ��һ���ַ�
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = GEQ;
                } else {
                    symbolType = GRE;
                }
                break;
            case '=':
                PEEK;
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = EQL;
                } else {
                    symbolType = ASSIGN;
                }
                break;
            case '!':
                PEEK;
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = NEQ;
                }
                break;
            case ';':
                symbolType = SEMICN;
                break;
            case ',':
                symbolType = COMMA;
                break;
            case '(':
                symbolType = LPARENT;
                break;
            case ')':
                symbolType = RPARENT;
                break;
            case '[':
                symbolType = LBRACK;
                break;
            case ']':
                symbolType = RBRACK;
                break;
            case '{':
                symbolType = LBRACE;
                break;
            case '}':
                symbolType = RBRACE;
                break;
            case '\'':                  //�ж��ǲ��� ������ '   
                GET;                    
                nextChar();             //�ж��¸��ַ��Ƿ�Ϸ�
                break;
            case '\"':                 //�ж��ǲ��� ˫���� "
                GET;
                nextString();
                break;
            case EOF:
                symbolType = FINISH;
                //fout.close();
                break;
            default:
                symbolType = ILLEGAL;
                break;
        }
        GET;
    }
	//fout << symbolType << ' ' << save << endl;      //������ �� �ַ� д���ļ�
}

//�ַ���
void Lexical_analysis::nextString() {
	save.clear();
    while (ch == 32 || ch == 33 || (ch >= 35 && ch <= 126)) {   //32 �ո�  33  !  34 "
        ADD(ch);
        GET;
    }
    // ���ѭ������ʱ��ch ��һ���µ�δ������ַ����߼���ȷ
    if (ch != '\"') {           // �����Ƿ��ַ�
        symbolType = ILLEGAL;   // ���� ILLEGAL ����
		save.clear();
        ADD(ch);                // ���Ƿ����ַ����� token �У�
                                //  ��ʱ token ��ֻ����һ���Ƿ��ַ�
        GET;                    // ��Ҫ�����ٶ�һ�����ã�����
    } else
        symbolType = STRCON;    // ���������� STRING
}

//�����ַ�
void Lexical_analysis::nextChar() {
    while (isspace(ch))
        GET;                    // �����հ׷�
	save.clear();
    ADD(ch);
    if (isalnum(ch) || ch == '_'|| ch=='+' || ch =='-' || ch == '*' || ch=='/')            //isalnum �ж��Ƿ�����ĸ���ַ��� �ǺϷ��ַ�
        symbolType = CHARCON;
    else                        // �Ƿ��ַ�
        symbolType = ILLEGAL;
    GET;                        // get һ���µ��ַ����ã���
}
//SymbolType << ���������,���enum��Ӧ�ַ���
ostream &operator<<(ostream &ofs, SymbolType st) {
    switch (st) {

#define case(type) case type:       \
    ofs << #type;                   \
    break                           // ����꣬�� case ��������
        case(IDENFR);     // ��ʶ��
        case(INTCON);     // ��������
        case(CHARCON);    // �ַ�����
        case(STRCON);     // �ַ���
        case(CONSTTK);    //const�ؼ���
        case(INTTK);      //int�ؼ���
        case(CHARTK);     //char�ؼ���
        case(VOIDTK);     //void�ؼ���
        case(MAINTK);     //main�ؼ���
        case(IFTK);       //if�ؼ���
        case(ELSETK);     //else�ؼ���
        case(DOTK);       //do�ؼ���
        case(WHILETK);    //while�ؼ���
        case(FORTK);      //for�ؼ���
        case(SCANFTK);    //scanf�ؼ���
        case(PRINTFTK);   //printf�ؼ���
        case(RETURNTK);   //return�ؼ���

        case(PLUS);       //�Ӻ� +
        case(MINU);       //���� -
        case(MULT);       //�˺� *
        case(DIV);        //���� /
        case(LSS);        //С�ں� <
        case(LEQ);        //С�ڵ��ں� <=
        case(GRE);        //���ں� >
        case(GEQ);        //���ڵ��ں� >=
        case(EQL);        //���ں� ==
        case(NEQ);        //���Ⱥ� !=
        case(ASSIGN);     //��ֵ�� =
        case(SEMICN);     //�ֺ� ;
        case(COMMA);      //���� ,
        case(LPARENT);    //��Բ���� (
        case(RPARENT);    //��԰���� )
        case(LBRACK);     //������ [
        case(RBRACK);     //�ҷ����� ]
        case(LBRACE);     //������� {
        case(RBRACE);      //�Ҽ����� }
#undef case                       // ȡ������ case���ó��������
        default:
            break;
    }
    return ofs;
}