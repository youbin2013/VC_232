// 232_VCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "232_VC.h"
#include "232_VCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//定义一个返回值结构体
RETURN_VALUE Return_Value;
//定义COM口返回值
int Index_M;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy232_VCDlg dialog

CMy232_VCDlg::CMy232_VCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy232_VCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy232_VCDlg)
	m_strRXData = _T("");
	m_strTXData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy232_VCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy232_VCDlg)
	DDX_Control(pDX, IDC_COMBO_ParityCheck, m_ParityCheck_M);
	DDX_Control(pDX, IDC_COMBO_StopBit, m_StopBit_M);
	DDX_Control(pDX, IDC_COMBO_Date_Select, m_Date_Select_M);
	DDX_Control(pDX, IDC_COMBO_BaudRate_Select, m_BaudRate_M);
	DDX_Control(pDX, IDC_COMBO_CommSelect, m_ComboBox);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy232_VCDlg, CDialog)
	//{{AFX_MSG_MAP(CMy232_VCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, OnButtonManualsend)
	ON_CBN_SELCHANGE(IDC_COMBO_BaudRate_Select, OnSelchangeCOMBOBaudRateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_Date_Select, OnSelchangeCOMBODateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_StopBit, OnSelchangeCOMBOStopBit)
	ON_CBN_SELCHANGE(IDC_COMBO_ParityCheck, OnSelchangeCOMBOParityCheck)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy232_VCDlg message handlers

BOOL CMy232_VCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//设置默认串口控件显示值
	m_ComboBox.SetCurSel(0);
	m_BaudRate_M.SetCurSel(0);
	m_Date_Select_M.SetCurSel(0);
	m_StopBit_M.SetCurSel(0);
	m_ParityCheck_M.SetCurSel(0);
	//获取系统有效COM口到COM口控件
	/**********************************************************/
	ShowComm();
	/*********************************************************/

/*	if(m_ctrlComm.GetPortOpen())//判断串口是否打开，打开则先关闭
	{
		m_ctrlComm.SetPortOpen(FALSE);//关闭串口
	}
	m_ctrlComm.SetCommPort(7);//设置默认COM口为7
	if(!m_ctrlComm.GetPortOpen())//判断串口是否打开，没打开则打开
	{
		m_ctrlComm.SetPortOpen(TRUE);
	}
	else
	{
		AfxMessageBox("CAN NOT OPEN PORT!");
	}
	m_ctrlComm.SetSettings("115200,n,8,1");//打开软件时端口设置默认波特率为115200，无校验位，8位数据，1位停止位
	m_ctrlComm.SetInputMode(1);//1：表示二进制方式读取数据
	m_ctrlComm.SetRThreshold(1);//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的ONCOMM事件
	m_ctrlComm.SetInputLen(0);//设置当前接收区数据长度为0
	m_ctrlComm.GetInput();//先预读缓存区以清除残留数据
*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy232_VCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy232_VCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy232_VCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CMy232_VCDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMy232_VCDlg)
	ON_EVENT(CMy232_VCDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/********************************************************************/
//--------------------串口接收函数-----------------------------
void CMy232_VCDlg::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;//定义一个VARIANT类对象
	LONG len,k;
	BYTE rxdata[2048];//设置一个BYTE数组接收数据
	CString strtemp;//定义一个临时变量
	if(m_ctrlComm.GetCommEvent() == 2)
	{
		variant_inp = m_ctrlComm.GetInput();//读缓存区
		len = variant_inp.parray->rgsabound->cElements;//获取数据长度
		memcpy(rxdata,(char*)variant_inp.parray->pvData,len);//把接收数据拷贝到BYTE数组
	}
	for(k = 0;k < len;k++)
	{
		BYTE bt = *(char*)(rxdata + k);
	//	if(m_ctrHexSend.GetCheck())
	//		strtemp.Format("%02x",bt);
	//	else
		strtemp.Format("%c",bt);//将字符串送入临时变量strtemp存放
		m_strRXData += strtemp;//加入接收编辑框对应字符串
	}
	UpdateData(FALSE);
}

/********************************************************************/
//--------------------串口发送函数-----------------------------
void CMy232_VCDlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//读取编辑框中的内容
	m_ctrlComm.SetOutput(COleVariant(m_strTXData));//发送数据
}


/*******************************************************************/
//----------------串口波特率控件改变控制函数-----------------------
void CMy232_VCDlg::OnSelchangeCOMBOBaudRateSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	Return_Value.m_BaudRate = ((CComboBox *)GetDlgItem(IDC_COMBO_BaudRate_Select))->GetCurSel();//当前选中的行
	//根据当前选中的值进行波特率设置
	switch(Return_Value.m_BaudRate)
	{
	case 1:
		m_ctrlComm.SetSettings("14400,,,");
		break;
	case 2:
		m_ctrlComm.SetSettings("19200,,,");
		break;
	case 3:
		m_ctrlComm.SetSettings("38400,,,");
		break;
	case 4:
		m_ctrlComm.SetSettings("56000,,,");
		break;
	case 5:
		m_ctrlComm.SetSettings("115200,,,");
		break;
	case 6:
		m_ctrlComm.SetSettings("230400,,,");
		break;
	default:
		m_ctrlComm.SetSettings("115200,,,");
		break;
	}
	UpdateData(FALSE);
}

/*******************************************************************/
//----------------串口数据位控件改变控制函数-----------------------
void CMy232_VCDlg::OnSelchangeCOMBODateSelect() 
{
	// TODO: Add your control notification handler code here
	Return_Value.m_Date_Select = ((CComboBox*)GetDlgItem(IDC_COMBO_Date_Select))->GetCurSel();//当前选中的行
	//根据当前选中的值进行数据位设置
	switch(Return_Value.m_Date_Select)
	{
	case 1:
		m_ctrlComm.SetSettings(",,7,");
		break;
	case 2:
		m_ctrlComm.SetSettings(",,6,");
		break;
	case 3:
		m_ctrlComm.SetSettings(",,5,");
		break;
	case 4:
		m_ctrlComm.SetSettings(",,4,");
		break;
	default:
		m_ctrlComm.SetSettings(",,8,");
		break;
	}
	UpdateData(FALSE);
}


/*******************************************************************/
//----------------串口停止位控件改变控制函数-----------------------
void CMy232_VCDlg::OnSelchangeCOMBOStopBit() 
{
	// TODO: Add your control notification handler code here
	Return_Value.m_StopBit = ((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->GetCurSel();//当前选中行
	//根据当前选中的值进行停止位设置
	switch(Return_Value.m_StopBit)
	{
	case 1:
		m_ctrlComm.SetSettings(",,,2");
		break;
	default:
		m_ctrlComm.SetSettings(",,,1");
		break;
	}
	UpdateData(FALSE);
}


/*******************************************************************/
//----------------串口校验位控件改变控制函数-----------------------
void CMy232_VCDlg::OnSelchangeCOMBOParityCheck() 
{
	// TODO: Add your control notification handler code here
	Return_Value.m_ParityCheck = ((CComboBox*)GetDlgItem(IDC_COMBO_ParityCheck))->GetCurSel();//当前选中行
	//根据当前选中的值进行校验位设置
	switch(Return_Value.m_ParityCheck)
	{
	case 1:
		m_ctrlComm.SetSettings(",O,,");
		break;
	case 2:
		m_ctrlComm.SetSettings(",E,,");
		break;
	default:
		m_ctrlComm.SetSettings(",N,,");
		break;
	}
	UpdateData(FALSE);
}


/*******************************************************************/
//----------------读注册表获取系统COM口函数-----------------------
void CMy232_VCDlg::ShowComm()
{
	long  lReg; 
	HKEY  hKey; 
	DWORD  MaxValueLength; 
	DWORD  dwValueNumber; 

	lReg=RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_QUERY_VALUE, &hKey); 
	if(lReg!=ERROR_SUCCESS) 
	{ 
		AfxMessageBox("Open Registry Error!\n"); 
		 return; 
	} 

	lReg=RegQueryInfoKeyA(hKey, 
	  NULL, 
	  NULL, 
	  NULL, 
	  NULL, 
	  NULL, 
	  NULL, 
	  &dwValueNumber, //返回和hKey关联的值 
	  &MaxValueLength, 
	  NULL, 
	  NULL, 
	  NULL); 
	if(lReg!=ERROR_SUCCESS) //没有成功 
	{ 
		 AfxMessageBox("Getting  Info  Error!\n"); 
		return; 
	} 

	LPSTR  pValueName,pCOMNumber; 
	DWORD  cchValueName,dwValueSize=6; 

	for(DWORD  i=0;i < dwValueNumber;i++) 
	{ 
		  cchValueName=MaxValueLength+1; 
		  dwValueSize=6; 
		  pValueName=(LPSTR)VirtualAlloc(NULL,cchValueName,MEM_COMMIT,PAGE_READWRITE); 
		  lReg=RegEnumValueA(hKey, 
		   i, 
		   pValueName, 
		   &cchValueName, 
		   NULL, 
		   NULL, 
		   NULL, 
		   NULL); 
  
		  if((lReg!=ERROR_SUCCESS)&&(lReg!=ERROR_NO_MORE_ITEMS)) 
		  { 
			 AfxMessageBox("Enum  Registry  Error or No More Items!\n"); 
			 continue; 
		  } 
  
		  pCOMNumber=(LPSTR)VirtualAlloc(NULL,6,MEM_COMMIT,PAGE_READWRITE); 
		  lReg=RegQueryValueExA(hKey, 
		   pValueName, 
		   NULL, 
		   NULL, 
		   (LPBYTE)pCOMNumber, 
		   &dwValueSize); 
  
		  if(lReg!=ERROR_SUCCESS) 
		  { 
			 AfxMessageBox("Can not get the name of the port"); 
			 continue; 
		  } 
		  CString strCommList(pCOMNumber);
		 // AfxMessageBox(pCOMNumber);
		 //  CharToUnicode(pCOMNumber,&strCommList);
		//m_ctlPort.AddString(strCommList);
		 BOOL m_bInsert=0;
  
	  if(((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCount()==0)
			((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->AddString(strCommList);
	  else
	  {
	   CString strTemp=strCommList;
	   strCommList.TrimLeft("COM");
	   for(int icurrent=0;icurrent<((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCount();icurrent++)
	   {
		CString strCurrent;
		((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetLBText(icurrent,strCurrent);
		strCurrent.TrimLeft("COM");
		if(_ttol(strCurrent)>_ttol(strCommList))
		{
		 ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->InsertString(icurrent,strTemp);
		 m_bInsert = 1;
		 break;
		}
	   }
	   if(!m_bInsert)
		((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->InsertString(icurrent,strTemp);
	  }
  
	  VirtualFree(pValueName,0,MEM_RELEASE); 
	  VirtualFree(pCOMNumber,0,MEM_RELEASE); 
	} 
}

/*******************************************************************/
//---------------------------打开关闭串口函数-----------------------
void CMy232_VCDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	//检查是否改变默认的串口值，没有改变Return_Value.m_Index的值是0，否则不为0
	switch(m_ctrlComm.GetPortOpen())//0表示没有打开串口，所以进行打开串口操作，1表示打开了串口，所以进行关闭串口操作
	{
		case 1:
			m_ctrlComm.SetPortOpen(FALSE);//关闭串口
			SetDlgItemText(IDC_BUTTON_START,"打开串口");//更改按键指示
			UpdateData(FALSE);
			break;
		case 0:
			Index_M = ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();//获取当前行
			m_ctrlComm.SetCommPort(Index_M + 1);//设置当前行为COM口
			m_ctrlComm.SetPortOpen(TRUE);//打开串口
			SetDlgItemText(IDC_BUTTON_START,"关闭串口");//更改按键指示
			UpdateData(FALSE);
			m_ctrlComm.SetSettings("115200,n,8,1");//打开软件时端口设置默认波特率为115200，无校验位，8位数据，1位停止位
			m_ctrlComm.SetInputMode(1);//1：表示二进制方式读取数据
			m_ctrlComm.SetRThreshold(1);//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的ONCOMM事件
			m_ctrlComm.SetInputLen(0);//设置当前接收区数据长度为0
			m_ctrlComm.GetInput();//先预读缓存区以清除残留数据
			break;
		default:
			AfxMessageBox("CAN NOT OPEN OR CLOSE PORT!");
			break;
	}
}

void CMy232_VCDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(nType == 1)
		return;
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_RXDATA);
	ChangeSize(pWnd,cx,cy);
	pWnd = GetDlgItem(IDC_EDIT_TXDATA);
	ChangeSize(pWnd,cx,cy);
	GetClientRect(&m_rect);
}

void CMy232_VCDlg::ChangeSize(CWnd *pWnd, int cx, int cy)
{
	if(pWnd)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.left = rect.left * cx / m_rect.Width();
		rect.right = rect.right * cx / m_rect.Width();
		rect.top = rect.top * cy / m_rect.Height();
		rect.bottom = rect.bottom * cy / m_rect.Height();
		pWnd->MoveWindow(rect);
	}
}
