// _Zen_Soft_Forth.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// Zen_Soft_ForthApp:
// See _Zen_Soft_Forth.cpp for the implementation of this class
//

class Zen_Soft_ForthApp : public CWinApp
{
public:
	Zen_Soft_ForthApp();

// Overrides
	public:
	virtual BOOL InitInstance();
    virtual BOOL OnIdle(LONG lCount);

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Zen_Soft_ForthApp theApp;