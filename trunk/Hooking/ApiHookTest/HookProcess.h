/*****************************************************************************
Filename: 	HookProcess.h
Copyright(C) XXXXXXXXXXXXX

Created:	2004-07-09
Author:     jyan
Abstract:	
            ʵ�� Dll ��ע�룬 �������޸���ڴ���Ϊ Jmp�������Լ�ָ���Ĵ����У�
            Ȼ�� LoadLibrary  -> �ָ� -> Jmp ��ȥ

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

    //Ψһ�Ĺ��к����� 
    //hProcess   Ϊһ���մ����������̱߳�����Ľ��̾��
    //pszFileExe Ϊ��� Exe ��·��
    //pszFileDll ΪҪע��� Dll
	BOOL HookProcess(HANDLE hProcess, char* pszFileExe, char* pszFileDll);

private:
	DWORD  GetProcessEntryPoint(char* pszFileExe);
	LPVOID AllocBufAfterBaseAdr(HANDLE hProcess, LPVOID pBase, int nSize);
	BOOL   WriteProcessMemorySafe(HANDLE hProcess, LPVOID pDes, LPVOID pSrc, int nSize);
	BOOL   ReadProcessMemorySafe(HANDLE hProcess, LPCVOID lpBaseAdr, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberofBytesRead);
};

#endif