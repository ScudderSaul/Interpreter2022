// Interpreter.h : main header file for the INTERPRETER application
//

#if !defined(AFX_INTERPRETER_H__3DF4CD16_E76C_11D1_BC33_00AA00098E79__INCLUDED_)
#define AFX_INTERPRETER_H__3DF4CD16_E76C_11D1_BC33_00AA00098E79__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0602 // _WIN32_WINNT_WIN8 
//#define  NTDDI_VERSION 0x06020000  // NTDDI_WIN8 
//#define WINVER 0x0602 // _WIN32_WINNT_WIN8 
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterpreterApp:
// See Interpreter.cpp for the implementation of this class
//

class CInterpreterApp : public CWinApp
{
public:
	virtual BOOL OnIdle(LONG lCount);
	CInterpreterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpreterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterpreterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETER_H__3DF4CD16_E76C_11D1_BC33_00AA00098E79__INCLUDED_)
