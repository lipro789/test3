#pragma once
#include "afxdialogex.h"


// CScoreOrder 对话框

class CScoreOrder : public CDialog
{
	DECLARE_DYNAMIC(CScoreOrder)

public:
	CScoreOrder(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreOrder();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_SCOREQUEUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SOGrade;
	CComboBox m_SOClass;
	CComboBox m_SOTerm;
	CComboBox m_SOCourse;
	CString m_strSOGrade;
	CString m_strSOClass;
	CString m_strSOTerm;
	CString m_strSOCourse;
	CListCtrl m_SOList;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	_ConnectionPtr m_pConnection;  //用于连接数据库
	virtual BOOL OnInitDialog();
};
