; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInterpreterView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Interpreter.h"
LastPage=0

ClassCount=6
Class1=CInterpreterApp
Class2=CInterpreterDoc
Class3=CInterpreterView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=CG_IDR_POPUP_INTERPRETER_VIEW
Resource3=IDR_INTERPTYPE
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_ABOUTBOX

[CLS:CInterpreterApp]
Type=0
HeaderFile=Interpreter.h
ImplementationFile=Interpreter.cpp
Filter=N

[CLS:CInterpreterDoc]
Type=0
HeaderFile=InterpreterDoc.h
ImplementationFile=InterpreterDoc.cpp
Filter=N

[CLS:CInterpreterView]
Type=0
HeaderFile=InterpreterView.h
ImplementationFile=InterpreterView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_SOURCE_SETOUTPUTFILE

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=Interpreter.cpp
ImplementationFile=Interpreter.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_INTERPTYPE]
Type=1
Class=CInterpreterView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_WINDOW_SPLIT
Command22=ID_SOURCE_GETSOURCEFILE
Command23=ID_SOURCE_INTERPRETFILE
Command24=ID_SOURCE_WRITEOUTPUT
Command25=ID_SOURCE_SETOUTPUTFILE
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:CG_IDR_POPUP_INTERPRETER_VIEW]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
CommandCount=3

