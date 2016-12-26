#ifndef CONTROLLER_TOOL_H_
#define CONTROLLER_TOOL_H_

#include <string>
#include <windows.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/condition_variable.hpp>
#include <windows.h>    // ��Ҫ����ͷ�ļ�RZCamera.hǰ��, ������벻��
#include "RZCamera.h"
#include "log.h"
#include "parse.h"
#include "common_definitions.h"

int _stdcall ConnectCallBack(const char* dev_path, unsigned int msg);

int _stdcall DevMsgCallBack(
    unsigned int        uMsg, 
    unsigned int        wParam, 
    long                lParam,
    unsigned char*      data, 
    unsigned char       len);

int PrepareCamera();

void DisableCamera();

namespace MC {

class Tool {
public:
    static Tool* GetInst();

    void SetStat(const DeviceStat& stat);

    bool Connected();

    ConnStatus GetStatus();

    std::string GetCause();

    void SetTop(int top);

    void SeteSafe(int safe);

    void SetPaper(int paper);

    const AllDoorStat& GetDoors();

private:
    Tool() {
        paper_door_ev_ = CreateEvent(
            NULL,       // Ĭ������
            TRUE,       // �ֶ�reset
            FALSE,      // ��ʼ״̬ non-signaled 
            NULL);      // δ����
    }

private:
    static Tool* g_inst;

    boost::mutex mutex_;
    DeviceStat device_stat_;

    boost::mutex door_mtx_;
    AllDoorStat doors_stat_;

public:
    HANDLE      paper_door_ev_;     // ��ֽ�Źر��¼�
};

}

#endif // CONTROLLER_TOOL_H_
