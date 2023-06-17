// CTeacherAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CTeacherAdd.h"


// CTeacherAdd 对话框

IMPLEMENT_DYNAMIC(CTeacherAdd, CDialog)

CTeacherAdd::CTeacherAdd(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_TEACHERADD, pParent)
	, m_TeacherAge(_T(""))
	, m_TeacherIntr(_T(""))
	, m_TeacherName(_T(""))
	, m_TeacherNum(_T(""))
	, m_TeacherOffice(_T(""))
	, m_TeacherTel(_T(""))
	, m_TeacherXL(_T(""))
	, m_TeacherZC(_T(""))
{

}

CTeacherAdd::~CTeacherAdd()
{
}

void CTeacherAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEAAGE, m_TeacherAge);
	DDX_Text(pDX, IDC_EDIT_TEAINTR, m_TeacherIntr);
	DDX_Text(pDX, IDC_EDIT_TEANAME, m_TeacherName);
	DDX_Text(pDX, IDC_EDIT_TEANUM, m_TeacherNum);
	DDX_Text(pDX, IDC_EDIT_TEAOFFICE, m_TeacherOffice);
	DDX_Text(pDX, IDC_EDIT_TEATEL, m_TeacherTel);
	DDX_Text(pDX, IDC_EDIT_TEAXL, m_TeacherXL);
	DDX_Text(pDX, IDC_EDIT_TEAZC, m_TeacherZC);
	DDX_Control(pDX, IDC_RADIO_TMM, m_R2);
	DDX_Control(pDX, IDC_RADIO_TGG, m_R1);
}


BEGIN_MESSAGE_MAP(CTeacherAdd, CDialog)
	ON_BN_CLICKED(IDOK, &CTeacherAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CTeacherAdd 消息处理程序


void CTeacherAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加教师信息
	UpdateData(TRUE);
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionTimeout = 20;
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	try
	{
		hr = pRecordset->Open("select * from 教师信息表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			pRecordset->AddNew();
			pRecordset->PutCollect("姓名", _variant_t(m_TeacherName));
			pRecordset->PutCollect("教师编号", _variant_t(m_TeacherNum));
			if (m_R1.GetCheck() == TRUE)
				pRecordset->PutCollect("性别", _variant_t(_T("男")));
			else 
				pRecordset->PutCollect("性别", _variant_t(_T("女")));
			/*if (GetCheckedRadioButton(IDC_RADIO_TGG, IDC_RADIO_TMM) == IDC_RADIO_TGG)
				pRecordset->PutCollect("性别", _variant_t(_T("男")));
			else if (GetCheckedRadioButton(IDC_RADIO_TGG, IDC_RADIO_TMM) == IDC_RADIO_TMM)
				pRecordset->PutCollect("性别", _variant_t(_T("女")));*/
			pRecordset->PutCollect("年龄", _variant_t(m_TeacherAge));
			pRecordset->PutCollect("职称", _variant_t(m_TeacherZC));
			pRecordset->PutCollect("学历", _variant_t(m_TeacherXL));
			pRecordset->PutCollect("电话号码", _variant_t(m_TeacherTel));
			pRecordset->PutCollect("办公室", _variant_t(m_TeacherOffice));
			pRecordset->PutCollect("简介", _variant_t(m_TeacherIntr));
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
}
