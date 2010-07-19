#include "stdafx.h"
#include "ApiHookTest.h"
#include "ApiHookTestDlg.h"
#include "HookProcess.h"
#include "DllInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void GetMePath(char* pszPath);

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
	virtual void DoDataExchange(CDataExchange* pDX);
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

CApiHookTestDlg::CApiHookTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CApiHookTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CApiHookTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApiHookTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApiHookTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CApiHookTestDlg, CDialog)
	//{{AFX_MSG_MAP(CApiHookTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_SELECTEXE, OnSelectexe)
	ON_BN_CLICKED(IDC_SELECTLOG, OnSelectlog)
	ON_BN_CLICKED(IDC_VIEWHOOKDLLINFO, OnViewhookdllinfo)
	ON_BN_CLICKED(IDC_CHANGEHOOKAPI, OnChangehookapi)
	ON_BN_CLICKED(IDC_VIEWLOG, OnViewlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CApiHookTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

 	//LoadLibrary("d:\\MyProject\\ApiHookTest\\HSock\\Debug\\HSock.dll");

    recvfrom(0, 0, 0, 0, 0, 0);
    WSADATA wd;
    WSAStartup(MAKEWORD(1,1), &wd);
    
    SOCKET s = socket(AF_INET, 1, 0);

    sockaddr_in addr;
    addr.sin_addr.S_un.S_addr = 0;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    memset(&addr.sin_zero[0], 0, sizeof(addr.sin_zero));
    
    int nR = bind(s, (sockaddr*)&addr, sizeof(addr));
    
    addr.sin_addr.S_un.S_un_b.s_b1 = 202;
    addr.sin_addr.S_un.S_un_b.s_b2 = 108;
    addr.sin_addr.S_un.S_un_b.s_b3 = 36;
    addr.sin_addr.S_un.S_un_b.s_b4 = 167;
    addr.sin_port = htons(80);

    //读取配置
    char szBuf[MAX_PATH];
    char szCurPath[MAX_PATH];
    
    GetMePath(&szCurPath[0]);
    strcat(szCurPath, "config.ini");
    
    GetPrivateProfileString("Option", "LogFilePath", "C:\\Hooks.log",
                            &szBuf[0], MAX_PATH, szCurPath);
    SetDlgItemText(IDC_LOGFILE, szBuf);



	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CApiHookTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CApiHookTestDlg::OnPaint() 
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

HCURSOR CApiHookTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CApiHookTestDlg::OnGo() 
{
    CString strExeFile;
    CString strExeCmd;
    CString strExeFilePath;

    CWnd* pWnd = GetDlgItem(IDC_EXEFILE);
    if(!pWnd)
    {
        return;
    }
    
    pWnd->GetWindowText(strExeFile);
    if(strExeFile.IsEmpty())
    {
        return;
    }
    strExeFilePath = strExeFile;
    strExeFilePath.SetAt(strExeFilePath.ReverseFind('\\') + 1 , NULL);

    pWnd = GetDlgItem(IDC_EXECMD);
    if(pWnd)
    {
        pWnd->GetWindowText(strExeCmd);
    }

    STARTUPINFO st;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&st, sizeof(st));
    ZeroMemory(&pi, sizeof(pi));
    st.cb = sizeof(st);

    CString strTmp;
    strTmp.Format("\"%s\" %s", strExeFile, strExeCmd);
    
    if (CreateProcess(NULL, (char*)(const char*)strTmp, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, (const char*)strExeFilePath, &st, &pi))
    {
        CHookProcess hook;
		char szMyPath[MAX_PATH] = {0};
		GetMePath(szMyPath);
		for(int i = strlen(szMyPath) - 1; i >= 0; i++)
		{
			if(szMyPath[i] == '\\')
			{
				szMyPath[i + 1] = NULL;
				break;
			}
		}
		//strcat(szMyPath, "Hook.dll");
        strcpy(szMyPath, "E:\\MyProject\\FunSpy\\release\\FunSpy.dll");
        HMODULE hInst = LoadLibrary(szMyPath);

        if(hook.HookProcess(pi.hProcess, (char*)(const char*)strExeFile, szMyPath))
        {
            ResumeThread(pi.hThread);
        
            CloseHandle(pi.hThread);		
            CloseHandle(pi.hProcess);
            return;
        }

		::MessageBox(m_hWnd, "创建进程失败！", "ApiHook", MB_OK | MB_ICONINFORMATION);
        TerminateProcess(pi.hProcess, 0);
    }

    MessageBox("启动程序失败!", "API Hook", MB_OK | MB_ICONINFORMATION);
}

void CApiHookTestDlg::OnSelectexe() 
{
    CFileDialog dlg(TRUE,NULL, NULL,
                    OFN_FILEMUSTEXIST|OFN_EXPLORER,
                    "可执行文件(*.exe)|*.exe||", this);

    // 去掉了 OFN_ENABLEHOOK, 这会导致Assert Fail. Ignored.
    dlg.m_ofn.Flags |= OFN_READONLY;
    // dlg.m_ofn.Flags &= ~OFN_ENABLEHOOK;
    
    if(dlg.DoModal()==IDOK)
    {
        CWnd* pExeFileWnd = GetDlgItem(IDC_EXEFILE);
        if(pExeFileWnd)
        {
            pExeFileWnd->SetWindowText(dlg.GetPathName());
        }
    }
}

void CApiHookTestDlg::OnSelectlog() 
{
    CFileDialog dlg(TRUE,NULL, NULL,
                    OFN_EXPLORER,
                    "可执行文件(*.log)|*.log||", this);
    
    // 去掉了 OFN_ENABLEHOOK, 这会导致Assert Fail. Ignored.
    dlg.m_ofn.Flags |= OFN_READONLY;
    // dlg.m_ofn.Flags &= ~OFN_ENABLEHOOK;
    
    if(dlg.DoModal()==IDOK)
    {
        CWnd* pLogFileWnd = GetDlgItem(IDC_LOGFILE);
        if(pLogFileWnd)
        {
            CString strLogFile = dlg.GetPathName();
            if(strLogFile.Find('.', 0) == -1)
            {
                strLogFile += ".log";
            }

            pLogFileWnd->SetWindowText(strLogFile);
        }
    }
}

void CApiHookTestDlg::OnViewhookdllinfo() 
{
    char szCurPath[MAX_PATH];
    char szCfgFile[MAX_PATH];
    
    GetMePath(szCurPath);
    strcpy(szCfgFile, szCurPath);
    
    strcat(szCfgFile, "config.dat");
    
    CDllInfoDlg dlg(this, szCfgFile);
    dlg.DoModal();
}

void CApiHookTestDlg::OnChangehookapi() 
{
    char szCurPath[MAX_PATH];
    char szCfgFile[MAX_PATH];

    GetMePath(szCurPath);
    strcpy(szCfgFile, szCurPath);

    strcat(szCfgFile, "config.dat");

    ShellExecute(m_hWnd, "open", "notepad.exe", szCfgFile, szCurPath, SW_NORMAL);
}

void CApiHookTestDlg::OnViewlog() 
{
	CWnd* pLogFileWnd = GetDlgItem(IDC_LOGFILE);
	if(pLogFileWnd)
	{
		CString strText;
		pLogFileWnd->GetWindowText(strText);
		CFile fileTmp;
		if(fileTmp.Open(strText, CFile::modeRead))
		{
			fileTmp.Close();
			ShellExecute(m_hWnd, "open", "notepad.exe", strText, NULL, SW_NORMAL);
		}
	}
}
