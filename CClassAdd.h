#pragma once
#include <afxwin.h>
#include"Resource.h"
class CClassAdd : public CDialog
{
	DECLARE_DYNAMIC(CClassAdd)
public:
	CClassAdd(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CClassAdd();

	// �Ի�������
	enum {IDD= IDD_DIALOG_CLASSADD	};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
public:
	CString m_ClassName;
	CString m_ClassNum;
	CString m_ClassGrade;
	_ConnectionPtr m_pConnection;//�����������ݿ�
	DECLARE_MESSAGE_MAP()
		afx_msg void OnBnClickedOk();
};

