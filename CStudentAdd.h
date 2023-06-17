#pragma once
#include "afxdialogex.h"

class CStudentAdd : public CDialog
{
	DECLARE_DYNAMIC(CStudentAdd)

public:
	CStudentAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STUDENTADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_StudentName;
	CString m_StudentNum;
	CString m_Grade;
	CString m_Class;
	CString m_StudentAge;

	_ConnectionPtr m_pConnection;    //用于连接数据库
 
	CDateTimeCtrl m_StudentBirth;

	afx_msg void OnBnClickedOk();
	CString m_StudentTel;
	CString m_StudentAddress;
};
