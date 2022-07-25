// InterpreterView.cpp : implementation of the CInterpreterView class
//

#include "stdafx.h"
#include "Interpreter.h"

#include "InterpreterDoc.h"
#include "InterpreterView.h"
#include "resource.h"

#pragma warning(disable: 4786)

#include <vector>
#include <string>

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterpreterView

IMPLEMENT_DYNCREATE(CInterpreterView, CView)

BEGIN_MESSAGE_MAP(CInterpreterView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CInterpreterView)
	ON_COMMAND(ID_SOURCE_GETSOURCEFILE, OnSourceGetsourcefile)
	ON_COMMAND(ID_SOURCE_INTERPRETFILE, OnSourceInterpretfile)
	ON_COMMAND(ID_SOURCE_WRITEOUTPUT, OnSourceWriteoutput)
	ON_COMMAND(ID_SOURCE_SETOUTPUTFILE, OnSourceSetoutputfile)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpreterView construction/destruction

CInterpreterView::CInterpreterView()
{
	// TODO: add construction code here

}

CInterpreterView::~CInterpreterView()
{
}

BOOL CInterpreterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//     cs.style |= (WS_HSCROLL | WS_VSCROLL);
//     cs.dwExStyle = WS_EX_CLIENTEDGE | cs.dwExStyle;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CInterpreterView drawing

void CInterpreterView::OnDraw(CDC* pDC)
{
	CInterpreterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    string Outs = pDoc->Out();
    CString OutMark = " \n-------------Output Folows--------------\n";

    char *tbuf = pDoc->TextBuffer();
    CString WindText = tbuf;
    WindText += OutMark;
    WindText += Outs.c_str();
    char *ind = WindText.GetBuffer(16000);
    char *lind = ind;
    char *indend = ind + WindText.GetLength();
    char workbuf[1000];
    int linelen;
    int vpos = 0;

    pDC->SetTextAlign( TA_NOUPDATECP | TA_TOP | TA_LEFT );
    
    lind = ind;
    linelen = 0;
    while(ind < indend)
    {
      
      ind++;
      linelen++;

      if((*ind) == '\n' || linelen > 80)
      {
        strncpy(workbuf, lind, (linelen - 1));
        workbuf[(linelen - 1)] = 0;
        if(linelen > 1)
        {
           for(int ii = 0;ii < strlen(workbuf);ii++)
           {
             if(isspace(workbuf[ii]))
             {
                workbuf[ii] = 32;
             }
           }
           pDC->ExtTextOut( 0, vpos, 0, NULL, workbuf, (linelen - 1),  NULL);
        }
        lind = ind + 1;
        linelen = 0;
        vpos += 20;
      }
    }

//    pDC->ExtTextOut( 0, 0, 0, NULL, tbuf, strlen(tbuf),  NULL);
//    pDC->ExtTextOut( 0, vpos, 0, NULL, Outs, Outs.GetLength(),  NULL);	
}

/////////////////////////////////////////////////////////////////////////////
// CInterpreterView printing

BOOL CInterpreterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CInterpreterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CInterpreterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CInterpreterView diagnostics

#ifdef _DEBUG
void CInterpreterView::AssertValid() const
{
	CView::AssertValid();
}

void CInterpreterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInterpreterDoc* CInterpreterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInterpreterDoc)));
	return (CInterpreterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInterpreterView message handlers

void CInterpreterView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_INTERPRETER_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CInterpreterView::OnSourceGetsourcefile() 
{
  CInterpreterDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  char fthfilt[] = " 4th Files (*.4th)|*.4th||";
  CFileDialog dlg( true, "4th", (pDoc->GetTitle( ) + ".4th"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES, fthfilt, NULL);

  if(dlg.DoModal() == IDOK)
  {
    CString gs = dlg.GetPathName( );
    pDoc->ReadFile(gs);   	
  }	
  InvalidateRect( NULL, TRUE );	
}

void CInterpreterView::OnSourceInterpretfile() 
{
  CInterpreterDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  
  pDoc->Interpret();
  InvalidateRect( NULL, TRUE );
	
}

void CInterpreterView::OnSourceWriteoutput() 
{
 CInterpreterDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  char fthfilt[] = " text Files (*.txt) | *.txt ||";
  CFileDialog dlg( true, "txt", (pDoc->GetTitle( ) + ".txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES, fthfilt, NULL);

  if(dlg.DoModal() == IDOK)
  {
    CString gs = dlg.GetPathName( );
    pDoc->WriteFile(gs);   	
  }	
}

void CInterpreterView::OnSourceSetoutputfile() 
{
 CInterpreterDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  char fthfilt[] = " text Files (*.txt) | *.txt ||";
  CFileDialog dlg( true, "txt", (pDoc->GetTitle( ) + ".txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES, fthfilt, NULL);

  if(dlg.DoModal() == IDOK)
  {
    CString gs = dlg.GetPathName( );
    pDoc->SetOutputFile(gs);   	
  }		
	
}
