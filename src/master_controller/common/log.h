#ifndef  CONTROLLER_LOG_H_
#define CONTROLLER_LOG_H_

#include <boost/thread/thread.hpp>

enum LogLevel {
    LL_DEBUG,       //����
    LL_MSG,         //��Ϣ
    LL_WARN,        //����
    LL_ERROR        //����
};

class Log {
public:
    static void WriteLog(LogLevel level, const char * fmt, ...);

private:
    static void init();

private:
    const static int MAX_LOG_LEN = 2048;

    static boost::mutex mtx_;
    static bool g_init;
};

#endif // CONTROLLER_LOG_H_
