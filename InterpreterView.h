// InterpreterView.h : interface of the CInterpreterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERPRETERVIEW_H__3DF4CD20_E76C_11D1_BC33_00AA00098E79__INCLUDED_)
#define AFX_INTERPRETERVIEW_H__3DF4CD20_E76C_11D1_BC33_00AA00098E79__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0602 // _WIN32_WINNT_WIN8 
//#define  NTDDI_VERSION 0x06020000  // NTDDI_WIN8 
//#define WINVER 0x0602 // _WIN32_WINNT_WIN8 
#endif

class CInterpreterView : public CView
{
protected: // create from serialization only
	CInterpreterView();
	DECLARE_DYNCREATE(CInterpreterView)

// Attributes
public:
	CInterpreterDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpreterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInterpreterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CInterpreterView)
	afx_msg void OnSourceGetsourcefile();
	afx_msg void OnSourceInterpretfile();
	afx_msg void OnSourceWriteoutput();
	afx_msg void OnSourceSetoutputfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in InterpreterView.cpp
inline CInterpreterDoc* CInterpreterView::GetDocument()
   { return (CInterpreterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETERVIEW_H__3DF4CD20_E76C_11D1_BC33_00AA00098E79__INCLUDED_)
