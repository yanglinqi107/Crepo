#include "mfc.h"

MyApp app;	//全局应用程序变量，有且仅有一个

BOOL MyApp::InitInstance()
{
	MyFrame* frame = new MyFrame;
	
	//显示和更新
	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();

	//保存指向应用程序的主窗口的指针，m_pMainWnd是CWinThread的数据成员，CWinApp是CWinThread的子类
	m_pMainWnd = frame;		

	return TRUE;
}


//消息映射分界宏
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	
	ON_WM_LBUTTONDOWN()  //鼠标左键按下

	ON_WM_CHAR()		//键盘

	ON_WM_PAINT()		//绘图

END_MESSAGE_MAP()


MyFrame::MyFrame()
{
	Create(NULL, TEXT("mfc"));
}

//鼠标左键按下
void MyFrame::OnLButtonDown(UINT, CPoint point)
{
	/*TCHAR buf[1024];
	wsprintf(buf, TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(buf, TEXT("鼠标左键按下"));*/

	//mfc中的字符串
	CString str;
	str.Format(TEXT("x = %d,,,y = %d"), point.x, point.y);
	MessageBox(str);
}

//键盘
void MyFrame::OnChar(UINT key, UINT, UINT)
{
	CString str;
	str.Format(TEXT("按下了%c键"), key);
	MessageBox(str);
}

//绘图
void MyFrame::OnPaint()
{
	//CPaintDC是CDC的子类，其它绘图的方法可以在CDC中找到
	CPaintDC dc(this); //this指定画图设备，就是图画在什么上面
	
	dc.TextOutW(100, 100, TEXT("为了部落"));

	//画椭圆
	dc.Ellipse(10, 10, 100, 100);
}

