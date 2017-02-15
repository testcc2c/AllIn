#ifndef QTDEMO_H
#define QTDEMO_H

#include <windows.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QPainter>
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
    void OpenDevPost(const Message* msg);
    void CloseDevPost(const Message* msg);

    /////////////////////////////// �豸����ҳ ////////////////////////////

private:
    void InitDevControl();          //ҳ���ʼ��

    void HandleOpenSafeDoor();      //�򿪰�ȫ��
    void HandleCloseSafeDoor();     //�رհ�ȫ��
    void HandleReadSafe();          // ��ȫ��״̬
    void HandleReadPaper();         // ��ֽ��״̬

private:
    void HandleBeepOn();        //����
    void HandleBeepOff();       //�رշ�����

    void HandleQuerySlots();    //��ȡ����״̬

    void HandleABCCheck();          //ũ��У׼

    void HandleReadSavedMAC();       //��ȡ�豸�����MAC

private:
    void HandleReadLocalMac();       //��ȡ����MAC
    void HandleBinding();            //��MAC
    void HandleUnbinding();          //���
    void HandleQueryMAC();          // ��ѯMAC

    void HandleOpenSafeDoorAlarm();  //�������ű���
    void HandleCloseSafeDoorAlarm(); //�رտ��ű���
    void HandleOpenVibrationAlarm(); //�����񶯱���
    void HandleCloseVibrationAlarm();//�ر��񶯱���

    void HandleQuerySN();           // ��ȡ�豸���
    void HandleSetSN();             // �����豸���

    void HandleCnnStatus();
    void HandleOpenCnn();
    void HandleCloseCnn();

    void HandleOpenPaper();

    void HandleOpenPaperLED();
    void HandleClosePaperLED();
    void HandleOpenSafeLED();
    void HandleCloseSafeLED();

    void HandleSetResolution();
    void HandleSetDPI();

    void HandleStartRecord();
    void HandleStopRecord();

    void HandleGetModelType();

private slots:
    void HandleErrCodeChange(const QString &);

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

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

    QPoint      mouse_press_pt_;
    QPoint      mouse_moving_pt_;

private slots:
    void HandleSelectImg(int index);    // ѡ��ͼƬ(ԭͼ����ͼ)
    void HandleCamListChange(int index);

private:
    void HandleOriImgClick();   // �㰴ԭͼ
    void HandleCutImgClick();   // �㰴��ͼ
    void HandleCapture();       // ����
    void HandleSelectPic();     // ѡ��ͼƬ
    void HandlePreStamp();      // ѡ��

    void HandleIllusrate();
    void HandleCheckStamp();    // У׼����

    void HandleRecogCode();     // ���桢��֤��ʶ��
    void HandleRecogEle();      // Ҫ��ʶ��

    int which_cam_;
    void HandleOpenCam();
    void HandleCloseCam();
    void HandleQueryCam();

private:
    void InitSnapshot();

private:
    bool    capture_suc;    // ���ղ���ʾͼƬ�Ƿ�ɹ�
    int     img_type_;      // 0-ԭͼ, 1-��ͼ
    QImage* img_;

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

        StampPara() : ink(0), rfid(0), stamp_idx(0) {}
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

private:
    void HandleOridinary();         // ��ͨ��ӡ
    void HandleAutoStamp();         // �Զ���ӡ
    void HandlePrepare();           // ׼����ӡ

    void HandleFinishStamp();       // ������ӡ
    void HandleReleaseMachine();    // �ͷ�ӡ�ػ�

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

    void HandleCheckParam();         //��ȡ����Χ

    void HandleReadAlarm();         //��������״̬

    void HandleReadRFID();

    ////////////////////////////// ��ʱ�� ///////////////////////////////////

private slots:
    void TimerDone();

private:
    void StartTimer(uint16_t milliseconds);
    void HexStr2Decimal(std::string hex_str, unsigned char* decimal_str, unsigned int len);
    
    int RadioButtonSelected(QRadioButton** btns, int size);

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

    QTimer* timer_;
    QLabel* status_label_;
};

#endif // QTDEMO_H
