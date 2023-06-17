#include "pch.h"
#include "CClassAdd.h"
//#include "MFC1StudentManager.h"//

// CClassAdd �Ի���

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ͨ����������Ӧ�ؼ�����˱���֮�󣬿���ͨ��UpdateData()������ȡ����¶Ի���ؼ���ֵ
	UpdateData(TRUE);//�������ڻ�ȡ���뵽�ؼ�������,�����浽�����У��ؼ�->����
	m_pConnection.CreateInstance(__uuidof(Connection));//ʵ�������Ӷ���
	m_pConnection->ConnectionTimeout = 20;//�������Ӵ�ʱ��
	HRESULT hr;
	hr=m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=ѧ����Ϣ����ϵͳ.mdb", "", "", adConnectUnspecified);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("��ʧ��"));
		return;
	}
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));

	try
	{
		//ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
		hr = pRecordset->Open("select * from �༶��Ϣ��", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			pRecordset->AddNew();///����¼�¼
			pRecordset->PutCollect("�༶����", _variant_t(m_ClassName));
			pRecordset->PutCollect("�༶���", _variant_t(m_ClassNum));
			pRecordset->PutCollect("�꼶", _variant_t(m_ClassGrade));
			pRecordset->Update();
			OnOK();
			AfxMessageBox(_T("��Ӽ�¼�ɹ���"));
		}

	}

	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return;
	}
	//�������ڸ��¿ؼ��е����ݣ�����->�ؼ���
	//��������˱�����ֵ���뽫�����µ��ؼ���ʾ�����ɵ��ô˺���
	UpdateData(FALSE);
}
