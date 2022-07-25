#pragma once
// #include "c:\program files\microsoft visual studio 8\vc\atlmfc\include\afxcmn.h"


// tracewindow dialog


#include "..\codeelement.h"

class tracewindow : public CDialog
{
	DECLARE_DYNAMIC(tracewindow)

public:
	tracewindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~tracewindow();
    void TraceUpdate(string &tracenew);
    string traceold;
  

// Dialog Data
	enum { IDD = IDD_TRACEFORTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    CWnd* pParentis;

	DECLARE_MESSAGE_MAP()
public:
    CRichEditCtrl tracebox;
    UINT timer;
    virtual BOOL OnInitDialog();
protected:
    virtual void OnOK();
    virtual void OnCancel();
};

