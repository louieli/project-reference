// HSock.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "HSock.h"
#include "Hooks.h"

void  GetMePath(char* pszPath);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
                char szBuf[MAX_PATH];
                char szCurPath[MAX_PATH];

                GetMePath(&szCurPath[0]);
                strcat(szCurPath, "config.ini");

                GetPrivateProfileString("Option", "LogFilePath", "C:\\Hooks.log",
                                        &szBuf[0], MAX_PATH, szCurPath);

				::DeleteFile(szBuf);
				CHookHelper* pHelper = (CHookHelper*)GetHookHelper();
                pHelper->SetLogFilePath(szBuf);
				pHelper->Log("Start Hook Funtions ......");
				
				if(pHelper)
				{
					pHelper->hookApi.HookFunFromConfigFile();
				}
				pHelper->Log("/************************************************************/");
			}
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

IHookHelper* GetHookHelper()
{
    static CHookHelper hookHelper;
    return (IHookHelper*)&hookHelper;
}

void  GetMePath(char* pszPath)
{
    GetModuleFileName(GetModuleHandle("Hook.dll"), pszPath, MAX_PATH);
    for(int i = strlen(pszPath) - 1; i >= 0; i--)
    {
        if(pszPath[i] == '\\')
        {
            pszPath[i+1] = NULL;
            break;
        }
    }
}