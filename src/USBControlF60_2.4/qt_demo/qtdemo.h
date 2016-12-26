#ifndef QTDEMO_H
#define QTDEMO_H

#include <windows.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QTimer>
#include <QThread>
#include <boost/thread/thread.hpp>
#include <boost/signals2/signal.hpp>
#include <base/base_pub.h>
#include "ui_qtdemo.h"
#include "common.h"
#include "message.h"

class Event;

class QtDemo : public QMainWindow
{
private:
    Q_OBJECT

signals:
    void explains();
    void ConnectStatus(const char* path, unsigned int msg);
    void UpdateProgress(int progress, int total);

 private slots:
    void HandleConnect(const char* path, unsigned int msg);

private:
    static boost::mutex mtx;
    static int connected;
    static int _stdcall ConnectCallBack(const char* path, unsigned int msg);
    static int _stdcall DevMsgCallBack(unsigned int uMsg, unsigned int wParam, long lParam,
                            unsigned char* data, unsigned char len);
    void ShowTimeElapsed(unsigned long begin);

    int register_conn_cb_;
    int register_msg_cb_;


public:
    QtDemo(QWidget *parent = 0);

    bool Init();

    void PushMessage(Message* msg);

    ~QtDemo();

    /////////////////////////////// ������ ////////////////////////////////

    //ʹ���硰connect(ui.combo_bound_mac_, SIGNAL(activated(int)), this, SLOT(HandleBoundMac(int)));��
    //���ź�-����Ҫ��ͷ�ļ���ʹ��private slots:��������Ӧ����
private slots:
    //tab�л�
    void HandleTabChange(int index);

private:
    //���豸
    void HandleBtnOpenDev();

    //�ر��豸
    void HandleBtnCloseDev();

    void OpenDevPost(const Message* msg);
    void CloseDevPost(const Message* msg);

    /////////////////////////////// �豸����ҳ ////////////////////////////

private:
    void InitDevControl();          //ҳ���ʼ��
    
    void HandleReset();             //��λ
    void HandleRestart();           //����
    void HandleSystemInfo();        //��ȡϵͳ��Ϣ
    void HandleExitEntainmainMode(); //�˳�ά��ģʽ
    void HandleEnterEntainmainMode();//����ά��ģʽ
    void HandleFirewareVersion();    //�̼��汾��

    void HandleOpenSafeDoor();      //�򿪰�ȫ��
    void HandleCloseSafeDoor();     //�رհ�ȫ��
    void HandleDeviceStatus();      //�豸״̬
    void HandleDoorStatus();        //��״̬

    void HandleSetSN();             //�������к�
    void HandleGetSN();             //��ȡ���к�

    void HandleSetPaperTimeout();   //��ֽ�ų�ʱ��ʾʱ��
    void HandleOpenPaperDoor();     //����ֽ��

    void HandleOpenLED();           //�򿪲����
    void HandleCloseLED();          //�رղ����
private slots:
    void HandleSliderLuminance(int val); //�����ȵ���

private:
    void HandleBeepAlways();        //����
    void HandleBeepInterval();      //�����
    void HandleDisableBeep();       //�رշ�����

    void HandleInfraredStatus();    //��ȡ����״̬

    void HandleABCCheck();          //ũ��У׼

    void HandleReadSavedMAC();       //��ȡ�豸�����MAC

private slots:
    void HandleBoundMac(int index);  //�Ѱ�MAC��ַ��combo

private:
    void HandleUnbinding();          //���
    void HandleReadLocalMac();       //��ȡ����MAC
    void HandleBinding();            //��MAC

    void HandleSetAuthCode();       //�����豸��֤��
    void HandleGetAuthCode();       //��ȡ�豸��֤��

    void HandleOpenSafeDoorAlarm();  //�������ű���
    void HandleCloseSafeDoorAlarm(); //�رտ��ű���
    void HandleOpenVibrationAlarm(); //�����񶯱���
    void HandleCloseVibrationAlarm();//�ر��񶯱���

    void HandleEnterTestMode();     //�������ģʽ
    void HandleExitTestMode();      //�˳�����ģʽ
    void HandleMoveX();             //�ƶ�X��
    void HandleMoveY();             //�ƶ�Y��
    void HandleTurnStamper();       //ת��

    void HandleEnableDebug();       //����debug
    void HandleDisableDebug();      //�ر�debug

    void HandleStamperStatus();     //������״̬

private:
    std::string GetLocalMAC();

private:
    static const int DEFAULT_LUMINANCE = 50; //Ĭ�ϲ��������ֵ

    struct MacSet {
        int combo_idx_;                         //�ɹ�����ɾ��combox��Ŀ������

        int unbind_idx_;                        //���mac��ַ(1��2)
        std::string unbind_mac_;                //���mac��ַ
        std::map<std::string, int> bound_mac_;  //��MAC, MAC��ַ--1/2

        MacSet() : combo_idx_(-1), unbind_idx_(-1) {}
    };

    MacSet macs_;

    bool test_mode_;        //����ģʽ��־

    /////////////////////////////// ����/����ҳ //////////////////////////////

private slots:
    void StampInk(int checked);

private:
    void HandleCapture();       //����
    void HandlePreStamp();      //ѡ��

private:
    void InitSnapshot();

private:
    QImage* img_;

    /////////////////////////////// ����ҳ ////////////////////////////////////

private:
    void InitUpdate();      //ҳ���ʼ��

    void HandleBtnSelectUpdateFile();   //ѡ�������ļ�
    void HandleBtnStartUpdating();      //��ʼ����

public:
    int BinFileCheck(const unsigned char* pReadBinBuffer, int len);
    int Syscheck(unsigned char fileSys, int &sys);
    int MCUcheck_SendB1(unsigned char* pReadBinBuffer, int len);

private:
    void firewareUpdateThread();

private:
    std::string     bin_file_;
    boost::thread*  update_thread_;

    //�豸�����¼�
public:
    static HANDLE UpdateEvent;

    //////////////////////////////// EEPROM����ҳ ////////////////////////////////////

private:
    void HandleBtnReadCapacityVersion();    //����С���汾��
    void HandleWriteData();                 //д����
    void HandleReadData();                  //������

    void HandleReadStampers();              //��ȡ��״̬
    void HandleLoadStamperMapping();        //������ӳ��
    void HandleSaveStamperMapping();        //������ӳ��

    void HandleWriteConvRatio();            //�洢ת������
    void HandleReadConvRatio();             //��ȡת������

    void HandleWriteKey();                  //д�豸keyֵ
    void HandleReadKey();                   //���豸keyֵ

private:
    QString current_ids[6];                 //��ǰӡ��ID, ����ȡ��״̬����ť���޸ĸ�ֵ

    ///////////////////////////// RFID����ҳ //////////////////////////////////

private:
    void InitRfidPage();            //ҳ���ʼ��

    void HandleRfidTutorial();      //����˵��

    void HandleAllaStamperStatus(); //������״̬
    void HandleRequestAllCard();    //�������п�

    void HandleSelectStamper();     //ѡ��
    void HandleGetRFID();           //������

private slots:
    void HandleKeyType(int index);

    //rfidҳ6��radiobutton
    void RfidStamper1();
    void RfidStamper2();
    void RfidStamper3();
    void RfidStamper4();
    void RfidStamper5();
    void RfidStamper6();

private:
    void HandleBtnSetBlockAddr();   //���ÿ����Ե�ַ
    void HandleVerifyKey();         //������У��
    void HandleRFIDFactoryCode();   //RFID��������
    void HandleWriteBlock();        //д��
    void HandleReadBlock();         //����

private:
    struct RFIDSet{
        std::map<int, unsigned int> stamper_rfid;

        unsigned char stamper;
        unsigned int rfid;

        unsigned char key_type;
        unsigned char key[6];
        unsigned char block;
    };

    ///////////////////////////// ���²��� ///////////////////////////

    //���²���
    struct StampPara {
        static const int MAX_X = 275; //����
        static const int MAX_Y = 250; //����
        static const int MAX_ANGLE = 360; //��

        static const int DEFAULT_X = 100;
        static const int DEFAULT_Y = 100;
        static const int DEFAULT_ANGLE = 0;

        static const int DEFAULT_WAIT = 1;
        static const int DEFAULT_TIMES = 9999;

        unsigned int rfid;
        unsigned char stamp_idx; //ӡ�º�, ��1��ʼ
        unsigned char ink;       //�Ƿ�պӡ��, 1--��
        unsigned char wait;      //�ȴ�ʱ��,��
        unsigned short x;
        unsigned short y;
        unsigned short angle;

        StampPara() : ink(0), rfid(0) {}
    };

private:
    void InitStamp();               //ҳ���ʼ��

    void HandleEnableFactory();     //��������ģʽ
    void HandleDisableFactory();    //�رչ���ģʽ

    void HandleStampReadStampers(); //��ȡ��״̬

private slots:
    void Stamper1();
    void Stamper2();
    void Stamper3();
    void Stamper4();
    void Stamper5();
    void Stamper6();

    void HandleCheckStampInk(int checked); //�Ƿ�պӡ��
    void HandleSliderX(int val);
    void HandleSliderY(int val);
    void HandleSliderAngle(int val);

private:
    void HandleOridinary();         //��ͨ����
    void HandleSelSeal();           //ѡ��
    void HandleConfirmStamp();      //ȷ�ϸ���ͨ��
    void HandleCheckMark();         //�����
    void HandldeCancelStamp();      //ȡ������(ӡ�¹�λ)

    void HandleReadStamp();         //��������Ϣ

    void HandleReadABC();           //ũ�ж�ȡ���ӱ�ǩ
    void HandleReadABCIndex();      //ũ�л�ȡӡ�²�λ��

private:
    unsigned int serial_;
    StampPara para_; //���²���

    ///////////////////////////// �����ӿ� //////////////////////////////////

private:
    void InitOther();

private:
    void HandleLock();   //����ӡ����
    void HandleUnlock(); //����ӡ����
    void HandleIsLock(); //�鿴����״̬

    void HandleWriteID(); //дӡ���Ǳ��
    void HandleReadID();  //��ӡ���Ǳ��

    void HandleWriteBackupSN(); //д���ð����к�
    void HandleReadBackupSN();  //�����ð����к�

    void HandleSetSideDoor();   //���ò�����ʾʱ��

    void HandleWriteMAC();      //дMAC
    void HandleReadMAC();       //��MAC

    void HandleReadVoltage();   //����ѹ

    void HandldeWriteCalPoints();   //дУ׼��
    void HandleReadPCalPoints();    //��У׼��

    void HandleReadRange();         //��ȡ����Χ

    void HandleReadAlarm();         //��������״̬

    void HandleHardwareVer();       //��ȡӲ���汾��

    ////////////////////////////// ��ʱ�� ///////////////////////////////////

private slots:
    void TimerDone();

private:
    void StartTimer(uint16_t milliseconds);
    void HexStr2Decimal(std::string hex_str, unsigned char* decimal_str, unsigned int len);
    
    int RadioButtonSelected(QRadioButton** btns, int size);

    void EventWorker();

    bool IsOpened();

    void Info(const QString& msg)
    {
        QMessageBox::information(
            NULL,
            DIALOG_HEADER,
            msg,
            QMessageBox::Yes,
            QMessageBox::NoButton);
    }

private:
    Ui::QtDemoClass ui;
    bool open_called; //�豸�Ƿ��ѱ���

    base::SynQueue<Message*> msg_queue_;
    base::SynQueue<Event*> event_queue_;
    boost::thread*  echo_thread_;

    RFIDSet rfid_;
    QTimer* timer_;
    QLabel* status_label_;
};

#endif // QTDEMO_H
