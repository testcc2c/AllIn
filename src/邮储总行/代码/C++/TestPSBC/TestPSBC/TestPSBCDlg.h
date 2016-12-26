
// TestPSBCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "PSBCDialog.h"
#include "BasicFunDialog.h"
#include "StampDialog.h"


// CTestPSBCDlg �Ի���
class CTestPSBCDlg : public CDialogEx
{
// ����
public:
	CTestPSBCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTPSBC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_psbcTab;
	CStampDialog m_stampDialog;
	CBasicFunDialog m_basicFunDialog;
	afx_msg void OnTcnSelchangeTabPsbc(NMHDR *pNMHDR, LRESULT *pResult);
};
