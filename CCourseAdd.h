#pragma once
#include "afxdialogex.h"


// CCourseAdd 对话框

class CCourseAdd : public CDialog
{
	DECLARE_DYNAMIC(CCourseAdd)

public:
	CCourseAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCourseAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COURSEADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_CourseName;
	CString m_CourseNum;
	CString m_CourseTime;
	CComboBox m_CTAdd;
	CString m_CourseTeacher;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	_ConnectionPtr m_pConnection;
};
