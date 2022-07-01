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
}


BEGIN_MESSAGE_MAP(CDialogShot, CDialogEx)
END_MESSAGE_MAP()


// CDialogShot message handlers
