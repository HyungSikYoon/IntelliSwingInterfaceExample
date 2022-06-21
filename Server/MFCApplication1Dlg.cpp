
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <grpc++/grpc++.h>
#include <time.h>

#include "../ProtoBuf/IntelliSwingInterface.grpc.pb.h"
#include <google/protobuf/util/time_util.h>
#pragma comment(lib, "Ws2_32.lib")
std::condition_variable conditional_variable;
std::mutex cv_m;
bool g_Ready = false;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog


class IntelliSwingProtocolServiceImpl final : public IntelliSwing::IntelliSwingProtocol::Service
{
public :
	::grpc::ServerWriter< ::IntelliSwing::SensorRunningMsg>* m_pWriter = nullptr;
	CMFCApplication1Dlg* pDiag = nullptr;

	virtual ::grpc::Status Initialize(::grpc::ServerContext* context, const ::IntelliSwing::InitializeMsg* request, ::IntelliSwing::ReturnMsg* response)
	{
		std::cout << "Initialize Received " << std::endl;
		return ::grpc::Status::OK;

	}
	virtual ::grpc::Status Release(::grpc::ServerContext* context, const ::IntelliSwing::ReleaseMsg* request, ::IntelliSwing::ReturnMsg* response)
	{
		std::cout << "Release Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status Reboot(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::ReturnMsg* response)
	{
		std::cout << "Reboot Received " << std::endl;

		return ::grpc::Status::OK;
	}

	// Sensor
	virtual ::grpc::Status Start(::grpc::ServerContext* context, const ::IntelliSwing::StartMsg* request, ::grpc::ServerWriter< ::IntelliSwing::SensorRunningMsg>* writer)
	{
		std::cout << "Start Received " << std::endl;
		if (pDiag)
		{
			std::unique_lock<std::mutex> lk(cv_m);
			g_Ready = false;
			m_pWriter = writer;
			pDiag->OnBeginServerToClient();
			std::cout << "waiting " << std::endl;
			conditional_variable.wait(lk, [] {return g_Ready; });
			pDiag->OnEndServerToClient();
			m_pWriter = nullptr;
			
			{
				::IntelliSwing::SensorRunningMsg msg;
				std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
				
				auto *timestamp = msg.mutable_timestamp();
				*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();
				
				auto* pHeartBeat = msg.mutable_heartbeat();

				pHeartBeat->set_msg("bye");

				grpc::WriteOptions writeOption;
				writeOption.set_last_message();
				writer->Write(msg, writeOption);
			}

		}
		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status Stop(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::ReturnMsg* response)
	{
		std::cout << "Stop Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetClubImage(::grpc::ServerContext* context, const ::IntelliSwing::ShotImageRequest* request, ::IntelliSwing::ImageData* response)
	{
		std::cout << "GetClubImage Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetBallImage(::grpc::ServerContext* context, const ::IntelliSwing::ShotImageRequest* request, ::IntelliSwing::ImageData* response)
	{
		std::cout << "GetBallImage Received " << std::endl;

		return ::grpc::Status::OK;
	}

	// Service
	virtual ::grpc::Status GetDeviceInfo(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::DeviceInfo* response)
	{
		std::cout << "GetDeviceInfo Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetDeviceStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::DiviceStatus* response)
	{
		std::cout << "GetDeviceStatus Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetLog(::grpc::ServerContext* context, const ::IntelliSwing::LogRequest* request, ::IntelliSwing::LogMessage* response)
	{
		std::cout << "GetLog Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetStatistics(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::SensorStatistics* response)
	{
		std::cout << "GetStatistics Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status RunSiteCalibration(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::SiteCalibrationResult* response)
	{
		std::cout << "RunSiteCalibration Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status UpdateFirmware(::grpc::ServerContext* context, const ::IntelliSwing::Firmware* request, ::IntelliSwing::UpdateFirmwareResult* response)
	{
		std::cout << "UpdateFirmware Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetImage(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::ImageData* response)
	{
		std::cout << "GetImage Received " << std::endl;

		return ::grpc::Status::OK;
	}

};

IntelliSwingProtocolServiceImpl g_serviceImpl;

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlButtonStart);
	DDX_Control(pDX, IDC_BUTTON2, m_ctrlButtonStop);
	DDX_Control(pDX, IDC_BUTTON3, m_ctrlButtonReady);
	DDX_Control(pDX, IDC_BUTTON4, m_ctrlButtonNotReady);
	DDX_Control(pDX, IDC_BUTTON5, m_ctrlButtonTriggered);
	DDX_Control(pDX, IDC_BUTTON6, m_ctrlButtonBallFlight);
	DDX_Control(pDX, IDC_BUTTON7, m_ctrlButtonClubPath);
	DDX_Control(pDX, IDC_BUTTON_SEND_END, m_ctrlButtonSendEnd);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButtonSendReady)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButtonSendNotReady)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButtonSendTriggered)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButtonSendBallInfo)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButtonSendClubInfo)
	ON_BN_CLICKED(IDC_BUTTON_SEND_END, &CMFCApplication1Dlg::OnBnClickedButtonSendEnd)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	m_pServer = new ZIntelliSwingServer(&g_serviceImpl);
	g_serviceImpl.pDiag = this;

	m_pServer->Start();
	m_ctrlButtonStart.EnableWindow(false);
	m_ctrlButtonStop.EnableWindow(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	// start

	m_pServer->Start();
	m_ctrlButtonStart.EnableWindow(false);
	m_ctrlButtonStop.EnableWindow(true);

}


void CMFCApplication1Dlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	//stop
	m_pServer->Shutdown();
	m_pServer->Stop();
	m_ctrlButtonStart.EnableWindow(true);
	m_ctrlButtonStop.EnableWindow(false);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendReady()
{
	// TODO: Add your control notification handler code here
	//ready
	if (g_serviceImpl.m_pWriter)
	{
		::IntelliSwing::SensorRunningMsg msg;

		auto* timestamp = msg.mutable_timestamp();
		*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();
		
		auto* pReady = msg.mutable_ready();
		pReady->set_istee(true);
		pReady->mutable_position()->set_x(10);
		pReady->mutable_position()->set_y(10);
		pReady->mutable_position()->set_z(10);

		g_serviceImpl.m_pWriter->Write(msg);
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonSendNotReady()
{
	// TODO: Add your control notification handler code here
	// not ready
	::IntelliSwing::SensorRunningMsg msg;
	auto* pNotReady = msg.mutable_notready();
	
	g_serviceImpl.m_pWriter->Write(msg);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendTriggered()
{
	// TODO: Add your control notification handler code here
	// triggered
	::IntelliSwing::SensorRunningMsg msg;
	auto* pTriggered = msg.mutable_shottriggered();
	pTriggered->set_shotid(99);
	pTriggered->set_timestamp(23456);

	g_serviceImpl.m_pWriter->Write(msg);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendBallInfo()
{
	// TODO: Add your control notification handler code here
	// ball flight
	::IntelliSwing::SensorRunningMsg msg;
	auto* pBallInfo = msg.mutable_ballinfo();
	pBallInfo->set_shotid(99);
	pBallInfo->set_ballspeed(23.45);
	pBallInfo->set_backspin(2356.2);

	g_serviceImpl.m_pWriter->Write(msg);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendClubInfo()
{
	// TODO: Add your control notification handler code here
	// club path
	::IntelliSwing::SensorRunningMsg msg;
	
	auto* timestamp = msg.mutable_timestamp();
	*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();
	
	auto* pClubInfo = msg.mutable_clubinfo();
	pClubInfo->set_shotid(99);
	pClubInfo->set_headspeed(10.56);
	pClubInfo->set_faceangle(10);

	g_serviceImpl.m_pWriter->Write(msg);
}

void CMFCApplication1Dlg::OnBnClickedButtonSendEnd()
{
	// TODO: Add your control notification handler code here
	std::lock_guard< std::mutex> lg(cv_m);
	g_Ready = true;
	conditional_variable.notify_all();
}


void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_pServer->Shutdown();
	m_pServer->Stop();
	delete m_pServer;
}

void CMFCApplication1Dlg::OnBeginServerToClient()
{
	m_ctrlButtonReady.EnableWindow(true);
	m_ctrlButtonNotReady.EnableWindow(true);
	m_ctrlButtonTriggered.EnableWindow(true);
	m_ctrlButtonBallFlight.EnableWindow(true);
	m_ctrlButtonClubPath.EnableWindow(true);
	m_ctrlButtonSendEnd.EnableWindow(true);
	Invalidate(TRUE);
	UpdateWindow();
}

void CMFCApplication1Dlg::OnEndServerToClient()
{
	m_ctrlButtonReady.EnableWindow(false);
	m_ctrlButtonNotReady.EnableWindow(false);
	m_ctrlButtonTriggered.EnableWindow(false);
	m_ctrlButtonBallFlight.EnableWindow(false);
	m_ctrlButtonClubPath.EnableWindow(false);
	m_ctrlButtonSendEnd.EnableWindow(false);
	Invalidate(TRUE);
	UpdateWindow();
}

