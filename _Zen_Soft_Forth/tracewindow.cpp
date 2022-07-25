// tracewindow.cpp : implementation file
//

#include "stdafx.h"
#include "_Zen_Soft_Forth.h"
#include "_Zen_Soft_ForthDlg.h"
#include "tracewindow.h"


extern Language lang;

// tracewindow dialog

IMPLEMENT_DYNAMIC(tracewindow, CDialog)

tracewindow::tracewindow(CWnd* pParent /*=NULL*/)
	: CDialog(tracewindow::IDD, pParent)
{
  pParentis = pParent;
  Create( IDD_TRACEFORTH, this); 
  traceold.clear();
}

tracewindow::~tracewindow()
{
    Zen_Soft_ForthDlg * zsfd = (Zen_Soft_ForthDlg *) pParentis;
    zsfd->CloseOfTrace();
}

void tracewindow::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TRACEBOX, tracebox);
}


BEGIN_MESSAGE_MAP(tracewindow, CDialog)
END_MESSAGE_MAP()


// tracewindow message handlers

void tracewindow::TraceUpdate(string & tracenew)
{
    traceold += tracenew;
    tracebox.SetReadOnly(FALSE);
    tracebox.SetWindowText(traceold.c_str());
    tracebox.SetModify();
    tracebox.SetReadOnly(TRUE);
    this->Invalidate();
}

BOOL tracewindow::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void tracewindow::OnOK()
{
    // TODO: Add your specialized code here and/or call the base class

    Zen_Soft_ForthDlg * zsfd = (Zen_Soft_ForthDlg *) pParentis;
    zsfd->CloseOfTrace();
    this->DestroyWindow();
}

void tracewindow::OnCancel()
{
    // TODO: Add your specialized code here and/or call the base class
      Zen_Soft_ForthDlg * zsfd = (Zen_Soft_ForthDlg *) pParentis;
    zsfd->CloseOfTrace();
      this->DestroyWindow();
}
