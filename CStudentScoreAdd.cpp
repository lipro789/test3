// CStudentScoreAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CStudentScoreAdd.h"


// CStudentScoreAdd 对话框

IMPLEMENT_DYNAMIC(CStudentScoreAdd, CDialog)

CStudentScoreAdd::CStudentScoreAdd(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_STUDENTCOREADD, pParent)
	, m_StudentNum(_T(""))
	, m_StudentName(_T(""))
	, m_StudentGrade(_T(""))
	, m_StudentTerm(_T(""))
	, m_StudentScore(_T(""))
	, m_StudentClass(_T(""))
	, m_StudentCourse(_T(""))
{

}

CStudentScoreAdd::~CStudentScoreAdd()
{
}

void CStudentScoreAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StudentNum);
	DDX_Text(pDX, IDC_EDIT2, m_StudentName);
	DDX_Text(pDX, IDC_EDIT3, m_StudentGrade);
	DDX_Text(pDX, IDC_EDIT4, m_StudentClass);
	DDX_Text(pDX, IDC_EDIT5, m_StudentTerm);
	DDX_Text(pDX, IDC_EDIT6, m_StudentCourse);
	DDX_Text(pDX, IDC_EDIT7, m_StudentScore);

}


BEGIN_MESSAGE_MAP(CStudentScoreAdd, CDialog)
	ON_BN_CLICKED(IDOK, &CStudentScoreAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CStudentScoreAdd 消息处理程序
BOOL CStudentScoreAdd::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//获取学生的信息
	CoInitialize(NULL);
	UpdateData(FALSE);
	//	GetDlgItem(IDC_EDIT1)//获取指定ID控件,返回指向给定控件或子窗口的指针
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_StudentNum);//将窗口标题设置为指定文本
	GetDlgItem(IDC_EDIT2)->SetWindowText(m_StudentName);
	GetDlgItem(IDC_EDIT3)->SetWindowText(m_StudentGrade);
	GetDlgItem(IDC_EDIT4)->SetWindowText(m_StudentClass);
	GetDlgItem(IDC_EDIT5)->SetWindowText(m_StudentTerm);
	GetDlgItem(IDC_EDIT6)->SetWindowText(m_StudentCourse);
	GetDlgItem(IDC_EDIT7)->SetWindowText(m_StudentScore);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStudentScoreAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加学生成绩
	UpdateData(TRUE);
	if (!m_StudentScore.IsEmpty())
	{
		ScoreAddDlg->m_scoreList.SetItemText(m_StudentIndex, 7, m_StudentScore);
	}
	OnOK();
}
