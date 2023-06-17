// CScoreAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFC1StudentManager.h"
#include "afxdialogex.h"
#include "CScoreAdd.h"
#include "CStudentScoreAdd.h"


// CScoreAdd 对话框

IMPLEMENT_DYNAMIC(CScoreAdd, CDialog)

CScoreAdd::CScoreAdd(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SCOREADD, pParent)
	, strGrade(_T(""))
	, strClass(_T(""))
	, strTerm(_T(""))
	, strCourse(_T(""))
{

}

CScoreAdd::~CScoreAdd()
{
}

void CScoreAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_scoreGrade);
	DDX_Control(pDX, IDC_COMBO3, m_scoreClass);
	DDX_Control(pDX, IDC_COMBO4, m_scoreTerm);
	DDX_Control(pDX, IDC_COMBO5, m_scoreCourse);
	DDX_CBString(pDX, IDC_COMBO2, strGrade);
	DDX_CBString(pDX, IDC_COMBO3, strClass);
	DDX_CBString(pDX, IDC_COMBO4, strTerm);
	DDX_CBString(pDX, IDC_COMBO5, strCourse);
	DDX_Control(pDX, IDC_LIST2, m_scoreList);
}


BEGIN_MESSAGE_MAP(CScoreAdd, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CScoreAdd::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CScoreAdd::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CScoreAdd::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScoreAdd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CScoreAdd::OnBnClickedButton3)
END_MESSAGE_MAP()


// CScoreAdd 消息处理程序
BOOL CScoreAdd::OnInitDialog() {
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//这里实现的是初始化年级、班级、学期和课程的值
	//UpdateData(FALSE);
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionTimeout = 20;
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	//select distinct 年级  from 班级信息表  语法：SELECT DISTINCT 列名称 FROM 表名称
	//从班级信息表的年级这一列中返回所有不同的值
	try
	{
		hr = pRecordset->Open("select distinct 年级  from 班级信息表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			m_scoreGrade.ResetContent();//	从组合框的列表框和编辑控件中移除所有项
			_variant_t var;
			CString strGradeValue;
			CString strClassValue;
			while (!pRecordset->adoEOF)
			{
				//获取年级名称,年级组合框列表初始化
				var = pRecordset->GetCollect("年级");//用于取得年级字段的值
				if (var.vt != VT_NULL)
					strGradeValue = (LPCSTR)_bstr_t(var);//_bstr_t是C++对BSTR的封装。LPCTSTR是 const char*
				m_scoreGrade.AddString(strGradeValue);//将字符串添加到组合框的列表框中列表的末尾
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
	m_scoreList.InsertColumn(0, _T("序号"), 0, 40, -1);//在列表控件中插入列
	m_scoreList.InsertColumn(1, _T("学号"), 0, 80, -1);
	m_scoreList.InsertColumn(2, _T("姓名"), 0, 80, -1);
	m_scoreList.InsertColumn(3, _T("年级"), 0, 60, -1);
	m_scoreList.InsertColumn(4, _T("班级"), 0, 60, -1);
	m_scoreList.InsertColumn(5, _T("学期"), 0, 80, -1);
	m_scoreList.InsertColumn(6, _T("课程"), 0, 70, -1);
	m_scoreList.InsertColumn(7, _T("成绩"), 0, 60, -1);
	//设置List的行被选中时全行选中
	m_scoreList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置列表视图控件扩展样式
	CoInitialize(NULL);//需要在线程上初始化 COM 库，以获取指向标准分配器和内存分配函数的指针。
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
 }

void CScoreAdd::OnOK() {
	UpdateData(TRUE);
	CDialog::OnOK();
 }
void CScoreAdd::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取班级
	UpdateData(TRUE);//从控件获取数据到变量中
	m_scoreClass.ResetContent();  //	从组合框的列表框和编辑控件中移除所有项
	//获取combox的值
	int SelectIndex = m_scoreGrade.GetCurSel();   //检索组合框的列表框中当前所选项（如果有）的索引
	if (SelectIndex < 0)
		return;
	else
	{
		HRESULT hr;
		try
		{
			/*CString strGrade;*/
			m_scoreGrade.GetLBText(SelectIndex, strGrade);//获取组合框列表中的字符串
			CString str;
			str.Format(_T("select 班级名称  from 班级信息表 where  年级 ='%s'"), strGrade);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strClassValue;
				while (!pRecordset->adoEOF)
				{
					//获取班级名称
					var = pRecordset->GetCollect("班级名称");//用于取得班级名称字段的值
					if (var.vt != VT_NULL)
						strClassValue = (LPCSTR)_bstr_t(var);//_bstr_t是C++对BSTR的封装。LPCTSTR是 const char*
					m_scoreClass.AddString(strClassValue);//将字符串添加到组合框的列表框中列表的末尾
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


void CScoreAdd::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加学期
	UpdateData(TRUE);
	int SelectIndex = m_scoreClass.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{
		m_scoreClass.GetLBText(SelectIndex, strClass);//获取组合框列表中的字符串
		m_scoreTerm.ResetContent();
		m_scoreTerm.AddString(_T("第一学期"));
		m_scoreTerm.AddString(_T("第二学期"));
		m_scoreTerm.AddString(_T("第三学期"));
		m_scoreTerm.AddString(_T("第四学期"));
		m_scoreTerm.AddString(_T("第五学期"));
		m_scoreTerm.AddString(_T("第六学期"));
		m_scoreTerm.AddString(_T("第七学期"));
		m_scoreTerm.AddString(_T("第八学期"));
	}
}


void CScoreAdd::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加课程
	UpdateData(TRUE);

	//获取combox的值
	int SelectIndex = m_scoreTerm.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{

		HRESULT hr;
		try
		{
			/*CString strGrade;*/
			m_scoreTerm.GetLBText(SelectIndex, strTerm);//获取组合框列表中的字符串
			CString str;
			str.Format(_T("select 课程  from 学期表 where  年级 ='%s' And 班级 ='%s' And  学期 ='%s'"), strGrade, strClass, strTerm);
			_RecordsetPtr pRecordset;
			pRecordset.CreateInstance(__uuidof(Recordset));
			hr = pRecordset->Open(_variant_t(str), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				_variant_t var;
				CString strCourseValue;
				int count = pRecordset->RecordCount;//返回在 Recordset 对象中访问的记录数
				if (count < 1)
				{
					m_scoreCourse.ResetContent();  //清除以前的记录
					CString strMSBox;
					strMSBox.Format(_T("%s班在%s年%s没有相应的课程要考试！"), strClass, strGrade, strTerm);
					AfxMessageBox(strMSBox);
					pRecordset->Close();
					pRecordset = NULL;
					return;
				}
				else
				{
					m_scoreCourse.ResetContent();  //清除以前的记录
					while (!pRecordset->adoEOF)
					{
						//获取班级名称
						var = pRecordset->GetCollect("课程");
						if (var.vt != VT_NULL)
							strCourseValue = (LPCSTR)_bstr_t(var);
						m_scoreCourse.AddString(strCourseValue);
						pRecordset->MoveNext();
					}
				}
				pRecordset->Close();
				pRecordset = NULL;
			}
		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
			return;
		}
	}
}


void CScoreAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//显示记录
	//	添加需要录入成绩的学生姓名、课程
	UpdateData(TRUE);

	//获取combox的值
	int SelectIndex = m_scoreCourse.GetCurSel();   //获取当前值的索引号
	if (SelectIndex < 0)
		return;
	else
	{
		//获取课程
		m_scoreCourse.GetLBText(SelectIndex, strCourse);
		HRESULT hr;
		//定义记录集指针
		_RecordsetPtr pRentRecordset;
		//实例化记录集指针
		pRentRecordset.CreateInstance(__uuidof(Recordset));

		//定义字符串存储SQL语句
		CString strSql;
		//定义_variant变量存储从数据库读取的字段
		_variant_t var;
		//定义字符串存储_variant_t变量中的字符串
		CString strValue;
		//List控件中记录的序号
		int curItem = 0;
		//初始化SQL语句字符串,获得配送数据库表中的
		strSql.Format(_T("select 姓名,学号 from 学生信息表 where 年级 ='%s' and 班级 ='%s'"), strGrade, strClass);
		try
		{
			//利用Open函数执行SQL命令,获得查询结果记录集
			//需要把CString类型转换为_variant_t类型
			hr = pRentRecordset->Open(_variant_t(strSql), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				//List清空
				m_scoreList.DeleteAllItems();  //清除所有的记录
				//判断记录集是否到末尾,对每条记录,把字段值插入List控件的每一行
				while (!pRentRecordset->adoEOF)
				{

					//插入该字符串值到List中
					int num = curItem + 1;
					strValue.Format(_T("%d"), num);
					m_scoreList.InsertItem(curItem, strValue);
					//获得记录集当前记录的"编号"字段的值
					var = pRentRecordset->GetCollect(_T("学号"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_scoreList.SetItemText(curItem, 1, strValue);

					var = pRentRecordset->GetCollect(_T("姓名"));
					if (var.vt != VT_NULL)
						strValue = (LPCSTR)_bstr_t(var);
					m_scoreList.SetItemText(curItem, 2, strValue);

					m_scoreList.SetItemText(curItem, 3, strGrade);
					m_scoreList.SetItemText(curItem, 4, strClass);
					m_scoreList.SetItemText(curItem, 5, strTerm);
					m_scoreList.SetItemText(curItem, 6, strCourse);

					//移动当前记录到下一条记录
					pRentRecordset->MoveNext();
					curItem++;
				}
			}
		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
			return;
		}
		pRentRecordset->Close();
		pRentRecordset = NULL;
	}
}


void CScoreAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
   //录入保存、修改
	//弹出添加个人成绩窗口
	UpdateData(TRUE);
	CStudentScoreAdd StudentScoreAdd;
	int SelectIndex = m_scoreList.GetSelectionMark();  //获取当前选中记录的索引号
	if (SelectIndex < 0)
		return;
	else
	{
		StudentScoreAdd.m_StudentNum = m_scoreList.GetItemText(SelectIndex, 1);
		StudentScoreAdd.m_StudentName = m_scoreList.GetItemText(SelectIndex, 2);
		StudentScoreAdd.m_StudentGrade = m_scoreList.GetItemText(SelectIndex, 3);
		StudentScoreAdd.m_StudentClass = m_scoreList.GetItemText(SelectIndex, 4);
		StudentScoreAdd.m_StudentTerm = m_scoreList.GetItemText(SelectIndex, 5);
		StudentScoreAdd.m_StudentCourse = m_scoreList.GetItemText(SelectIndex, 6);
		StudentScoreAdd.ScoreAddDlg = this;     //把当前的CScoreAdd类赋给CStudentScoreAdd类对象
		//中ScoreAddDlg这个成员变量，使得在CStudentScoreAdd类中能够调用CScoreAdd类的成员。

		StudentScoreAdd.m_StudentIndex = SelectIndex;
		StudentScoreAdd.DoModal();
	}
}

void CScoreAdd::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//把添加的学生成绩及个人相关信息添加到学生信息管理系统的成绩表中
	UpdateData(TRUE);
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionTimeout = 20;
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=学生信息管理系统.mdb", "", "", adConnectUnspecified);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	HRESULT hr;
	try
	{
		hr = pRecordset->Open("select * from 成绩表", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		if (SUCCEEDED(hr))
		{
			int recordCount = m_scoreList.GetItemCount();
			if (recordCount > 0)
			{
				for (int i = 0; i < recordCount; i++)
				{
					pRecordset->AddNew();
					pRecordset->PutCollect("学号", _variant_t(m_scoreList.GetItemText(i, 1)));
					pRecordset->PutCollect("姓名", _variant_t(m_scoreList.GetItemText(i, 2)));
					pRecordset->PutCollect("年级", _variant_t(m_scoreList.GetItemText(i, 3)));
					pRecordset->PutCollect("班级", _variant_t(m_scoreList.GetItemText(i, 4)));
					pRecordset->PutCollect("学期", _variant_t(m_scoreList.GetItemText(i, 5)));
					pRecordset->PutCollect("课程", _variant_t(m_scoreList.GetItemText(i, 6)));
					pRecordset->PutCollect("成绩", _variant_t(m_scoreList.GetItemText(i, 7)));
				}
				pRecordset->Update();
				AfxMessageBox(_T("保存成绩成功！"));
			}
		}
	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return;
	}
}
