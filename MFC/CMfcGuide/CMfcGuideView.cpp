
// CMfcGuideView.cpp: CCMfcGuideView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CMfcGuide.h"
#endif

#include "CMfcGuideDoc.h"
#include "CMfcGuideView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMfcGuideView

IMPLEMENT_DYNCREATE(CCMfcGuideView, CView)

BEGIN_MESSAGE_MAP(CCMfcGuideView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCMfcGuideView 构造/析构

CCMfcGuideView::CCMfcGuideView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCMfcGuideView::~CCMfcGuideView()
{
}

BOOL CCMfcGuideView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCMfcGuideView 绘图

void CCMfcGuideView::OnDraw(CDC* pDC)
{
	CCMfcGuideDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->TextOutW(100, 100, TEXT("为了部落"));
}


// CCMfcGuideView 打印

BOOL CCMfcGuideView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCMfcGuideView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCMfcGuideView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCMfcGuideView 诊断

#ifdef _DEBUG
void CCMfcGuideView::AssertValid() const
{
	CView::AssertValid();
}

void CCMfcGuideView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCMfcGuideDoc* CCMfcGuideView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCMfcGuideDoc)));
	return (CCMfcGuideDoc*)m_pDocument;
}
#endif //_DEBUG


// CCMfcGuideView 消息处理程序


void CCMfcGuideView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);

	CString str;   
	str.Format(TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(str);
}


void CCMfcGuideView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()

	dc.TextOutW(100, 100, TEXT("为了联盟"));
}
