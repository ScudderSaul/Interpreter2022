// forthinformation.cpp : implementation file
//

#include "stdafx.h"
#include "_Zen_Soft_Forth.h"
#include "forthinformation.h"
#include <afxhtml.h>



// forthinformation dialog

IMPLEMENT_DYNCREATE(forthinformation, CDHtmlDialog)

forthinformation::forthinformation(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(forthinformation::IDD, 0, pParent)
{
   Create( IDD_FORTHINFO, this);
}

forthinformation::~forthinformation()
{

}

void forthinformation::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL forthinformation::OnInitDialog()
{
    SetHostFlags(DOCHOSTUIFLAG_FLAT_SCROLLBAR);
	CDHtmlDialog::OnInitDialog();
    LoadFromResource(forthinformation::IDH);
//    LoadFromResource(IDB_BITMAP1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(forthinformation, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(forthinformation)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// forthinformation message handlers

HRESULT forthinformation::OnButtonOK(IHTMLElement* /*pElement*/)
{
	 this->DestroyWindow();
	return S_OK;
}

HRESULT forthinformation::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	 this->DestroyWindow();
	return S_OK;
}
