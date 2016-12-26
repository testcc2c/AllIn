// BasicFunDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestPSBC.h"
#include "BasicFunDialog.h"
#include "afxdialogex.h"



// CBasicFunDialog �Ի���

IMPLEMENT_DYNAMIC(CBasicFunDialog, CDialogEx)

CBasicFunDialog::CBasicFunDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasicFunDialog::IDD, pParent)
{

}

CBasicFunDialog::~CBasicFunDialog()
{
}

void CBasicFunDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, editInfo, m_editInfo);
	DDX_Control(pDX, editMachineNum, m_machineNum);
	DDX_Control(pDX, editDeviceNum, m_editDeviceNum);
	DDX_Control(pDX, editPX, m_editPx);
	DDX_Control(pDX, editPY, m_editPy);
	DDX_Control(pDX, editPAngle, m_PAngle);
	DDX_Control(pDX, editAbSafeDoor, m_eOpenSafeDoor);
	DDX_Control(pDX, editErrorNo, m_editNo);
	DDX_Control(pDX, editSeialNo, m_editSerialNo);
	DDX_Control(pDX, editSealInfo, m_sealEditInfo);
	DDX_Control(pDX, btnSlotInfo, m_slotInfo);
	DDX_Control(pDX, editStampId, m_slotStampIde);
}


BEGIN_MESSAGE_MAP(CBasicFunDialog, CDialogEx)
	ON_BN_CLICKED(btnOpenCon, &CBasicFunDialog::OnBnClickedbtnopencon)
	ON_BN_CLICKED(btnInitMachie, &CBasicFunDialog::OnBnClickedbtninitmachie)
	ON_BN_CLICKED(btnGetStampInfo, &CBasicFunDialog::OnBnClickedbtngetstampinfo)
	ON_BN_CLICKED(btnSetSlotInfo, &CBasicFunDialog::OnBnClickedbtnsetslotinfo)
	ON_BN_CLICKED(btnSetStampInfo, &CBasicFunDialog::OnBnClickedbtnsetstampinfo)
	ON_BN_CLICKED(btnSetSlotInfo3, &CBasicFunDialog::OnBnClickedbtnsetslotinfo3)
	ON_BN_CLICKED(btnOpenPageDoor, &CBasicFunDialog::OnBnClickedbtnopenpagedoor)
	ON_BN_CLICKED(btnCheckStamp, &CBasicFunDialog::OnBnClickedbtncheckstamp)
	ON_BN_CLICKED(btnEOpenSafeDoor, &CBasicFunDialog::OnBnClickedbtneopensafedoor)
	ON_BN_CLICKED(btnOpenSafeDoor, &CBasicFunDialog::OnBnClickedbtnopensafedoor)
	ON_BN_CLICKED(btnGetDeviceNum, &CBasicFunDialog::OnBnClickedbtngetdevicenum)
	ON_BN_CLICKED(btnGetDeviceTypeNum, &CBasicFunDialog::OnBnClickedbtngetdevicetypenum)
	ON_BN_CLICKED(btnGetPDoorStatus, &CBasicFunDialog::OnBnClickedbtngetpdoorstatus)
	ON_BN_CLICKED(btnOpenCamLight, &CBasicFunDialog::OnBnClickedbtnopencamlight)
	ON_BN_CLICKED(btnCloseCamLight, &CBasicFunDialog::OnBnClickedbtnclosecamlight)
	ON_BN_CLICKED(btnGetErrorInfo, &CBasicFunDialog::OnBnClickedbtngeterrorinfo)
	ON_BN_CLICKED(btnCloseCon, &CBasicFunDialog::OnBnClickedbtnclosecon)
	ON_BN_CLICKED(btnCheckCon, &CBasicFunDialog::OnBnClickedbtncheckcon)
	ON_BN_CLICKED(btnSlotInfo, &CBasicFunDialog::OnBnClickedbtnslotinfo)
    ON_BN_CLICKED(btnGetSDoorLockStatus, &CBasicFunDialog::OnBnClickedbtngetsdoorlockstatus)
END_MESSAGE_MAP()


// CBasicFunDialog ��Ϣ�������


void CBasicFunDialog::OnBnClickedbtnopencon()
{
	CString cserail;
	int result =0;
	CString cResult;
	m_editSerialNo.GetWindowText(cserail);
    if (cserail.IsEmpty()) {
        MessageBox("�������豸���к�");
        return;
    }

    char* serail = cserail.GetBuffer(cserail.GetLength());
    cserail.ReleaseBuffer();

	result=psbcStampApi::Instance()->connMachine(serail)==0?0:-1;
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtninitmachie()
{
	int result=0;
	result = psbcStampApi::Instance()->initializationMachine()==0?0:-1;
	ShowPromptInfo(result);
}

void CBasicFunDialog::ShowPromptInfo(int index)
{
    m_editInfo.Clear();

	CString tmpString("ִ�н��:");
	tmpString.AppendFormat("%s",psbcPromptInfo::Instance()->_mapPromptInfo[index].c_str());
	m_editInfo.SetWindowTextA(tmpString.GetBuffer(0));
}

void CBasicFunDialog::ShowPromptInfo(int index,CString info)
{
    m_editInfo.Clear();

	CString tmpString("ִ�н��:");
	tmpString.AppendFormat("%s",psbcPromptInfo::Instance()->_mapPromptInfo[index].c_str());
	tmpString.Append("   �����Ϣ:");
	tmpString.Append(info);
	m_editInfo.SetWindowTextA(tmpString.GetBuffer(0));
}

void CBasicFunDialog::OnBnClickedbtngetstampinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    // ��ȡ������
    CString m_machinNumInfo;
    m_sealEditInfo.GetWindowText(m_machinNumInfo);
    if (m_machinNumInfo.IsEmpty()) {
        MessageBox("�������ѯ�豸���");
        return;
    }

    char* machine_num = m_machinNumInfo.GetBuffer(m_machinNumInfo.GetLength());
    m_machinNumInfo.ReleaseBuffer();

    char *pinfoResult = psbcStampApi::Instance()->querySealInfo(machine_num);
	CString temp;
    if(pinfoResult != NULL)
	{
	    temp.AppendFormat("%s", pinfoResult);
	}
	else
    {
        temp.AppendFormat("��ѯ��Ϣʧ��:%s", pinfoResult);
	}

	ShowPromptInfo(0, temp.GetBuffer(temp.GetLength()));
}

void CBasicFunDialog::OnBnClickedbtnsetslotinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 char infoResult[256]={0};
	 char mechineNum[24]={0};

	 char *pinfoResult = psbcStampApi::Instance()->querySlotInfo(mechineNum);
	 memcpy(infoResult,pinfoResult,sizeof(infoResult));

	 CString temp;
	 temp.AppendFormat("�����Ϣ:%s",infoResult);
	 ShowPromptInfo(0,temp.GetBuffer(0));
	
}

void CBasicFunDialog::OnBnClickedbtnsetstampinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString machineNum;
	m_machineNum.GetWindowText(machineNum);
    if (machineNum.IsEmpty()) {
        MessageBox("�������豸���");
        return;
    }

    char* machineN = machineNum.GetBuffer(machineNum.GetLength());
    machineNum.ReleaseBuffer();

    CString stampId;
	m_slotStampIde.GetWindowText(stampId);
    if (stampId.IsEmpty()) {
        MessageBox("����������Ϣ");
        return;
    }

    char* slotId = stampId.GetBuffer(stampId.GetLength());
    stampId.ReleaseBuffer();

    // ��������Ϣ
	int result =psbcStampApi::Instance()->initStamp(machineN, slotId) == 0 ? 0 : -1;
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtnsetslotinfo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString deviceNum;
	m_editDeviceNum.GetWindowText(deviceNum);
    if (deviceNum.IsEmpty()) {
        MessageBox("�������豸���");
        return;
    }

    char* _devnum = deviceNum.GetBuffer(deviceNum.GetLength());
    deviceNum.ReleaseBuffer();

	int result = psbcStampApi::Instance()->setMachineNum(_devnum)==0?0:-1;
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtnopenpagedoor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    int result = psbcStampApi::Instance()->openPaperDoor() == 0 ? 0 : -1;
    ShowPromptInfo(result);
}


void CBasicFunDialog::OnBnClickedbtncheckstamp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString _cx;
	CString _cy;
	CString _cangle;
	int _x=0;
	int _y=0;
	int _angle=0;

	m_editPx.GetWindowText(_cx);
    if (_cx.IsEmpty()) {
        MessageBox("������X����ֵ");
        return;
    }

	m_editPy.GetWindowText(_cy);
    if (_cy.IsEmpty()) {
        MessageBox("������Y����ֵ");
        return;
    }

	m_PAngle.GetWindowText(_cangle);
    if (_cangle.IsEmpty()) {
        MessageBox("��������ת�Ƕ�ֵ");
        return;
    }

	_x = atoi(_cx.GetBuffer(0));
	_y = atoi(_cy.GetBuffer(0));
	_angle = atoi(_cangle.GetBuffer(0));

	int result = psbcStampApi::Instance()->checkManualPrintPara(_x,_y,_angle)==0?0:-2;
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtneopensafedoor()
{
	CString abInfo;
	m_eOpenSafeDoor.GetWindowText(abInfo);
    if (abInfo.IsEmpty()) {
        MessageBox("�������쳣������Ϣ");
        return;
    }

    char* ab_info = abInfo.GetBuffer(abInfo.GetLength());
    abInfo.ReleaseBuffer();

	int result = psbcStampApi::Instance()->openMachineBackDoorUnNormal(ab_info);
    if (0 == result)
	    ShowPromptInfo(result);
    else
        ShowPromptInfo(-1);
}

void CBasicFunDialog::OnBnClickedbtnopensafedoor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int result =0;
	result = psbcStampApi::Instance()->openMachineBackDoor();
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtngetdevicenum()
{
	char *presultInfo;
	CString cResult;
	presultInfo= psbcStampApi::Instance()->getMachineNum();
	cResult.AppendFormat("%s",presultInfo);
	ShowPromptInfo(0,cResult);
}

void CBasicFunDialog::OnBnClickedbtngetdevicetypenum()
{
	char *presultInfo;
	CString cResult;
	presultInfo= psbcStampApi::Instance()->getMachineType();
	cResult.AppendFormat("%s",presultInfo);
	ShowPromptInfo(0,cResult);
}

void CBasicFunDialog::OnBnClickedbtngetpdoorstatus()
{
    // 1-- - δ�ر�, 2-- - �ر�
    int result = psbcStampApi::Instance()->checkPaperDoorState();
    switch (result) {
    case 1:
        ShowPromptInfo(result);
        break;
    case 2:
        ShowPromptInfo(result);
        break;
    default:
        MessageBox("��ȡ״̬ʧ��");
        break;
    }
}

void CBasicFunDialog::OnBnClickedbtngetsdoorlockstatus()
{
    // TODO: Add your control notification handler code here
    // 1---δ�ر�, 2---�ر�,
    int result = psbcStampApi::Instance()->checkBackDoorState();
    switch (result) {
    case 1:
        ShowPromptInfo(3);
        break;
    case 2:
        ShowPromptInfo(4);
        break;
    default:
        MessageBox("��ȡ״̬ʧ��");
        break;
    }
}

void CBasicFunDialog::OnBnClickedbtnopencamlight()
{
	int result =psbcStampApi::Instance()->openVideoCapLight()==0?0:-1;
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtnclosecamlight()
{
	int result =psbcStampApi::Instance()->closeVideoCapLight()==0?0:-1;
	ShowPromptInfo(result);
}


void CBasicFunDialog::OnBnClickedbtngeterrorinfo()
{
	CString error;
	int errNo;
	CString cResult;
    m_editNo.GetWindowText(error);
    if (error.IsEmpty()) {
        MessageBox("�����������");
        return;
    }

    std::string err_str = error.GetBuffer(error.GetLength());
    error.ReleaseBuffer();
    for (size_t i = 0; i < err_str.length(); ++i) {
        char ch = err_str.at(i);
        if (ch < '0' || ch > '9')
            return ShowPromptInfo(-2);
    }

	errNo= atoi(error.GetBuffer(0));
	char *presultInfo=psbcStampApi::Instance()->geterrMsg(errNo);

	CString tmpErrorInfo;
    tmpErrorInfo.AppendFormat("%s",presultInfo);
	ShowPromptInfo(0, tmpErrorInfo);
}

void CBasicFunDialog::OnBnClickedbtnclosecon()
{
	int result = psbcStampApi::Instance()->disconnMachine()==0?0:-1;
	ShowPromptInfo(result);
}

void CBasicFunDialog::OnBnClickedbtncheckcon()
{
    // 0-- - �ɹ�, -1-- - ʧ��, ����������
	int result = psbcStampApi::Instance()->isConnMachine();
    switch (result) {
    case 0:
        ShowPromptInfo(7);
        break;
    case -1:
        ShowPromptInfo(8);
        break;
    default:
        ShowPromptInfo(-1);
        break;
    }
}

void CBasicFunDialog::OnBnClickedbtnslotinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    CString m_machinNumInfo;
    m_sealEditInfo.GetWindowText(m_machinNumInfo);
    if (m_machinNumInfo.IsEmpty()) {
        MessageBox("�������ѯ�豸���");
        return;
    }

    char* machine_num = m_machinNumInfo.GetBuffer(m_machinNumInfo.GetLength());
    m_machinNumInfo.ReleaseBuffer();

    char *pinfoResult = psbcStampApi::Instance()->querySlotInfo(machine_num);
    CString temp;
    if (pinfoResult != NULL)
    {
        temp.AppendFormat("�����Ϣ:%s", pinfoResult);
    }
    else
    {
        temp.AppendFormat("��ѯ��Ϣʧ��:%s", pinfoResult);
    }
	
	ShowPromptInfo(0,temp.GetBuffer(0));
}

BOOL CBasicFunDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    psbcStampApi::Instance()->connMachine("OnInitDialog");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
