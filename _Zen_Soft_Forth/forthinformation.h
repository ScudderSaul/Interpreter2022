#pragma once

#ifdef _WIN32_WCE
#error CDHtmlDialog is not supported for Windows CE.
#endif 

// forthinformation dialog

class forthinformation : public CDHtmlDialog
{
	DECLARE_DYNCREATE(forthinformation)

public:
	forthinformation(CWnd* pParent = NULL);   // standard constructor
	virtual ~forthinformation();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_FORTHINFO, IDH = IDR_HTML_FORTHINFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
