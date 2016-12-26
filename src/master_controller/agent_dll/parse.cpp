#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include "parse.h"
#include "log.h"

MC::Config* MC::Config::config_inst = NULL;

bool MC::Config::Parse()
{
    std::string path;
    if (!MC::GetMoudulePath(path))
        return false;

    std::string xml_path = path + "client.xml";
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(xml_path, pt);
    std::string type = pt.get<std::string>("con.type");
    std::string name = pt.get<std::string>("con.name");

    if (0 == strcmp(type.c_str(), "PIPE")) {        // �ܵ�
        conn_type_ = MC::CT_PIPE;

        char cnn_name[1024] = { 0 };
        sprintf_s(cnn_name, "\\\\.\\pipe\\%s", name.c_str());
        pipe_name_ = cnn_name;
    }
    else if (0 == strcmp(type.c_str(), "MQ")) {     // ��Ϣ����
        conn_type_ = MC::CT_MQ;

        send_mq_name_ = name;
        recv_mq_name_ = name + "copy";
    }
    else {                                          // ��֧�ֵ�ͨ�ŷ�ʽ, �˳�
        Log::WriteLog(LL_ERROR, "AsynAPISet::Start->��֧�ֵ�ͨ�ŷ�ʽ, ֱ���˳�");
        return false;
    }

    return true;
}

