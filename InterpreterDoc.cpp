// InterpreterDoc.cpp : implementation of the CInterpreterDoc class
//

#include "stdafx.h"
#include "Interpreter.h"

#include "InterpreterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterpreterDoc

IMPLEMENT_DYNCREATE(CInterpreterDoc, CDocument)

BEGIN_MESSAGE_MAP(CInterpreterDoc, CDocument)
	//{{AFX_MSG_MAP(CInterpreterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpreterDoc construction/destruction

CInterpreterDoc::CInterpreterDoc()
{
	filein = 0;
    text[0] = 0;
    ofilename.reserve(400);

}

CInterpreterDoc::~CInterpreterDoc()
{
}

BOOL CInterpreterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CInterpreterDoc serialization

void CInterpreterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CInterpreterDoc diagnostics

#ifdef _DEBUG
void CInterpreterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInterpreterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInterpreterDoc commands
