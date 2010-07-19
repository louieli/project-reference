// HookProcess.cpp: implementation of the CHookProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HookProcess.h"
#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")

CHookProcess::CHookProcess()
{

}

CHookProcess::~CHookProcess()
{

}

BOOL CHookProcess::HookProcess(HANDLE hProcess, char* pszFileExe, char* pszFileDll)
{
	BYTE  szBuf[1024*8];
	DWORD dwReadBy(0);
	DWORD dwOldProtect(0);
	DWORD dwTemp(0);
	DWORD dwNtHeaderAdr(0);
	DWORD dwOldEntryPoint(0);
	DWORD dwNewEntryPoint(0);	
	DWORD dwEntryPointAdr(0);

	//�õ���ڵ�ַ��dwOldEntryPoint���� �Լ�������ڵ�ַ�����ĵ�ַ��dwEntryPointAdr��
	DWORD dwBaseAdr = GetProcessModuleHandle(pszFileExe);

	if(!ReadProcessMemory(hProcess, (const void*)dwBaseAdr, &szBuf[0], sizeof(IMAGE_DOS_HEADER), &dwReadBy))
	{
		return FALSE;
	}

	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)&szBuf;
	dwNtHeaderAdr = dwBaseAdr + pDosHeader->e_lfanew;

	if(!ReadProcessMemory(hProcess, (const void*)dwNtHeaderAdr, &szBuf[0], sizeof(IMAGE_NT_HEADERS), &dwReadBy))
	{
		return FALSE;
	}	

	IMAGE_NT_HEADERS* pNtHeaders = (IMAGE_NT_HEADERS*)&szBuf[0];
	dwEntryPointAdr = (DWORD)&pNtHeaders->OptionalHeader.AddressOfEntryPoint - (DWORD)pNtHeaders + dwNtHeaderAdr;
	dwOldEntryPoint = pNtHeaders->OptionalHeader.AddressOfEntryPoint;

	//��Ŀ����̿ռ��з���һ���ڴ�
	LPBYTE pAllocNew = (LPBYTE)VirtualAllocEx(hProcess, NULL, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if(pAllocNew == NULL)
	{
		return FALSE;
	}

	dwNewEntryPoint = (DWORD)&pAllocNew[strlen(pszFileDll) + 1];
	
	//���͵���ڵ�ַ �ĳ����Ǹշ���ĵ�ַ�� Ȼ��������д�������
	if(!VirtualProtectEx(hProcess, (LPVOID)dwEntryPointAdr, 4, PAGE_READWRITE, &dwOldProtect))
	{
		return FALSE;
	}

	if(!WriteProcessMemory(hProcess, (LPVOID)dwEntryPointAdr, &dwNewEntryPoint, 4, &dwTemp))
	{
		return FALSE;
	}
	
	if(!VirtualProtectEx(hProcess, (LPVOID)dwEntryPointAdr, 4, dwOldProtect, &dwOldProtect))
	{
		return FALSE;
	}

	//��֯������, �Լ�·���ַ���
	HINSTANCE hKernel = GetModuleHandle("kernel32.dll");
	if(!hKernel)
	{
		return FALSE;
	}

	DWORD dwLoadLibFun = (DWORD)GetProcAddress(hKernel, "LoadLibraryA");
	if(dwLoadLibFun == 0L)
	{
		return FALSE;
	}

	int nPos = 0;
	
	memcpy(szBuf, pszFileDll, strlen(pszFileDll) + 1);
	nPos += (strlen(pszFileDll) + 1);

	szBuf[nPos++] = 0x68;         //push adr
	*(DWORD*)&szBuf[nPos] = (DWORD)&pAllocNew[0];
	nPos += 4;

	szBuf[nPos++] = 0xB8;         //mov eax, adr
	*(DWORD*)&szBuf[nPos] = dwLoadLibFun;
	nPos += 4;

	szBuf[nPos++] = 0xFF;         //call eax
	szBuf[nPos++] = 0xD0;

	szBuf[nPos++] = 0xB8;         //mov eax, adr
	*(DWORD*)&szBuf[nPos] = dwOldEntryPoint;
	nPos += 4;

	szBuf[nPos++] = 0xFF;         //jmp eax
	szBuf[nPos++] = 0xE0;        
	
	//������ �Լ���Ϣ������ hProcess��ȥ
	if(!WriteProcessMemory(hProcess, pAllocNew, &szBuf[0], nPos, &dwTemp))
	{
		return FALSE;
	}

	if(!VirtualProtectEx(hProcess, pAllocNew, 1024, PAGE_EXECUTE_READ, &dwOldProtect))
	{
		return FALSE;
	}

	return TRUE;
}

DWORD CHookProcess::GetProcessModuleHandle(char* pszFileExe)
{
	PLOADED_IMAGE pImage = ImageLoad(pszFileExe, NULL);

	if(pImage == NULL)
	{
		return 0L;
	}

	DWORD dwAdr = pImage->FileHeader->OptionalHeader.ImageBase;

	ImageUnload(pImage);
	
	return dwAdr;	
}

DWORD CHookProcess::GetProcessEntryPoint(char* pszFileExe)
{
	PLOADED_IMAGE pImage = ImageLoad(pszFileExe, NULL);
	
	if(pImage == NULL)
	{
		return 0L;
	}
	
	DWORD dwAdr = pImage->FileHeader->OptionalHeader.AddressOfEntryPoint + pImage->FileHeader->OptionalHeader.ImageBase;

	ImageUnload(pImage);
	
	return dwAdr;
}