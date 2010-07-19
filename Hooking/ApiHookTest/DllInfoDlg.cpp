// DllInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ApiHookTest.h"
#include "DllInfoDlg.h"
#include "DataEngine.h"
#include "imagehlp.h"

#pragma comment(lib, "imagehlp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDllInfoDlg dialog
extern void GetMePath(char* pszPath);


CDllInfoDlg::CDllInfoDlg(CWnd* pParent /*=NULL*/, const char* pszCfgFile)
	: CDialog(CDllInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDllInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    if(pszCfgFile)
    {
        m_strCfgFile = pszCfgFile;
    }

    m_pCallBack = NULL;
}


void CDllInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDllInfoDlg)
	DDX_Control(pDX, IDC_FRAME, m_static);
	DDX_Control(pDX, IDC_DLLS, m_comboDlls);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDllInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CDllInfoDlg)
	ON_CBN_SELCHANGE(IDC_DLLS, OnSelchangeDlls)
	ON_BN_CLICKED(IDC_SHOWME, OnShowme)
	ON_BN_CLICKED(IDC_VIEW_EXPORT_INFO, OnViewExportInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDllInfoDlg message handlers

void CDllInfoDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CDllInfoDlg::OnOK() 
{
	CDialog::OnOK();
}


void StrReplace(string& str, const char* pszOld, const char* pszNew)
{
	if(!pszOld || !pszNew)
	{
		return;
	}
	
	int nPos = 0;
	
	while((nPos = str.find(pszOld, nPos)) >= 0)
	{
		str.insert(nPos, pszNew);
		nPos += strlen(pszNew);
		str.erase(nPos, strlen(pszOld));
	}
}

BOOL CDllInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CDataEngine dataEngine;
    dataEngine.parser(m_strCfgFile.c_str());

    data_info *pInfo = NULL;
    int nIndex = 0;

    vector<string> vstrDlls;
    vector<string>::iterator ite;

	char szMePaht[MAX_PATH];
	GetMePath(szMePaht);

    while((pInfo = dataEngine.get_info(nIndex++)) != NULL)
    {
        ite = vstrDlls.begin();
        while(ite != vstrDlls.end())
        {
            if(*ite == pInfo->mine_module)
            {
                break;
            }
            ite++;
        }
        
        if(ite == vstrDlls.end())
        {
            vstrDlls.push_back(pInfo->mine_module);
        }
    }

    for(ite = vstrDlls.begin(); ite != vstrDlls.end(); ite++)
    {
		StrReplace((*ite), "[LOCAL_PATH]", szMePaht);
        m_comboDlls.AddString((*ite).c_str());
    }

    m_comboDlls.SetCurSel(0);
    SetActiveDll(0);
    
	return TRUE;
}

typedef void (PASCAL *PSHOWME)(HWND hParent);

typedef struct tagDllInfo
{
    char    szAuthor[100];
    char    szEmail[100];
    char    szHomePage[255];
    char    szIntroduce[2048];
    HICON   hIconSign;
    HBITMAP hBpSign;
    PSHOWME pCallBack;

    tagDllInfo()
    {
        memset(this, 0, sizeof(tagDllInfo));
    }
}DLL_INFO, *LPDLL_INFO;

typedef void (PASCAL *PGETDLLINFO)(DLL_INFO& info);

void CDllInfoDlg::SetActiveDll(int nIndex)
{
    DLL_INFO info;

    int nCount = m_comboDlls.GetCount();

    if( nCount> 0 && nIndex < nCount && nIndex >= 0)
    {
        CString strDll;
        m_comboDlls.GetLBText(nIndex, strDll);

        HMODULE hDll = LoadLibrary(strDll);
        if(hDll != NULL)
        {
            PGETDLLINFO pFun = (PGETDLLINFO)GetProcAddress(hDll, "GetDllInfo");
            if(pFun)
            {
                pFun(info);
            }
        }
    }

    SetDlgItemText(IDC_AUTH, info.szAuthor);
    SetDlgItemText(IDC_EMAIL, info.szEmail);
    SetDlgItemText(IDC_HOMEPAGE, info.szHomePage);
    SetDlgItemText(IDC_INTRODUCE, info.szIntroduce);

	m_static.SetImag(info.hIconSign, info.hBpSign);

    m_pCallBack = info.pCallBack;
    if(info.pCallBack)
    {
        GetDlgItem(IDC_SHOWME)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_SHOWME)->EnableWindow(FALSE);
    }
}

void CDllInfoDlg::OnSelchangeDlls() 
{
    int nIndex = m_comboDlls.GetCurSel();
    SetActiveDll(nIndex);
}

void CDllInfoDlg::OnShowme() 
{
    PSHOWME pFun = (PSHOWME)m_pCallBack;

    if(pFun)
    {
        pFun(m_hWnd);
    }
}

DWORD RVA2RawAdr(IMAGE_SECTION_HEADER* pSections, DWORD dwRVA)
{
    DWORD dwRawRVAAdr(0);
	
    if(!pSections)
    {
        return dwRawRVAAdr;
    }
	
    while(pSections->VirtualAddress != 0)
    {
        if(dwRVA >= pSections->VirtualAddress &&
			dwRVA < pSections->VirtualAddress + pSections->SizeOfRawData)
        {
            dwRawRVAAdr = (dwRVA - pSections->VirtualAddress) + pSections->PointerToRawData;
            break;
        }
		pSections++;
    }
	
    return dwRawRVAAdr;
}

typedef struct tagDll_ExportFunInfo
{
    WORD   wOrdinal;
    DWORD  dwOffset;
    string strFunName;
}EXPORT_FUN_INFO, *PEXPORT_FUN_INFO;

int GetExportFunInfo(vector<EXPORT_FUN_INFO>& infos, const char* pszDllFile)
{
    int nCount(0);
	
    if(!pszDllFile)
    {
        return nCount;
    }
	
    PLOADED_IMAGE pImage = ImageLoad((char*)pszDllFile, NULL);
    if(!pImage)
    {
        return nCount;
    }
	
    DWORD dwBase = (DWORD)pImage->MappedAddress;
    PIMAGE_SECTION_HEADER pSections = (PIMAGE_SECTION_HEADER)((DWORD)pImage->FileHeader + sizeof(IMAGE_NT_HEADERS));
    PIMAGE_EXPORT_DIRECTORY pExportDir = (PIMAGE_EXPORT_DIRECTORY)(RVA2RawAdr(pSections, pImage->FileHeader->OptionalHeader.DataDirectory[0].VirtualAddress) + dwBase);
	
    infos.clear();
	
    EXPORT_FUN_INFO info;
	
    DWORD* pFunOffsetAdr = (DWORD*)(RVA2RawAdr(pSections, pExportDir->AddressOfFunctions) + dwBase);
    for(int i = 0; i < pExportDir->NumberOfFunctions; i++)
    {
        info.dwOffset = 0;
        info.strFunName = "";
        info.wOrdinal = 0;
        
        info.dwOffset = *(pFunOffsetAdr + i);
        info.wOrdinal = i + 1;
        infos.push_back(info);
    }
	
    DWORD* pFunNamesAdr = (DWORD*)(RVA2RawAdr(pSections, pExportDir->AddressOfNames) + dwBase);
    WORD* pFunNamesOrdinalAdr = (WORD*)(RVA2RawAdr(pSections, pExportDir->AddressOfNameOrdinals) + dwBase);
	
    char* pName = NULL;
    for(i = 0; i < pExportDir->NumberOfNames; i++)
    {
        pName = (char*)(RVA2RawAdr(pSections, *(pFunNamesAdr+i)) + dwBase);
        EXPORT_FUN_INFO& tmpInfo = infos[*(pFunNamesOrdinalAdr+i)];
        tmpInfo.strFunName = pName;
    }
	
    return infos.size();
}

void CDllInfoDlg::OnViewExportInfo() 
{
	vector<EXPORT_FUN_INFO> infos;

	int nIndex = m_comboDlls.GetCurSel();
	int nCount = m_comboDlls.GetCount();

	if( nCount> 0 && nIndex < nCount && nIndex >= 0)
    {
        CString strDll;
        m_comboDlls.GetLBText(nIndex, strDll);
		if(!strDll.IsEmpty())
		{
			if(GetExportFunInfo(infos, strDll) > 0)
			{
				CString strTmpFile;
				GetCurrentDirectory(MAX_PATH, strTmpFile.GetBuffer(MAX_PATH));
				strTmpFile.ReleaseBuffer();
				strTmpFile += "\\tmp.txt";
		
				CFile fileTmp;
				if(fileTmp.Open(strTmpFile, CFile::modeCreate | CFile::modeReadWrite))
				{
					CString strTmp;
					strTmp.Format("%s Export Information:", strDll);
					fileTmp.Write(strTmp, strTmp.GetLength());

					vector<EXPORT_FUN_INFO>::iterator ite = infos.begin();

					for(; ite != infos.end(); ite++)
					{
						if(ite->dwOffset == 0)
							continue;
						
						strTmp.Format("\r\n%3d   0x%p   %s", ite->wOrdinal, ite->dwOffset, ite->strFunName.c_str());
						fileTmp.Write(strTmp, strTmp.GetLength());
					}
					fileTmp.Close();

					ShellExecute(m_hWnd, "open", "notepad.exe", strTmpFile, NULL, SW_NORMAL);					
				}
			}
		}
    }
}
