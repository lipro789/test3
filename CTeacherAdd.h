#pragma once
#include "afxdialogex.h"


// CTeacherAdd 对话框

class CTeacherAdd : public CDialog
{
	DECLARE_DYNAMIC(CTeacherAdd)

public:
	CTeacherAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacherAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEACHERADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_TeacherAge;
	CString m_TeacherIntr;
	CString m_TeacherName;
	CString m_TeacherNum;
	CString m_TeacherOffice;
	CString m_TeacherTel;
	CString m_TeacherXL;
	CString m_TeacherZC;
	_ConnectionPtr m_pConnection;

	afx_msg void OnBnClickedOk();
	CButton m_R2;
	CButton m_R1;
};
