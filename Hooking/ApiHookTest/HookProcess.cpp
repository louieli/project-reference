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
	DWORD dwTemp(0);	
	DWORD dwOldProtect(0);
	DWORD dwOldEntryPoint(0);

	//得到入口地址（dwOldEntryPoint）
	dwOldEntryPoint = GetProcessEntryPoint(pszFileExe);
	
	//在目标进程空间中分配一段内存
	//内存中个格式
	//  DllFile(strlen(pszFileDll) ) + 0(1 Byte) + 旧的入口代码(10 Byte) + 新入口代码(n<10)
	LPBYTE pAllocNew = (LPBYTE)AllocBufAfterBaseAdr(hProcess, (LPVOID)dwOldEntryPoint, 1024);
	if(pAllocNew == NULL)
	{
		return FALSE;
	}

	int nPos = 0;

	//将Dll文件路径拷贝过去
	{
		if(!WriteProcessMemorySafe(hProcess, &pAllocNew[nPos], pszFileDll, strlen(pszFileDll) + 1))
		{
			return FALSE;
		}

		nPos += (strlen(pszFileDll) + 1);
	}

	//将旧的入口代码 10 字节 拷贝过去
	{
		if(!ReadProcessMemorySafe(hProcess, (LPVOID)dwOldEntryPoint, &szBuf[0], 10, &dwTemp))
		{
			return FALSE;
		}

		if(!WriteProcessMemorySafe(hProcess, &pAllocNew[nPos], (LPVOID)&szBuf[0], 10))
		{
			return FALSE;
		}

		nPos += 10;
	}

	//写入汇编硬代码
	//主要任务是 LoadLibrary(DllFile)  然后 Jmp 到旧原来的入口处
	/*
	     push adrDllPath
		 mov  eax, &LoadLibrary
		 call eax
		 //拷贝我们保存下来的旧的入口代码回去(10 Byte)，然后jmp过去
		 mov  eax, adrOldCode
		 mov  ebx, adrEntryPoint
		 mov  cl,  byte ptr[eax]
		 mov  byte ptr[ebx], cl
		 add  eax, 2
		 add  ebx, 2
		 mov  cx,  word ptr[eax]
		 mov  word ptr[ebx], cx
		 ... (公加5次)
		 mov  eax, adrEntryPoint
		 jmp  eax

         偶得汇编很差，没用什么循环，10个字节，每次2个，共复制了5遍，（不要笑哦 -_-!）
	 */
	{
		int nAsmPos = 0;

		//push DllFilePahtAdr
		szBuf[nAsmPos++] = 0x68;
		*(DWORD*)&szBuf[nAsmPos] = (DWORD)pAllocNew;
		nAsmPos += 4;
		
		//mov eax, &LoadLibrary
		HMODULE hKernel = GetModuleHandle("kernel32.dll");
		if(hKernel == NULL)
		{
			return FALSE;
		}

		DWORD dwLoadLibFun = (DWORD)GetProcAddress(hKernel, "LoadLibraryA");
		if(dwLoadLibFun == 0)
		{
			return FALSE;
		}

		szBuf[nAsmPos++] = 0xB8;
		*(DWORD*)&szBuf[nAsmPos] = dwLoadLibFun;
		nAsmPos += 4;
		
		//call eax
		szBuf[nAsmPos++] = 0xFF;
		szBuf[nAsmPos++] = 0xD0;
	    
		//mov  eax, adrOldCode
		dwTemp = strlen(pszFileDll) + 1 + (DWORD)pAllocNew;
		szBuf[nAsmPos++] = 0xB8;
		*(DWORD*)&szBuf[nAsmPos] = dwTemp;
		nAsmPos += 4;

		//mov ebx, adrEntryPoint
		szBuf[nAsmPos++] = 0xBB;
		*(DWORD*)&szBuf[nAsmPos] = dwOldEntryPoint;
		nAsmPos += 4;

		//共拷贝2字节
		//mov cx, word ptr[eax]
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x8B;
		szBuf[nAsmPos++] = 0x08;
		//mov word ptr[ebx], cx
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x89;
		szBuf[nAsmPos++] = 0x0B;
		
		//共拷贝4字节
		//add eax, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC0;
		szBuf[nAsmPos++] = 0x02;
		//add ebx, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC3;
		szBuf[nAsmPos++] = 0x02;
		//mov cx, word ptr[eax]
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x8B;
		szBuf[nAsmPos++] = 0x08;
		//mov word ptr[ebx], cx
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x89;
		szBuf[nAsmPos++] = 0x0B;
		
		//共拷贝6字节
		//add eax, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC0;
		szBuf[nAsmPos++] = 0x02;
		//add ebx, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC3;
		szBuf[nAsmPos++] = 0x02;
		//mov cx, word ptr[eax]
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x8B;
		szBuf[nAsmPos++] = 0x08;
		//mov word ptr[ebx], cx
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x89;
		szBuf[nAsmPos++] = 0x0B;
		
		//共拷贝8字节
		//add eax, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC0;
		szBuf[nAsmPos++] = 0x02;
		//add ebx, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC3;
		szBuf[nAsmPos++] = 0x02;
		//mov cx, word ptr[eax]
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x8B;
		szBuf[nAsmPos++] = 0x08;
		//mov word ptr[ebx], cx
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x89;
		szBuf[nAsmPos++] = 0x0B;
		
		//共拷贝10字节
		//add eax, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC0;
		szBuf[nAsmPos++] = 0x02;
		//add ebx, 2
		szBuf[nAsmPos++] = 0x83;
		szBuf[nAsmPos++] = 0xC3;
		szBuf[nAsmPos++] = 0x02;
		//mov cx, word ptr[eax]
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x8B;
		szBuf[nAsmPos++] = 0x08;
		//mov word ptr[ebx], cx
		szBuf[nAsmPos++] = 0x66;
		szBuf[nAsmPos++] = 0x89;
		szBuf[nAsmPos++] = 0x0B;

		//mov eax, adrEntryPoing
		szBuf[nAsmPos++] = 0xB8;
		*(DWORD*)&szBuf[nAsmPos] = dwOldEntryPoint;
		nAsmPos += 4;
		
		//jmp eax
		szBuf[nAsmPos++] = 0xFF;
		szBuf[nAsmPos++] = 0xE0;

		if(!WriteProcessMemorySafe(hProcess, &pAllocNew[nPos], &szBuf[0], nAsmPos))
		{
			return FALSE;
		}
	}
	
	//将旧的入口代码 变成一个 jmp 跳到我们的代码中
	/*
	*  mov eax, adr
	*	jmp eax
	*/
	{
		DWORD dwAdr = 11 + strlen(pszFileDll) + (DWORD)&pAllocNew[0];
		int nPos = 0;

		szBuf[nPos++] = 0xB8;
		*(DWORD*)&szBuf[nPos] = dwAdr;
		nPos += 4;

		szBuf[nPos++] = 0xFF;
		szBuf[nPos++] = 0xE0;

		if(!WriteProcessMemorySafe(hProcess, (LPVOID)dwOldEntryPoint, &szBuf[0], nPos))
		{
			return FALSE;
		}

		VirtualProtectEx(hProcess, (LPVOID)dwOldEntryPoint, 10, PAGE_READWRITE, &dwTemp);
	}
	
	return TRUE;
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

LPVOID CHookProcess::AllocBufAfterBaseAdr(HANDLE hProcess, LPVOID pBase, int nSize)
{
	//在目标进程空间中分配一段内存
	LPBYTE pAllocNew = NULL;
	LPBYTE pBase1 = (LPBYTE)pBase;
	int    nCount = 100000;
	
	for(nCount = 0; nCount < 100000 && pAllocNew == NULL; nCount--)
	{
		pBase1 += 8*1024;
		pAllocNew = (LPBYTE)VirtualAllocEx(hProcess, pBase1, nSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}

	return pAllocNew;
}

BOOL CHookProcess::WriteProcessMemorySafe(HANDLE hProcess, LPVOID pDes, LPVOID pSrc, int nSize)
{
	DWORD dwOldProtect(0);
	DWORD dwWrite(0);
	try
	{
		if(!VirtualProtectEx(hProcess, pDes, nSize, PAGE_READWRITE, &dwOldProtect))
		{
			return FALSE;
		}
		
		if(!WriteProcessMemory(hProcess, pDes, pSrc, nSize, &dwWrite) ||
			dwWrite != (DWORD)nSize)
		{
			return FALSE;
		}
		
		VirtualProtectEx(hProcess, pDes, nSize, dwOldProtect, &dwOldProtect);
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CHookProcess::ReadProcessMemorySafe(HANDLE hProcess, LPCVOID lpBaseAdr, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberofBytesRead)
{
	DWORD dwOldProtect(0);
	DWORD dwWrite(0);
	try
	{
		if(!VirtualProtectEx(hProcess, (void*)lpBaseAdr, nSize, PAGE_READWRITE, &dwOldProtect))
		{
			return FALSE;
		}
		
		if(!ReadProcessMemory(hProcess, lpBaseAdr, lpBuffer, nSize, lpNumberofBytesRead))
		{
			return FALSE;
		}
		
		VirtualProtectEx(hProcess, (void*)lpBaseAdr, nSize, dwOldProtect, &dwOldProtect);
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}