; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CApiHookTestDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ApiHookTest.h"

ClassCount=5
Class1=CApiHookTestApp
Class2=CApiHookTestDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_APIHOOKTEST_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CDllInfoDlg
Class5=CMyStatic
Resource4=IDD_DLL_INFO_DLG

[CLS:CApiHookTestApp]
Type=0
HeaderFile=ApiHookTest.h
ImplementationFile=ApiHookTest.cpp
Filter=N

[CLS:CApiHookTestDlg]
Type=0
HeaderFile=ApiHookTestDlg.h
ImplementationFile=ApiHookTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CApiHookTestDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ApiHookTestDlg.h
ImplementationFile=ApiHookTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_APIHOOKTEST_DIALOG]
Type=1
Class=CApiHookTestDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_EXEFILE,edit,1350631552
Control3=IDC_SELECTEXE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHANGEHOOKAPI,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LOGFILE,edit,1350631552
Control8=IDC_SELECTLOG,button,1342242816
Control9=IDC_GO,button,1342242816
Control10=IDC_STATIC,static,1342177296
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EXECMD,edit,1350631552
Control13=IDC_VIEWHOOKDLLINFO,button,1342242816
Control14=IDC_VIEWLOG,button,1342242816

[DLG:IDD_DLL_INFO_DLG]
Type=1
Class=CDllInfoDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_DLLS,combobox,1344340226
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_VIEW_EXPORT_INFO,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_INTRODUCE,edit,1342249092
Control10=IDC_SHOWME,button,1342242816
Control11=IDC_FRAME,static,1342177284
Control12=IDC_HOMEPAGE,edit,1342244992
Control13=IDC_EMAIL,edit,1342244992
Control14=IDC_AUTH,edit,1342244992

[CLS:CDllInfoDlg]
Type=0
HeaderFile=DllInfoDlg.h
ImplementationFile=DllInfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDllInfoDlg
VirtualFilter=dWC

[CLS:CMyStatic]
Type=0
HeaderFile=MyStatic.h
ImplementationFile=MyStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CMyStatic

