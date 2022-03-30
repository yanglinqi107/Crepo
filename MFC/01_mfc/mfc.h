#pragma once
#include <afxwin.h>  //mfc头文件

class MyApp : public CWinApp   //CWinApp应用程序类
{
public:
	//程序入口
	virtual BOOL InitInstance();
};

class MyFrame : public CFrameWnd   //窗口框架类
{
public:
	MyFrame();

	afx_msg void OnLButtonDown(UINT, CPoint);

	afx_msg void OnChar(UINT, UINT, UINT);

	afx_msg void OnPaint();

	//消息映射声明宏  提供消息映射机制
	DECLARE_MESSAGE_MAP()
};