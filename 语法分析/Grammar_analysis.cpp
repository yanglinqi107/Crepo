#include "Grammar_analysis.h"
using namespace std;

constexpr auto JFYSF = "<加法运算符>";		
constexpr auto CFYSF = "<乘法运算符>";		
constexpr auto GXYSF = "<关系运算符>";		
constexpr auto ZM = "<字母>";				
constexpr auto SZ = "<数字>";				
constexpr auto FLSZ = "<非零数字>";			
constexpr auto ZF = "<字符>";				
constexpr auto ZFC = "<字符串>";			
constexpr auto CX = "<程序>";				
constexpr auto CLSM = "<常量说明>";			
constexpr auto CLDY = "<常量定义>";			
constexpr auto WFHZS = "<无符号整数>";		
constexpr auto ZS = "<整数>";				
constexpr auto BSF = "<标识符>";			
constexpr auto SMTB = "<声明头部>";			
constexpr auto BLSM = "<变量说明>";			
constexpr auto BLDY = "<变量定义>";			
constexpr auto LXBSF = "<类型标识符>";		
constexpr auto YFHZHSDY = "<有返回值函数定义>"; 
constexpr auto WFHZHSDY = "<无返回值函数定义>";	
constexpr auto FHYJ = "<复合语句>";				
constexpr auto CSB = "<参数表>";				
constexpr auto ZHS = "<主函数>";
constexpr auto BDS = "<表达式>";
constexpr auto X = "<项>";
constexpr auto YZ = "<因子>";
constexpr auto YJ = "<语句>";
constexpr auto FZYJ = "<赋值语句>";
constexpr auto TJYJ = "<条件语句>";
constexpr auto TJ = "<条件>";
constexpr auto XHYJ = "<循环语句>";
constexpr auto BC = "<步长>";
constexpr auto YFHZHSDYYJ = "<有返回值函数调用语句>";
constexpr auto WFHZHSDYYJ = "<无返回值函数调用语句>";
constexpr auto ZCSB = "<值参数表>";
constexpr auto YJL = "<语句列>";
constexpr auto DYJ = "<读语句>";
constexpr auto XYJ = "<写语句>";
constexpr auto REYJ = "<返回语句>";
constexpr auto HSDYYJ = "函数调用语句";

/*
* 字符串				 5
* 无符号整数			 3
* 整数				(19 || 20)  3
* 常量定义			声明头部   29  （3|4）
* 常量说明			 6   常量定义   ;   +
* 程序
* 声明头部			（7|8）  2
* 变量定义			 声明头部 || 声明头部[3](数组)   +
* 变量说明			 变量定义		;	 +
*
*
*
*
*
*
*
*/

//void Grammar_analysis::grammarAnalyze()
//{
//	SymbolType smType = lexical_analysis.symbolType;
//	g_symbolType.push_back(smType);
//	int sub = g_symbolType.size() - 1;
//	if (smType == STRCON)
//	{
//		fout << ZFC << endl;
//	}
//	else if (smType == INTCON)
//	{
//		fout << WFHZS << endl;
//		fout << ZS << endl;
//	}
//	else if (smType == IDENFR)
//	{
//		is_SMTB(sub, true);
//	}
//	else if (smType == INTCON || smType == CHARTK)
//	{
//		is_CLDY(sub, true);
//	}
//}

//语法分析
void Grammar_analysis::grammarAnalyze()
{
	if (is_CX() != 1) MYERROR;
	PRINTG(CX);
	fout.close();
}

//从词法分析程序读词
int Grammar_analysis::next_Word()
{
	if (lexical_analysis.getSymbol() == FINISH) return 0;		
	lexical_analysis.nextSymbol();			//读一个词
	//cout << lexical_analysis.save << endl;
	now_symbolType = lexical_analysis.symbolType;
	now_save = lexical_analysis.save;
	return 1;
}

//＜程序＞ ::=［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
int Grammar_analysis::is_CX()
{
	GETWORD;
	if (is_CLSM() == 1) PRINTG(CLSM);
	bool flag = false;
	int result = is_BLSM(flag);
	if (flag) PRINTG(BLSM);
	if (result == -1)
	{
		print_reserve();
		if (is_YFHZHSDY() != 1) MYERROR;
		PRINTG(YFHZHSDY);
	}
	do
	{
		if (lexical_analysis.symbolType == INTTK || lexical_analysis.symbolType == CHARTK)
		{
			PRINTL;
			GETWORD;
			if (lexical_analysis.symbolType != IDENFR) MYERROR;
			PRINTL;
			GETWORD;
			if (is_YFHZHSDY() != 1) MYERROR;
			PRINTG(YFHZHSDY);
		}
		else if (lexical_analysis.symbolType == VOIDTK)
		{
			int result = is_WFHZHSDY();
			if (result == -1) break;
			else if (result != 1) MYERROR;
		}
		else MYERROR;
	} while (true);

	if (is_ZHS() != 1) MYERROR;
	PRINTG(ZHS);
	return 1;
}

//＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
int Grammar_analysis::is_CLSM()
{
	if (lexical_analysis.symbolType != CONSTTK) return 0;
	PRINTL;
	GETWORD;
	do 
	{	
		if (is_CLDY() != 1) MYERROR;
		PRINTG(CLDY);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != CONSTTK) break;
		PRINTL;
		GETWORD;
	} while (true);
	return 1;
}

//＜常量定义＞ ::= int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}| char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
int Grammar_analysis::is_CLDY()
{
	if (lexical_analysis.symbolType == CHARTK)
	{
		PRINTL;
		GETWORD;
		do
		{
			if (lexical_analysis.symbolType != IDENFR) MYERROR;
			PRINTL;
			GETWORD;
			if (lexical_analysis.symbolType != ASSIGN) MYERROR;
			PRINTL;
			GETWORD;
			if (lexical_analysis.symbolType != CHARCON) MYERROR;
			PRINTL;
			GETWORD;
			if (lexical_analysis.symbolType != COMMA) break;
			PRINTL;
			GETWORD;
		} while (true);
		return 1;
	}
	else if (lexical_analysis.symbolType == INTTK)
	{
		PRINTL;
		GETWORD;
		do
		{
			if (lexical_analysis.symbolType != IDENFR) MYERROR;
			PRINTL;
			GETWORD;
			if (lexical_analysis.symbolType != ASSIGN) MYERROR;
			PRINTL;
			GETWORD;
			if (is_ZS() != 1) MYERROR;
			PRINTG(ZS);
			if (lexical_analysis.symbolType != COMMA) break;
			PRINTL;
			GETWORD;
		} while (true);
		return 1;
	}
	else
	{
		MYERROR;
	}
	return 0;
}

//判断整数
int Grammar_analysis::is_ZS()
{
	if (lexical_analysis.symbolType == PLUS || lexical_analysis.symbolType == MINU)
	{
		PRINTL;
		GETWORD;
	}
	if(is_WFHZS())
	{
		PRINTG(WFHZS);
		return 1;	
	}
	return 0;
}

//判断无符号整数
int Grammar_analysis::is_WFHZS()
{
	if (lexical_analysis.symbolType == INTCON && lexical_analysis.save[0] != '0')
	{
		PRINTL;
		GETWORD;
		return 1;
	}
	return 0;
}

//＜变量说明＞ ::= ＜变量定义＞;{＜变量定义＞;}
int Grammar_analysis::is_BLSM(bool& flag)
{
	do
	{
		int result = is_BLDY();
		if (result != 1) return result;
		PRINTG(BLDY);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		flag = true;
		PRINTL;
		GETWORD;
	} while (true);
	return 1;
}

//＜变量定义＞ ::= ＜类型标识符＞(＜标识符＞|＜标识符＞'['＜无符号整数＞']'){,(＜标识符＞|＜标识符＞'['＜无符号整数＞']' )}
//＜无符号整数＞表示数组元素的个数，其值需大于0
int Grammar_analysis::is_BLDY()
{
	if (lexical_analysis.symbolType != INTTK && lexical_analysis.symbolType != CHARTK) return 0;
	do
	{
		RESERVE;
		GETWORD;
		if (lexical_analysis.symbolType != IDENFR) MYERROR;
		RESERVE;
		GETWORD;
		if (lexical_analysis.symbolType == LPARENT) return -1;
		else if (lexical_analysis.symbolType == LBRACK)  //有返回值函数定义
		{
			print_reserve();
			PRINTL;
			GETWORD;
			if (is_WFHZS() != 1) MYERROR;
			PRINTG(WFHZS);
			if (lexical_analysis.symbolType != RBRACK) MYERROR;
			PRINTL;
			GETWORD;
		}
		else if (lexical_analysis.symbolType != COMMA)
		{
			print_reserve();
			break;
		}
		else MYERROR;
		print_reserve();
	} while (true);
	return 1;
}

//＜有返回值函数定义＞ ::= ＜声明头部＞'('＜参数表＞')' '{'＜复合语句＞'}'
int Grammar_analysis::is_YFHZHSDY()
{
	if (lexical_analysis.symbolType != LPARENT) return 0;
	PRINTG(SMTB);
	PRINTL;
	GETWORD;
	int result = is_CSB();
	if (result == 1) PRINTG(CSB);
	if (lexical_analysis.symbolType != RPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LBRACE) MYERROR;
	PRINTL;
	GETWORD;
	if (is_FHYJ() != 1) MYERROR;
	PRINTG(FHYJ);
	if (lexical_analysis.symbolType != RBRACE) MYERROR;
	PRINTL;
	GETWORD;
	return 1;
}

//＜无返回值函数定义＞ ::= void＜标识符＞'('＜参数表＞')''{'＜复合语句＞'}'
int Grammar_analysis::is_WFHZHSDY()
{
	if (lexical_analysis.symbolType != VOIDTK) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType == MAINTK) return -1;	//主函数
	if (lexical_analysis.symbolType != IDENFR) MYERROR;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) MYERROR;
	PRINTL;
	GETWORD;
	int result = is_CSB();
	if (result == 1) PRINTG(CSB);
	if (lexical_analysis.symbolType != RPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LBRACE) MYERROR;
	PRINTL;
	GETWORD;
	if (is_FHYJ() != 1) MYERROR;
	PRINTG(FHYJ);
	if (lexical_analysis.symbolType != RBRACE) MYERROR;
	return 1;
}

//＜参数表＞ ::= ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
int Grammar_analysis::is_CSB()
{
	if (lexical_analysis.symbolType == RPARENT)
	{
		return 2;
	}
	do {
		if (lexical_analysis.symbolType != INTTK && lexical_analysis.symbolType != CONSTTK) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != IDENFR) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != COMMA) break;
		PRINTL;
		GETWORD;
	} while (true);
	return 1;
}

//＜复合语句＞ ::=［＜常量说明＞］［＜变量说明＞］＜语句列＞
int Grammar_analysis::is_FHYJ()
{
	if (is_CLSM() == 1) PRINTG(CLSM);
	bool flag = false;
	int result = is_BLSM(flag);
	if (flag) PRINTG(BLSM);
	if (result == -1) MYERROR;
	if (is_YJL() != 1) return 0;
	PRINTG(YJL);
	return 1;
}

//＜语句列＞ ::=｛＜语句＞｝
int Grammar_analysis::is_YJL()
{
	int result = 0;
	do
	{
		if (is_YJ() != 1) return result;
		result = 1;
		PRINTG(YJ);
	} while (true);
}

//＜语句＞ ::= ＜条件语句＞｜＜循环语句＞| '{'＜语句列＞'}'| ＜有返回值函数调用语句＞;
//  |＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;|＜返回语句＞;
int Grammar_analysis::is_YJ()
{
	if (lexical_analysis.symbolType == SEMICN)
	{
		PRINTL;
		GETWORD;
		return 1;
	}
	if (is_TJYJ() == 1)
	{
		PRINTG(TJYJ);
		return 1;
	}
	if (is_XHYJ() == 1)
	{
		PRINTG(XHYJ);
		return 1;
	}
	if (lexical_analysis.symbolType == LBRACE)
	{
		if (is_YJL() != 1) MYERROR;
		PRINTG(YJL);
		if (lexical_analysis.symbolType != RBRACE) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	if (lexical_analysis.symbolType == IDENFR)
	{
		PRINTL;
		GETWORD;
		if (is_YFHZHSDYYJ() == 1)
		{
			PRINTG(HSDYYJ);
		}
		else if (is_FZYJ() == 1)
		{
			PRINTG(FZYJ);
		}
		else MYERROR;
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	if (is_DYJ() == 1)
	{
		PRINTG(DYJ);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	if (is_XYJ() == 1)
	{
		PRINTG(XYJ);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	if (is_REYJ() == 1)
	{
		PRINTG(REYJ);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	return 0;
}

//＜条件语句＞ ::= if '('＜条件＞')'＜语句＞［else＜语句＞］
int Grammar_analysis::is_TJYJ()
{
	if (lexical_analysis.symbolType != IFTK) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (is_TJ() != 1) MYERROR;
	PRINTG(TJ);
	if (is_YJ() != 1) MYERROR;
	PRINTG(YJ);
	if (lexical_analysis.symbolType == ELSETK)
	{
		PRINTL;
		GETWORD;
		if (is_YJ() != 1) MYERROR;
		PRINTG(YJ);
	}
	return 1;
}

//＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞ 
//整型表达式之间才能进行关系运算｜＜表达式＞    //表达式为整型，其值为0条件为假，值不为0时条件为真
int Grammar_analysis::is_TJ()
{
	if (is_BDS() == 1)
	{
		PRINTG(BDS);
		if (is_GXYSF() != 1)
		{
			PRINTG(GXYSF);
			return 1;
		}
		if (is_BDS() != 1) MYERROR;
		PRINTG(BDS);
		return 1;
	}
	return 0;
}

//＜循环语句＞ ::= while '('＜条件＞')'＜语句＞ |
//do＜语句＞while '('＜条件＞')' |
//for'('＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞')'＜语句＞
int Grammar_analysis::is_XHYJ()
{	
	switch (lexical_analysis.symbolType)
	{
	case WHILETK:
	{
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != LPARENT) MYERROR;
		PRINTL;
		GETWORD;
		if (is_TJ() != 1) MYERROR;
		PRINTG(TJ);
		if (lexical_analysis.symbolType != RPARENT) MYERROR;
		if (is_YJ() != 1) MYERROR;
		PRINTG(YJ);
		break;
	}
	case DOTK:
	{
		PRINTL;
		GETWORD;
		if (is_YJ() != 1) MYERROR;
		PRINTG(YJ);
		if (lexical_analysis.symbolType != WHILETK) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != LPARENT) MYERROR;
		PRINTL;
		GETWORD;
		if (is_TJ() != 1) MYERROR;
		PRINTG(TJ);
		if (lexical_analysis.symbolType != RPARENT) MYERROR;
		PRINTL;
		GETWORD;
		break;
	}
	case FORTK:
	{
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != LPARENT) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != IDENFR) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != ASSIGN) MYERROR;
		PRINTL;
		GETWORD;
		if (is_BDS() != 1) MYERROR;
		PRINTG(BDS);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		if (is_TJ() != 1) MYERROR;
		PRINTG(TJ);
		if (lexical_analysis.symbolType != SEMICN) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != IDENFR) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != ASSIGN) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != IDENFR) MYERROR;
		PRINTL;
		GETWORD;
		if ((lexical_analysis.symbolType != PLUS) || (lexical_analysis.symbolType != MINU)) MYERROR;
		PRINTL;
		GETWORD;
		if (is_BC() != 1) MYERROR;
		PRINTG(BC);
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != RPARENT) MYERROR;
		PRINTL;
		GETWORD;
		if (is_YJ() != 1) MYERROR;
		break;
	}
	default:
		return 0;
	}
	return 1;
}

//＜步长＞::= ＜无符号整数＞  
int Grammar_analysis::is_BC()
{
	if (is_WFHZS() != 1) return 0;
	PRINTG(WFHZS);	
	return 1;
}

//＜有返回值函数调用语句＞ ::= ＜标识符＞'('＜值参数表＞')'
int Grammar_analysis::is_YFHZHSDYYJ()
{
	if (lexical_analysis.symbolType != LPARENT) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType == RPARENT) return 1;
	if (is_ZCSB() != 1) MYERROR;
	PRINTG(ZCSB);
	if (lexical_analysis.symbolType != RPARENT) MYERROR;
	PRINTL;
	GETWORD;
	return 1;
}

//＜无返回值函数调用语句＞::= ＜标识符＞'('＜值参数表＞')'
int Grammar_analysis::is_WFHZHSDYYJ()
{
	if (lexical_analysis.symbolType != IDENFR) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) return 0;
	PRINTL;
	GETWORD;
	if (is_ZCSB() != 1) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != RPARENT) return 0;
	PRINTL;
	GETWORD;
	return 1;
}

//＜赋值语句＞ ::=  ＜标识符＞＝＜表达式＞|＜标识符＞'['＜表达式＞']'=＜表达式＞
int Grammar_analysis::is_FZYJ()
{
	if (lexical_analysis.symbolType == LBRACK)
	{
		PRINTL;
		GETWORD;
		if (is_BDS() != 1) MYERROR;
		PRINTG(BDS);
		if (lexical_analysis.symbolType != RBRACK) MYERROR;
		PRINTL;
		GETWORD;
	}
	if (lexical_analysis.symbolType != ASSIGN) return 0;
	PRINTL;
	GETWORD;
	if (is_BDS() != 1) MYERROR;
	PRINTG(BDS);
	return 1;
}

//＜读语句＞ ::=  scanf '('＜标识符＞{,＜标识符＞}')'
int Grammar_analysis::is_DYJ()
{
	if (lexical_analysis.symbolType != SCANFTK) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) MYERROR;
	PRINTL;
	GETWORD;
	do
	{
		if (lexical_analysis.symbolType != IDENFR) MYERROR;
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType != COMMA) break;
		PRINTL;
		GETWORD;
	} while (true);
	if (lexical_analysis.symbolType != RPARENT) MYERROR;
	PRINTL;
	GETWORD;
	return 1;
}

//＜写语句＞::= printf '('＜字符串＞,＜表达式＞ ')'| printf '('＜字符串＞ ')'| printf '('＜表达式＞')'
int Grammar_analysis::is_XYJ()
{
	if (lexical_analysis.symbolType != PRINTFTK) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (is_ZFC() == 1)
	{
		PRINTG(ZFC);
		if (lexical_analysis.symbolType == RPARENT)
		{
			PRINTL;
			GETWORD;
			return 1;
		}
		if (lexical_analysis.symbolType != COMMA) MYERROR;
		PRINTL;
		GETWORD;
		if (is_BDS() != 1) MYERROR;
		if (lexical_analysis.symbolType != RPARENT) MYERROR;
		PRINTL;
		GETWORD; 
		return 1;
	}
	else if (is_BDS() == 1)
	{
		if (lexical_analysis.symbolType != RPARENT) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	return 0;
}

//＜返回语句＞::=  return['('＜表达式＞')'] 
int Grammar_analysis::is_REYJ()
{
	if (lexical_analysis.symbolType != RETURNTK) return 0;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (is_BDS() != 1) MYERROR;
	PRINTG(BDS);
	if (lexical_analysis.symbolType != RPARENT) MYERROR;
	PRINTL;
	GETWORD;
	return 1;
}

//主函数
int Grammar_analysis::is_ZHS()
{
	if (lexical_analysis.symbolType != MAINTK) MYERROR;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != RPARENT) MYERROR;
	PRINTL;
	GETWORD;
	if (lexical_analysis.symbolType != LBRACE) MYERROR;
	PRINTL;
	GETWORD;
	if (is_FHYJ() != 1) MYERROR;
	PRINTG(FHYJ);
	if (lexical_analysis.symbolType != RBRACE) MYERROR;
	PRINTL;
	GETWORD;
	return 1;
}

//＜字符串＞ ::= "｛十进制编码为32,33,35-126的ASCII字符｝"
int Grammar_analysis::is_ZFC()
{
	if (lexical_analysis.symbolType != STRCON) return 0;
	PRINTL;
	GETWORD;
	return 1;
}

//＜表达式＞ ::=［＋｜－］＜项＞{＜加法运算符＞＜项＞}   //[+|-]只作用于第一个<项>
int Grammar_analysis::is_BDS()
{
	if (lexical_analysis.symbolType == PLUS || lexical_analysis.symbolType == MINU)
	{
		PRINTL;
		GETWORD;
	}
	if (is_X() != 1) return 0;
	PRINTG(X);
	do
	{
		if (is_JFYSF() != 1) break;
		PRINTL;
		GETWORD;
		if (is_X() != 1) return 1;
		PRINTG(X);
	} while (true);
	return 1;
}

//＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
int Grammar_analysis::is_X()
{
	if (is_YZ() != 1) return 0;
	PRINTG(YZ);
	do {
		if (is_CFYSF() != 1) break;
		PRINTL;
		GETWORD;
		if (is_YZ() != 1) return 1;
		PRINTG(YZ);
	} while (true);
	return 1;
}

//＜因子＞ ::= ＜标识符＞｜＜标识符＞'['＜表达式＞']'|'('＜表达式＞')'｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞  
int Grammar_analysis::is_YZ()
{
	switch (lexical_analysis.symbolType)
	{
	case IDENFR:
	{
		PRINTL;
		GETWORD;
		if (lexical_analysis.symbolType == LBRACK)
		{
			PRINTL;
			GETWORD;
			if (is_BDS() != 1) MYERROR;
			PRINTG(BDS);
			if (lexical_analysis.symbolType != RBRACK) MYERROR;
			PRINTL;
			GETWORD;
		}
		else if (lexical_analysis.symbolType == LPARENT)
		{
			if (is_YFHZHSDYYJ() != 1) MYERROR;
			PRINTG(YFHZHSDYYJ);
		}
		return 1;
	}
	case LPARENT:
	{
		PRINTL;
		GETWORD;
		if (is_BDS() != 1) MYERROR;
		PRINTG(BDS);
		if (lexical_analysis.symbolType != RPARENT) MYERROR;
		PRINTL;
		GETWORD;
		return 1;
	}
	default:
	{
		if (is_ZS() == 1)
		{
			PRINTG(ZS);
			return 1;
		}
		if (is_ZF() == 1) 
		{ 
			PRINTL;
			GETWORD;
			return 1;
		}
		break;
	}
	}
	return 0;
}

//字符
int Grammar_analysis::is_ZF()
{
	if (is_JFYSF() == 1) return 1;
	if (is_CFYSF() == 1) return 1;
	if (is_ZM() == 1) return 1;
	if (is_SZ() == 1) return 1;
	return 0;
}

//加法运算符
int Grammar_analysis::is_JFYSF()
{
	switch (lexical_analysis.symbolType)
	{
	case PLUS: return 1;
	case MINU: return 1;
	default: break;
	}
	return 0;
}

//乘法运算符
int Grammar_analysis::is_CFYSF()
{
	switch (lexical_analysis.symbolType)
	{
	case MULT: return 1;
	case DIV: return 1;
	default: break;
	}
	return 0;
}

//字母
int Grammar_analysis::is_ZM()
{
	if (lexical_analysis.symbolType == CHARCON)
	{
		char ch = lexical_analysis.save[0];
		if (isalpha(ch) || ch == '_') return 1;
	}
	return 0;
}

//数字
int Grammar_analysis::is_SZ()
{
	if (lexical_analysis.symbolType == INTCON && lexical_analysis.save.size() == 1)
	{
		return 1;
	}
	return 0;
}

//＜值参数表＞ ::= ＜表达式＞{,＜表达式＞}｜＜空＞
int Grammar_analysis::is_ZCSB()
{
	if (is_BDS() != 1) return 0;
	PRINTG(BDS);
	do
	{
		if (lexical_analysis.symbolType != COMMA) break;
		PRINTL;
		GETWORD;
		if (is_BDS() != 1) return 0;
		PRINTG(BDS);
	} while (true);
	return 1;
}

//关系运算符
int Grammar_analysis::is_GXYSF()
{
	switch (lexical_analysis.symbolType)
	{
	case LSS:return 1;
	case LEQ:return 1;
	case GRE:return 1;
	case GEQ:return 1;
	case EQL:return 1;
	case NEQ:return 1;
	}
	return 0;
}



