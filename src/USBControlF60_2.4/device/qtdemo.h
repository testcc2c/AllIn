#ifndef QTDEMO_H
#define QTDEMO_H

#include <windows.h>
#include <vector>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QTimer>
#include <QThread>
#include <boost/thread/thread.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/exception/all.hpp>
#include <base/base_pub.h>
#include "ui_qtdemo.h"
#include "preview.h"
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

    void AutoOpen();

    void PushMessage(Message* msg);

    ~QtDemo();

private:
    //���豸
    void HandleBtnOpenDev();

    //�ر��豸
    void HandleBtnCloseDev();

    void HandlePreviewPaper();
    void HandlePreviewEnv();
    void HandlePreviewSafe();

    void HandleLogoClicked();

    /////////////////////////////// �豸����ҳ ////////////////////////////

private:
    void InitDevControl();           // ҳ���ʼ��
    
    void HandleRedetect();             // ����豸
    void HandleViewError();          // ��ʾ�豸�������ԭ�򼰽������

    std::vector<ErrorCode> ec_vec_;

    ////////////////////////////// ��ʱ�� ///////////////////////////////////

private slots:
    void TimerDone();
    void UpdateRedetectTimer();

private:
    void UpdateDeviceSN();
    void UpdateDeviceStatus();
    void UpdateDoors();
    void UpdateAlarm();
    void UpdateStampers();
    void UpdateError();
    void UpdateCameras();

    void StartTimer(uint16_t milliseconds);
    void HexStr2Decimal(std::string hex_str, unsigned char* decimal_str, unsigned int len);
    void ClearBackground();
    bool ParseXML();

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
    CameraPreview* preview_dlg_;

    base::SynQueue<Message*> msg_queue_;
    boost::thread*  echo_thread_;

    QTimer* timer_;
    QLabel* status_label_;

    boost::mutex    count_mtx_;
    int             count_;
    QTimer*         update_timer_;

    QPalette        default_palette_;

    boost::property_tree::ptree xml_pt_;
};

#endif // QTDEMO_H
