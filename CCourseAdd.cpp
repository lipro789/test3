// CCourseAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CCourseAdd.h"


// CCourseAdd 对话框

IMPLEMENT_DYNAMIC(CCourseAdd, CDialog)

CCourseAdd::CCourseAdd(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_COURSEADD, pParent)
	, m_CourseName(_T(""))
	, m_CourseNum(_T(""))
	, m_CourseTime(_T(""))
	, m_CourseTeacher(_T(""))
{

}

CCourseAdd::~CCourseAdd()
{
}

void CCourseAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COURSENAME, m_CourseName);
	DDX_Text(pDX, IDC_EDIT_COURSENUM, m_CourseNum);
	DDX_Text(pDX, IDC_EDIT_COURSETIME, m_CourseTime);
	DDX_Control(pDX, IDC_COMBO1, m_CTAdd);
	DDX_CBString(pDX, IDC_COMBO1, m_CourseTeacher);
}


BEGIN_MESSAGE_MAP(CCourseAdd, CDialog)
	ON_BN_CLICKED(IDOK, &CCourseAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CCourseAdd 消息处理程序


void CCourseAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加课程信息
	UpdateData(TRUE);
	//   m_pConnection.CreateInstance(__uuidof(Connection));
	   //m_pConnection->ConnectionTimeout=20;
	   //m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb","","",adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	try
	{
		hr = pRecordset->Open("select * from 课程信息", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			pRecordset->AddNew();
			pRecordset->PutCollect("课程名称", _variant_t(m_CourseName));
			pRecordset->PutCollect("课程编号", _variant_t(m_CourseNum));
			pRecordset->PutCollect("学时", _variant_t(m_CourseTime));
			if (GetCheckedRadioButton(IDC_RADIO_NEED, IDC_RADIO_UNNEED) == IDC_RADIO_NEED)
				pRecordset->PutCollect("必修/选修", _variant_t(_T("必修")));
			else if (GetCheckedRadioButton(IDC_RADIO_NEED, IDC_RADIO_UNNEED) == IDC_RADIO_UNNEED)
				pRecordset->PutCollect("必修/选修", _variant_t(_T("选修")));
						pRecordset->PutCollect("任课老师", _variant_t(m_CourseTeacher));
			pRecordset->Update();
			OnOK();
			AfxMessageBox(_T("添加纪录成功！"));
		}

	}

	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return;
	}
	pRecordset->Close();
	pRecordset = NULL;
	UpdateData(FALSE);
}
BOOL CCourseAdd::OnInitDialog() {
	CDialog::OnInitDialog();
	//添加教师名单
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionTimeout = 20;
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	try
	{
		hr = pRecordset->Open("select 姓名 from 教师信息表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			_variant_t var;
			CString strValue;
			while (!pRecordset->adoEOF)
			{
				var = pRecordset->GetCollect("姓名");
				if (var.vt != VT_NULL)
					strValue = (LPCSTR)_bstr_t(var);
				m_CTAdd.AddString(strValue);
				pRecordset->MoveNext();
			}
		}
	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return TRUE;
	}
	pRecordset->Close();
	pRecordset = NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
 }