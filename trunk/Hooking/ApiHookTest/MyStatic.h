/*****************************************************************************
Filename: 	MyStatic.h
Copyright(C) XXXXXXXXXXXXX

Created:	2004-07-09
Author:     jyan
Abstract:	
            简单实现在背景画一个 hIcon 或者 hBitmap

Modified History:	
        Who             When                Modify
*****************************************************************************/

#if !defined(AFX_MYSTATIC_H__D312D840_0CBB_4F41_B682_53BBEF346541__INCLUDED_)
#define AFX_MYSTATIC_H__D312D840_0CBB_4F41_B682_53BBEF346541__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();

public:
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetImag(HICON hIcon, HBITMAP hBp);
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	HBITMAP  m_hBp;
	HICON    m_hIcon;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__D312D840_0CBB_4F41_B682_53BBEF346541__INCLUDED_)
