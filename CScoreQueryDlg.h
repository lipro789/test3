#pragma once
#include "afxdialogex.h"


// CScoreQueryDlg 对话框

class CScoreQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CScoreQueryDlg)

public:
	CScoreQueryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreQueryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCOREQUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SQGrade;
	CComboBox m_SQClass;
	CComboBox m_SQTerm;
	CComboBox m_SQCourse;
	CString m_SQName;
	CString m_SQNo;
	CString strSQGrade;
	CString strSQClass;
	CString strSQTerm;
	CString strSQCourse;
	CListCtrl m_SQList;
	_ConnectionPtr m_pConnection;//用于连接数据库
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedButton1();
};
