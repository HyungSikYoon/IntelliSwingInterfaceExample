// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#include <plog/Log.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#pragma comment(lib, "ZSensorInterfaceDll.lib")

// CClientDlg dialog
class LogHelper
{
	const size_t            m_line;
	const char* const       m_func;

public:
	LogHelper(const char* func, size_t line) : m_func(func), m_line(line)
	{
		IF_PLOG_(PLOG_DEFAULT_INSTANCE_ID, plog::warning) (*plog::get<PLOG_DEFAULT_INSTANCE_ID>()) += plog::Record(plog::warning, m_func, m_line, "", "", PLOG_DEFAULT_INSTANCE_ID).ref()<< " --> Start" ;
		
	}
	~LogHelper()
	{
		IF_PLOG_(PLOG_DEFAULT_INSTANCE_ID, plog::warning) (*plog::get<PLOG_DEFAULT_INSTANCE_ID>()) += plog::Record(plog::warning, m_func, m_line, "", "", PLOG_DEFAULT_INSTANCE_ID).ref()<< " <-- End" ;

	}

};


#define LOG_BEGIN_END LogHelper helper(__FUNCTION__, __LINE__)


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClientDlg dialog




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_GET_DEVICE_INFO, &CClientDlg::OnBnClickedButtonGetDeviceInfo)
	ON_BN_CLICKED(IDC_BUTTON_INITIALIZE, &CClientDlg::OnBnClickedButtonInitialize)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, &CClientDlg::OnBnClickedButtonRelease)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CClientDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_START, &CClientDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CClientDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_GET_CLUB_IMG, &CClientDlg::OnBnClickedButtonGetClubImg)
	ON_BN_CLICKED(IDC_BUTTON_GET_BALL_IMG, &CClientDlg::OnBnClickedButtonGetBallImg)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_STATUS, &CClientDlg::OnBnClickedButtonDeviceStatus)
	ON_BN_CLICKED(IDC_BUTTON_GET_LOG, &CClientDlg::OnBnClickedButtonGetLog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	LOG_BEGIN_END;
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

	// TODO: Add extra initialization here


	//LogHelper logHelp("this is log");
	LOGW<<"OnInit Dialog";
	m_pIntelliSwingProtocolAdapter = new ZSensor::IIntelliSwingProtocolAdapter(this);
	m_pIntelliSwingProtocolAdapter->Connect("localhost", 50051);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedButtonGetDeviceInfo()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonInitialize()
{
	// TODO: Add your control notification handler code here
	ZSensor::InitializeMsg initialize;
	ZSensor::ReturnMsg returnMsg;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->Initialize(initialize, returnMsg);
	}
}

void CClientDlg::OnBnClickedButtonRelease()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonReboot()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonGetClubImg()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonGetBallImg()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonDeviceStatus()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnBnClickedButtonGetLog()
{
	// TODO: Add your control notification handler code here
}

void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}

void CClientDlg::OnReady(ZSensor::Ready &ready)
{
	LOG_BEGIN_END;
}
void CClientDlg::OnNotReady(ZSensor::NotReady &notReady)
{
	LOG_BEGIN_END;
}
void CClientDlg::OnShortTriggered(ZSensor::ShortTriggered &shotTriggered)
{
	LOG_BEGIN_END;
}
void CClientDlg::OnBallFlightInfo(ZSensor::BallFlightInfo &ballFlightInfo)
{
	LOG_BEGIN_END;
}
void CClientDlg::OnClubPathInfo(ZSensor::ClubPathInfo &clubInfo)
{
	LOG_BEGIN_END;
}

void CClientDlg::OnDestroy()
{
	__super::OnDestroy();

	// TODO: Add your message handler code here
	delete m_pIntelliSwingProtocolAdapter;
	m_pIntelliSwingProtocolAdapter = NULL;
}
