#ifndef _HOOK_API_INTERFACE_H
#define _HOOK_API_INTERFACE_H

#pragma comment(lib, "Hook.lib")

struct IHookHelper
{
	virtual void Enter(DWORD dwMineFunAdr) = 0;
	virtual void Leave(DWORD dwMineFunAdr) = 0;
	virtual void Log(const char* pContent) = 0;
	virtual void SetLogFilePath(const char* pLogFile) = 0;
    virtual const char* GetLogFilePath() = 0;
};

extern IHookHelper* g_pHelper;

class CFunHelper
{
public:
    CFunHelper(LPVOID pMineAdr)
    {
        g_pHelper->Enter((DWORD)pMineAdr);
        m_dwAdr = (DWORD)pMineAdr;
    }
    virtual ~CFunHelper()
    {
        g_pHelper->Leave(m_dwAdr);
    }
    
private:
    DWORD  m_dwAdr;
};

extern "C" __declspec(dllimport) IHookHelper* GetHookHelper();

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

#endif