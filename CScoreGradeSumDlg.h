#pragma once
#include "afxdialogex.h"


// CScoreGradeSumDlg 对话框

class CScoreGradeSumDlg : public CDialog
{
	DECLARE_DYNAMIC(CScoreGradeSumDlg)

public:
	CScoreGradeSumDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreGradeSumDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCOREGRADESUM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SGSumGrade;
	CComboBox m_SGSumTerm;
	CComboBox m_SGSumCourse;
	CString m_strSGSumGrade;
	CString m_strSGSumTerm;
	CString m_strSGSumCourse;
	CString m_SGSumMean;
	CString m_SGSumNum1;
	CString m_SGSumNum2;
	CString m_SGSumNum3;
	CString m_SGSumNum4;
	CString m_SGSumNum5;
	_ConnectionPtr m_pConnection;        //用于连接数据库
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo6();
};
