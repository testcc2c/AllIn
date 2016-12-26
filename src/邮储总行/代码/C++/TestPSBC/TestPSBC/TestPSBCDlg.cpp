
// TestPSBCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestPSBC.h"
#include "TestPSBCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestPSBCDlg �Ի���




CTestPSBCDlg::CTestPSBCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestPSBCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestPSBCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_PSBC, m_psbcTab);
}

BEGIN_MESSAGE_MAP(CTestPSBCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PSBC, &CTestPSBCDlg::OnTcnSelchangeTabPsbc)
END_MESSAGE_MAP()


// CTestPSBCDlg ��Ϣ�������

BOOL CTestPSBCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//add  by yuanyi 

	CRect rc; 
	m_psbcTab.GetClientRect(rc); 
	rc.top += 25; 
	rc.bottom -= 0; 
	rc.left += 0; 
	rc.right -= 1; 
;	 


	m_psbcTab.InsertItem(0, _T("�豸����"));
	m_basicFunDialog.Create(IDD_DIALOG_BASIC, &m_psbcTab);
	m_basicFunDialog.MoveWindow(&rc);
	m_basicFunDialog.ShowWindow(SW_SHOW);	 

	m_psbcTab.InsertItem(1, _T("��ӡ����"));
	m_stampDialog.Create(IDD_DIALOG_STAMP, &m_psbcTab);	
	m_stampDialog.MoveWindow(&rc);
	m_stampDialog.ShowWindow(SW_HIDE);	 

	m_psbcTab.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestPSBCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestPSBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestPSBCDlg::OnTcnSelchangeTabPsbc(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(m_psbcTab.GetCurSel())
	{
	case 0:
		//�豸����
		m_basicFunDialog.ShowWindow(SW_SHOW);	 
		m_stampDialog.ShowWindow(SW_HIDE);

		break;
	case 1:
		//��ӡ����
		m_basicFunDialog.ShowWindow(SW_HIDE);	 
		m_stampDialog.ShowWindow(SW_SHOW);

	default:
		break;
	}
	*pResult = 0;
}
