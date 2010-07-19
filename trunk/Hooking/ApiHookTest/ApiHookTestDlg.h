#if !defined(AFX_APIHOOKTESTDLG_H__F6B31BA1_B125_46E1_8870_16991DAE605E__INCLUDED_)
#define AFX_APIHOOKTESTDLG_H__F6B31BA1_B125_46E1_8870_16991DAE605E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


class CApiHookTestDlg : public CDialog
{
public:
	CApiHookTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CApiHookTestDlg)
	enum { IDD = IDD_APIHOOKTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApiHookTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CApiHookTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGo();
	afx_msg void OnSelectexe();
	afx_msg void OnSelectlog();
	afx_msg void OnViewhookdllinfo();
	afx_msg void OnChangehookapi();
	afx_msg void OnViewlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APIHOOKTESTDLG_H__F6B31BA1_B125_46E1_8870_16991DAE605E__INCLUDED_)
