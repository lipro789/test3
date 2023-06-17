#pragma once
#include "afxdialogex.h"


// CScoreAdd 对话框

class CScoreAdd : public CDialog
{
	DECLARE_DYNAMIC(CScoreAdd)

public:
	CScoreAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCOREADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_scoreGrade; //获取年级名称
	CComboBox m_scoreClass;//获取班级名称
	CComboBox m_scoreTerm;//获取学期信息
	CComboBox m_scoreCourse;//获取课程信息
	_ConnectionPtr m_pConnection;//用于连接数据库

	CString strGrade;//用于存储年级
	CString strClass;//用于存储班级
	CString strTerm;//用于存储学期
	CString strCourse;//用于存储课程
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();

	CListCtrl m_scoreList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
