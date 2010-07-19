#ifndef _HOOK_PROCESS_H
#define _HOOK_PROCESS_H

class CHookProcess  
{
public:
	CHookProcess();
	virtual ~CHookProcess();

	BOOL HookProcess(HANDLE hProcess, char* pszFileExe, char* pszFileDll);

private:
	DWORD GetProcessModuleHandle(char* pszFileExe);
	DWORD GetProcessEntryPoint(char* pszFileExe);
};

#endif