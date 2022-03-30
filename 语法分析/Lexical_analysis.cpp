#include "Lexical_analysis.h"
#include <ctype.h>
#include <map>
#include <string>
#include <iostream>
#include<fstream>

using namespace std;
using std::ofstream;

static string strGot;   //静态全局变量，字符串
static char ch;         //静态全局变量，字符
static map<string, SymbolType> reservedWords;   //保留字，map是STL的一个关联容器，它提供一对一的hash，类似于字典

//单例
Lexical_analysis &Lexical_analysis::initialLexicalanalysis(ifstream &file,ofstream &ofs) {
    static Lexical_analysis theLexical_analysis(file,ofs);
    return theLexical_analysis;
}

//构造函数
Lexical_analysis::Lexical_analysis(ifstream &file,ofstream &ofs) : sourceFile(file),fout(ofs),save("") {
    ch = sourceFile.get();
    //fout.open("output.txt");
//保留字表      使用map容器，将关键字和枚举中的int型对应 key-value
#define INSERT_RES(str, type)    \
        reservedWords.insert(pair<string, SymbolType>(str, type))   // 定义宏，简化填表代码
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

#define GET     ch = sourceFile.get()   // 定义宏，简化从文件中读取一个字符的操作
#define PEEK    ch = sourceFile.peek()  // 定义宏，简化查看文件流第一个字符的操作
#define ADD(c)  save.append(1, c)     // 定义宏，简化往字符串结尾添加字符的操作


//词法分析部分
void Lexical_analysis::nextSymbol() {
    while (isspace(ch)) {           // isspace 检查 ch 是否是空字符串
        GET;
    }
    // 作用：将 整数 识别出来并存入save字符串中
    if (isdigit(ch)) {              //isdigit 判断字符是否是数字 
        symbolType = INTCON;        //则将词法分析类的 枚举变量 设为 整数常量
		save.clear();               //清空字符串 save  
		ADD(ch);                    //将当前字符加到 save 字符串中
        for (GET; isdigit(ch); GET) {   //继续从文件中读字符，并将字符存入save字符串，直到不是数字
			ADD(ch);
        }
    } else if (isalpha(ch) || ch == '_') {      //判断读入的字符 是否 是字母或下划线
        strGot.clear();                         //清空strGot和save
		save.clear();
        ADD(ch);                                //将当前字符加到 save 字符串中     
        for (GET; isalpha(ch) || isdigit(ch)|| ch == '_'; GET) {  //继续从文件中读字符，并将字符存入save字符串，直到不是 数字、字母或下划线
            ADD(ch);
        }
        map<string, SymbolType>::iterator it = reservedWords.find(save);    //将读取到的保留字和保留字表中的保留字对比
        if (it == reservedWords.end()) {                    //如果找到，该保留字类型为标识符，即用户自定义的变量名等
            symbolType = IDENFR;
        } else {
            symbolType = it->second;                        //否则，保留字类型为保留字表中key对应的value值
        }
    } else {                                //若输入的字符不是数字，字母，下划线
		save.clear();                       //清空save字符串
        ADD(ch);                            // 先把待判断的字符加入字符串

        switch (ch) {                       //判断这个字符
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
                PEEK;                       //peek  预读取下一个字符           
                if (ch == '=') {            //判断下一个字符是否是等号 = 
                    GET;                    //读取下一个字符，存入save
					ADD(ch);
                    symbolType = LEQ;
                } else {
                    symbolType = LSS;
                }
                break;
            case '>':
                PEEK;                       //peek  预读取下一个字符
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
            case '\'':                  //判断是不是 单引号 '   
                GET;                    
                nextChar();             //判断下个字符是否合法
                break;
            case '\"':                 //判断是不是 双引号 "
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
	//fout << symbolType << ' ' << save << endl;      //将类型 和 字符 写入文件
}

//字符串
void Lexical_analysis::nextString() {
	save.clear();
    while (ch == 32 || ch == 33 || (ch >= 35 && ch <= 126)) {   //32 空格  33  !  34 "
        ADD(ch);
        GET;
    }
    // 这里，循环跳出时，ch 是一个新的未处理的字符，逻辑正确
    if (ch != '\"') {           // 读到非法字符
        symbolType = ILLEGAL;   // 返回 ILLEGAL 类型
		save.clear();
        ADD(ch);                // 将非法的字符存入 token 中，
                                //  此时 token 中只有这一个非法字符
        GET;                    // 不要忘了再读一个备用！！！
    } else
        symbolType = STRCON;    // 正常，返回 STRING
}

//单个字符
void Lexical_analysis::nextChar() {
    while (isspace(ch))
        GET;                    // 跳过空白符
	save.clear();
    ADD(ch);
    if (isalnum(ch) || ch == '_'|| ch=='+' || ch =='-' || ch == '*' || ch=='/')            //isalnum 判断是否是字母或字符串 是合法字符
        symbolType = CHARCON;
    else                        // 非法字符
        symbolType = ILLEGAL;
    GET;                        // get 一个新的字符备用！！
}
//SymbolType << 运算符重载,输出enum对应字符串
ostream &operator<<(ostream &ofs, SymbolType st) {
    switch (st) {

#define case(type) case type:       \
    ofs << #type;                   \
    break                           // 定义宏，简化 case 语句的输入
        case(IDENFR);     // 标识符
        case(INTCON);     // 整数常量
        case(CHARCON);    // 字符常量
        case(STRCON);     // 字符串
        case(CONSTTK);    //const关键字
        case(INTTK);      //int关键字
        case(CHARTK);     //char关键字
        case(VOIDTK);     //void关键字
        case(MAINTK);     //main关键字
        case(IFTK);       //if关键字
        case(ELSETK);     //else关键字
        case(DOTK);       //do关键字
        case(WHILETK);    //while关键字
        case(FORTK);      //for关键字
        case(SCANFTK);    //scanf关键字
        case(PRINTFTK);   //printf关键字
        case(RETURNTK);   //return关键字

        case(PLUS);       //加号 +
        case(MINU);       //减号 -
        case(MULT);       //乘号 *
        case(DIV);        //除号 /
        case(LSS);        //小于号 <
        case(LEQ);        //小于等于号 <=
        case(GRE);        //大于号 >
        case(GEQ);        //大于等于号 >=
        case(EQL);        //等于号 ==
        case(NEQ);        //不等号 !=
        case(ASSIGN);     //赋值号 =
        case(SEMICN);     //分号 ;
        case(COMMA);      //逗号 ,
        case(LPARENT);    //左圆括号 (
        case(RPARENT);    //右园括号 )
        case(LBRACK);     //左方括号 [
        case(RBRACK);     //右方括号 ]
        case(LBRACE);     //左尖括号 {
        case(RBRACE);      //右尖括号 }
#undef case                       // 取消定义 case，让出这个名字
        default:
            break;
    }
    return ofs;
}