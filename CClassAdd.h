#pragma once
#include <afxwin.h>
#include"Resource.h"
class CClassAdd : public CDialog
{
	DECLARE_DYNAMIC(CClassAdd)
public:
	CClassAdd(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CClassAdd();

	// 对话框数据
	enum {IDD= IDD_DIALOG_CLASSADD	};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
public:
	CString m_ClassName;
	CString m_ClassNum;
	CString m_ClassGrade;
	_ConnectionPtr m_pConnection;//定义链接数据库
	DECLARE_MESSAGE_MAP()
		afx_msg void OnBnClickedOk();
};

