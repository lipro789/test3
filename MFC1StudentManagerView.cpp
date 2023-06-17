
// MFC1StudentManagerView.cpp: CMFC1StudentManagerView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC1StudentManager.h"
#endif

#include "MFC1StudentManagerDoc.h"
#include "MFC1StudentManagerView.h"
#include "CClassAdd.h"
#include "CCourseAdd.h"
#include "CTeacherAdd.h"
#include "CStudentAdd.h"
#include "CScoreAdd.h"
#include "CScoreQueryDlg.h"
#include "CScoreOrder.h"
#include "CScoreGradeSumDlg.h"
#include "CScoreClassSumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1StudentManagerView

IMPLEMENT_DYNCREATE(CMFC1StudentManagerView, CView)

BEGIN_MESSAGE_MAP(CMFC1StudentManagerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_CLASSADD, &CMFC1StudentManagerView::OnClassadd)
	ON_COMMAND(ID_COURSEADD, &CMFC1StudentManagerView::OnCourseadd)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	ON_COMMAND(ID_TEACHERADD, &CMFC1StudentManagerView::OnTeacheradd)
	ON_COMMAND(ID_STUDENTADD, &CMFC1StudentManagerView::OnStudentadd)
	ON_COMMAND(ID_SCOREADD, &CMFC1StudentManagerView::OnScoreadd)
	ON_COMMAND(ID_SCOREQUERY, &CMFC1StudentManagerView::OnScorequery)
	ON_COMMAND(ID_SCOREQUEUE, &CMFC1StudentManagerView::OnScorequeue)
	ON_COMMAND(ID_SCOREGRADE, &CMFC1StudentManagerView::OnScoregrade)
	ON_COMMAND(ID_SCORECLASS, &CMFC1StudentManagerView::OnScoreclass)
END_MESSAGE_MAP()

// CMFC1StudentManagerView 构造/析构

CMFC1StudentManagerView::CMFC1StudentManagerView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFC1StudentManagerView::~CMFC1StudentManagerView()
{
}

BOOL CMFC1StudentManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC1StudentManagerView 绘图

void CMFC1StudentManagerView::OnDraw(CDC* /*pDC*/)
{
	CMFC1StudentManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFC1StudentManagerView 打印

BOOL CMFC1StudentManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC1StudentManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC1StudentManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFC1StudentManagerView 诊断

#ifdef _DEBUG
void CMFC1StudentManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1StudentManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1StudentManagerDoc* CMFC1StudentManagerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1StudentManagerDoc)));
	return (CMFC1StudentManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1StudentManagerView 消息处理程序
void CMFC1StudentManagerView::OnClassadd()
{
	// TODO: 在此添加命令处理程序代码
	//打开添加班级信息的窗口
	CClassAdd CClass;//创建添加班级信息窗口对象
	CClass.DoModal();//创建模态对话框
}

void CMFC1StudentManagerView::OnCourseadd()
{
	// TODO: 在此添加命令处理程序代码
	CCourseAdd CCourse;
	CCourse.DoModal();
}


void CMFC1StudentManagerView::OnTeacheradd()
{
	// TODO: 在此添加命令处理程序代码
	CTeacherAdd CTeacher;
	CTeacher.DoModal();
}


void CMFC1StudentManagerView::OnStudentadd()
{
	// TODO: 在此添加命令处理程序代码
	CStudentAdd CStudent;
	CStudent.DoModal();
}


void CMFC1StudentManagerView::OnScoreadd()
{
	// TODO: 在此添加命令处理程序代码
	CScoreAdd CScore;
	CScore.DoModal();
}


void CMFC1StudentManagerView::OnScorequery()
{
	// TODO: 在此添加命令处理程序代码
	CScoreQueryDlg CScoreQuery;
	CScoreQuery.DoModal();
}


void CMFC1StudentManagerView::OnScorequeue()
{
	// TODO: 在此添加命令处理程序代码
	CScoreOrder COrder;
	COrder.DoModal();
}


void CMFC1StudentManagerView::OnScoregrade()
{
	// TODO: 在此添加命令处理程序代码
	CScoreGradeSumDlg GradeSum;
	GradeSum.DoModal();
}


void CMFC1StudentManagerView::OnScoreclass()
{
	// TODO: 在此添加命令处理程序代码
	CScoreClassSumDlg ClassSum;
	ClassSum.DoModal();
}
