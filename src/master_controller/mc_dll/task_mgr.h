#ifndef MASTERCTRL_TASK_MGR_H_
#define MASTERCTRL_TASK_MGR_H_

#include <string>
#include <map>
#include <boost/thread/thread.hpp>
#include "common_definitions.h"

namespace MC {

// ������ӡ�����
class TaskMgr {

public:
    static TaskMgr* GetInst();

    // ����Ψһ��ӡ�����
    std::string GeneTask();
   
    // ��ѯ��ӡ�����״̬
    enum TaskState QueryTaskState(const std::string& task_id);

    // ɾ����ӡ�����
    bool RemoveTask(const std::string& task_id);

private:
    TaskMgr() {

    }

private:
    boost::mutex                            task_mtx_;
    std::map<std::string, enum TaskState>   task_map_;

    static TaskMgr* task_inst;
};  // TaskMgr

std::string GenerateGUID(int bits = 16);

} // namespace MC

#endif // MASTERCTRL_TASK_MGR_H_
