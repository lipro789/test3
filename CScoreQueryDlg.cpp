// CScoreQueryDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CScoreQueryDlg.h"


// CScoreQueryDlg 对话框

IMPLEMENT_DYNAMIC(CScoreQueryDlg, CDialog)

CScoreQueryDlg::CScoreQueryDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SCOREQUERY, pParent)
	, m_SQName(_T(""))
	, m_SQNo(_T(""))
	, strSQGrade(_T(""))
	, strSQClass(_T(""))
	, strSQTerm(_T(""))
	, strSQCourse(_T(""))
{

}

CScoreQueryDlg::~CScoreQueryDlg()
{
}

void CScoreQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SQGrade);
	DDX_Control(pDX, IDC_COMBO2, m_SQClass);
	DDX_Control(pDX, IDC_COMBO4, m_SQTerm);
	DDX_Control(pDX, IDC_COMBO3, m_SQCourse);
	DDX_Text(pDX, IDC_EDIT1, m_SQName);
	DDX_Text(pDX, IDC_EDIT2, m_SQNo);
	DDX_CBString(pDX, IDC_COMBO1, strSQGrade);
	DDX_CBString(pDX, IDC_COMBO2, strSQClass);
	DDX_CBString(pDX, IDC_COMBO4, strSQTerm);
	DDX_CBString(pDX, IDC_COMBO3, strSQCourse);
	DDX_Control(pDX, IDC_LIST1, m_SQList);
}


BEGIN_MESSAGE_MAP(CScoreQueryDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScoreQueryDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CScoreQueryDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CScoreQueryDlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreQueryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CScoreQueryDlg 消息处理程序
BOOL CScoreQueryDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化年级和List控件内容
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
			m_SQGrade.ResetContent();
			_variant_t var;
			CString strSQGradeValue;
			while (!pRecordset->adoEOF)
			{
				//获取年级名称
				var = pRecordset->GetCollect("年级");
				if (var.vt != VT_NULL)
					strSQGradeValue = (LPCSTR)_bstr_t(var);
				m_SQGrade.AddString(strSQGradeValue);
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

	//名单表格显示的初始化
	m_SQList.InsertColumn(0, _T("学号"), 0, 80, -1);
	m_SQList.InsertColumn(1, _T("姓名"), 0, 80, -1);
	m_SQList.InsertColumn(2, _T("年级"), 0, 60, -1);
	m_SQList.InsertColumn(3, _T("班级"), 0, 60, -1);
	m_SQList.InsertColumn(4, _T("学期"), 0, 80, -1);
	m_SQList.InsertColumn(5, _T("课程"), 0, 70, -1);
	m_SQList.InsertColumn(6, _T("成绩"), 0, 60, -1);
	//设置List的行被选中时全行选中
	m_SQList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CoInitialize(NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CScoreQueryDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加班级
	UpdateData(TRUE);
	m_SQClass.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SQGrade.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SQGrade.GetLBText(SelectIndex, strSQGrade);
			CString str;
			str.Format(_T("select distinct 班级 from 成绩表 where  年级 ='%s'"), strSQGrade);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSQClassValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("班级");
					if (var.vt != VT_NULL)
						strSQClassValue = (LPCSTR)_bstr_t(var);
					m_SQClass.AddString(strSQClassValue);
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


void CScoreQueryDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加学期
	m_SQTerm.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SQClass.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SQClass.GetLBText(SelectIndex, strSQClass);
			CString str;
			str.Format(_T("select distinct 学期  from 成绩表 where  年级 ='%s' and 班级 ='%s'"), strSQGrade, strSQClass);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{

				CString strSQTermValue;
				m_SQTerm.AddString(_T(""));
				while (!pRecordset->adoEOF)
				{
					//获取学期名称
					_variant_t var;
					var = pRecordset->GetCollect("学期");
					if (var.vt != VT_NULL)
						strSQTermValue = (LPCSTR)_bstr_t(var);
					m_SQTerm.AddString(strSQTermValue);
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


void CScoreQueryDlg::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
		//添加课程
	m_SQCourse.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SQTerm.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SQTerm.GetLBText(SelectIndex, strSQTerm);
			CString str;
			str.Format(_T("select distinct 课程  from 成绩表 where  年级 ='%s' and 班级 ='%s' and 学期 ='%s'"), strSQGrade, strSQClass, strSQTerm);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSQCourseValue;
				m_SQCourse.AddString(_T(""));
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("课程");
					if (var.vt != VT_NULL)
						strSQCourseValue = (LPCSTR)_bstr_t(var);
					m_SQCourse.AddString(strSQCourseValue);
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


void CScoreQueryDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strSQL;  //查询条件
	//定义记录集
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	_variant_t var;
	CString strValue;   //用于暂时保存记录
	int nCount = 0;      //用于记录记录数
	int curItem = 0;     //List控件中记录的序号
	try
	{
		m_SQList.DeleteAllItems();   //清除所有的记录
		//姓名和学号同时为空
		if (m_SQName.IsEmpty() && m_SQNo.IsEmpty())
		{
			AfxMessageBox(_T("请输入姓名或者学号！"));
			return;
		}
		//姓名不为空，学号为空，或者姓名不为空和学号不为空
		if (((!m_SQName.IsEmpty()) && m_SQNo.IsEmpty()) || ((!m_SQName.IsEmpty()) && (!m_SQNo.IsEmpty())))
		{
			//年级、班级、学期、课程为空
			if (strSQGrade.IsEmpty())
			{
				strSQL.Format(_T("select * from 成绩表 where 姓名='%s'"), m_SQName);
			}
			//年级不为空
			else
			{
				if (strSQClass.IsEmpty())
				{
					strSQL.Format(_T("select * from 成绩表 where 姓名='%s'and 年级 = '%s'"), m_SQName, strSQGrade);
				}
				else
				{
					if (strSQTerm.IsEmpty() && strSQCourse.IsEmpty())
						strSQL.Format(_T("select * from 成绩表 where 姓名='%s' and 年级='%s' and 班级='%s'"), m_SQName, strSQGrade, strSQClass);
					else if (!strSQTerm.IsEmpty() && strSQCourse.IsEmpty())
						strSQL.Format(_T("select * from 成绩表 where 姓名='%s'and 年级='%s'and 班级='%s'and 学期='%s'"), m_SQName, strSQGrade, strSQClass, strSQTerm);
					else if (strSQTerm.IsEmpty() && !strSQCourse.IsEmpty())
						strSQL.Format(_T("select * from 成绩表 where 姓名='%s'and 年级='%s'and 班级='%s'and 课程='%s'"), m_SQName, strSQGrade, strSQClass, strSQCourse);
					else if ((!strSQTerm.IsEmpty()) && (!strSQCourse.IsEmpty()))
						strSQL.Format(_T("select * from 成绩表 where 姓名='%s'and 年级='%s'and 班级='%s'and 课程='%s'and 学期='%s'"), m_SQName, strSQGrade, strSQClass, strSQCourse, strSQTerm);
				}
			}
		}
		//姓名为空，学号不为空
		if (m_SQName.IsEmpty() && (!m_SQNo.IsEmpty()))
		{
			//年级、班级、学期、课程为空
			if (strSQGrade.IsEmpty())
			{
				strSQL.Format(_T("select * from 成绩表 where 学号='%s'"), m_SQNo);
			}
			//年级不为空
			else
			{
				if (strSQClass.IsEmpty())
				{
					strSQL.Format(_T("select * from 成绩表 where 学号='%s'and 年级 = '%s'"), m_SQNo, strSQGrade);
				}
				else
				{
					if (strSQTerm.IsEmpty() && strSQCourse.IsEmpty())
						strSQL.Format(_T("select * from 成绩表 where 学号='%s' and 年级='%s' and 班级='%s'"), m_SQNo, strSQGrade, strSQClass);
					else if (!strSQTerm.IsEmpty() && strSQCourse.IsEmpty())
						strSQL.Format(_T("select * from 成绩表 where 学号='%s'and 年级='%s'and 班级='%s'and 学期='%s'"), m_SQNo, strSQGrade, strSQClass, strSQTerm);
					else if (strSQTerm.IsEmpty() && !strSQCourse.IsEmpty())
						strSQL.Format(_T("select * from 成绩表 where 学号='%s'and 年级='%s'and 班级='%s'and 课程='%s'"), m_SQNo, strSQGrade, strSQClass, strSQCourse);
					else if ((!strSQTerm.IsEmpty()) && (!strSQCourse.IsEmpty()))
						strSQL.Format(_T("select * from 成绩表 where 学号='%s'and 年级='%s'and 班级='%s'and 课程='%s'and 学期='%s'"), m_SQNo, strSQGrade, strSQClass, strSQCourse, strSQTerm);
				}
			}
		}
		hr = pRecordset->Open(_variant_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			nCount = pRecordset->RecordCount;
			if (nCount < 1)
			{
				AfxMessageBox(_T("没有符合条件的相关信息，请重新输入！"));
				return;
			}
			else
			{
				while (!pRecordset->adoEOF)
				{
					//插入学号
					var = pRecordset->GetCollect(_T("学号"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.InsertItem(curItem, strValue);
					//插入姓名
					var = pRecordset->GetCollect(_T("姓名"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.SetItemText(curItem, 1, strValue);
					//插入年级
					var = pRecordset->GetCollect(_T("年级"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.SetItemText(curItem, 2, strValue);
					//插入班级
					var = pRecordset->GetCollect(_T("班级"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.SetItemText(curItem, 3, strValue);
					//插入学期
					var = pRecordset->GetCollect(_T("学期"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.SetItemText(curItem, 4, strValue);
					//插入课程
					var = pRecordset->GetCollect(_T("课程"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.SetItemText(curItem, 5, strValue);
					//插入成绩
					var = pRecordset->GetCollect(_T("成绩"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_SQList.SetItemText(curItem, 6, strValue);
					pRecordset->MoveNext();
					curItem++;
				}
				pRecordset->Close();
				pRecordset = NULL;
			}
		}
	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return;
	}
}
