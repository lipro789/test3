// CScoreClassSumDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CScoreClassSumDlg.h"


// CScoreClassSumDlg 对话框

IMPLEMENT_DYNAMIC(CScoreClassSumDlg, CDialog)

CScoreClassSumDlg::CScoreClassSumDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SCORECLASSSUM, pParent)
	, strSCSumGrade(_T(""))
	, strSCSumClass(_T(""))
	, strSCSumTerm(_T(""))
	, strSCSumCourse(_T(""))
	, m_SCSumMean(_T(""))
	, m_SCSumNum1(_T(""))
	, m_SCSumNum2(_T(""))
	, m_SCSumNum3(_T(""))
	, m_SCSumNum4(_T(""))
	, m_SCSumNum5(_T(""))
{

}

CScoreClassSumDlg::~CScoreClassSumDlg()
{
}

void CScoreClassSumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SCSumGrade);
	DDX_Control(pDX, IDC_COMBO6, m_SCSumClass);
	DDX_Control(pDX, IDC_COMBO7, m_SCSumTerm);
	DDX_Control(pDX, IDC_COMBO8, m_SCSumCourse);
	DDX_CBString(pDX, IDC_COMBO1, strSCSumGrade);
	DDX_CBString(pDX, IDC_COMBO6, strSCSumClass);
	DDX_CBString(pDX, IDC_COMBO7, strSCSumTerm);
	DDX_CBString(pDX, IDC_COMBO8, strSCSumCourse);
	DDX_Text(pDX, IDC_EDIT1, m_SCSumMean);
	DDX_Text(pDX, IDC_EDIT2, m_SCSumNum1);
	DDX_Text(pDX, IDC_EDIT3, m_SCSumNum2);
	DDX_Text(pDX, IDC_EDIT4, m_SCSumNum3);
	DDX_Text(pDX, IDC_EDIT5, m_SCSumNum4);
	DDX_Text(pDX, IDC_EDIT6, m_SCSumNum5);
}


BEGIN_MESSAGE_MAP(CScoreClassSumDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScoreClassSumDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CScoreClassSumDlg::OnCbnSelchangeCombo6)
	ON_CBN_SELCHANGE(IDC_COMBO7, &CScoreClassSumDlg::OnCbnSelchangeCombo7)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreClassSumDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CScoreClassSumDlg 消息处理程序
BOOL CScoreClassSumDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//添加年级
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionTimeout = 20;
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	try
	{
		hr = pRecordset->Open("select distinct 年级  from 成绩表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			m_SCSumGrade.ResetContent();
			_variant_t var;
			CString strSCSumGradeValue;
			while (!pRecordset->adoEOF)
			{
				//获取年级名称
				var = pRecordset->GetCollect("年级");
				if (var.vt != VT_NULL)
					strSCSumGradeValue = (LPCSTR)_bstr_t(var);
				m_SCSumGrade.AddString(strSCSumGradeValue);
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


void CScoreClassSumDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//通过年级来添加班级
	m_SCSumClass.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SCSumGrade.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			/*CString strGrade;*/
			m_SCSumGrade.GetLBText(SelectIndex, strSCSumGrade);
			CString str;
			str.Format(_T("select distinct 班级  from 成绩表 where  年级 ='%s'"), strSCSumGrade);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSCSumClassValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("班级");
					if (var.vt != VT_NULL)
						strSCSumClassValue = (LPCSTR)_bstr_t(var);
					m_SCSumClass.AddString(strSCSumClassValue);
					pRecordset->MoveNext();
				}
			}
			pRecordset->Close();
			pRecordset = NULL;
		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
			return;
		}
	}
}


void CScoreClassSumDlg::OnCbnSelchangeCombo6()
{
	// TODO: 在此添加控件通知处理程序代码
	//通过年级和班级来添加学期信息
	m_SCSumTerm.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SCSumClass.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			/*CString strGrade;*/
			m_SCSumClass.GetLBText(SelectIndex, strSCSumClass);
			CString str;
			str.Format(_T("select distinct 学期  from 成绩表 where  年级 ='%s' and 班级 ='%s'"), strSCSumGrade, strSCSumClass);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSCSumTermValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("学期");
					if (var.vt != VT_NULL)
						strSCSumTermValue = (LPCSTR)_bstr_t(var);
					m_SCSumTerm.AddString(strSCSumTermValue);
					pRecordset->MoveNext();
				}
			}
			pRecordset->Close();
			pRecordset = NULL;
		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
			return;
		}
	}
}


void CScoreClassSumDlg::OnCbnSelchangeCombo7()
{
	// TODO: 在此添加控件通知处理程序代码
	//通过年级、班级和学期来添加课程信息
	m_SCSumCourse.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SCSumTerm.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			/*CString strGrade;*/
			m_SCSumTerm.GetLBText(SelectIndex, strSCSumTerm);
			CString str;
			str.Format(_T("select distinct 课程  from 成绩表 where  年级 ='%s' and 班级 ='%s' and 学期 ='%s'"), strSCSumGrade, strSCSumClass, strSCSumTerm);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSCSumCourseValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("课程");
					if (var.vt != VT_NULL)
						strSCSumCourseValue = (LPCSTR)_bstr_t(var);
					m_SCSumCourse.AddString(strSCSumCourseValue);
					pRecordset->MoveNext();
				}
			}
			pRecordset->Close();
			pRecordset = NULL;
		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
			return;
		}
	}
}


void CScoreClassSumDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
//用于统计各种信息
	//求出班级某科目成绩的平均分
	UpdateData(TRUE);
	int SelectIndex = m_SCSumCourse.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{
		m_SCSumCourse.GetLBText(SelectIndex, strSCSumCourse);
		CString strSQL;
		_variant_t vIndex = (long)0;
		_variant_t vCount;
		_variant_t RecordsAffected;
		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance(__uuidof(Recordset));
		//求出班级某课平均分
		//将获取的第一个字段的值放入vCount中
		strSQL.Format(_T("select AVG(成绩) from 成绩表 where 年级 ='%s' and 班级 = '%s' and 学期 ='%s' and 课程 ='%s'"), strSCSumGrade, strSCSumClass, strSCSumTerm, strSCSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SCSumMean = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在90~100的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 班级 = '%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=90"), strSCSumGrade, strSCSumClass, strSCSumTerm, strSCSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SCSumNum1 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在80~89的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 班级 = '%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=80 and 成绩<90"), strSCSumGrade, strSCSumClass, strSCSumTerm, strSCSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SCSumNum2 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在70~79的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 班级 = '%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=70 and 成绩<80"), strSCSumGrade, strSCSumClass, strSCSumTerm, strSCSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SCSumNum3 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在60~69的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 班级 = '%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=60 and 成绩<70"), strSCSumGrade, strSCSumClass, strSCSumTerm, strSCSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SCSumNum4 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出不及格的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 班级 = '%s' and 学期 ='%s' and 课程 ='%s' and 成绩 <60"), strSCSumGrade, strSCSumClass, strSCSumTerm, strSCSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SCSumNum5 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();
	}
	UpdateData(FALSE);
}
