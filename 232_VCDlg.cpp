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

//����һ������ֵ�ṹ��
RETURN_VALUE Return_Value;
//����COM�ڷ���ֵ
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
	//����Ĭ�ϴ��ڿؼ���ʾֵ
	m_ComboBox.SetCurSel(0);
	m_BaudRate_M.SetCurSel(0);
	m_Date_Select_M.SetCurSel(0);
	m_StopBit_M.SetCurSel(0);
	m_ParityCheck_M.SetCurSel(0);
	//��ȡϵͳ��ЧCOM�ڵ�COM�ڿؼ�
	/**********************************************************/
	ShowComm();
	/*********************************************************/

/*	if(m_ctrlComm.GetPortOpen())//�жϴ����Ƿ�򿪣������ȹر�
	{
		m_ctrlComm.SetPortOpen(FALSE);//�رմ���
	}
	m_ctrlComm.SetCommPort(7);//����Ĭ��COM��Ϊ7
	if(!m_ctrlComm.GetPortOpen())//�жϴ����Ƿ�򿪣�û�����
	{
		m_ctrlComm.SetPortOpen(TRUE);
	}
	else
	{
		AfxMessageBox("CAN NOT OPEN PORT!");
	}
	m_ctrlComm.SetSettings("115200,n,8,1");//�����ʱ�˿�����Ĭ�ϲ�����Ϊ115200����У��λ��8λ���ݣ�1λֹͣλ
	m_ctrlComm.SetInputMode(1);//1����ʾ�����Ʒ�ʽ��ȡ����
	m_ctrlComm.SetRThreshold(1);//����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�ONCOMM�¼�
	m_ctrlComm.SetInputLen(0);//���õ�ǰ���������ݳ���Ϊ0
	m_ctrlComm.GetInput();//��Ԥ���������������������
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
//--------------------���ڽ��պ���-----------------------------
void CMy232_VCDlg::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;//����һ��VARIANT�����
	LONG len,k;
	BYTE rxdata[2048];//����һ��BYTE�����������
	CString strtemp;//����һ����ʱ����
	if(m_ctrlComm.GetCommEvent() == 2)
	{
		variant_inp = m_ctrlComm.GetInput();//��������
		len = variant_inp.parray->rgsabound->cElements;//��ȡ���ݳ���
		memcpy(rxdata,(char*)variant_inp.parray->pvData,len);//�ѽ������ݿ�����BYTE����
	}
	for(k = 0;k < len;k++)
	{
		BYTE bt = *(char*)(rxdata + k);
	//	if(m_ctrHexSend.GetCheck())
	//		strtemp.Format("%02x",bt);
	//	else
		strtemp.Format("%c",bt);//���ַ���������ʱ����strtemp���
		m_strRXData += strtemp;//������ձ༭���Ӧ�ַ���
	}
	UpdateData(FALSE);
}

/********************************************************************/
//--------------------���ڷ��ͺ���-----------------------------
void CMy232_VCDlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//��ȡ�༭���е�����
	m_ctrlComm.SetOutput(COleVariant(m_strTXData));//��������
}


/*******************************************************************/
//----------------���ڲ����ʿؼ��ı���ƺ���-----------------------
void CMy232_VCDlg::OnSelchangeCOMBOBaudRateSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	Return_Value.m_BaudRate = ((CComboBox *)GetDlgItem(IDC_COMBO_BaudRate_Select))->GetCurSel();//��ǰѡ�е���
	//���ݵ�ǰѡ�е�ֵ���в���������
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
//----------------��������λ�ؼ��ı���ƺ���-----------------------
void CMy232_VCDlg::OnSelchangeCOMBODateSelect() 
{
	// TODO: Add your control notification handler code here
	Return_Value.m_Date_Select = ((CComboBox*)GetDlgItem(IDC_COMBO_Date_Select))->GetCurSel();//��ǰѡ�е���
	//���ݵ�ǰѡ�е�ֵ��������λ����
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
//----------------����ֹͣλ�ؼ��ı���ƺ���-----------------------
void CMy232_VCDlg::OnSelchangeCOMBOStopBit() 
{
	// TODO: Add your control notification handler code here
	Return_Value.m_StopBit = ((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->GetCurSel();//��ǰѡ����
	//���ݵ�ǰѡ�е�ֵ����ֹͣλ����
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
//----------------����У��λ�ؼ��ı���ƺ���-----------------------
void CMy232_VCDlg::OnSelchangeCOMBOParityCheck() 
{
	// TODO: Add your control notification handler code here
	Return_Value.m_ParityCheck = ((CComboBox*)GetDlgItem(IDC_COMBO_ParityCheck))->GetCurSel();//��ǰѡ����
	//���ݵ�ǰѡ�е�ֵ����У��λ����
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
//----------------��ע����ȡϵͳCOM�ں���-----------------------
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
	  &dwValueNumber, //���غ�hKey������ֵ 
	  &MaxValueLength, 
	  NULL, 
	  NULL, 
	  NULL); 
	if(lReg!=ERROR_SUCCESS) //û�гɹ� 
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
//---------------------------�򿪹رմ��ں���-----------------------
void CMy232_VCDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	//����Ƿ�ı�Ĭ�ϵĴ���ֵ��û�иı�Return_Value.m_Index��ֵ��0������Ϊ0
	switch(m_ctrlComm.GetPortOpen())//0��ʾû�д򿪴��ڣ����Խ��д򿪴��ڲ�����1��ʾ���˴��ڣ����Խ��йرմ��ڲ���
	{
		case 1:
			m_ctrlComm.SetPortOpen(FALSE);//�رմ���
			SetDlgItemText(IDC_BUTTON_START,"�򿪴���");//���İ���ָʾ
			UpdateData(FALSE);
			break;
		case 0:
			Index_M = ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();//��ȡ��ǰ��
			m_ctrlComm.SetCommPort(Index_M + 1);//���õ�ǰ��ΪCOM��
			m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
			SetDlgItemText(IDC_BUTTON_START,"�رմ���");//���İ���ָʾ
			UpdateData(FALSE);
			m_ctrlComm.SetSettings("115200,n,8,1");//�����ʱ�˿�����Ĭ�ϲ�����Ϊ115200����У��λ��8λ���ݣ�1λֹͣλ
			m_ctrlComm.SetInputMode(1);//1����ʾ�����Ʒ�ʽ��ȡ����
			m_ctrlComm.SetRThreshold(1);//����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�ONCOMM�¼�
			m_ctrlComm.SetInputLen(0);//���õ�ǰ���������ݳ���Ϊ0
			m_ctrlComm.GetInput();//��Ԥ���������������������
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
