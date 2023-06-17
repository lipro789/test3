#include "pch.h"
#include "CClassAdd.h"
//#include "MFC1StudentManager.h"//

// CClassAdd 对话框

IMPLEMENT_DYNAMIC(CClassAdd, CDialog)

CClassAdd::CClassAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CClassAdd::IDD, pParent)
, m_ClassName(_T(""))
, m_ClassNum(_T(""))
, m_ClassGrade(_T(""))
{

}

CClassAdd::~CClassAdd()
{
}
void CClassAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CLASSSNAME, m_ClassName);
	DDX_Text(pDX, IDC_CLASSSNUM, m_ClassNum);
	DDX_Text(pDX, IDC_CLASSSGRADE, m_ClassGrade);
}
BEGIN_MESSAGE_MAP(CClassAdd, CDialog)
ON_BN_CLICKED(IDOK, &CClassAdd::OnBnClickedOk)
END_MESSAGE_MAP()


void CClassAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//在通过类向导向相应控件添加了变量之后，可以通过UpdateData()函数获取或跟新对话框控件的值
	UpdateData(TRUE);//函数用于获取输入到控件的数据,并保存到变量中，控件->变量
	m_pConnection.CreateInstance(__uuidof(Connection));//实例化连接对象
	m_pConnection->ConnectionTimeout = 20;//设置连接打开时间
	HRESULT hr;
	hr=m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("打开失败"));
		return;
	}
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));

	try
	{
		//执行SQL语句，得到记录集, connection必须已和数据库连接
		hr = pRecordset->Open("select * from 班级信息表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			pRecordset->AddNew();///添加新记录
			pRecordset->PutCollect("班级名称", _variant_t(m_ClassName));
			pRecordset->PutCollect("班级编号", _variant_t(m_ClassNum));
			pRecordset->PutCollect("年级", _variant_t(m_ClassGrade));
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
	//函数用于更新控件中的数据，变量->控件，
	//当你更改了变量的值并想将它更新到控件显示出来可调用此函数
	UpdateData(FALSE);
}
