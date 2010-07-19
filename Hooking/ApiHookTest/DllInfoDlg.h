/*****************************************************************************
Filename: 	DllInfoDlg.h
Copyright(C) XXXXXXXXXXXXX

Created:	2004-07-09
Author:     jyan
Abstract:	
            显示当前 Hook 配置中涉及到 Dll 的信息，如果 Dll 导出了 GetDllInfo 和 ShowMe
            函数，会在需要的时候调用

Modified History:	
        Who             When                Modify
*****************************************************************************/


#if !defined(AFX_DLLINFODLG_H__90871C6E_4458_4FED_AE5F_28B47021CC9A__INCLUDED_)
#define AFX_DLLINFODLG_H__90871C6E_4458_4FED_AE5F_28B47021CC9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "mystatic.h"
#include "string"
#include "vector"
using namespace std;

class CDllInfoDlg : public CDialog
{
// Construction
public:
	void SetActiveDll(int nIndex);
	CDllInfoDlg(CWnd* pParent, const char* pszCfgFile);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDllInfoDlg)
	enum { IDD = IDD_DLL_INFO_DLG };
	CMyStatic	m_static;
	CComboBox	m_comboDlls;
	//}}AFX_DATA
    
    string m_strCfgFile;
    PVOID  m_pCallBack;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDllInfoDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDlls();
	afx_msg void OnShowme();
	afx_msg void OnViewExportInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLINFODLG_H__90871C6E_4458_4FED_AE5F_28B47021CC9A__INCLUDED_)
