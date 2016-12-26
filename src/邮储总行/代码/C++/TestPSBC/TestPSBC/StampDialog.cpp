// StampDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestPSBC.h"
#include "StampDialog.h"
#include "afxdialogex.h"
#include "psbctype.h"


// CStampDialog �Ի���

IMPLEMENT_DYNAMIC(CStampDialog, CDialogEx)

CStampDialog::CStampDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStampDialog::IDD, pParent)
	
{

}

CStampDialog::~CStampDialog()
{
}

void CStampDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, mualX, m_mualX);
	DDX_Control(pDX, mualY, m_mualY);
	DDX_Control(pDX, mualAngle, m_mualAnlge);
	DDX_Control(pDX, maulPrintNum, m_maulPrintNum);
	DDX_Control(pDX, editImagePath, m_ImagePath);
	DDX_Control(pDX, editType, m_editType);
	DDX_Control(pDX, editBorderPro, m_borderPro);
	DDX_Control(pDX, btnSrcImage, m_SrcImage);
	DDX_Control(pDX, btnDstImage, m_dstImage);
	DDX_Control(pDX, btnRotateAngle, m_RotateAngle);
	DDX_Control(pDX, eidtOutPut, m_editOutput);
	DDX_Control(pDX, ImgPicCtl, m_imgeCtrl);
    DDX_Control(pDX, IDC_COMBO_CAMERA_PARA, camera_para_type_);
    DDX_Control(pDX, IDC_EDIT_PARA_VALUE, camera_para_value_);
}


BEGIN_MESSAGE_MAP(CStampDialog, CDialogEx)
	ON_BN_CLICKED(btnSetPagingSeal, &CStampDialog::OnBnClickedbtnsetpagingseal)
	ON_BN_CLICKED(btnPhotoSensitive, &CStampDialog::OnBnClickedbtnphotosensitive)
	ON_BN_CLICKED(btnManuStamp, &CStampDialog::OnBnClickedbtnmanustamp)
	ON_BN_CLICKED(btnAutoStamp, &CStampDialog::OnBnClickedbtnautostamp)
	ON_BN_CLICKED(btnLockPrinter, &CStampDialog::OnBnClickedbtnlockprinter)
    ON_BN_CLICKED(IDC_BUTTON_SET_CAMERA, &CStampDialog::OnBnSetCameraParam)
	ON_BN_CLICKED(btnunLockPrinter, &CStampDialog::OnBnClickedbtnunlockprinter)
	ON_BN_CLICKED(btnLockStatus, &CStampDialog::OnBnClickedbtnlockstatus)
	ON_BN_CLICKED(btnOpenCam, &CStampDialog::OnBnClickedbtnopencam)
	ON_BN_CLICKED(btnCloseCam, &CStampDialog::OnBnClickedbtnclosecam)
	ON_BN_CLICKED(btnGetImage, &CStampDialog::OnBnClickedbtngetimage)
	ON_BN_CLICKED(btnRotateImage, &CStampDialog::OnBnClickedbtnrotateimage)
	ON_BN_CLICKED(btnCheckCamStatus, &CStampDialog::OnBnClickedbtncheckcamstatus)
	ON_BN_CLICKED(btnOpenLockInfo, &CStampDialog::OnBnClickedbtnopenlockinfo)
    ON_BN_CLICKED(btnDeleteLockInfo, &CStampDialog::OnBnClickedbtndeletelockinfo)
    ON_CBN_SELCHANGE(IDC_COMBO_CAMERA_PARA, &CStampDialog::OnComboChange)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CStampDialog ��Ϣ�������


void CStampDialog::OnBnClickedbtnsetpagingseal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int result = psbcStampApi::Instance()->setAcrossPageSeal() == 0 ? 0 : -1;
	ShowPromptInfo(result);
}

void CStampDialog::OnBnClickedbtnphotosensitive()
{
	CString _cx;
	CString _cy;
	CString _cangle;
	CString _cPrintNo;
	int _x=0;
	int _y=0;
	int _angle=0;
	int _PrintNo;

	m_mualX.GetWindowText(_cx);
    if (_cx.IsEmpty()) {
        MessageBox("��������ӡX����");
        return;
    }

	m_mualY.GetWindowText(_cy);
    if (_cy.IsEmpty()) {
        MessageBox("��������ӡY����");
        return;
    }

	m_mualAnlge.GetWindowText(_cangle);
	m_maulPrintNum.GetWindowText(_cPrintNo);

	_x     = atoi(_cx.GetBuffer(0));
	_y     = atoi(_cy.GetBuffer(0));
	_angle = atoi(_cangle.GetBuffer(0));
	_PrintNo = atoi(_cPrintNo.GetBuffer(0));

	int result = psbcStampApi::Instance()->manualPrintStartByLight(
        _PrintNo,
        _x,
        _y,
        _angle) == 0 ?0 : -1;
    ShowPromptInfo(result);
}

void CStampDialog::OnBnClickedbtnmanustamp()
{
    CString _cx;
	CString _cy;
	CString _cangle;
	CString _cPrintNo;
	int _x=0;
	int _y=0;
	int _angle=0;
	int _PrintNo;
	int result = 0;

	m_mualX.GetWindowText(_cx);
    if (_cx.IsEmpty()) {
        MessageBox("��������ӡX����");
        return;
    }

	m_mualY.GetWindowText(_cy);
    if (_cy.IsEmpty()) {
        MessageBox("��������ӡY����");
        return;
    }

	m_mualAnlge.GetWindowText(_cangle);
	m_maulPrintNum.GetWindowText(_cPrintNo);

	_x     = atoi(_cx.GetBuffer(0));
	_y     = atoi(_cy.GetBuffer(0));
	_angle = atoi(_cangle.GetBuffer(0));
    _PrintNo = atoi(_cPrintNo.GetBuffer(0));

	result = psbcStampApi::Instance()->manualPrintStart(
        _PrintNo,
        _x,
        _y,
        _angle) == 0 ? 0 : -1;
    ShowPromptInfo(result);
}

void CStampDialog::OnBnClickedbtnautostamp()
{
    MessageBox("ע��: ��ʱX,Y�����������ֵ�ĵ�λ�Ǻ���(mm)");

    CString _cx;
	CString _cy;
	CString _cangle;
	CString _cPrintNo;
	int _x=0;
	int _y=0;
	int _angle=0;
	int _PrintNo;

	m_mualX.GetWindowText(_cx);
    if (_cx.IsEmpty()) {
        MessageBox("��������ӡX����");
        return;
    }

	m_mualY.GetWindowText(_cy);
    if (_cy.IsEmpty()) {
        MessageBox("��������ӡY����");
        return;
    }

	m_mualAnlge.GetWindowText(_cangle);
	m_maulPrintNum.GetWindowText(_cPrintNo);

	_x     = atoi(_cx.GetBuffer(0));
	_y     = atoi(_cy.GetBuffer(0));
	_angle = atoi(_cangle.GetBuffer(0));
	_PrintNo = atoi(_cPrintNo.GetBuffer(0));

	int result = psbcStampApi::Instance()->autoPrintStart(
        _PrintNo,
        _x,
        _y,
        _angle) == 0 ? 0 : -1;
    ShowPromptInfo(result);
}

void CStampDialog::OnBnClickedbtnlockprinter()
{
	int result=0;
	result = psbcStampApi::Instance()->lockPrinter()==0?0:-1;
	ShowPromptInfo(result);
}

void CStampDialog::OnComboChange()
{
    int idx = camera_para_type_.GetCurSel();
    CString text;
    camera_para_type_.GetLBText(idx, text);

    CString val;
    camera_para_value_.GetWindowText(val);
    if (val.IsEmpty()) {
        MessageBox("���������ֵ");
        return;
    }

    int para_val = atoi(val.GetBuffer(val.GetLength()));
    val.ReleaseBuffer();

    camera_para_map_.insert(std::make_pair(text, para_val));

    MessageBox(text + " " + val);
}

void CStampDialog::OnBnSetCameraParam()
{
    if (camera_para_map_.size() < 7) {
        MessageBox("δ�����в�����������, δ���ò�������ȡ��ֵΪ0���д���.");
    }

    int brightness = 0;
    int constrast = 0;
    int hue = 0;
    int saturation = 0;
    int sharpness = 0;
    int whitebalance = 0;
    int gain = 0;
    std::map<CString, int>::iterator it = camera_para_map_.begin();
    for (; it != camera_para_map_.end(); ++it) {
        if (it->first == "����") {
            brightness = it->second;
            continue;
        }

        if (it->first == "�Աȶ�") {
            constrast = it->second;
            continue;
        }

        if (it->first == "ɫ��") {
            hue = it->second;
            continue;
        }

        if (it->first == "���Ͷ�") {
            saturation = it->second;
            continue;
        }

        if (it->first == "������") {
            sharpness = it->second;
            continue;
        }

        if (it->first == "��ƽ��") {
            whitebalance = it->second;
            continue;
        }

        if (it->first == "�ع�ֵ") {
            gain = it->second;
            continue;
        }
    }

    int ret = psbcStampApi::Instance()->setVedioProperties(
        brightness,
        constrast,
        hue,
        saturation,
        sharpness,
        whitebalance,
        gain);
    ShowPromptInfo(ret);
}

void CStampDialog::OnBnClickedbtnunlockprinter()
{
	int result=0;
	result = psbcStampApi::Instance()->unLockPrinter()==0?0:-1;
	ShowPromptInfo(result);
}

void CStampDialog::OnBnClickedbtnlockstatus()
{
    int result = psbcStampApi::Instance()->checkLockState();
    switch (result) {
    case 0:
        ShowPromptInfo(5);
        break;
    case -1:
        ShowPromptInfo(6);
        break;
    default:
        ShowPromptInfo(-1);
        break;
    }
}

void CStampDialog::OnBnClickedbtnopencam()
{
	int result = psbcStampApi::Instance()->openVideoCap()==0?9:10;
	ShowPromptInfo(result);
}

void CStampDialog::OnBnClickedbtnclosecam()
{
	int result = psbcStampApi::Instance()->closeVideoCap()==0?11:12;
	ShowPromptInfo(result);
}

// ����-��ȡͼ��
void CStampDialog::OnBnClickedbtngetimage()
{
    // ��ͼ·��
    CString _cPath;
	m_ImagePath.GetWindowText(_cPath);
    if (_cPath.IsEmpty()) {
        MessageBox("������ͼƬ���·��");
        return;
    }

    char* szPath = _cPath.GetBuffer(_cPath.GetLength());
    _cPath.ReleaseBuffer();

    // ͼƬ��ʽ
    CString _cType;
	m_editType.GetWindowText(_cType);
    if (_cType.IsEmpty()) {
        MessageBox("�밴Ҫ������ͼƬ��ʽ");
        return;
    }

    char* type_str = _cType.GetBuffer(_cType.GetLength());
    int type = atoi(type_str);
    if (type != 0 && type != 1) {
        MessageBox("��֧�ֵ�ͼƬ��ʽ, ����������");
        return;
    }

    // �Ƿ��б�
    CString _cbp;
	m_borderPro.GetWindowText(_cbp);
    if (_cbp.IsEmpty()) {
        MessageBox("��ָ���Ƿ����ͼ����");
        return;
    }

    char* erase_str = _cbp.GetBuffer(_cbp.GetLength());
    _cbp.ReleaseBuffer();
    int bp = atoi(erase_str);
    if (bp != 0 && bp != 1) {
        MessageBox("��ָ���Ƿ����ͼ����");
        return;
    }

	int result = psbcStampApi::Instance()->getImageFormat(
        (const char *)szPath,
        type,
        bp) ==0 ? 0 : -1;
    if (0 != result) {
        MessageBox("����ʧ��");
        return;
    }

	// ��ȡͼƬ�Ŀ� �߶�  
	UpdateWindow();
	int height, width;
	CRect rect;//���������
	CRect rect1;
	CImage image; //����ͼƬ��
	//����·������ͼƬ  
	if(image.Load((char*)szPath)==0) {
		height = image.GetHeight();
		width = image.GetWidth();
		m_imgeCtrl.GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		CDC *pDc = m_imgeCtrl.GetDC();//���pictrue�ؼ���Dc
		SetStretchBltMode(pDc->m_hDC,STRETCH_HALFTONE); 
		image.StretchBlt(pDc->m_hDC,rect,SRCCOPY);
		ReleaseDC(pDc);//�ͷ�picture�ؼ���Dc
	}
}

void CStampDialog::OnBnClickedbtnrotateimage()
{
	CString _csrcPath;
	CString _cdestPath;
	CString _cangle;

	int result = 0;
	CImage  image;  
 
	m_SrcImage.GetWindowText(_csrcPath);
    if (_csrcPath.IsEmpty()) {
        MessageBox("������Դͼ·��");
        return;
    }

    char* szSrcPath = _csrcPath.GetBuffer(_csrcPath.GetLength());
    _csrcPath.ReleaseBuffer();

	m_dstImage.GetWindowText(_cdestPath);
    if (_cdestPath.IsEmpty()) {
        MessageBox("������Ŀ��ͼƬ·��");
        return;
    }

    char* szDstPath = _cdestPath.GetBuffer(_cdestPath.GetLength());
    _cdestPath.ReleaseBuffer();

	m_RotateAngle.GetWindowText(_cangle);
    if (_cangle.IsEmpty()) {
        MessageBox("��ָ����ת�Ƕ�");
        return;
    }

	int cangle = atoi(_cangle.GetBuffer(_cangle.GetLength()));
    _cangle.ReleaseBuffer();

    // ����·������ͼƬ
	result = psbcStampApi::Instance()->revolveImg(
        (const char*)szSrcPath,
        (const char*)szDstPath,
        cangle) == 0 ? 0 : -1;
    if (0 != result) {
        MessageBox("ͼƬ��תʧ��");
        return;
    }

	int height, width;
	CRect rect;//���������
	CRect rect1;
	//����·������ͼƬ  
	if(image.Load((char*)szDstPath)==0)
	{
		height = image.GetHeight();
		width = image.GetWidth();
		m_imgeCtrl.GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		CDC *pDc = m_imgeCtrl.GetDC();//���pictrue�ؼ���Dc
		SetStretchBltMode(pDc->m_hDC,STRETCH_HALFTONE); 
		image.StretchBlt(pDc->m_hDC,rect,SRCCOPY);
		ReleaseDC(pDc);//�ͷ�picture�ؼ���Dc
	}
}

void CStampDialog::OnBnClickedbtncheckcamstatus()
{
    int result = psbcStampApi::Instance()->checkVideoState();
    char buf[512] = { 0 };
    sprintf(buf, "��ǰ����ͷ%s", result == 1 ? "��" : "�ر�");
    m_editOutput.Clear();
    m_editOutput.SetWindowTextA(buf);
}

void CStampDialog::OnBnClickedbtnopenlockinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char* pLockInof = psbcStampApi::Instance()->readOpenBackDoorExceptionInfo();
    char buf[512] = { 0 };
    sprintf(buf, "�����쳣������¼: %s", pLockInof);

    m_editOutput.Clear();
    m_editOutput.SetWindowTextA(buf);
}

void CStampDialog::OnBnClickedbtndeletelockinfo()
{
	int result = psbcStampApi::Instance()->delOpenBackDoorExceptionInfo();
    char buf[512] = { 0 };
    sprintf(buf, "����쳣������Ϣ��¼%s", result == 0? "�ɹ�" : "ʧ��");

    m_editOutput.Clear();
    m_editOutput.SetWindowTextA(buf);
}

void CStampDialog::ShowPromptInfo(int index)
{
	CString tmpString("ִ�н��:");
	tmpString.AppendFormat("%s",psbcPromptInfo::Instance()->_mapPromptInfo[index].c_str());
	m_editOutput.SetWindowTextA(tmpString.GetBuffer(0));
}

void CStampDialog::ShowPromptInfo(int index,CString info)
{
	CString tmpString("ִ�н��:");
	tmpString.AppendFormat("%s",psbcPromptInfo::Instance()->_mapPromptInfo[index].c_str());
	tmpString.Append("   �����Ϣ:");
	tmpString.Append(info);
	m_editOutput.SetWindowTextA(tmpString.GetBuffer(0));
}

HBRUSH CStampDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == this)
	{
		CBrush m_brBk;
		return m_brBk;

	}

	return hbr;

}


BOOL CStampDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    // ���ղ���
	m_ImagePath.SetWindowTextA("C:\\reImag.jpg");
	m_editType.SetWindowTextA("1");
	m_borderPro.SetWindowTextA("1");

	m_SrcImage.SetWindowTextA("C:\\reImag.jpg");
	m_dstImage.SetWindowTextA("C:\\dstImag.jpg");
	m_RotateAngle.SetWindowTextA("90");

    // Ĭ����ӡ����
    m_mualAnlge.SetWindowTextA("0");
    m_maulPrintNum.SetWindowTextA("1");

    // ��������ͷ����
    camera_para_map_.clear();
    camera_para_type_.Clear();
    camera_para_type_.AddString("����");
    camera_para_type_.AddString("�Աȶ�");
    camera_para_type_.AddString("ɫ��");
    camera_para_type_.AddString("���Ͷ�");
    camera_para_type_.AddString("������");
    camera_para_type_.AddString("��ƽ��");
    camera_para_type_.AddString("�ع�ֵ");
    camera_para_type_.SetCurSel(camera_para_type_.AddString("���������ֵ���л���Ӧ��������"));

    m_mualX.SetWindowTextA("1000");
    m_mualY.SetWindowTextA("600");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
