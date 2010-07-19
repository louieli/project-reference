/*****************************************************************************
Filename: 	Hooks.h
Copyright(C) XXXXXXXXXXXXX

Created:	2004-07-09
Author:     jyan
Abstract:	
            实现 HookApi 功能，实现方法是在 系统代码 和 Jmp 代码中切换

Modified History:	
        Who             When                Modify
*****************************************************************************/

#ifndef _HOOKS_API_H
#define _HOOKS_API_H

#include "hookapiinterface.h"
#include "string"

#pragma warning(disable: 4786)
#include "map"
using namespace std; 

struct HookFunInfo 
{
	char  m_szSysBuf[5];
    char  m_szMyBuf[5];
	
	DWORD m_dwMyAdr;
	DWORD m_dwSysAdr;

	BOOL Init(DWORD dwMyAdr, DWORD dwSysAdr);
	void SysToMy();
	void MyToSys();
};

class CHookApi  
{
public:
	CHookApi();
	virtual ~CHookApi();

	BOOL HookFun(DWORD dwMyAdr, DWORD dwSysAdr);
	void UnHookFun(DWORD dwMyAdr);
	
	BOOL IsHook(DWORD dwMyAdr);

	void SysToMy(DWORD dwMyAdr);
	void MyToSys(DWORD dwMyAdr);

	void HookFunFromConfigFile();

private:
	map<DWORD, HookFunInfo>  m_infos;
    typedef map<DWORD, HookFunInfo>::iterator MAP_ITE;
};

typedef struct tagExportFunInfo
{
	WORD   wIndex;
	DWORD  dwOffset;
	string strFunName;
}EXPORT_FUN_INFO, *PEXPORT_FUN_INFO;

class CHookHelper : public IHookHelper
{
public:
	CHookHelper();
	virtual ~CHookHelper();

	virtual void Enter(DWORD dwMineAdr);
	virtual void Leave(DWORD dwMineAdr);

	virtual void Log(const char* pContent);
	virtual void SetLogFilePath(const char* pLogFile);
    virtual const char* GetLogFilePath();

	virtual HANDLE HookProce(const char* pszExeFile, const char* pszDllFile, BOOL bSuspend);
	
	CHookApi hookApi;

private:
	string  m_strLogFile;
};

#endif