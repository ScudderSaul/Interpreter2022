// _Zen_Soft_Forth.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "_Zen_Soft_Forth.h"
#include "_Zen_Soft_ForthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

forthinformation *pnfrth;

// Zen_Soft_ForthApp

BEGIN_MESSAGE_MAP(Zen_Soft_ForthApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Zen_Soft_ForthApp construction

Zen_Soft_ForthApp::Zen_Soft_ForthApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Zen_Soft_ForthApp object

Zen_Soft_ForthApp theApp;

Zen_Soft_ForthDlg *pzsfdlg = NULL;
Language lang;


// Zen_Soft_ForthApp initialization

BOOL Zen_Soft_ForthApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();
    AfxInitRichEdit2();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("_Zen_Soft Forth"));

    lang.SetStringOut();

	Zen_Soft_ForthDlg dlg;
	m_pMainWnd = &dlg;
    pzsfdlg = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL Zen_Soft_ForthApp::OnIdle(LONG lCount)
{
  BOOL bBaseIdle = CWinApp::OnIdle(lCount);
  BOOL bMoreIdle = TRUE;

  if((lCount % 1000) == 0)
  {
    if(pzsfdlg != NULL)
    {
   //     pzsfdlg->UpdateOutput();
    }
  }
  if ((lCount % 100000) == 0)
	{
       bMoreIdle = bBaseIdle;
	}

	return bMoreIdle;
}

