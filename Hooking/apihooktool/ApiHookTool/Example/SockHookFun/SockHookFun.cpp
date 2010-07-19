// SockHookFun.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SockHookFun.h"
#include "winsock.h"
#include "mswsock.h"
#include "HookApiInterFace.h"
#include "stdio.h"

IHookHelper* g_pHelper = GetHookHelper();

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

SOCKET PASCAL my_accept (SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen)
{
	CFunHelper helper(&my_accept);
	g_pHelper->Log("accept()");

    return accept(s, addr, addrlen);
}

int PASCAL FAR my_bind (SOCKET s, const struct sockaddr FAR *addr, int namelen)
{
	CFunHelper helper(&my_bind);
	
    int nR = bind(s, addr, namelen);

    char szBuf[255];
    sprintf(szBuf, "%d bind()", nR);
    g_pHelper->Log(szBuf);
    
    return nR;
}

int PASCAL FAR my_closesocket (SOCKET s)
{
	CFunHelper helper(&my_closesocket);
	g_pHelper->Log("closesocket()");
	
    return closesocket(s);
}

int PASCAL FAR my_connect (SOCKET s, const struct sockaddr FAR *name, int namelen)
{
    CFunHelper helper(&my_connect);
    CFunHelper helper1(&my_WSAGetLastError);
    CFunHelper helper2(&my_WSASetLastError);
    CFunHelper helper3(&my_ntohs);

    int nR = connect(s, name, namelen);
    int nError = WSAGetLastError();

    const sockaddr_in* pAddr = (const sockaddr_in*)name;    
    char szBuf[255];
    
    sprintf(szBuf, "%d connect(%d, %p, %d)  [%d.%d.%d.%d  %d]  LastError = %d", nR, s, name, namelen,
        pAddr->sin_addr.S_un.S_un_b.s_b1,
        pAddr->sin_addr.S_un.S_un_b.s_b2,
        pAddr->sin_addr.S_un.S_un_b.s_b3,
        pAddr->sin_addr.S_un.S_un_b.s_b4,
        ntohs(pAddr->sin_port),
        nError);

    g_pHelper->Log(szBuf);
    
    WSASetLastError(nError);
    
    return nR;
}

int PASCAL FAR my_ioctlsocket (SOCKET s, long cmd, u_long FAR *argp)
{
	CFunHelper helper(&my_ioctlsocket);
	g_pHelper->Log("ioctlsocket()");
	
    return ioctlsocket(s, cmd, argp);
}

int PASCAL FAR my_getpeername (SOCKET s, struct sockaddr FAR *name,
                               int FAR * namelen)
{
	CFunHelper helper(&my_getpeername);
	g_pHelper->Log("getpeername()");
	
    return getpeername(s, name, namelen);
}

int PASCAL FAR my_getsockname (SOCKET s, struct sockaddr FAR *name,
                               int FAR * namelen)
{
	CFunHelper helper(&my_getsockname);
	g_pHelper->Log("getsockname()");
	
    return getsockname(s, name, namelen);
}

int PASCAL FAR my_getsockopt (SOCKET s, int level, int optname,
                           char FAR * optval, int FAR *optlen)
{
	CFunHelper helper(&my_getsockopt);
	g_pHelper->Log("getsockopt()");
	
    return getsockopt(s, level, optname, optval, optlen);
}

u_long PASCAL FAR my_htonl (u_long hostlong)
{
	CFunHelper helper(&my_htonl);
	g_pHelper->Log("htonl()");
	
    return htonl(hostlong);
}

u_short PASCAL FAR my_htons (u_short hostshort)
{
	CFunHelper helper(&my_htons);
	g_pHelper->Log("htons()");
	
    return htons(hostshort);
}

unsigned long PASCAL  FAR my_inet_addr (const char FAR * cp)
{
	CFunHelper helper(&my_inet_addr);
	
    unsigned long u = inet_addr(cp);

    char szBuf[255];
    sprintf(szBuf, "%d inet_addr(%s)", u, cp);
    g_pHelper->Log(szBuf);

    return u;
}

/////////////////////////////////
char* PASCAL FAR my_inet_ntoa (struct in_addr in)
{
	CFunHelper helper(&my_inet_ntoa);
	g_pHelper->Log("inet_ntoa()");
	
    return inet_ntoa(in);
}

int PASCAL FAR my_listen (SOCKET s, int backlog)
{
	CFunHelper helper(&my_listen);
	g_pHelper->Log("listen()");
	
    return listen(s, backlog);
}

u_long PASCAL FAR my_ntohl (u_long netlong)
{
	CFunHelper helper(&my_ntohl);
	g_pHelper->Log("ntohl()");
	
    return ntohl(netlong);
}

u_short PASCAL FAR my_ntohs (u_short netshort)
{
	CFunHelper helper(&my_ntohs);
	g_pHelper->Log("ntohs()");
	
    return ntohs(netshort);
}

int PASCAL FAR my_recv (SOCKET s, char FAR * buf, int len, int flags)
{
	CFunHelper helper(&my_recv);
	g_pHelper->Log("recv()");
	
    return recv(s, buf, len, flags);
}

int PASCAL FAR my_recvfrom (SOCKET s, char FAR * buf, int len, int flags,
                                            struct sockaddr FAR *from, int FAR * fromlen)
{
    CFunHelper helper(&my_recvfrom);
    CFunHelper helper1(&my_WSAGetLastError);
    CFunHelper helper2(&my_WSASetLastError);
    CFunHelper helper3(&my_ntohs);
    
    int nR = recvfrom(s, buf, len, flags, from, fromlen);
    int nError = WSAGetLastError();
    
    const sockaddr_in* pAddr = (const sockaddr_in*)from;    
    char szBuf[255];
    
    if(pAddr)
    {
        sprintf(szBuf, "%d recvfrom()  [%d.%d.%d.%d  %d]  LastError = %d",
        nR,
        pAddr->sin_addr.S_un.S_un_b.s_b1,
        pAddr->sin_addr.S_un.S_un_b.s_b2,
        pAddr->sin_addr.S_un.S_un_b.s_b3,
        pAddr->sin_addr.S_un.S_un_b.s_b4,
        ntohs(pAddr->sin_port),
        nError);
    }
    else
    {
        sprintf(szBuf, "%d recvfrom()", nR);
    }

    g_pHelper->Log(szBuf);
    
    WSASetLastError(nError);
    return nR;
}

int PASCAL FAR my_select (int nfds, fd_set FAR *readfds, fd_set FAR *writefds,
                       fd_set FAR *exceptfds, const struct timeval FAR *timeout)
{
	CFunHelper helper(&my_select);
	g_pHelper->Log("select()");
	
    return select(nfds, readfds, writefds, exceptfds, timeout);
}

int PASCAL FAR my_send (SOCKET s, const char FAR * buf, int len, int flags)
{
    CFunHelper helper(&my_send);
    CFunHelper helper1(&my_WSAGetLastError);
    CFunHelper helper2(&my_WSASetLastError);
    CFunHelper helper3(&my_ntohs);
    
    int nR = send(s, buf , len, flags);
    int nError = WSAGetLastError();
    
    char szBuf[255];
    sprintf(szBuf, "%d send(%d, %p, %d, %d)", nR, s, buf, len, flags);
	g_pHelper->Log(szBuf);
	
    WSASetLastError(nError);

    return nR;
}

int PASCAL FAR my_sendto (SOCKET s, const char FAR * buf, int len, int flags,
                          const struct sockaddr FAR *to, int tolen)
{
    CFunHelper helper(&my_sendto);
    CFunHelper helper1(&my_WSAGetLastError);
    CFunHelper helper2(&my_WSASetLastError);
    CFunHelper helper3(&my_ntohs);
    
    int nR = sendto(s, buf, len, flags, to, tolen);
    int nError = WSAGetLastError();
    
    const sockaddr_in* pAddr = (const sockaddr_in*)to;    
    char szBuf[255];
    
    sprintf(szBuf, "%d sendto(%d, %p, %d, %d, %p, %d)  [%d.%d.%d.%d  %d]  LastError = %d",
        nR, s, buf, len, flags, to, tolen,
        pAddr->sin_addr.S_un.S_un_b.s_b1,
        pAddr->sin_addr.S_un.S_un_b.s_b2,
        pAddr->sin_addr.S_un.S_un_b.s_b3,
        pAddr->sin_addr.S_un.S_un_b.s_b4,
        ntohs(pAddr->sin_port),
        nError);
    
    g_pHelper->Log(szBuf);
    
    WSASetLastError(nError);
    return nR;
}

int PASCAL FAR my_setsockopt (SOCKET s, int level, int optname,
                           const char FAR * optval, int optlen)
{
	CFunHelper helper(&my_setsockopt);
	g_pHelper->Log("setsockopt()");
	
    return setsockopt(s, level, optname, optval, optlen);
}

int PASCAL FAR my_shutdown (SOCKET s, int how)
{
	CFunHelper helper(&my_shutdown);
	g_pHelper->Log("shutdown()");
	
    return shutdown(s, how);
}

SOCKET PASCAL FAR my_socket (int af, int type, int protocol)
{
	CFunHelper helper(&my_socket);
	
    SOCKET s = socket(af, type, protocol);

    char szBuf[255];
    sprintf(szBuf, "%d socket(%d, %d, %d)", s, af, type, protocol);
    g_pHelper->Log(szBuf);

    return s;
}


struct hostent* PASCAL FAR my_gethostbyaddr(const char FAR * addr,
                                              int len, int type)
{
	CFunHelper helper(&my_gethostbyaddr);
	g_pHelper->Log("gethostbyaddr()");
	
    return gethostbyaddr(addr, len, type);
}

struct hostent* PASCAL FAR my_gethostbyname(const char FAR * name)
{
	CFunHelper helper(&my_gethostbyname);
	g_pHelper->Log("gethostbyname()");
	
    return gethostbyname(name);
}

int PASCAL FAR my_gethostname (char FAR * name, int namelen)
{
	CFunHelper helper(&my_gethostname);
	g_pHelper->Log("gethostname()");
	
    return gethostname(name, namelen);
}

struct servent* PASCAL FAR my_getservbyport(int port, const char FAR * proto)
{
	CFunHelper helper(&my_getservbyport);
	g_pHelper->Log("getservbyport()");
	
    return getservbyport(port, proto);
}

struct servent* PASCAL FAR my_getservbyname(const char FAR * name,
                                              const char FAR * proto)
{
	CFunHelper helper(&my_getservbyname);
	g_pHelper->Log("getservbyname()");
	
    return getservbyname(name, proto);
}

struct protoent* PASCAL FAR my_getprotobynumber(int proto)
{
	CFunHelper helper(&my_getprotobynumber);
	g_pHelper->Log("getprotobynumber()");
	
    return getprotobynumber(proto);
}

struct protoent* PASCAL FAR my_getprotobyname(const char FAR * name)
{
	CFunHelper helper(&my_getprotobyname);
	g_pHelper->Log("getprotobyname()");
	
    return getprotobyname(name);
}

/* Microsoft Windows Extension function prototypes */

int PASCAL FAR my_WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData)
{
	CFunHelper helper(&my_WSAStartup);
	
    int nR = WSAStartup(wVersionRequired, lpWSAData);

    char szBuf[255];
    sprintf(szBuf, "%d WSAStartup()", nR);
    g_pHelper->Log(szBuf);

    return nR;
}

int PASCAL FAR my_WSACleanup(void)
{
	CFunHelper helper(&my_WSACleanup);
	g_pHelper->Log("WSACleanup()");
	
    return WSACleanup();
}

void PASCAL FAR my_WSASetLastError(int iError)
{
	CFunHelper helper(&my_WSASetLastError);
	g_pHelper->Log("WSASetLastError()");
	
    WSASetLastError(iError);	
}

int PASCAL FAR my_WSAGetLastError(void)
{
	CFunHelper helper(&my_WSAGetLastError);
	
    int nR = WSAGetLastError();

    char szBuf[255];
    sprintf(szBuf, "%d WSAGetLastError()", nR);
    g_pHelper->Log(szBuf);
    
    return nR;
}

BOOL PASCAL FAR my_WSAIsBlocking(void)
{
	CFunHelper helper(&my_WSAIsBlocking);
	g_pHelper->Log("my_WSAIsBlocking()");
	
    return WSAIsBlocking();
}

int PASCAL FAR my_WSAUnhookBlockingHook(void)
{
	CFunHelper helper(&my_WSAUnhookBlockingHook);
	g_pHelper->Log("WSAUnhookBlockingHook()");
	
    return WSAUnhookBlockingHook();
}

FARPROC PASCAL FAR my_WSASetBlockingHook(FARPROC lpBlockFunc)
{
	CFunHelper helper(&my_WSASetBlockingHook);
	g_pHelper->Log("WSASetBlockingHook()");
	
    return WSASetBlockingHook(lpBlockFunc);
}

int PASCAL FAR my_WSACancelBlockingCall(void)
{
	CFunHelper helper(&my_WSACancelBlockingCall);
	g_pHelper->Log("WSACancelBlockingCall()");
	
    return WSACancelBlockingCall();
}

HANDLE PASCAL FAR my_WSAAsyncGetServByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name,
                                        const char FAR * proto,
                                        char FAR * buf, int buflen)
{
	CFunHelper helper(&my_WSAAsyncGetServByName);
	g_pHelper->Log("WSAAsyncGetServByName()");
	
    return WSAAsyncGetServByName(hWnd, wMsg, name, proto, buf, buflen);
}

HANDLE PASCAL FAR my_WSAAsyncGetServByPort(HWND hWnd, u_int wMsg, int port,
                                        const char FAR * proto, char FAR * buf,
                                        int buflen)
{
	CFunHelper helper(&my_WSAAsyncGetServByPort);
	g_pHelper->Log("WSAAsyncGetServByPort()");
	
    return WSAAsyncGetServByPort(hWnd, wMsg, port, proto, buf, buflen);
}

HANDLE PASCAL FAR my_WSAAsyncGetProtoByName(HWND hWnd, u_int wMsg,
                                         const char FAR * name, char FAR * buf,
                                         int buflen)
{
	CFunHelper helper(&my_WSAAsyncGetProtoByName);
	g_pHelper->Log("WSAAsyncGetProtoByName()");
	
    return WSAAsyncGetProtoByName(hWnd, wMsg, name, buf, buflen);
}

HANDLE PASCAL FAR my_WSAAsyncGetProtoByNumber(HWND hWnd, u_int wMsg,
                                           int number, char FAR * buf,
                                           int buflen)
{
	CFunHelper helper(&my_WSAAsyncGetProtoByNumber);
	g_pHelper->Log("WSAAsyncGetProtoByNumber()");
	
    return WSAAsyncGetProtoByNumber(hWnd, wMsg, number, buf, buflen);
}

HANDLE PASCAL FAR my_WSAAsyncGetHostByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name, char FAR * buf,
                                        int buflen)
{
	CFunHelper helper(&my_WSAAsyncGetHostByName);
	g_pHelper->Log("WSAAsyncGetHostByName()");
	
    return WSAAsyncGetHostByName(hWnd, wMsg, name, buf, buflen);
}

HANDLE PASCAL FAR my_WSAAsyncGetHostByAddr(HWND hWnd, u_int wMsg,
                                        const char FAR * addr, int len, int type,
                                        char FAR * buf, int buflen)
{
	CFunHelper helper(&my_WSAAsyncGetHostByAddr);
	g_pHelper->Log("WSAAsyncGetHostByAddr()");
	
    return WSAAsyncGetHostByAddr(hWnd, wMsg, addr, len, type, buf, buflen);
}

int PASCAL FAR my_WSACancelAsyncRequest(HANDLE hAsyncTaskHandle)
{
	CFunHelper helper(&my_WSACancelAsyncRequest);
	g_pHelper->Log("WSACancelAsyncRequest()");
	
    return WSACancelAsyncRequest(hAsyncTaskHandle);
}

int PASCAL FAR my_WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg,
                               long lEvent)
{
	CFunHelper helper(&my_WSAAsyncSelect);
	g_pHelper->Log("WSAAsyncSelect()");
	
    return WSAAsyncSelect(s, hWnd, wMsg, lEvent);
}

int PASCAL FAR my_WSARecvEx (SOCKET s, char FAR * buf, int len, int FAR *flags)
{
	CFunHelper helper(&my_WSARecvEx);
	g_pHelper->Log("WSARecvEx()");
	
    return WSARecvEx(s, buf, len, flags);
}

INT PASCAL my_EnumProtocolsA (LPINT lpiProtocols,
                              LPVOID lpProtocolBuffer,
                              LPDWORD lpdwBufferLength)
{
	CFunHelper helper(&my_EnumProtocolsA);
	g_pHelper->Log("EnumProtocolsA()");
	
    return EnumProtocolsA(lpiProtocols, lpProtocolBuffer, lpdwBufferLength);
}

INT PASCAL  my_EnumProtocolsW (
                                    IN     LPINT           lpiProtocols,
                                    IN OUT LPVOID          lpProtocolBuffer,
                                    IN OUT LPDWORD         lpdwBufferLength)
{
	CFunHelper helper(&my_EnumProtocolsW);
	g_pHelper->Log("EnumProtocolsW()");
	
    return EnumProtocolsW(lpiProtocols, lpProtocolBuffer, lpdwBufferLength);
}

INT PASCAL  my_GetAddressByNameA (
                                       IN     DWORD                dwNameSpace,
                                       IN     LPGUID               lpServiceType,
                                       IN     LPSTR                lpServiceName OPTIONAL,
                                       IN     LPINT                lpiProtocols OPTIONAL,
                                       IN     DWORD                dwResolution,
                                       IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo OPTIONAL,
                                       IN OUT LPVOID               lpCsaddrBuffer,
                                       IN OUT LPDWORD              lpdwBufferLength,
                                       IN OUT LPSTR                lpAliasBuffer OPTIONAL,
                                       IN OUT LPDWORD              lpdwAliasBufferLength OPTIONAL)
{
	CFunHelper helper(&my_GetAddressByNameA);
	g_pHelper->Log("GetAddressByNameA()");
	
    return GetAddressByNameA(dwNameSpace, lpServiceType, lpServiceName,
		                     lpiProtocols, dwResolution, lpServiceAsyncInfo,
							 lpCsaddrBuffer, lpdwBufferLength, lpAliasBuffer,lpdwAliasBufferLength);
}

INT PASCAL  my_GetAddressByNameW (
                                       IN     DWORD                dwNameSpace,
                                       IN     LPGUID               lpServiceType,
                                       IN     LPWSTR               lpServiceName OPTIONAL,
                                       IN     LPINT                lpiProtocols OPTIONAL,
                                       IN     DWORD                dwResolution,
                                       IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo OPTIONAL,
                                       IN OUT LPVOID               lpCsaddrBuffer,
                                       IN OUT LPDWORD              lpdwBufferLength,
                                       IN OUT LPWSTR               lpAliasBuffer OPTIONAL,
                                       IN OUT LPDWORD              lpdwAliasBufferLength OPTIONAL)
{
	CFunHelper helper(&my_GetAddressByNameW);
	g_pHelper->Log("GetAddressByNameW()");
	
    return GetAddressByNameW(dwNameSpace, lpServiceType, lpServiceName, lpiProtocols,
		                     dwResolution, lpServiceAsyncInfo, lpCsaddrBuffer, lpdwBufferLength,
							 lpAliasBuffer, lpdwAliasBufferLength);
}

INT PASCAL  my_GetTypeByNameA (
                                    IN     LPSTR         lpServiceName,
                                    IN OUT LPGUID          lpServiceType)
{
	CFunHelper helper(&my_GetTypeByNameA);
	g_pHelper->Log("GetTypeByNameA()");
	
    return GetTypeByNameA(lpServiceName, lpServiceType);
}

INT PASCAL  my_GetTypeByNameW (
                IN     LPWSTR         lpServiceName,
                IN OUT LPGUID          lpServiceType)
{
	CFunHelper helper(&my_GetTypeByNameW);
	g_pHelper->Log("GetTypeByNameW()");
	
    return GetTypeByNameW(lpServiceName, lpServiceType);
}

INT PASCAL  my_GetNameByTypeA (
                                    IN     LPGUID          lpServiceType,
                                    IN OUT LPSTR         lpServiceName,
                                    IN     DWORD           dwNameLength)
{
	CFunHelper helper(&my_GetNameByTypeA);
	g_pHelper->Log("GetNameByTypeA()");
	
    return GetNameByTypeA(lpServiceType, lpServiceName, dwNameLength);
}

INT PASCAL  my_GetNameByTypeW (
                                    IN     LPGUID          lpServiceType,
                                    IN OUT LPWSTR         lpServiceName,
                                    IN     DWORD           dwNameLength)
{
	CFunHelper helper(&my_GetNameByTypeW);
	g_pHelper->Log("GetNameByTypeW()");
	
    return GetNameByTypeW(lpServiceType, lpServiceName, dwNameLength);
}

INT PASCAL  my_SetServiceA (
                                 IN     DWORD                dwNameSpace,
                                 IN     DWORD                dwOperation,
                                 IN     DWORD                dwFlags,
                                 IN     LPSERVICE_INFOA      lpServiceInfo,
                                 IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo,
                                 IN OUT LPDWORD              lpdwStatusFlags)
{
	CFunHelper helper(&my_SetServiceA);
	g_pHelper->Log("SetServiceA()");
	
    return SetServiceA(dwNameSpace, dwOperation,
		               dwFlags, lpServiceInfo, lpServiceAsyncInfo,
					   lpdwStatusFlags);
}

INT PASCAL  my_SetServiceW (
                                 IN     DWORD                dwNameSpace,
                                 IN     DWORD                dwOperation,
                                 IN     DWORD                dwFlags,
                                 IN     LPSERVICE_INFOW      lpServiceInfo,
                                 IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo,
                                 IN OUT LPDWORD              lpdwStatusFlags)
{
	CFunHelper helper(&my_SetServiceW);
	g_pHelper->Log("SetServiceW()");
	
    return SetServiceW(dwNameSpace, dwOperation, dwFlags, lpServiceInfo,
		               lpServiceAsyncInfo, lpdwStatusFlags);
}

INT PASCAL  my_GetServiceA (
                                 IN     DWORD                dwNameSpace,
                                 IN     LPGUID               lpGuid,
                                 IN     LPSTR              lpServiceName,
                                 IN     DWORD                dwProperties,
                                 IN OUT LPVOID               lpBuffer,
                                 IN OUT LPDWORD              lpdwBufferSize,
                                 IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo)
{
	CFunHelper helper(&my_GetServiceA);
	g_pHelper->Log("GetServiceA()");
	
    return GetServiceA(dwNameSpace, lpGuid, lpServiceName, dwProperties,
		               lpBuffer, lpdwBufferSize, lpServiceAsyncInfo);
}

INT PASCAL  my_GetServiceW (
                                 IN     DWORD                dwNameSpace,
                                 IN     LPGUID               lpGuid,
                                 IN     LPWSTR              lpServiceName,
                                 IN     DWORD                dwProperties,
                                 IN OUT LPVOID               lpBuffer,
                                 IN OUT LPDWORD              lpdwBufferSize,
                                 IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo)
{
	CFunHelper helper(&my_GetServiceW);
	g_pHelper->Log("GetServiceW()");
	
    return GetServiceW(dwNameSpace, lpGuid, lpServiceName, dwProperties, lpBuffer,
		               lpdwBufferSize, lpServiceAsyncInfo);
}

void PASCAL ShowMe(HWND hParant)
{
    MessageBox(hParant, "Hello World!", "*_*", MB_OK);
}

void PASCAL GetDllInfo (DLL_INFO& info)
{
    strcpy(info.szIntroduce, "this is a simple test\r\nthanks for help of my friend Neville\r\nJYan 2004.5.25");
    strcpy(info.szHomePage, "NULL");
    strcpy(info.szEmail, "yj_3000@163.com");
    strcpy(info.szAuthor, "JYan");
    info.pCallBack = &ShowMe;
	info.hBpSign = ::LoadBitmap(GetModuleHandle("SockHookFun.dll"), MAKEINTRESOURCE(IDB_SIGN));
}
