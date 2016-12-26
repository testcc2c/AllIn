#ifndef QTDEMO_COMMON_H_
#define QTDEMO_COMMON_H_

#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <QString>

const QString DIALOG_HEADER = QString::fromLocal8Bit("���ʽӡ�ػ����Գ���V2.4");
const std::string kLogger = "QtDemo";
//#define INFINITE 0xffffffff
#define STATUS_TEXT 2000

enum OperationCMD {
    OC_OPEN_DEV_SUC = 0,
    OC_DEV_ALREADY_OPENED,
    OC_OPEN_DEV_FAIL,
    OC_CLOSE_DEV_SUC,
    OC_CLOSE_DEV_FAIL,
    OC_READ_CAPA_VERSION_FAIL,
    OC_DEV_NOT_OPENED,
    OC_WRITE_DATA_SUC,
    OC_WRITE_DATA_FAIL,
    OC_READ_DATA_SUC,
    OC_READ_DATA_FAIL,
};

#define MAX_CMD OC_READ_DATA_FAIL + 1

static QString cmd_des[MAX_CMD] = 
{
    QString::fromLocal8Bit("�豸�򿪳ɹ�"),
    QString::fromLocal8Bit("�豸�Ѵ�"),
    QString::fromLocal8Bit("�豸��ʧ��"),
    QString::fromLocal8Bit("�豸�رճɹ�"),
    QString::fromLocal8Bit("�豸�ر�ʧ��"),
    QString::fromLocal8Bit("��������С���汾��ʧ��"),
    QString::fromLocal8Bit("�豸δ��"),
    QString::fromLocal8Bit("д���ݳɹ�"),
    QString::fromLocal8Bit("д����ʧ��"),
    QString::fromLocal8Bit("�����ݳɹ�"),
    QString::fromLocal8Bit("������ʧ��"),
};

#endif //QTDEMO_COMMON_H_
