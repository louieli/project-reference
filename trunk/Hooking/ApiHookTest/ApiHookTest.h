// ApiHookTest.h : main header file for the APIHOOKTEST application
//

#if !defined(AFX_APIHOOKTEST_H__18667430_EC4D_427F_AA4E_5F5FE2A47885__INCLUDED_)
#define AFX_APIHOOKTEST_H__18667430_EC4D_427F_AA4E_5F5FE2A47885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CApiHookTestApp:
// See ApiHookTest.cpp for the implementation of this class
//

class CApiHookTestApp : public CWinApp
{
public:
	CApiHookTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApiHookTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CApiHookTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APIHOOKTEST_H__18667430_EC4D_427F_AA4E_5F5FE2A47885__INCLUDED_)
