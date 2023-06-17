#pragma once
#include "afxdialogex.h"
#include"CScoreAdd.h"


class CScoreAdd; //CScoreAdd对话框

// CStudentScoreAdd 对话框

class CStudentScoreAdd : public CDialog
{
	DECLARE_DYNAMIC(CStudentScoreAdd)

public:
	CStudentScoreAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentScoreAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STUDENTCOREADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_StudentNum;
	CString m_StudentName;
	CString m_StudentGrade;
	CString m_StudentClass;
	CString m_StudentTerm;
	CString m_StudentCourse;
	CString m_StudentScore;
	//用于得到成绩录入窗口的成员变量的值
	CScoreAdd* ScoreAddDlg;////引用成绩录入窗口类，可以实现改变成绩录入对话框的值
	int m_StudentIndex;//
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
};
