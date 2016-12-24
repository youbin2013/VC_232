// 232_VC.h : main header file for the 232_VC application
//

#if !defined(AFX_232_VC_H__0DC73F69_A372_4F4E_B251_D0D16DCDA11B__INCLUDED_)
#define AFX_232_VC_H__0DC73F69_A372_4F4E_B251_D0D16DCDA11B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy232_VCApp:
// See 232_VC.cpp for the implementation of this class
//

class CMy232_VCApp : public CWinApp
{
public:
	CMy232_VCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy232_VCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy232_VCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_232_VC_H__0DC73F69_A372_4F4E_B251_D0D16DCDA11B__INCLUDED_)
