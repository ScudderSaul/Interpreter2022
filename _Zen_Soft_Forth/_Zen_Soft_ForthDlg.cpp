// _Zen_Soft_ForthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "_Zen_Soft_Forth.h"
#include "_Zen_Soft_ForthDlg.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Language lang;
extern forthinformation *pnfrth;
extern Zen_Soft_ForthDlg *pzsfdlg;

#ifndef RGB
#define RGB(rr,gg,bb) (((long) ((bb) << 8 | (gg)) << 8) | (rr))
#endif 

void CALLBACK EXPORT ATimerCallback(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
   )
{
    if(pzsfdlg)
    {
       pzsfdlg->UpdateOutput();
    }
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
    ~CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedForth();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

CAboutDlg::~CAboutDlg()
{
    if( pnfrth != NULL)
    {
      pnfrth->OnButtonCancel(NULL);
      delete  pnfrth;
      pnfrth = NULL;
    }
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    ON_BN_CLICKED(IDC_FORTH, OnBnClickedForth)
END_MESSAGE_MAP()


void CAboutDlg::OnBnClickedForth()
{
    if( pnfrth != NULL)
    {
      pnfrth->OnButtonCancel(NULL);
      delete  pnfrth;
      pnfrth = NULL;
    }
    pnfrth = new forthinformation(this);
    pnfrth->ShowWindow(SW_SHOW   );   
}


// Zen_Soft_ForthDlg dialog




Zen_Soft_ForthDlg::Zen_Soft_ForthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Zen_Soft_ForthDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    lang.Prompt();
    lang.Parse("\n", "input");
    pndlg = NULL;
    pnfrth = NULL;
    input_name = "INPUT";
    started = false;
}

Zen_Soft_ForthDlg::~Zen_Soft_ForthDlg()
{
    
    if(pndlg != NULL)
    {
       delete pndlg;
    }
    if( pnfrth != NULL)
    {
      pnfrth->OnButtonCancel(NULL);
      delete  pnfrth;
    }
}

void Zen_Soft_ForthDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_INPUT_AREA, buffer);
    DDX_Control(pDX, IDC_OUTPUT, output);
    DDX_Control(pDX, IDC_FORTHHISTORY, history);
}

BEGIN_MESSAGE_MAP(Zen_Soft_ForthDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_EN_CHANGE(IDC_INPUT_AREA, OnEnChangeInputArea)
    ON_BN_CLICKED(IDC_INTERPRET, OnBnClickedInterpret)
    ON_EN_CHANGE(IDC_OUTPUT, OnEnChangeOutput)
    ON_BN_CLICKED(IDC_LOADFILE, OnBnClickedLoadfile)
    ON_BN_CLICKED(IDC_OPENTRACE, OnBnClickedOpentrace)
    ON_BN_CLICKED(IDC_SHOWINFO, OnBnClickedShowinfo)
    ON_BN_CLICKED(IDC_SAVEFILE, OnBnClickedSavefile)
    ON_BN_CLICKED(IDC_SAVE_OUTPUT, OnBnClickedSaveOutput)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_HISTORY, OnBnClickedHistory)
    ON_BN_CLICKED(IDC_FORGETSESSION, OnBnClickedForgetsession)
    ON_NOTIFY(EN_MSGFILTER, IDC_INPUT_AREA, OnEnMsgfilterInputArea)
END_MESSAGE_MAP()


// Zen_Soft_ForthDlg message handlers

BOOL Zen_Soft_ForthDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    long tl = buffer.GetEventMask();
    buffer.SetEventMask(tl | ENM_CHANGE | ENM_KEYEVENTS);

    lfeed.StartFeed();
    timer =  SetTimer(   31415,  999,  ATimerCallback);
    shiftflag = false;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Zen_Soft_ForthDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Zen_Soft_ForthDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Zen_Soft_ForthDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Zen_Soft_ForthDlg::OnEnChangeInputArea()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void Zen_Soft_ForthDlg::UpdateOutput()
{
    if(started)
    {
        string obuf;

        bool tstbusy;
        lfeed.Busy(tstbusy);
        if(tstbusy)
        {
            output.SetBackgroundColor(FALSE, RGB(175, 255, 175));

        }
        else
        {
            output.SetBackgroundColor(TRUE, RGB(255, 255, 255));
        }


        lfeed.GetOutBuf(obuf); 
        if(obuf.empty() == false)
        {

            out_history += obuf;
            output.SetReadOnly(FALSE);
            output.SetWindowText(out_history.c_str());
            output.SetModify();
            output.SetReadOnly(TRUE);
            this->Invalidate();
        }
        if(pndlg != NULL)
        {
            lfeed.GetTraceOutBuf(obuf);
            if(obuf.empty() == false)
            {
                pndlg->TraceUpdate(obuf);
            }
        }
    }


}

void Zen_Soft_ForthDlg::OnBnClickedInterpret()
{
    CString str, ostr;
    started = true;
    if(in_parse.fail())
    {
        in_parse.clear();  
    }
    buffer.GetWindowText(str);

    in_now = str.GetBuffer();
    in_parse << in_now;
    in_parse << "\n\r";

    str.Empty();
    buffer.SetWindowText(str);


    if(in_history.empty() == true)
    {
        in_history = in_now;
    }
    else
    {
        in_history += in_now;
    }

    history.SetReadOnly(FALSE);
    history.SetWindowText(in_history.c_str());
    history.SetReadOnly(TRUE);

   lfeed.ResumeIterate();     // start parser thread
   lfeed.OutResumeIterate();  // start output colection thread;
 
   in_parsestr = "\n";
   while(in_parsestr.empty() == false)
   {
      in_parsestr.clear();
      getline(in_parse, in_parsestr);  // unformated line
      if(in_parsestr.empty() == false)
      {
         lfeed.Parse(in_parsestr, input_name);  // send input to parser feeder
      }
   }
}

void Zen_Soft_ForthDlg::OnEnChangeOutput()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void Zen_Soft_ForthDlg::OnBnClickedLoadfile()
{
    char * tmp_buffer = NULL;

    CFileDialog aDlg(TRUE, NULL, NULL
             , OFN_HIDEREADONLY | OFN_NOTESTFILECREATE  | OFN_PATHMUSTEXIST ,
                   "Forth Files (*.4th)|*.4th| All Files (*.*)|*.*||");

             aDlg.m_ofn.lpstrTitle = "Load forth file";

             if(aDlg.DoModal( ) == IDOK)
             {
                CString gg = aDlg.GetPathName();
                int fd = -1;
                if((fd = open(gg.GetBuffer(), _O_RDONLY)) >= 0)
                {
                    struct _stat st;
                    if( _fstat(fd, &st) == 0)
                    {
                         tmp_buffer = new char[st.st_size + 10];
                         if(tmp_buffer != NULL)
                         {
                            int len;
                            if((len = _read(fd, tmp_buffer, st.st_size)) > 0)
                            {
                                tmp_buffer[len] = 0;
                               // in_history += tmp_buffer;
                                buffer.SetWindowText(tmp_buffer);
                            }
                            delete [] tmp_buffer;
                         }
                    }
                    _close(fd);
                }
             }

}

void Zen_Soft_ForthDlg::OnBnClickedOpentrace()
{
    if(pndlg != NULL)
    {
        lfeed.ClearTraceOutput();
    }
    else
    {
        lfeed.StartStringTrace();
        pndlg = new tracewindow(this);
        pndlg->ShowWindow(SW_SHOW   );
    }
}

void  Zen_Soft_ForthDlg::CloseOfTrace()
{
    if(pndlg != NULL)
    {
        pndlg = NULL;
        lfeed.StopStringTrace();
        lfeed.ClearTraceOutput();
    }
}

void Zen_Soft_ForthDlg::OnBnClickedShowinfo()
{
    if( pnfrth != NULL)
    {
      pnfrth->OnButtonCancel(NULL);
      delete  pnfrth;
      pnfrth = NULL;
    }
    pnfrth = new forthinformation(this);
    pnfrth->ShowWindow(SW_SHOW   );
}

void Zen_Soft_ForthDlg::OnBnClickedSavefile()
{
        CFileDialog aDlg(FALSE, "4th", "*.4th"
             , OFN_HIDEREADONLY  | OFN_PATHMUSTEXIST | OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
                   "Forth Files (*.4th)|*.4th| All Files (*.*)|*.*||");

             aDlg.m_ofn.lpstrTitle = "Save Forth file (*.4th)";

             if(aDlg.DoModal( ) == IDOK)
             {
                CString gg = aDlg.GetPathName();
                int fd = -1;
                CString ng;
                if((fd = _open(gg.GetBuffer(), _O_RDWR | _O_TRUNC | _O_CREAT)) >= 0)
                {
                         buffer.GetWindowText(ng);
                    _write(fd, ng.GetBuffer(), ng.GetLength());
                    _close(fd);
                }
             }

}

void Zen_Soft_ForthDlg::OnBnClickedSaveOutput()
{
            CFileDialog aDlg(FALSE, "txt", "*.txt"
             , OFN_HIDEREADONLY  | OFN_PATHMUSTEXIST | OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
                   "Forth Output Files (*.txt)|*.txt| All Files (*.*)|*.*||");

             aDlg.m_ofn.lpstrTitle = "Save Forth file (*.4th)";

             if(aDlg.DoModal( ) == IDOK)
             {
                CString gg = aDlg.GetPathName();
                int fd = -1;
                CString ng;
                if((fd = _open(gg.GetBuffer(), _O_RDWR | _O_TRUNC | _O_CREAT)) >= 0)
                {
                         output.GetWindowText(ng);
                    _write(fd, ng.GetBuffer(), ng.GetLength());
                    _close(fd);
                }
             }

}


void Zen_Soft_ForthDlg::OnBnClickedOk()
{
    KillTimer(timer);
    OnOK();
}

void Zen_Soft_ForthDlg::OnBnClickedHistory()
{
       CFileDialog aDlg(FALSE, "4th", "*.4th"
             , OFN_HIDEREADONLY  | OFN_PATHMUSTEXIST | OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
                   "Forth Files (*.4th)|*.4th| All Files (*.*)|*.*||");

             aDlg.m_ofn.lpstrTitle = "Save History as file (*.4th)";

             if(aDlg.DoModal( ) == IDOK)
             {
                CString gg = aDlg.GetPathName();
                int fd = -1;
                CString ng;
                if((fd = _open(gg.GetBuffer(), _O_RDWR | _O_TRUNC | _O_CREAT)) >= 0)
                {
                         output.GetWindowText(ng);
                    _write(fd, ng.GetBuffer(), ng.GetLength());
                    _close(fd);
                }
             }
}

void Zen_Soft_ForthDlg::OnBnClickedForgetsession()
{
    lfeed.ResumeIterate();     // start parser thread
    lfeed.OutResumeIterate();  // start output colection thread;
    in_parsestr = "forget char \n\r";
    input_name = "CLEAR";
    lfeed.Parse(in_parsestr, input_name); 
}

#ifdef MESSAGEDATADES

An application can use the following values to manipulate the keystroke flags.

KF_ALTDOWN Manipulates the ALT key flag, which indicated if the ALT key is pressed. 
KF_DLGMODE Manipulates the dialog mode flag, which indicates whether a dialog box is active. 
KF_EXTENDED Manipulates the extended key flag. 
KF_MENUMODE Manipulates the menu mode flag, which indicates whether a menu is active. 
KF_REPEAT Manipulates the repeat count. 
KF_UP Manipulates the transition state flag. 

SHORT GetKeyState(          int nVirtKey
);
Parameters

nVirtKey
[in] Specifies a virtual key. If the desired virtual key is a letter or digit (A through Z, a through z, or 0 through 9), nVirtKey must be set to the ASCII value of that character. For other keys, it must be a virtual-key code. 
If a non-English keyboard layout is used, virtual keys with values in the range ASCII A through Z and 0 through 9 are used to specify most of the character keys. For example, for the German keyboard layout, the virtual key of value ASCII O (0x4F) refers to the "o" key, whereas VK_OEM_1 refers to the "o with umlaut" key.

Return Value

The return value specifies the status of the specified virtual key, as follows: 

If the high-order bit is 1, the key is down; otherwise, it is up.
If the low-order bit is 1, the key is toggled. A key, such as the CAPS LOCK key, is toggled if it is turned on. The key is off and untoggled if the low-order bit is 0. A toggle key's indicator light (if any) on the keyboard will be on when the key is toggled, and off when the key is untoggled.


Remarks

The key status returned from this function changes as a thread reads key messages from its message queue. The status does not reflect the interrupt-level state associated with the hardware. Use the GetAsyncKeyState function to retrieve that information. 

An application calls GetKeyState in response to a keyboard-input message. This function retrieves the state of the key when the input message was generated. 

To retrieve state information for all the virtual keys, use the GetKeyboardState function. 

An application can use the virtual-key code constants VK_SHIFT, VK_CONTROL, and VK_MENU as values for the nVirtKey parameter. This gives the status of the SHIFT, CTRL, or ALT keys without distinguishing between left and right. An application can also use the following virtual-key code constants as values for nVirtKey to distinguish between the left and right instances of those keys. 

VK_LSHIFT

VK_RSHIFT

VK_LCONTROL

VK_RCONTROL

VK_LMENU

VK_RMENU

GetAsyncKeyState Function  

--------------------------------------------------------------------------------

The GetAsyncKeyState function determines whether a key is up or down at the time the function is called, and whether the key was pressed after a previous call to GetAsyncKeyState. 

Syntax

SHORT GetAsyncKeyState(          int vKey
);
Parameters

vKey
[in] Specifies one of 256 possible virtual-key codes. For more information, see Virtual-Key Codes. 
Windows NT/2000/XP: You can use left- and right-distinguishing constants to specify certain keys. See the Remarks section for further information.

Return Value

If the function succeeds, the return value specifies whether the key was pressed since the last call to GetAsyncKeyState, and whether the key is currently up or down. If the most significant bit is set, the key is down, and if the least significant bit is set, the key was pressed after the previous call to GetAsyncKeyState. However, you should not rely on this last behavior; for more information, see the Remarks. 

Windows NT/2000/XP: The return value is zero for the following cases: 

The current desktop is not the active desktop
The foreground thread belongs to another process and the desktop does not allow the hook or the journal record.
Windows 95/98/Me: The return value is the global asynchronous key state for each virtual key. The system does not check which thread has the keyboard focus.

Windows 95/98/Me: Windows 95 does not support the left- and right-distinguishing constants. If you call GetAsyncKeyState with these constants, the return value is zero. 


/*
 * Virtual Keys, Standard Set
 */
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0x07 : unassigned
 */

#define VK_BACK           0x08
#define VK_TAB            0x09

/*
 * 0x0A - 0x0B : reserved
 */

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_KANA           0x15
#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19

#define VK_ESCAPE         0x1B

#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */

#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D

/*
 * 0x5E : reserved
 */

#define VK_SLEEP          0x5F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

/*
 * 0x88 - 0x8F : unassigned
 */

#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

/*
 * NEC PC-9800 kbd definitions
 */
#define VK_OEM_NEC_EQUAL  0x92   // '=' key on numpad

/*
 * Fujitsu/OASYS kbd definitions
 */
#define VK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

/*
 * 0x97 - 0x9F : unassigned
 */

/*
 * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
 * No other API or message will distinguish left and right keys in this way.
 */
#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC

#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0xB8 - 0xB9 : reserved
 */

#define VK_OEM_1          0xBA   // ';:' for US
#define VK_OEM_PLUS       0xBB   // '+' any country
#define VK_OEM_COMMA      0xBC   // ',' any country
#define VK_OEM_MINUS      0xBD   // '-' any country
#define VK_OEM_PERIOD     0xBE   // '.' any country
#define VK_OEM_2          0xBF   // '/?' for US
#define VK_OEM_3          0xC0   // '`~' for US

/*
 * 0xC1 - 0xD7 : reserved
 */

/*
 * 0xD8 - 0xDA : unassigned
 */

#define VK_OEM_4          0xDB  //  '[{' for US
#define VK_OEM_5          0xDC  //  '\|' for US
#define VK_OEM_6          0xDD  //  ']}' for US
#define VK_OEM_7          0xDE  //  ''"' for US
#define VK_OEM_8          0xDF

/*
 * 0xE0 : reserved
 */

/*
 * Various extended or enhanced keyboards
 */
#define VK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define VK_ICO_HELP       0xE3  //  Help key on ICO
#define VK_ICO_00         0xE4  //  00 key on ICO

#if(WINVER >= 0x0400)
#define VK_PROCESSKEY     0xE5
#endif /* WINVER >= 0x0400 */

#define VK_ICO_CLEAR      0xE6


#if(_WIN32_WINNT >= 0x0500)
#define VK_PACKET         0xE7
#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0xE8 : unassigned
 */

/*
 * Nokia/Ericsson definitions
 */
#define VK_OEM_RESET      0xE9
#define VK_OEM_JUMP       0xEA
#define VK_OEM_PA1        0xEB
#define VK_OEM_PA2        0xEC
#define VK_OEM_PA3        0xED
#define VK_OEM_WSCTRL     0xEE
#define VK_OEM_CUSEL      0xEF
#define VK_OEM_ATTN       0xF0
#define VK_OEM_FINISH     0xF1
#define VK_OEM_COPY       0xF2
#define VK_OEM_AUTO       0xF3
#define VK_OEM_ENLW       0xF4
#define VK_OEM_BACKTAB    0xF5

#define VK_ATTN           0xF6
#define VK_CRSEL          0xF7
#define VK_EXSEL          0xF8
#define VK_EREOF          0xF9
#define VK_PLAY           0xFA
#define VK_ZOOM           0xFB
#define VK_NONAME         0xFC
#define VK_PA1            0xFD
#define VK_OEM_CLEAR      0xFE

/*
 * 0xFF : reserved
 */


 /* !NOVIRTUALKEYCODES */







#endif

void Zen_Soft_ForthDlg::OnEnMsgfilterInputArea(NMHDR *pNMHDR, LRESULT *pResult)
{
   pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);
   UINT tst;
   UINT key;

       tst = pMsgFilter->msg;
       key = pMsgFilter->wParam;
       BYTE keyst[256];

 //      BOOL GetKeyboardState( &keyst);

       if(tst == 256 && key == 13)
       {
             if(GetKeyState(VK_SHIFT) != 0)
             {
               
             }
             else
             {
                 OnBnClickedInterpret();
             }
       }

       if(GetKeyState(VK_F1 ) > 0)
       {
           OnBnClickedShowinfo();
       }

       *pResult = 0;
}
