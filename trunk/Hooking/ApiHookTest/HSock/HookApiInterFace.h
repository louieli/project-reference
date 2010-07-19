#ifndef _HOOK_API_INTERFACE_H
#define _HOOK_API_INTERFACE_H

struct IHookHelper
{
	virtual void Enter(DWORD dwMineFunAdr) = 0;
	virtual void Leave(DWORD dwMineFunAdr) = 0;
	virtual void Log(const char* pContent) = 0;
	virtual void SetLogFilePath(const char* pLogFile) = 0;
    virtual const char* GetLogFilePath() = 0;
};

extern "C" __declspec(dllexport) IHookHelper* GetHookHelper();

#endif