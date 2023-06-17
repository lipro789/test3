// CStudentAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CStudentAdd.h"


// CStudentAdd 对话框

IMPLEMENT_DYNAMIC(CStudentAdd, CDialog)

CStudentAdd::CStudentAdd(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_STUDENTADD, pParent)
	, m_StudentName(_T(""))
	, m_StudentNum(_T(""))
	, m_Grade(_T(""))
	, m_Class(_T(""))
	, m_StudentAge(_T(""))
	, m_StudentTel(_T(""))
	, m_StudentAddress(_T(""))
{

}

CStudentAdd::~CStudentAdd()
{
}

void CStudentAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StudentName);
	DDX_Text(pDX, IDC_EDIT2, m_StudentNum);
	DDX_Text(pDX, IDC_EDIT3, m_Grade);
	DDX_Text(pDX, IDC_EDIT4, m_Class);
	DDX_Text(pDX, IDC_EDIT5, m_StudentAge);
	DDX_Text(pDX, IDC_EDIT6, m_StudentTel);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StudentBirth);
	DDX_Text(pDX, IDC_EDIT6, m_StudentTel);
	DDX_Text(pDX, IDC_EDIT7, m_StudentAddress);
}


BEGIN_MESSAGE_MAP(CStudentAdd, CDialog)
	ON_BN_CLICKED(IDOK, &CStudentAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CStudentAdd 消息处理程序


void CStudentAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加学生信息
	UpdateData(TRUE);
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionTimeout = 20;
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	try
	{
		hr = pRecordset->Open("select * from 学生信息表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			pRecordset->AddNew();
			pRecordset->PutCollect("姓名", _variant_t(m_StudentName));
			pRecordset->PutCollect("学号", _variant_t(m_StudentNum));
			pRecordset->PutCollect("年级", _variant_t(m_Grade));
			pRecordset->PutCollect("班级", _variant_t(m_Class));
			if (GetCheckedRadioButton(IDC_RADIO_GG, IDC_RADIO_MM) == IDC_RADIO_GG)
				pRecordset->PutCollect("性别", _variant_t(_T("男")));
			else if (GetCheckedRadioButton(IDC_RADIO_GG, IDC_RADIO_MM) == IDC_RADIO_MM)
				pRecordset->PutCollect("性别", _variant_t(_T("女")));
			pRecordset->PutCollect("年龄", _variant_t(m_StudentAge));
			CString strDate;
			GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(strDate);
			pRecordset->PutCollect("出生年月", _variant_t(strDate));
			pRecordset->PutCollect("电话号码", _variant_t(m_StudentTel));
			pRecordset->PutCollect("家庭地址", _variant_t(m_StudentAddress));
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
	UpdateData(FALSE);
	OnOK();
}

