#ifndef _HOOK_SOCK_FUNS_H
#define _HOOK_SOCK_FUNS_H

#include "winsock2.h"
#include "Nspapi.h"


SOCKET PASCAL FAR my_accept (SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen);
int PASCAL FAR my_bind (SOCKET s, const struct sockaddr FAR *addr, int namelen);

int PASCAL FAR my_closesocket (SOCKET s);

int PASCAL FAR my_connect (SOCKET s, const struct sockaddr FAR *name, int namelen);

int PASCAL FAR my_ioctlsocket (SOCKET s, long cmd, u_long FAR *argp);

int PASCAL FAR my_getpeername (SOCKET s, struct sockaddr FAR *name,
                            int FAR * namelen);

int PASCAL FAR my_getsockname (SOCKET s, struct sockaddr FAR *name,
                            int FAR * namelen);

int PASCAL FAR my_getsockopt (SOCKET s, int level, int optname,
                           char FAR * optval, int FAR *optlen);

u_long PASCAL FAR my_htonl (u_long hostlong);

u_short PASCAL FAR my_htons (u_short hostshort);

unsigned long PASCAL  PASCAL FAR my_inet_addr (const char FAR * cp);

char* PASCAL FAR my_inet_ntoa (struct in_addr in);

int PASCAL FAR my_listen (SOCKET s, int backlog);

u_long PASCAL FAR my_ntohl (u_long netlong);

u_short PASCAL FAR my_ntohs (u_short netshort);

int PASCAL FAR my_recv (SOCKET s, char FAR * buf, int len, int flags);

int PASCAL FAR my_recvfrom (SOCKET s, char FAR * buf, int len, int flags,
                         struct sockaddr FAR *from, int FAR * fromlen);

int PASCAL FAR my_select (int nfds, fd_set FAR *readfds, fd_set FAR *writefds,
                       fd_set FAR *exceptfds, const struct timeval FAR *timeout);

int PASCAL FAR my_send (SOCKET s, const char FAR * buf, int len, int flags);

int PASCAL FAR my_sendto (SOCKET s, const char FAR * buf, int len, int flags,
                       const struct sockaddr FAR *to, int tolen);

int PASCAL FAR my_setsockopt (SOCKET s, int level, int optname,
                           const char FAR * optval, int optlen);

int PASCAL FAR my_shutdown (SOCKET s, int how);

SOCKET PASCAL FAR my_socket (int af, int type, int protocol);


struct hostent* PASCAL FAR my_gethostbyaddr(const char FAR * addr,
                                              int len, int type);

struct hostent* PASCAL FAR my_gethostbyname(const char FAR * name);

int PASCAL FAR my_gethostname (char FAR * name, int namelen);

struct servent* PASCAL FAR my_getservbyport(int port, const char FAR * proto);

struct servent* PASCAL FAR my_getservbyname(const char FAR * name,
                                              const char FAR * proto);

struct protoent* PASCAL FAR my_getprotobynumber(int proto);

struct protoent* PASCAL FAR my_getprotobyname(const char FAR * name);

/* Microsoft Windows Extension function prototypes */

int PASCAL FAR my_WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData);

int PASCAL FAR my_WSACleanup(void);

void PASCAL FAR my_WSASetLastError(int iError);

int PASCAL FAR my_WSAGetLastError(void);

BOOL PASCAL FAR my_WSAIsBlocking(void);

int PASCAL FAR my_WSAUnhookBlockingHook(void);

FARPROC PASCAL FAR my_WSASetBlockingHook(FARPROC lpBlockFunc);

int PASCAL FAR my_WSACancelBlockingCall(void);

HANDLE PASCAL FAR my_WSAAsyncGetServByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name,
                                        const char FAR * proto,
                                        char FAR * buf, int buflen);

HANDLE PASCAL FAR my_WSAAsyncGetServByPort(HWND hWnd, u_int wMsg, int port,
                                        const char FAR * proto, char FAR * buf,
                                        int buflen);

HANDLE PASCAL FAR my_WSAAsyncGetProtoByName(HWND hWnd, u_int wMsg,
                                         const char FAR * name, char FAR * buf,
                                         int buflen);

HANDLE PASCAL FAR my_WSAAsyncGetProtoByNumber(HWND hWnd, u_int wMsg,
                                           int number, char FAR * buf,
                                           int buflen);

HANDLE PASCAL FAR my_WSAAsyncGetHostByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name, char FAR * buf,
                                        int buflen);

HANDLE PASCAL FAR my_WSAAsyncGetHostByAddr(HWND hWnd, u_int wMsg,
                                        const char FAR * addr, int len, int type,
                                        char FAR * buf, int buflen);

int PASCAL FAR my_WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);

int PASCAL FAR my_WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg,
                               long lEvent);

int PASCAL FAR my_WSARecvEx (SOCKET s, char FAR * buf, int len, int FAR *flags);

INT PASCAL my_EnumProtocolsA (
    IN     LPINT           lpiProtocols,
    IN OUT LPVOID          lpProtocolBuffer,
    IN OUT LPDWORD         lpdwBufferLength);
INT PASCAL my_EnumProtocolsW (
    IN     LPINT           lpiProtocols,
    IN OUT LPVOID          lpProtocolBuffer,
    IN OUT LPDWORD         lpdwBufferLength
    );

INT PASCAL my_GetAddressByNameA (
    IN     DWORD                dwNameSpace,
    IN     LPGUID               lpServiceType,
    IN     LPSTR                lpServiceName OPTIONAL,
    IN     LPINT                lpiProtocols OPTIONAL,
    IN     DWORD                dwResolution,
    IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo OPTIONAL,
    IN OUT LPVOID               lpCsaddrBuffer,
    IN OUT LPDWORD              lpdwBufferLength,
    IN OUT LPSTR                lpAliasBuffer OPTIONAL,
    IN OUT LPDWORD              lpdwAliasBufferLength OPTIONAL);

INT PASCAL my_GetAddressByNameW (
    IN     DWORD                dwNameSpace,
    IN     LPGUID               lpServiceType,
    IN     LPWSTR              lpServiceName OPTIONAL,
    IN     LPINT                lpiProtocols OPTIONAL,
    IN     DWORD                dwResolution,
    IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo OPTIONAL,
    IN OUT LPVOID               lpCsaddrBuffer,
    IN OUT LPDWORD              lpdwBufferLength,
    IN OUT LPWSTR              lpAliasBuffer OPTIONAL,
    IN OUT LPDWORD              lpdwAliasBufferLength OPTIONAL);

INT PASCAL my_GetTypeByNameA (
    IN     LPSTR         lpServiceName,
    IN OUT LPGUID          lpServiceType);
INT PASCAL my_GetTypeByNameW (
    IN     LPWSTR         lpServiceName,
    IN OUT LPGUID          lpServiceType);

INT PASCAL my_GetNameByTypeA (
    IN     LPGUID          lpServiceType,
    IN OUT LPSTR         lpServiceName,
    IN     DWORD           dwNameLength);

INT PASCAL my_GetNameByTypeW (
    IN     LPGUID          lpServiceType,
    IN OUT LPWSTR         lpServiceName,
    IN     DWORD           dwNameLength);

INT PASCAL my_SetServiceA (
    IN     DWORD                dwNameSpace,
    IN     DWORD                dwOperation,
    IN     DWORD                dwFlags,
    IN     LPSERVICE_INFOA      lpServiceInfo,
    IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo,
    IN OUT LPDWORD              lpdwStatusFlags);

INT PASCAL my_SetServiceW (
    IN     DWORD                dwNameSpace,
    IN     DWORD                dwOperation,
    IN     DWORD                dwFlags,
    IN     LPSERVICE_INFOW      lpServiceInfo,
    IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo,
    IN OUT LPDWORD              lpdwStatusFlags);

INT PASCAL my_GetServiceA (
    IN     DWORD                dwNameSpace,
    IN     LPGUID               lpGuid,
    IN     LPSTR              lpServiceName,
    IN     DWORD                dwProperties,
    IN OUT LPVOID               lpBuffer,
    IN OUT LPDWORD              lpdwBufferSize,
    IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo);

INT PASCAL my_GetServiceW (
    IN     DWORD                dwNameSpace,
    IN     LPGUID               lpGuid,
    IN     LPWSTR              lpServiceName,
    IN     DWORD                dwProperties,
    IN OUT LPVOID               lpBuffer,
    IN OUT LPDWORD              lpdwBufferSize,
    IN     LPSERVICE_ASYNC_INFO lpServiceAsyncInfo);


#endif