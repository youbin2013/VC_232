// 232_VCDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_232_VCDLG_H__014EB398_A5DE_427A_B8ED_3737EFF917E1__INCLUDED_)
#define AFX_232_VCDLG_H__014EB398_A5DE_427A_B8ED_3737EFF917E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy232_VCDlg dialog

class CMy232_VCDlg : public CDialog
{
// Construction
public:
	void ChangeSize(CWnd* pWnd,int cx,int cy);
	void ShowComm(void);
	CMy232_VCDlg(CWnd* pParent = NULL);	// standard constructor
	CRect m_rect;

// Dialog Data
	//{{AFX_DATA(CMy232_VCDlg)
	enum { IDD = IDD_MY232_VC_DIALOG };
	CComboBox	m_ParityCheck_M;
	CComboBox	m_StopBit_M;
	CComboBox	m_Date_Select_M;
	CComboBox	m_BaudRate_M;
	CComboBox	m_ComboBox;
	CMSComm	m_ctrlComm;
	CString	m_strRXData;
	CString	m_strTXData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy232_VCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy232_VCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnComm();
	afx_msg void OnButtonManualsend();
	afx_msg void OnSelchangeCOMBOBaudRateSelect();
	afx_msg void OnSelchangeCOMBODateSelect();
	afx_msg void OnSelchangeCOMBOStopBit();
	afx_msg void OnSelchangeCOMBOParityCheck();
	afx_msg void OnButtonStart();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


//定义一个结构体，控制选择框
typedef struct{
	int m_Index;	//COM口返回值
	int m_BaudRate; //波特率返回值
	int m_Date_Select;//数据位返回值
	int m_StopBit;//停止位返回值
	int m_ParityCheck;//校验位返回值
}RETURN_VALUE;

//定义com口返回值
extern int Index_M;

#endif // !defined(AFX_232_VCDLG_H__014EB398_A5DE_427A_B8ED_3737EFF917E1__INCLUDED_)
