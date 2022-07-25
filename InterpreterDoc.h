// InterpreterDoc.h : interface of the CInterpreterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERPRETERDOC_H__3DF4CD1E_E76C_11D1_BC33_00AA00098E79__INCLUDED_)
#define AFX_INTERPRETERDOC_H__3DF4CD1E_E76C_11D1_BC33_00AA00098E79__INCLUDED_


#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0602 // _WIN32_WINNT_WIN8 
//#define  NTDDI_VERSION 0x06020000  // NTDDI_WIN8 
//#define WINVER 0x0602 // _WIN32_WINNT_WIN8 
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "codeelement.h"

class CInterpreterDoc : public CDocument
{
protected: // create from serialization only
	CInterpreterDoc();
	DECLARE_DYNCREATE(CInterpreterDoc)

// Attributes
public:

    Language lang;
    char text[10000];
    int filein;
    string ofilename;

    void Interpret()
    {
       if(filein != 0)
       {
          lang.Parse(text, NULL);
       }
    }

    char * TextBuffer()
    {
      return(text);
    }

    string & Out()
    {
      return(lang.Out());
    }

    void ReadFile(CString & gg)
    {
      CFile af(gg.GetBuffer( 256 ), CFile::modeRead );
      filein = af.Read(text, 9999);
      text[filein] = 0;
      af.Close();
    }

    void WriteFile(CString & gg)
    {
      CFile af(gg.GetBuffer( 256 ), CFile::modeCreate | CFile::modeReadWrite );
      af.Write((lang.Out()).c_str(),(lang.Out()).length( ) );
      af.Close();
    }

    void SetOutputFile(CString & gg)
    {
      CFile af(gg.GetBuffer( 256 ), CFile::modeCreate | CFile::modeReadWrite );
      af.Close();
      ofilename = gg.GetBuffer(256);
      lang.SetOut(ofilename.c_str());
    }


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpreterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInterpreterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInterpreterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETERDOC_H__3DF4CD1E_E76C_11D1_BC33_00AA00098E79__INCLUDED_)
