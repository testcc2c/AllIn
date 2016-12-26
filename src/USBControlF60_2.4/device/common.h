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
#include <QColor>

const QString DIALOG_HEADER = QString::fromLocal8Bit("ũ�з��ʽӡ�ػ� �Լ칤��");

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

enum ErrorCode {
    EC_X0           = 0,
    EC_X1,
    EC_X_CENTER,
    EC_Y0,
    EC_Y1,
    EC_LOCATION,
    EC_SELECT_STAMPER,
    EC_Z,

    EC_STARTUP,

    EC_X_BUSY,
    EC_Y_BUSY,
    EC_Z_BUSY,

    EC_OUTSIZE_MEM,
    EC_DOOR_TIMEOUT,

    EC_MAX
};

static QString err_des[EC_MAX] =
{
    QString::fromLocal8Bit("X0���⴫��������"),
    QString::fromLocal8Bit("X1���⴫��������"),
    QString::fromLocal8Bit("X��λ���⴫��������"),
    QString::fromLocal8Bit("Y0���⴫��������"),
    QString::fromLocal8Bit("Y1���⴫��������"),
    QString::fromLocal8Bit("Y��ǰ��λ���⴫��������"),
    QString::fromLocal8Bit("ץ�¼����⴫��������"),
    QString::fromLocal8Bit("Z��ת�µ�λ���⴫��������"),

    QString::fromLocal8Bit("����ʱ����°�ȫ״̬����"),

    QString::fromLocal8Bit("X���æ"),
    QString::fromLocal8Bit("Y���æ"),
    QString::fromLocal8Bit("Z���æ"),

    QString::fromLocal8Bit("�ⲿ�洢���豸����"),
    QString::fromLocal8Bit("�ſ�����ʱ��ʾ")
};

static QString err_resolver[EC_MAX] =
{
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),

    QString::fromLocal8Bit("�²����¸��������仯����������ӡ�䣬�����±�����Ƿ��滻"),

    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),
    QString::fromLocal8Bit(""),

    QString::fromLocal8Bit("������Զ�ӡ��������Ч��ϵͳ����������Ч����ϵά����Ա"),
    QString::fromLocal8Bit("��رհ�ȫ�ż���ֽ��")
};

#endif //QTDEMO_COMMON_H_
