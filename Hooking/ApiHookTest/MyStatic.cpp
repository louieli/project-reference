// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ApiHookTest.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
	m_hBp = NULL;
	m_hIcon = NULL;	
}

CMyStatic::~CMyStatic()
{
	if(m_hIcon)
	{
		::DeleteObject(m_hIcon);
		m_hIcon = NULL;
	}
	if(m_hBp)
	{
		::DeleteObject(m_hBp);
		m_hBp = NULL;
	}	
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers

BOOL CMyStatic::OnEraseBkgnd(CDC* pDC) 
{
	CClientDC dc(this);
	CRect  rcClient;
	GetClientRect(&rcClient);
	
	if(m_hBp)
	{
		CDC  memDc;
		memDc.CreateCompatibleDC(&dc);
		HBITMAP bpOld = (HBITMAP)memDc.SelectObject(m_hBp);
		
		BITMAP bpInfo;
		::GetObject(m_hBp, sizeof(BITMAP), &bpInfo);

		dc.StretchBlt(1, 1, rcClient.Width() - 2, rcClient.Height() - 2,
			          &memDc, 0, 0, bpInfo.bmWidth, bpInfo.bmHeight, SRCCOPY);

		memDc.SelectObject(bpOld);
	}
	else if(m_hIcon)
	{
		int x = (rcClient.Width() - 32) / 2;
		int y = (rcClient.Height() - 32) / 2;
		::DrawIconEx(dc.m_hDC, x, y, m_hIcon, 32, 32, 0, NULL, 0);
	}
	else
	{
		dc.FillSolidRect(&rcClient, RGB(255,255,255));
	}

	dc.MoveTo(0,0);
	dc.LineTo(rcClient.Width(), 0);
	dc.LineTo(rcClient.Width(), rcClient.Height());
	dc.LineTo(0, rcClient.Height());
	dc.LineTo(0, 0);

	return TRUE;
}

void CMyStatic::SetImag(HICON hIcon, HBITMAP hBp)
{
	if(m_hIcon)
	{
		::DeleteObject(m_hIcon);
	}
	if(m_hBp)
	{
		::DeleteObject(m_hBp);
	}

	m_hIcon = hIcon;
	m_hBp   = hBp;

	Invalidate();
}

void CMyStatic::OnPaint() 
{
	CPaintDC dc(this);	
}
