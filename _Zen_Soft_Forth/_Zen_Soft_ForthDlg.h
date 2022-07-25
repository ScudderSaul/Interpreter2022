// _Zen_Soft_ForthDlg.h : header file
//

#pragma once
//#include "c:\program files\microsoft visual studio 8\vc\atlmfc\include\afxcmn.h"
#include "..\codeelement.h"
#include "tracewindow.h"
#include "forthinformation.h"
#include "ParserInput.h"
//#include "k:\program files\microsoft visual studio 8\vc\atlmfc\include\afxcmn.h"
//#include "c:\program files\microsoft visual studio 8\vc\atlmfc\include\afxwin.h"


// Zen_Soft_ForthDlg dialog
class Zen_Soft_ForthDlg : public CDialog
{
// Construction
public:
	Zen_Soft_ForthDlg(CWnd* pParent = NULL);	// standard constructor
    ~Zen_Soft_ForthDlg();
    void UpdateOutput();
    void CloseOfTrace();

// Dialog Data
	enum { IDD = IDD__ZEN_SOFT_FORTH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
    string istr;
    string out_history;

    string in_history;
    string in_now;
    stringstream in_parse;
    string in_parsestr;
    string input_name;
    tracewindow *pndlg;
    ParseFeeder lfeed;
    bool started;
    UINT timer;
    MSGFILTER *pMsgFilter;
    bool shiftflag;
    
    void UnsetTraceRecord()
    {
       pndlg = NULL;
    }

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeInputArea();
    afx_msg void OnBnClickedInterpret();
    CRichEditCtrl buffer;
    CRichEditCtrl output;
    afx_msg void OnEnChangeOutput();
    afx_msg void OnBnClickedLoadfile();
    afx_msg void OnBnClickedOpentrace();
    afx_msg void OnBnClickedShowinfo();
    afx_msg void OnBnClickedSavefile();
    afx_msg void OnBnClickedSaveOutput();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedHistory();
    afx_msg void OnBnClickedForgetsession();
    CRichEditCtrl history;
 
    afx_msg void OnEnMsgfilterInputArea(NMHDR *pNMHDR, LRESULT *pResult);
};
