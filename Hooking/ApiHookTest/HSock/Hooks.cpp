#include "stdafx.h"
#include "Hooks.h"
#include "Imagehlp.h"
#include "dataengine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#define MY_TRY 
#define MY_CATCH(p) if(0)
#else
#define MY_TRY try
#define MY_CATCH(p) catch(p)
#endif

extern void GetMePath(char* pszPath);
void StrReplace(string& str, const char* pszOld, const char* pszNew);

void HookFunInfo::SysToMy()
{
	DWORD  dwOldStatus(0);
	
	MY_TRY
	{
		VirtualProtect((void*)m_dwSysAdr, 8, PAGE_EXECUTE_READWRITE, &dwOldStatus);
		
		WriteProcessMemory( GetCurrentProcess(),
			(LPVOID)m_dwSysAdr, (LPVOID)&m_szMyBuf, sizeof(m_szMyBuf) ,NULL);
		
		VirtualProtect((void*)m_dwSysAdr, 8, dwOldStatus, &dwOldStatus);
	}
	MY_CATCH(...)
	{
	}
}

void HookFunInfo::MyToSys()
{
	DWORD  dwOldStatus(0);
	
	MY_TRY
	{
		
		VirtualProtect((void*)m_dwSysAdr, 8, PAGE_EXECUTE_READWRITE, &dwOldStatus);
		
		WriteProcessMemory( GetCurrentProcess(),
			(LPVOID)m_dwSysAdr, (LPVOID)&m_szSysBuf, sizeof(m_szMyBuf) ,NULL);
		
		VirtualProtect((void*)m_dwSysAdr, 8, dwOldStatus, &dwOldStatus);
	}
	MY_CATCH(...)
	{
	}
}

BOOL HookFunInfo::Init(DWORD dwMyAdr, DWORD dwSysAdr)
{
	MY_TRY
	{		
		m_dwMyAdr  = dwMyAdr;
		m_dwSysAdr = dwSysAdr;
		
		memset(&m_szMyBuf[0], 0, 5);
		memset(&m_szSysBuf[0], 0, 5);
		
		m_szMyBuf[0] = (char)0xE9;
		*(DWORD*)&m_szMyBuf[1] = (dwMyAdr - dwSysAdr - 5);
		
		memcpy(&m_szSysBuf[0], (BYTE*)dwSysAdr, 5);
		return TRUE;
	}
	MY_CATCH(...)
	{
	}
	return FALSE;
}

CHookApi::CHookApi()
{

}

CHookApi::~CHookApi()
{
	map<DWORD, HookFunInfo>::iterator iteInfo = m_infos.begin();
	for(; iteInfo != m_infos.end(); iteInfo++)
	{
		iteInfo->second.MyToSys();
	}

	m_infos.clear();
}

BOOL CHookApi::HookFun(DWORD dwMyAdr, DWORD dwSysAdr)
{
	UnHookFun(dwMyAdr);

	if(!m_infos[dwMyAdr].Init(dwMyAdr, dwSysAdr))
	{
		return FALSE;
	}

	m_infos[dwMyAdr].SysToMy();
	return TRUE;
}

void CHookApi::UnHookFun(DWORD dwMyAdr)
{
	if(m_infos.find(dwMyAdr) != m_infos.end())
	{
		m_infos[dwMyAdr].MyToSys();
		m_infos.erase(dwMyAdr);
	}
}

BOOL CHookApi::IsHook(DWORD dwMyAdr)
{
	return (m_infos.find(dwMyAdr) != m_infos.end());
}

void CHookApi::SysToMy(DWORD dwMyAdr)
{
	if(IsHook(dwMyAdr))
	{
		m_infos[dwMyAdr].SysToMy();
	}
}

void CHookApi::MyToSys(DWORD dwMyAdr)
{
	if(IsHook(dwMyAdr))
	{
		m_infos[dwMyAdr].MyToSys();
	}	
}

void CHookApi::HookFunFromConfigFile()
{
	char szFileName[MAX_PATH];
	IHookHelper* pHelper = GetHookHelper();
	
    GetMePath(&szFileName[0]);
	strcat(szFileName, "config.dat");
	pHelper->Log(szFileName);

	CDataEngine engine;
	engine.parser(szFileName);

	data_info* pInfo = NULL;
	int        nIndex(0);
	HMODULE    hInst = NULL;
	DWORD      dwDesAdr(0);
	DWORD      dwMineAdr(0);
	char       szBuf[1024];

	int nCount = 0;
	while((pInfo=engine.get_info(nIndex++)) != NULL)
	{
		nCount ++;
		sprintf(szBuf, "%-4d ----------------", nCount);
		pHelper->Log(szBuf);
		
		hInst = LoadLibraryA(pInfo->des_module.c_str());
		if(hInst)
		{
			dwDesAdr = (DWORD)GetProcAddress(hInst, pInfo->des_fun.c_str());
			if(dwDesAdr != 0)
			{
				char szMyPaht[MAX_PATH];
				GetMePath(szMyPaht);
				StrReplace(pInfo->mine_module, "[LOCAL_PATH]", szMyPaht);

				hInst = LoadLibraryA(pInfo->mine_module.c_str());
				pHelper->Log(pInfo->mine_module.c_str());
				if(hInst)
				{
					dwMineAdr = (DWORD)GetProcAddress(hInst, pInfo->mine_fun.c_str());

					if(dwMineAdr != 0)
					{
						if(HookFun(dwMineAdr, dwDesAdr))
						{
							pHelper->Log("6");
							sprintf(szBuf, "^_^  [%s | %s] As [%s | %s]",
								    pInfo->des_module.c_str(),
									pInfo->des_fun.c_str(),
									pInfo->mine_module.c_str(),
									pInfo->mine_fun.c_str());
							
							pHelper->Log(&szBuf[0]);
							pHelper->Log("---------------------");
							continue;
						}
					}
					else
					{
						string strtemp;
						strtemp = "GetProcAddress(";
						strtemp += pInfo->mine_fun;
						strtemp += ") Failed!";
						pHelper->Log(strtemp.c_str());						
					}
				}
				else
				{
					string strtemp;
					strtemp = "LoadLibrary(";
					strtemp += pInfo->mine_module;
					strtemp += ") Failed!";
					pHelper->Log(strtemp.c_str());
				}
			}
			else
			{
				string strtemp;
				strtemp = "GetProcAddress(";
				strtemp += pInfo->des_fun;
				strtemp += ") Failed!";
				pHelper->Log(strtemp.c_str());				
			}
		}
		else
		{
			string strtemp;
			strtemp = "LoadLibrary(";
			strtemp += pInfo->des_module;
			strtemp += ") Failed!";
			pHelper->Log(strtemp.c_str());
		}

		sprintf(szBuf, "-_-  [%s | %s] As [%s | %s]",
								    pInfo->des_module.c_str(),
									pInfo->des_fun.c_str(),
									pInfo->mine_module.c_str(),
									pInfo->mine_fun.c_str());
		
		pHelper->Log(&szBuf[0]);
		pHelper->Log("---------------------");
	}

	if(nCount == 0)
	{
		pHelper->Log("can not find valid data in config.dat!");
	}
}

/********************************************************************/
CHookHelper::CHookHelper()
{
	m_strLogFile = "c:\\hooks.log";
	::DeleteFileA(m_strLogFile.c_str());
}

CHookHelper::~CHookHelper()
{
}

void CHookHelper::Enter(DWORD dwMineAdr)
{
	hookApi.MyToSys(dwMineAdr);
}

void CHookHelper::Leave(DWORD dwMineAdr)
{
	hookApi.SysToMy(dwMineAdr);
}

void CHookHelper::Log(const char* pContent)
{
	FILE* pFile = fopen(m_strLogFile.c_str(), "a+");
	if(pFile)
	{
		fseek(pFile, 0, SEEK_END);
		fwrite(pContent, 1, strlen(pContent), pFile);
		fwrite("\r\n", 1, 2, pFile);
		fclose(pFile);
	}
}

void CHookHelper::SetLogFilePath(const char* pLogFile)
{
	if(pLogFile)
	{
		m_strLogFile = pLogFile;
		::DeleteFileA(m_strLogFile.c_str());
	}
}

const char* CHookHelper::GetLogFilePath()
{
    return m_strLogFile.c_str();
}

HANDLE CHookHelper::HookProce(const char* pszExeFile, const char* pszDllFile, BOOL bSuspend)
{
	return NULL;
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
