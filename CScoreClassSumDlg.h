#pragma once
#include "afxdialogex.h"


// CScoreClassSumDlg 对话框

class CScoreClassSumDlg : public CDialog
{
	DECLARE_DYNAMIC(CScoreClassSumDlg)

public:
	CScoreClassSumDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreClassSumDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORECLASSSUM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SCSumGrade;
	CComboBox m_SCSumClass;
	CComboBox m_SCSumTerm;
	CComboBox m_SCSumCourse;
	CString strSCSumGrade;
	CString strSCSumClass;
	CString strSCSumTerm;
	CString strSCSumCourse;
	CString m_SCSumMean;
	CString m_SCSumNum1;
	CString m_SCSumNum2;
	CString m_SCSumNum3;
	CString m_SCSumNum4;
	CString m_SCSumNum5;
	_ConnectionPtr m_pConnection;        //用于连接数据库
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo6();
	afx_msg void OnCbnSelchangeCombo7();
	afx_msg void OnBnClickedButton1();
};
