#pragma once
#include <afxwin.h>  //mfcͷ�ļ�

class MyApp : public CWinApp   //CWinAppӦ�ó�����
{
public:
	//�������
	virtual BOOL InitInstance();
};

class MyFrame : public CFrameWnd   //���ڿ����
{
public:
	MyFrame();

	afx_msg void OnLButtonDown(UINT, CPoint);

	afx_msg void OnChar(UINT, UINT, UINT);

	afx_msg void OnPaint();

	//��Ϣӳ��������  �ṩ��Ϣӳ�����
	DECLARE_MESSAGE_MAP()
};