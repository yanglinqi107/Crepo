#include "mfc.h"

MyApp app;	//ȫ��Ӧ�ó�����������ҽ���һ��

BOOL MyApp::InitInstance()
{
	MyFrame* frame = new MyFrame;
	
	//��ʾ�͸���
	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();

	//����ָ��Ӧ�ó���������ڵ�ָ�룬m_pMainWnd��CWinThread�����ݳ�Ա��CWinApp��CWinThread������
	m_pMainWnd = frame;		

	return TRUE;
}


//��Ϣӳ��ֽ��
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	
	ON_WM_LBUTTONDOWN()  //����������

	ON_WM_CHAR()		//����

	ON_WM_PAINT()		//��ͼ

END_MESSAGE_MAP()


MyFrame::MyFrame()
{
	Create(NULL, TEXT("mfc"));
}

//����������
void MyFrame::OnLButtonDown(UINT, CPoint point)
{
	/*TCHAR buf[1024];
	wsprintf(buf, TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(buf, TEXT("����������"));*/

	//mfc�е��ַ���
	CString str;
	str.Format(TEXT("x = %d,,,y = %d"), point.x, point.y);
	MessageBox(str);
}

//����
void MyFrame::OnChar(UINT key, UINT, UINT)
{
	CString str;
	str.Format(TEXT("������%c��"), key);
	MessageBox(str);
}

//��ͼ
void MyFrame::OnPaint()
{
	//CPaintDC��CDC�����࣬������ͼ�ķ���������CDC���ҵ�
	CPaintDC dc(this); //thisָ����ͼ�豸������ͼ����ʲô����
	
	dc.TextOutW(100, 100, TEXT("Ϊ�˲���"));

	//����Բ
	dc.Ellipse(10, 10, 100, 100);
}

