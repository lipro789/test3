// CScoreGradeSumDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CScoreGradeSumDlg.h"


// CScoreGradeSumDlg 对话框

IMPLEMENT_DYNAMIC(CScoreGradeSumDlg, CDialog)

CScoreGradeSumDlg::CScoreGradeSumDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SCOREGRADESUM, pParent)
	, m_strSGSumGrade(_T(""))
	, m_strSGSumTerm(_T(""))
	, m_strSGSumCourse(_T(""))
	, m_SGSumNum1(_T(""))
	, m_SGSumNum2(_T(""))
	, m_SGSumNum5(_T(""))
	, m_SGSumMean(_T(""))
	, m_SGSumNum3(_T(""))
	, m_SGSumNum4(_T(""))
{

}

CScoreGradeSumDlg::~CScoreGradeSumDlg()
{
}

void CScoreGradeSumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SGSumGrade);
	DDX_Control(pDX, IDC_COMBO6, m_SGSumTerm);
	DDX_Control(pDX, IDC_COMBO7, m_SGSumCourse);
	DDX_CBString(pDX, IDC_COMBO1, m_strSGSumGrade);
	DDX_CBString(pDX, IDC_COMBO6, m_strSGSumTerm);
	DDX_CBString(pDX, IDC_COMBO7, m_strSGSumCourse);

	DDX_Text(pDX, IDC_EDIT2, m_SGSumNum1);
	DDX_Text(pDX, IDC_EDIT3, m_SGSumNum2);

	DDX_Text(pDX, IDC_EDIT6, m_SGSumNum5);
	DDX_Text(pDX, IDC_EDIT1, m_SGSumMean);
	DDX_Text(pDX, IDC_EDIT4, m_SGSumNum3);
	DDX_Text(pDX, IDC_EDIT5, m_SGSumNum4);
}


BEGIN_MESSAGE_MAP(CScoreGradeSumDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreGradeSumDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScoreGradeSumDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CScoreGradeSumDlg::OnCbnSelchangeCombo6)
END_MESSAGE_MAP()


// CScoreGradeSumDlg 消息处理程序
BOOL CScoreGradeSumDlg::OnInitDialog() {
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
			m_SGSumGrade.ResetContent();
			_variant_t var;
			CString strSGSumGradeValue;
			while (!pRecordset->adoEOF)
			{
				//获取年级名称
				var = pRecordset->GetCollect("年级");
				if (var.vt != VT_NULL)
					strSGSumGradeValue = (LPCSTR)_bstr_t(var);// _variant_t转换为CString：
				m_SGSumGrade.AddString(strSGSumGradeValue);
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


void CScoreGradeSumDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//用于统计各种信息
	//求出班级某科目成绩的平均分
	UpdateData(TRUE);
	int SelectIndex = m_SGSumCourse.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{
		m_SGSumCourse.GetLBText(SelectIndex, m_strSGSumCourse);
		CString strSQL;
		_variant_t vIndex = (long)0;
		_variant_t vCount;
		_variant_t RecordsAffected;
		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance(__uuidof(Recordset));
		//求出班级某课平均分
		//将获取的第一个字段的值放入vCount中
		strSQL.Format(_T("select AVG(成绩) from 成绩表 where 年级 ='%s' and 学期 ='%s' and 课程 ='%s'"), m_strSGSumGrade, m_strSGSumTerm, m_strSGSumCourse);
	/*Execute方法的原型如下所示:
		Execute(_bstr_t CommandText, VARIANT * RecordsAffected, long Options)
			其中
			CommandText  是命令字串，通常是SQL命令。
			RecordsAffected  是操作完成后所影响的行数,
			Options    表示CommandText中内容的类型，Options可以取如下值之一：
			adCmdText : 表明CommandText是文本命令
			adCmdTable : 表明CommandText是一个表名
			adCmdProc : 表明CommandText是一个存储过程
			adCmdUnknown : 未知

			Execute执行完后返回一个指向记录集的指针*/
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);//取得第1列的值
		m_SGSumMean = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在90~100的人数
		//执行SQL统计命令得到包含记录条数的记录集
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=90"), m_strSGSumGrade, m_strSGSumTerm, m_strSGSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);//取得第1列的值
		m_SGSumNum1 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在80~89的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=80 and 成绩<90"), m_strSGSumGrade, m_strSGSumTerm, m_strSGSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SGSumNum2 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在70~79的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=70 and 成绩<80"), m_strSGSumGrade, m_strSGSumTerm, m_strSGSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SGSumNum3 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出分数在60~69的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 学期 ='%s' and 课程 ='%s' and 成绩 >=60 and 成绩<70"), m_strSGSumGrade, m_strSGSumTerm, m_strSGSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SGSumNum4 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();

		//求出不及格的人数
		strSQL.Format(_T("select count(*) from 成绩表 where 年级 ='%s' and 学期 ='%s' and 课程 ='%s' and 成绩 <60"), m_strSGSumGrade, m_strSGSumTerm, m_strSGSumCourse);
		pRecordset = m_pConnection->Execute(_bstr_t(strSQL), &RecordsAffected, adCmdText);
		vCount = pRecordset->GetCollect(vIndex);
		m_SGSumNum5 = (CString)vCount;
		pRecordset->Close();
		pRecordset.Release();
	}
	UpdateData(FALSE);
}


void CScoreGradeSumDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//通过年级添加学期
	m_SGSumTerm.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SGSumGrade.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			/*CString strGrade;*/
			m_SGSumGrade.GetLBText(SelectIndex, m_strSGSumGrade);
			CString str;
			str.Format(_T("select distinct 学期  from 成绩表 where  年级 ='%s'"), m_strSGSumGrade);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSGSumTermValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("学期");
					if (var.vt != VT_NULL)
						strSGSumTermValue = (LPCSTR)_bstr_t(var);
					m_SGSumTerm.AddString(strSGSumTermValue);
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


void CScoreGradeSumDlg::OnCbnSelchangeCombo6()
{
	// TODO: 在此添加控件通知处理程序代码
	//根据年级和学期来添加课程
	m_SGSumCourse.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SGSumTerm.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SGSumTerm.GetLBText(SelectIndex, m_strSGSumTerm);
			CString str;
			str.Format(_T("select distinct 课程  from 成绩表 where  年级 ='%s' and 学期 ='%s'"), m_strSGSumGrade, m_strSGSumTerm);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSGSumCourseValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("课程");
					if (var.vt != VT_NULL)
						strSGSumCourseValue = (LPCSTR)_bstr_t(var);
					m_SGSumCourse.AddString(strSGSumCourseValue);
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
