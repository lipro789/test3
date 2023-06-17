// CScoreOrder.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CScoreOrder.h"


// CScoreOrder 对话框

IMPLEMENT_DYNAMIC(CScoreOrder, CDialog)

CScoreOrder::CScoreOrder(CWnd* pParent /*=nullptr*/)
	: CDialog(ID_SCOREQUEUE, pParent)
	, m_strSOGrade(_T(""))
	, m_strSOClass(_T(""))
	, m_strSOTerm(_T(""))
	, m_strSOCourse(_T(""))
{

}

CScoreOrder::~CScoreOrder()
{
}

void CScoreOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SOGrade);
	DDX_Control(pDX, IDC_COMBO2, m_SOClass);
	DDX_Control(pDX, IDC_COMBO4, m_SOTerm);
	DDX_Control(pDX, IDC_COMBO3, m_SOCourse);
	DDX_CBString(pDX, IDC_COMBO1, m_strSOGrade);
	DDX_CBString(pDX, IDC_COMBO2, m_strSOClass);
	DDX_CBString(pDX, IDC_COMBO4, m_strSOTerm);
	DDX_CBString(pDX, IDC_COMBO3, m_strSOCourse);
	DDX_Control(pDX, IDC_LIST3, m_SOList);
}


BEGIN_MESSAGE_MAP(CScoreOrder, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScoreOrder::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CScoreOrder::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CScoreOrder::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreOrder::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScoreOrder::OnBnClickedButton2)
END_MESSAGE_MAP()


// CScoreOrder 消息处理程序
BOOL CScoreOrder::OnInitDialog() {
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	//添加年级并初始化List控件
	//这里实现的是初始化年级、班级、学期和课程的值
	//UpdateData(FALSE);
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
			m_SOGrade.ResetContent();
			_variant_t var;
			CString strSOGradeValue;
			while (!pRecordset->adoEOF)
			{
				//获取年级名称
				var = pRecordset->GetCollect("年级");
				if (var.vt != VT_NULL)
					strSOGradeValue = (LPCSTR)_bstr_t(var);
				m_SOGrade.AddString(strSOGradeValue);
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
	m_SOList.InsertColumn(0, _T("序号"), 0, 40, -1);
	m_SOList.InsertColumn(1, _T("学号"), 0, 80, -1);
	m_SOList.InsertColumn(2, _T("姓名"), 0, 80, -1);
	m_SOList.InsertColumn(3, _T("年级"), 0, 60, -1);
	m_SOList.InsertColumn(4, _T("班级"), 0, 60, -1);
	m_SOList.InsertColumn(5, _T("学期"), 0, 80, -1);
	m_SOList.InsertColumn(6, _T("课程"), 0, 70, -1);
	m_SOList.InsertColumn(7, _T("成绩"), 0, 60, -1);
	//设置List的行被选中时全行选中
	m_SOList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CoInitialize(NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CScoreOrder::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加班级
	UpdateData(TRUE);
	m_SOClass.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SOGrade.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SOGrade.GetLBText(SelectIndex, m_strSOGrade);
			CString str;
			str.Format(_T("select distinct 班级 from 成绩表 where  年级 ='%s'"), m_strSOGrade);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSOClassValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("班级");
					if (var.vt != VT_NULL)
						strSOClassValue = (LPCSTR)_bstr_t(var);
					m_SOClass.AddString(strSOClassValue);
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


void CScoreOrder::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加学期
	m_SOTerm.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SOClass.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SOClass.GetLBText(SelectIndex, m_strSOClass);
			CString str;
			str.Format(_T("select distinct 学期  from 成绩表 where  年级 ='%s' and 班级 ='%s'"), m_strSOGrade, m_strSOClass);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSOTermValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("学期");
					if (var.vt != VT_NULL)
						strSOTermValue = (LPCSTR)_bstr_t(var);
					m_SOTerm.AddString(strSOTermValue);
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


void CScoreOrder::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加课程
	m_SOCourse.ResetContent();  //清除以前的记录
	//获取combox的值
	int SelectIndex = m_SOTerm.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SOTerm.GetLBText(SelectIndex, m_strSOTerm);
			CString str;
			str.Format(_T("select distinct 课程  from 成绩表 where  年级 ='%s' and 班级 ='%s' and 学期 ='%s'"), m_strSOGrade, m_strSOClass, m_strSOTerm);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSOCourseValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("课程");
					if (var.vt != VT_NULL)
						strSOCourseValue = (LPCSTR)_bstr_t(var);
					m_SOCourse.AddString(strSOCourseValue);
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


void CScoreOrder::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//对班级的成绩进行排序
	//根据条件对成绩进行排序，并把结果显示在List中
	int SelectIndex = m_SOCourse.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{
		HRESULT hr;
		try
		{
			m_SOCourse.GetLBText(SelectIndex, m_strSOCourse);
			CString str;
			str.Format(_T("select *  from 成绩表 where  年级 ='%s' and 班级 ='%s' and 学期 ='%s' and 课程 ='%s' order by 成绩 desc"), m_strSOGrade, m_strSOClass, m_strSOTerm, m_strSOCourse);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSOValue;
				int nItem = 0;   //用来存储记录个数
				m_SOList.DeleteAllItems();  //清除所有的记录
				while (!pRecordset->adoEOF)
				{
					//插入该字符串值到List中
					//添加序号
					int num = nItem + 1;
					strSOValue.Format(_T("%d"), num);
					m_SOList.InsertItem(nItem, strSOValue);
					//获得记录集当前记录的"学号"字段的值
					var = pRecordset->GetCollect(_T("学号"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 1, strSOValue);
					//获得记录集当前记录的"姓名"字段的值
					var = pRecordset->GetCollect(_T("姓名"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 2, strSOValue);
					//获得记录集当前记录的"年级"字段的值
					var = pRecordset->GetCollect(_T("年级"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 3, strSOValue);
					//获得记录集当前记录的"班级"字段的值
					var = pRecordset->GetCollect(_T("班级"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 4, strSOValue);
					//获得记录集当前记录的"学期"字段的值
					var = pRecordset->GetCollect(_T("学期"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 5, strSOValue);
					//获得记录集当前记录的"课程"字段的值
					var = pRecordset->GetCollect(_T("课程"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 6, strSOValue);
					//获得记录集当前记录的"成绩"字段的值
					var = pRecordset->GetCollect(_T("成绩"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 7, strSOValue);

					//移动当前记录到下一条记录
					pRecordset->MoveNext();
					nItem++;
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


void CScoreOrder::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//对年级的成绩进行排序
	//根据条件对成绩进行排序，并把结果显示在List中
	int SelectIndex = m_SOCourse.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			m_SOCourse.GetLBText(SelectIndex, m_strSOCourse);
			CString str;
			str.Format(_T("select *  from 成绩表 where  年级 ='%s' and 学期 ='%s' and 课程 ='%s' order by 成绩 desc"), m_strSOGrade, m_strSOTerm, m_strSOCourse);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strSOValue;
				int nItem = 0;   //用来存储记录个数
				m_SOList.DeleteAllItems();  //清除所有的记录
				while (!pRecordset->adoEOF)
				{
					//插入该字符串值到List中
					//添加序号
					int num = nItem + 1;
					strSOValue.Format(_T("%d"), num);
					m_SOList.InsertItem(nItem, strSOValue);
					//获得记录集当前记录的"学号"字段的值
					var = pRecordset->GetCollect(_T("学号"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 1, strSOValue);
					//获得记录集当前记录的"姓名"字段的值
					var = pRecordset->GetCollect(_T("姓名"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 2, strSOValue);
					//获得记录集当前记录的"年级"字段的值
					var = pRecordset->GetCollect(_T("年级"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 3, strSOValue);
					//获得记录集当前记录的"班级"字段的值
					var = pRecordset->GetCollect(_T("班级"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 4, strSOValue);
					//获得记录集当前记录的"学期"字段的值
					var = pRecordset->GetCollect(_T("学期"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 5, strSOValue);
					//获得记录集当前记录的"课程"字段的值
					var = pRecordset->GetCollect(_T("课程"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 6, strSOValue);
					//获得记录集当前记录的"成绩"字段的值
					var = pRecordset->GetCollect(_T("成绩"));
					if (var.vt != VT_NULL)
						strSOValue = (LPCSTR)_bstr_t(var);
					m_SOList.SetItemText(nItem, 7, strSOValue);

					//移动当前记录到下一条记录
					pRecordset->MoveNext();
					nItem++;
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
