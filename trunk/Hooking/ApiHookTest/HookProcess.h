/*****************************************************************************
Filename: 	HookProcess.h
Copyright(C) XXXXXXXXXXXXX

Created:	2004-07-09
Author:     jyan
Abstract:	
            实现 Dll 的注入， 方法是修改入口代码为 Jmp，跳到自己指定的代码中，
            然后 LoadLibrary  -> 恢复 -> Jmp 回去

Modified History:	
        Who             When                Modify
*****************************************************************************/

#ifndef _HOOK_PROCESS_H
#define _HOOK_PROCESS_H

class CHookProcess  
{
public:
	CHookProcess();
	virtual ~CHookProcess();

    //唯一的共有函数， 
    //hProcess   为一个刚创建，且主线程被挂起的进程句柄
    //pszFileExe 为这个 Exe 的路径
    //pszFileDll 为要注入的 Dll
	BOOL HookProcess(HANDLE hProcess, char* pszFileExe, char* pszFileDll);

private:
	DWORD  GetProcessEntryPoint(char* pszFileExe);
	LPVOID AllocBufAfterBaseAdr(HANDLE hProcess, LPVOID pBase, int nSize);
	BOOL   WriteProcessMemorySafe(HANDLE hProcess, LPVOID pDes, LPVOID pSrc, int nSize);
	BOOL   ReadProcessMemorySafe(HANDLE hProcess, LPCVOID lpBaseAdr, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberofBytesRead);
};

#endif