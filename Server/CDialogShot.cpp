// CDialogShot.cpp : implementation file
//

#include "pch.h"
#include "CDialogShot.h"
#include "afxdialogex.h"


// CDialogShot dialog

IMPLEMENT_DYNAMIC(CDialogShot, CDialogEx)

CDialogShot::CDialogShot(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SHOT, pParent)
	, m_nBackspin(3000)
	, m_nBallDirection(3)
	, m_nBallIncidence(15)
	, m_nBallSpeed(43)
	, m_nSideSpin(-300)
	, m_nHeadSpeed(35)
	, m_fAttackAngle(10)
	, m_fDynamicLoft(10)
	, m_fClubPath(0)
	, m_fFaceAngle(0)
	, m_fSwingPlane(75)
	, m_fSwingDirection(0)
	, m_fLowPoint(-1)
	, m_fImpactHeight(0)
	, m_fImpactOffset(0)
	, m_fClubLie(0)
	, m_fClubClosureRate(0)
	, m_fClubFAxis(0)
	, m_fToeHeelDiff(0)
{

}

CDialogShot::~CDialogShot()
{
}

void CDialogShot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BALL_BACKSPIN, m_nBackspin);
	DDV_MinMaxInt(pDX, m_nBackspin, -3000, 8000);
	DDX_Text(pDX, IDC_EDIT_BALL_DIRECTION, m_nBallDirection);
	DDV_MinMaxInt(pDX, m_nBallDirection, -90, 90);
	DDX_Text(pDX, IDC_EDIT_BALL_INCIDENCE, m_nBallIncidence);
	DDV_MinMaxInt(pDX, m_nBallIncidence, -10, 90);
	DDX_Text(pDX, IDC_EDIT_BALL_SPEED, m_nBallSpeed);
	DDV_MinMaxInt(pDX, m_nBallSpeed, 0, 120);
	DDX_Text(pDX, IDC_EDIT_BALL_SIDE_SPIN, m_nSideSpin);
	DDV_MinMaxInt(pDX, m_nSideSpin, -5000, 5000);
	DDX_Text(pDX, IDC_EDIT6, m_nHeadSpeed);
	DDV_MinMaxInt(pDX, m_nHeadSpeed, 0, 70);
	DDX_Text(pDX, IDC_EDIT_C_ATTACK_ANGLE, m_fAttackAngle);
	DDV_MinMaxFloat(pDX, m_fAttackAngle, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_DYNAMIC_LOFT, m_fDynamicLoft);
	DDV_MinMaxFloat(pDX, m_fDynamicLoft, 0, 45);
	DDX_Text(pDX, IDC_EDIT_C_CLUBPATH, m_fClubPath);
	DDV_MinMaxFloat(pDX, m_fClubPath, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_FACE_ANGLE, m_fFaceAngle);
	DDV_MinMaxFloat(pDX, m_fFaceAngle, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_SWING_PLANE, m_fSwingPlane);
	DDV_MinMaxFloat(pDX, m_fSwingPlane, 45, 95);
	DDX_Text(pDX, IDC_EDIT_C_SWING_DIRECTION, m_fSwingDirection);
	DDV_MinMaxFloat(pDX, m_fSwingDirection, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_LOW_POINT, m_fLowPoint);
	DDV_MinMaxFloat(pDX, m_fLowPoint, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_IMPACT_HEIGHT, m_fImpactHeight);
	DDV_MinMaxFloat(pDX, m_fImpactHeight, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_IMPACT_OFFSET, m_fImpactOffset);
	DDV_MinMaxFloat(pDX, m_fImpactOffset, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_CLUB_LIE, m_fClubLie);
	DDV_MinMaxFloat(pDX, m_fClubLie, -10, 45);
	DDX_Text(pDX, IDC_EDIT_C_CLOSURE_RATE, m_fClubClosureRate);
	DDV_MinMaxFloat(pDX, m_fClubClosureRate, -100, 100);
	DDX_Text(pDX, IDC_EDIT_C_F_AXIS, m_fClubFAxis);
	DDV_MinMaxFloat(pDX, m_fClubFAxis, -20, 20);
	DDX_Text(pDX, IDC_EDIT_C_TOE_HEEL_DIFF, m_fToeHeelDiff);
	DDV_MinMaxFloat(pDX, m_fToeHeelDiff, -20, 20);
}


BEGIN_MESSAGE_MAP(CDialogShot, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogShot::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogShot message handlers


void CDialogShot::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
