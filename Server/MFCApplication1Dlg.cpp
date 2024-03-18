
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <fstream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <grpc++/grpc++.h>
#include <time.h>

#include "CDialogShot.h"

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

public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// CMFCApplication1Dlg dialog

class LogHelper
{
	std::string m_msg;
public :
	LogHelper(std::string msg) : m_msg(msg)
	{
		std::cout << m_msg <<" S" << std::endl;
	}
	~LogHelper()
	{
		std::cout << m_msg << " E" << std::endl;

	}

};

float g_faceCenter[17][3] = {
{-20.3526230, -86.9796524, 11.3709688 },
{ -21.7014542 , -73.5128937 , 8.50272465 },
{ -22.2775497 , -59.3999863 , 6.06226254 },
{ -21.7014542 , -47.5058174 , 4.45481682 },
{ -21.3911972 , -36.2516556 , 3.31229401 },
{ -22.1485062 , -24.5455093 , 2.51431632 },
{ -21.4366226 , -15.5111351 , 2.17065501 },
{ -22.1485062 , -6.93497849 , 2.06381416 },
{ -21.7387466 , 2.36436844 , 2.16408062 },
{ -22.9031448 , 10.1804428 , 2.40346003 },
{ -21.7387466 , 17.9966660 , 2.78451157 },
{ -20.1234512 , 27.3313293 , 3.42521405 },
{ -19.7511520 , 35.7609634 , 4.17742157 },
{ -17.6664505 , 44.6949234 , 5.15449190 },
{ -17.2525940 , 53.5819778 , 6.31006145 },
{ -17.5062485 , 62.0950928 , 7.58875704 },
{ -16.2228317 , 70.6374741 , 9.04077244 },
};


float g_shaftDirs[17][3] = {
{0.422733903, -0.192542568, -0.885563910 },
{ 0.437958658 , -0.217506245 , -0.872286141 },
{ 0.433547229 , -0.192065045 , -0.880424619 },
{ 0.454875052 , -0.178811610 , -0.872419059 },
{ 0.470481575 , -0.164678603 , -0.866907120 },
{ 0.482159495 , -0.158990353 , -0.861535847 },
{ 0.449377179 , -0.204228982 , -0.869684339 },
{ 0.454241097 , -0.183429495 , -0.871790588 },
{ 0.419285685 , -0.183967084 , -0.889019549 },
{ 0.456415355 , -0.174714774 , -0.872444630 },
{ 0.476162016 , -0.146401748 , -0.867084920 },
{ 0.443604082 , -0.148778901 , -0.883787453 },
{ 0.457523823 , -0.123176292 , -0.880624473 },
{ 0.437162936 , -0.103417441 , -0.893416643 },
{ 0.451052308 , -0.0984296724 , -0.887053370 },
{ 0.462812692 , -0.0922184885 , -0.881646276 },
{ 0.485925376 , -0.0819318295 , -0.870151460 },
};

float g_hoselTops[17][3] = {
{-78.0244980, -53.0747986, 31.3137970 },
{ -76.9820023 , -40.6896820 , 32.3070984 },
{ -81.3299942 , -28.7938309 , 27.8172989 },
{ -82.0669937 , -16.8015003 , 27.4762993 },
{ -81.3299942 , -5.71229935 , 27.8172989 },
{ -83.1769943 , 4.88409805 , 26.8987999 },
{ -84.3270035 , 14.5984993 , 26.8207016 },
{ -84.5329971 , 23.3997993 , 26.3240013 },
{ -82.4020004 , 32.0025024 , 28.0957985 },
{ -81.4679947 , 40.8859024 , 28.4745979 },
{ -83.0259933 , 48.7900009 , 28.0957985 },
{ -83.5360031 , 57.0048981 , 27.3069000 },
{ -83.0259933 , 64.5049973 , 28.9645996 },
{ -81.2369919 , 72.2490005 , 31.1139984 },
{ -80.8669968 , 80.4229965 , 31.1875992 },
{ -78.8290024 , 88.1579971 , 31.1139984 },
{ -78.6665115 , 96.3759995 , 33.6817017 },
};

float g_FaceNormal[17][3] = {

{0.589099586, 0.641196191, 0.491761297 },
{ 0.462807953 , 0.727510273 , 0.506495416 },
{ 0.371169150 , 0.766884863 , 0.523565769 },
{ 0.175145894 , 0.799759209 , 0.574203074 },
{ -0.0165819041 , 0.826000154 , 0.563425899 },
{ -0.210050434 , 0.828048110 , 0.519822240 },
{ -0.345674962 , 0.813324809 , 0.467986763 },
{ -0.437204868 , 0.761515081 , 0.478483766 },
{ -0.527203023 , 0.724227309 , 0.444467932 },
{ -0.614823043 , 0.668705404 , 0.418121666 },
{ -0.654366970 , 0.635715425 , 0.409474939 },
{ -0.705268562 , 0.596290708 , 0.383449644 },
{ -0.741953969 , 0.552301168 , 0.380089253 },
{ -0.768339157 , 0.527410209 , 0.362620145 },
{ -0.799425364 , 0.496897310 , 0.337656766 },
{ -0.825010896 , 0.481269449 , 0.296203762 },
{ -0.848563015 , 0.449333787 , 0.279356360 },
};

class IntelliSwingProtocolServiceImpl final : public IntelliSwing::IntelliSwingProtocol::Service
{
public :
	::grpc::ServerWriter< ::IntelliSwing::SensorRunningMsg>* m_pWriter = nullptr;
	CMFCApplication1Dlg* pDiag = nullptr;

	virtual ::grpc::Status Initialize(::grpc::ServerContext* context, const ::IntelliSwing::InitializeMsg* request, ::IntelliSwing::ReturnMsg* response)
	{
		std::cout << "Initialize Received " << std::endl;
		std::cout << request->handtype() << std::endl;
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
			
			//hsyoon : heatbeat removed
			/*{
				::IntelliSwing::SensorRunningMsg msg;
				std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
				
				auto *timestamp = msg.mutable_timestamp();
				*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();
				
				auto* pHeartBeat = msg.mutable_heartbeat();

				pHeartBeat->set_msg("bye");

				grpc::WriteOptions writeOption;
				writeOption.set_last_message();
				writer->Write(msg, writeOption);
			}*/

		}
		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status Stop(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::ReturnMsg* response)
	{
		std::cout << "Stop Received " << std::endl;

		std::unique_lock<std::mutex> lk(cv_m);
		g_Ready = true;
		conditional_variable.notify_all();
		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetClubImage(::grpc::ServerContext* context, const ::IntelliSwing::ShotImageRequest* request, ::IntelliSwing::ImageData* response)
	{
		std::cout << "GetClubImage Received " << std::endl;

		std::string filename = "imageDataClub.bin";
		std::ifstream _ifstream(filename, std::ios::binary);
		response->ParseFromIstream(&_ifstream);
		_ifstream.close();
		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetBallImage(::grpc::ServerContext* context, const ::IntelliSwing::ShotImageRequest* request, ::IntelliSwing::ImageData* response)
	{
		std::cout << "GetBallImage Received " << std::endl;
		std::string filename = "imageDataBall.bin";
		std::ifstream _ifstream(filename, std::ios::binary);
		response->ParseFromIstream(&_ifstream);
		_ifstream.close();
		return ::grpc::Status::OK;
	}

	virtual ::grpc::Status GetClubImageStream(::grpc::ServerContext* context, const ::IntelliSwing::ShotImageRequest* request, ::grpc::ServerWriter< ::IntelliSwing::ImageData>* writer)override
	{
		std::cout << "GetClubImageStream Received " << std::endl;
		std::string filename = "imageDataClub.bin";
		std::ifstream _ifstream(filename, std::ios::binary);

		::IntelliSwing::ImageData response;
		response.ParseFromIstream(&_ifstream);
		int nImgCnt = response.datas_size();
		for (int i = 0; i < nImgCnt; i++)
		{
			::IntelliSwing::ImageData msg;
			msg.set_width(response.width());
			msg.set_height(response.height());
			msg.set_channel(response.channel());
			msg.set_data_type(response.data_type());
			msg.set_image_type(response.image_type());
			msg.set_fps(response.fps());

			const ::IntelliSwing::ImageData_Image&rimg = response.datas(i);
			::IntelliSwing::ImageData_Image* pImg = msg.add_datas();
			pImg->set_timestamp(rimg.timestamp());

			pImg->set_data(rimg.data());

			writer->Write(msg);
		}
		_ifstream.close();
		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetBallImageStream(::grpc::ServerContext* context, const ::IntelliSwing::ShotImageRequest* request, ::grpc::ServerWriter< ::IntelliSwing::ImageData>* writer)override
	{
		std::cout << "GetBallImageStream Received " << std::endl;
		std::string filename = "imageDataBall.bin";
		std::ifstream _ifstream(filename, std::ios::binary);

		::IntelliSwing::ImageData response;
		response.ParseFromIstream(&_ifstream);
		int nImgCnt = response.datas_size();
		for (int i = 0; i < nImgCnt; i++)
		{
			::IntelliSwing::ImageData msg;
			msg.set_width(response.width());
			msg.set_height(response.height());
			msg.set_channel(response.channel());
			msg.set_data_type(response.data_type());
			msg.set_image_type(response.image_type());
			msg.set_fps(response.fps());

			const ::IntelliSwing::ImageData_Image& rimg = response.datas(i);
			::IntelliSwing::ImageData_Image* pImg = msg.add_datas();
			pImg->set_timestamp(rimg.timestamp());

			pImg->set_data(rimg.data());

			writer->Write(msg);
		}
		_ifstream.close();
		return ::grpc::Status::OK;
	}

	// Service
	virtual ::grpc::Status GetDeviceInfo(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::DeviceInfo* response)
	{
		std::cout << "GetDeviceInfo Received " << std::endl;

		return ::grpc::Status::OK;
	}
	virtual ::grpc::Status GetDeviceStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::IntelliSwing::DeviceStatus* response)
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
	virtual ::grpc::Status UpdateFirmware(::grpc::ServerContext* context, const ::IntelliSwing::UpdateFirmwareRequest* request, ::IntelliSwing::UpdateFirmwareResult* response)
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
	DDX_Control(pDX, IDC_BUTTON_SEND_SHOT, m_ctrlButtonSendShot);
	DDX_Control(pDX, IDC_CHECK_IS_ON_TEE, m_ctrlCheckIsOnTee);
	DDX_Control(pDX, IDC_COMBO_GROUND, m_ctrlComboGroundType);
	DDX_Control(pDX, IDC_BUTTON_SEND_TERMINITED, m_ctrlButtonStopped);
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
	ON_BN_CLICKED(IDC_BUTTON_SEND_SHOT, &CMFCApplication1Dlg::OnBnClickedButtonSendShot)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUND, &CMFCApplication1Dlg::OnSelchangeComboGround)
	ON_BN_CLICKED(IDC_BUTTON_SEND_TERMINITED, &CMFCApplication1Dlg::OnClickedButtonSendTerminited)
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

	// extra initialization
	m_pServer = new ZIntelliSwingServer(&g_serviceImpl);
	g_serviceImpl.pDiag = this;

	m_pServer->Start();
	m_ctrlButtonStart.EnableWindow(false);
	m_ctrlButtonStop.EnableWindow(true);

	m_ctrlComboGroundType.AddString(_T("0:FAIRWAY"));
	m_ctrlComboGroundType.AddString(_T("1:ROUGH"));
	m_ctrlComboGroundType.AddString(_T("2:BUNKER"));
	m_ctrlComboGroundType.AddString(_T("3:TEE"));
	m_ctrlComboGroundType.AddString(_T("4:GREEN"));
	m_ctrlComboGroundType.AddString(_T("5:NONE"));
	m_ctrlComboGroundType.SetCurSel(0);

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
	LogHelper log("OnBnClickedStart");
	m_pServer->Start();
	m_ctrlButtonStart.EnableWindow(false);
	m_ctrlButtonStop.EnableWindow(true);

}


void CMFCApplication1Dlg::OnBnClickedStop()
{
	LogHelper log("OnBnClickedStop");
	m_pServer->Shutdown();
	m_pServer->Stop();
	m_ctrlButtonStart.EnableWindow(true);
	m_ctrlButtonStop.EnableWindow(false);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendReady()
{
	LogHelper log("OnBnClickedButtonSendReady");

	if (g_serviceImpl.m_pWriter)
	{
		LogHelper log("OnBnClickedButtonSendReady 2");

		::IntelliSwing::SensorRunningMsg msg;
		*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
		
		auto* pReady = msg.mutable_ready();
		pReady->set_istee(m_ctrlCheckIsOnTee.GetCheck() );
		pReady->mutable_position()->set_x(10);
		pReady->mutable_position()->set_y(10);
		pReady->mutable_position()->set_z(10);
		pReady->set_goundattribution((IntelliSwing::GroundAttr) m_ctrlComboGroundType.GetCurSel());

		g_serviceImpl.m_pWriter->Write(msg);
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonSendNotReady()
{
	LogHelper log("OnBnClickedButtonSendNotReady");
	::IntelliSwing::SensorRunningMsg msg;
	*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
	auto* pNotReady = msg.mutable_notready();
	
	g_serviceImpl.m_pWriter->Write(msg);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendTriggered()
{
	LogHelper log("OnBnClickedButtonSendTriggered");
	::IntelliSwing::SensorRunningMsg msg;
	*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
	auto* pTriggered = msg.mutable_shottriggered();
	pTriggered->set_shotid(++m_nShotID);
	uint64_t timestampI64 = google::protobuf::util::TimeUtil::TimestampToMilliseconds(google::protobuf::util::TimeUtil::GetCurrentTime());
	pTriggered->set_timestamp(timestampI64);

	g_serviceImpl.m_pWriter->Write(msg);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendBallInfo()
{
	LogHelper log("OnBnClickedButtonSendBallInfo");
	::IntelliSwing::SensorRunningMsg msg;
	*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
	auto* pBallInfo = msg.mutable_ballinfo();
	pBallInfo->set_shotid(m_nShotID);
	pBallInfo->set_ballspeed(23.45);
	pBallInfo->set_backspin(2356.2);

	g_serviceImpl.m_pWriter->Write(msg);
}


void CMFCApplication1Dlg::OnBnClickedButtonSendClubInfo()
{
	LogHelper log("OnBnClickedButtonSendClubInfo");
	::IntelliSwing::SensorRunningMsg msg;

	auto* timestamp = msg.mutable_timestamp();
	*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();

	auto* pClubInfo = msg.mutable_clubinfo();
	pClubInfo->set_shotid(m_nShotID);
	pClubInfo->set_headspeed(10.56);
	pClubInfo->set_faceangle(10);

	g_serviceImpl.m_pWriter->Write(msg);
}

void CMFCApplication1Dlg::OnBnClickedButtonSendShot()
{
	LogHelper log("OnBnClickedButtonSendShot");
	CDialogShot dlgShot;
	if (dlgShot.DoModal() == IDOK)
	{
		std::cout << "Send Shot ball speed "<< dlgShot.m_nBallSpeed << std::endl;

		//send trigger
		{
			::IntelliSwing::SensorRunningMsg msg;
			*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
			auto* pTriggered = msg.mutable_shottriggered();
			pTriggered->set_shotid(++m_nShotID);
			uint64_t timestampI64 = google::protobuf::util::TimeUtil::TimestampToMilliseconds(google::protobuf::util::TimeUtil::GetCurrentTime());
			pTriggered->set_timestamp(timestampI64);

			g_serviceImpl.m_pWriter->Write(msg);
		}
		Sleep(100);

		//send ball
		{
			::IntelliSwing::SensorRunningMsg msg;
			*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
			auto* pBallInfo = msg.mutable_ballinfo();
			pBallInfo->set_shotid(m_nShotID);
			pBallInfo->set_ballspeed(dlgShot.m_nBallSpeed);
			pBallInfo->set_incidence(dlgShot.m_nBallIncidence);
			pBallInfo->set_direction(dlgShot.m_nBallDirection);
			pBallInfo->set_backspin(dlgShot.m_nBackspin);
			pBallInfo->set_sidespin(dlgShot.m_nSideSpin);

			g_serviceImpl.m_pWriter->Write(msg);
		}
		Sleep(300);

		//send club
		{
			::IntelliSwing::SensorRunningMsg msg;

			auto* timestamp = msg.mutable_timestamp();
			*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();

			auto* pClubInfo = msg.mutable_clubinfo();
			pClubInfo->set_shotid(m_nShotID);
			pClubInfo->set_headspeed(dlgShot.m_nHeadSpeed);
			pClubInfo->set_faceangle(dlgShot.m_fFaceAngle);
			pClubInfo->set_attackangle(dlgShot.m_fAttackAngle);
			pClubInfo->mutable_path()->set_gaclubpath(dlgShot.m_fClubPath);


			{
				uint64_t basetime = 50000000;
				uint64_t intervalUs = 1000000 / 500;
				float impactFrameNumber = 12.4;
				uint64_t impactTimeStampUS = basetime + impactFrameNumber * intervalUs;
				auto *pPathElm = pClubInfo->mutable_path();

				pPathElm->set_impactindex(impactFrameNumber);
				pPathElm->set_impacttimestamp(impactTimeStampUS);

				for (int i = 0; i < 17; i++)
				{
					auto* pFaceCenter = pPathElm->add_facecenter();
					pFaceCenter->set_x(g_faceCenter[i][0]);
					pFaceCenter->set_y(g_faceCenter[i][1]);
					pFaceCenter->set_z(g_faceCenter[i][2]);

					auto* pFaceNormal = pPathElm->add_facenormal();
					pFaceNormal->set_x(g_FaceNormal[i][0]);
					pFaceNormal->set_y(g_FaceNormal[i][1]);
					pFaceNormal->set_z(g_FaceNormal[i][2]);

					auto* pHoselTop = pPathElm->add_hoseltop();
					pHoselTop->set_x(g_hoselTops[i][0]);
					pHoselTop->set_y(g_hoselTops[i][1]);
					pHoselTop->set_z(g_hoselTops[i][2]);

					auto* pShaftDir = pPathElm->add_shaftdir();
					pShaftDir->set_x(g_shaftDirs[i][0]);
					pShaftDir->set_y(g_shaftDirs[i][1]);
					pShaftDir->set_z(g_shaftDirs[i][2]);

					uint64_t ts = basetime + i * intervalUs;
					pPathElm->add_timestamp(ts);

				}
			}
			pClubInfo->set_dynamicloft(dlgShot.m_fDynamicLoft);
			pClubInfo->set_swingplane(dlgShot.m_fSwingPlane);
			pClubInfo->set_swingdirection(dlgShot.m_fSwingDirection);
			pClubInfo->set_lowpoint(dlgShot.m_fLowPoint);
			auto* pImpactPoint = pClubInfo->mutable_impactpoint();
			pImpactPoint->set_gaclubimpactpoint_hor(dlgShot.m_fImpactOffset);
			pImpactPoint->set_gaclubimpactpoint_ver(dlgShot.m_fImpactHeight);
			pImpactPoint->set_gaclubimpactareawidth(50);
			pImpactPoint->set_gaclubimpactareaheight(50);
			pClubInfo->set_clublie(dlgShot.m_fClubLie);
			pClubInfo->set_clubclosurerate(dlgShot.m_fClubClosureRate);
			pClubInfo->set_clubfaxis(dlgShot.m_fClubFAxis);
			pClubInfo->set_toeheeldiff(dlgShot.m_fToeHeelDiff);

			g_serviceImpl.m_pWriter->Write(msg);
		}

		Sleep(100);

		//send club imag ready
		{
			::IntelliSwing::SensorRunningMsg msg;

			auto* timestamp = msg.mutable_timestamp();
			*timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();

			auto* pBallImageReady = msg.mutable_imageready();
			pBallImageReady->set_shotid(m_nShotID);
			pBallImageReady->set_isballimageprepared(true);
			pBallImageReady->set_isclubimageprepared(true);

			g_serviceImpl.m_pWriter->Write(msg);
		}
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonSendEnd()
{
	LogHelper log("OnBnClickedButtonSendEnd");
	std::lock_guard< std::mutex> lg(cv_m);
	g_Ready = true;
	conditional_variable.notify_all();
}


void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

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
	m_ctrlButtonSendShot.EnableWindow(true);
	m_ctrlButtonStopped.EnableWindow(true);
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
	m_ctrlButtonSendShot.EnableWindow(false);
	m_ctrlButtonStopped.EnableWindow(false);
	Invalidate(TRUE);
	UpdateWindow();
}




void CMFCApplication1Dlg::OnSelchangeComboGround()
{
	// TODO: Add your control notification handler code here
	std::cout << "Ground Index "<<m_ctrlComboGroundType.GetCurSel() << std::endl;
}

void CMFCApplication1Dlg::OnClickedButtonSendTerminited()
{
	LogHelper log("OnButtonSendTerminited");

	std::lock_guard< std::mutex> lg(cv_m);
	::IntelliSwing::SensorRunningMsg msg;
	*msg.mutable_timestamp() = google::protobuf::util::TimeUtil::GetCurrentTime();
	auto* pStopped = msg.mutable_sensorstopped();
	pStopped->set_stopcause(::IntelliSwing::SensorRunningMsg_SensorStopped_StopCause::SensorRunningMsg_SensorStopped_StopCause_Sleep);
	uint64_t timestampI64 = google::protobuf::util::TimeUtil::TimestampToMilliseconds(google::protobuf::util::TimeUtil::GetCurrentTime());

	g_serviceImpl.m_pWriter->Write(msg);

	Sleep(10);
	g_Ready = true;

	conditional_variable.notify_all();
}
