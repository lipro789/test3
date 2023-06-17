
// MFC1StudentManagerView.h: CMFC1StudentManagerView 类的接口
//

#pragma once


class CMFC1StudentManagerView : public CView
{
protected: // 仅从序列化创建
	CMFC1StudentManagerView() noexcept;
	DECLARE_DYNCREATE(CMFC1StudentManagerView)

// 特性
public:
	CMFC1StudentManagerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFC1StudentManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClassadd();
	afx_msg void OnCourseadd();
	afx_msg void OnTeacheradd();
	afx_msg void OnStudentadd();
	afx_msg void OnScoreadd();
	afx_msg void OnScorequery();
	afx_msg void OnScorequeue();
	afx_msg void OnScoregrade();
	afx_msg void OnScoreclass();
};

#ifndef _DEBUG  // MFC1StudentManagerView.cpp 中的调试版本
inline CMFC1StudentManagerDoc* CMFC1StudentManagerView::GetDocument() const
   { return reinterpret_cast<CMFC1StudentManagerDoc*>(m_pDocument); }
#endif

