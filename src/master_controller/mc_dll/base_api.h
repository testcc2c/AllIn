#ifndef CONTROLLER_BASE_API_H_
#define CONTROLLER_BASE_API_H_

#include <string>
#include "log.h"
#include "tool.h"
#include "parse.h"
#include "USBControlF60.h"

#ifdef MASTERCTRL_EXPORTS
#define MASTERCTRL_API _declspec(dllexport)
#else
#define MASTERCTRL_API _declspec(dllimport)
#endif

namespace MC {

class MASTERCTRL_API BaseAPI {
public:
    BaseAPI(std::string des) : des_(des) {
        int ret = FOpenDev(NULL);
        MC::DeviceStat stat;
        stat.conn_ = ret == 0;
        stat.status_ = 0 == ret ? MC::CS_FREE : MC::CS_OPEN_FAIL;
        stat.cause_ = "��ʼ�����豸";
        MC::Tool::GetInst()->SetStat(stat);

        PrepareCamera();
    }

    virtual ~BaseAPI() {
        int ret = FCloseDev();
        MC::DeviceStat stat;
        stat.conn_ = !(ret == 0);
        stat.status_ = 0 == ret ? MC::CS_CLOSE_SUC : MC::CS_CLOSE_FAIL;
        stat.cause_ = "�����Ͽ��豸";
        MC::Tool::GetInst()->SetStat(stat);

        DisableCamera();
    }

private:
    std::string des_;
};

// ������ͼ��ӡ�����������ȡ���µ������ͼ���ĵ�λ��, ��������
void CaculatePos(
    int pCenterX,   // ԭͼ��/2
    int pCenterY,   // ԭͼ��/2
    int inX,        // ��ͼ��ӡ������x����
    int inY,        // ��ͼ��ӡ������y����
    int& outX,
    int& outY,
    int& angle);

// ������ͼ���ĵ������ȡԭͼ�����������ӡ�Ƕ�
int STSeachSealPoint(
    const char* in_src_img_name,
    int in_x,
    int in_y,
    double in_angle,
    int &out_x,
    int &out_y,
    double &out_angle);

// ��ԭͼ��ӡ��������ת��Ϊ�豸(ӡ�ػ�)��ӡ����(����)
MC::Point* GetSealCoord(int nX, int nY);

// ͼƬУ�����и�ڱ�
int CutImage(
    const std::string&  ori,
    std::string&        cut);

// �ϲ�ͼƬ
int MergeImage(
    const std::string& img1,
    const std::string& img2,
    const std::string& merged);

// ģ�����͡��Ƕȡ���ӡ��ʶ��
// �������:
// @img_path    --- ԭͼƬ·��
// �������:
// @model_type  --- ģ������
// @outangle    --- ��ת�Ƕ�
// @x           --- ��ӡ��� x ����(ģ���ϵ�)
// @y           --- ��ӡ��� y ����(ģ���ϵ�)
int GetModelTypeAnglePoint(
    const std::string&  img_path,       // ԭͼƬ·��
    std::string&        model_type,     // ģ������
    double&             outangle,       // ��ת�Ƕ�
    int&                x,
    int&                y);

// ���桢��֤��ʶ��
// �������:
// @cut_img     --- �ü����ͼƬ·��
// @model_type  --- �����ģ������
// �������:
// @out_model_type  --- ʶ�����ģ������
// @voucher_no      --- ƾ֤���
// @trace_no        --- ׷����
// @x               --- ����ڲü���ͼƬ����ӡx����
// @y               --- ����ڲü���ͼƬ����ӡy����
// @angle           --- ��ת�Ƕ�
int IdentifyImage(
    const std::string&  cut_img,
    const std::string&  model_type,
    std::string&        out_model_type,
    std::string&        voucher_no,
    std::string&        trace_no,
    int&                x,
    int&                y,
    int&                angle);

// Ҫ������ʶ��
// img      --- ԭͼ·��
// x        --- ���Ͻ�x����
// y        --- ���Ͻ�y����
// width    --- ��
// height   --- ��
// angle    --- ��ת�Ƕ�
// result   --- ʶ����
int IdentifyArea(
    const std::string&  img,
    int                 x,
    int                 y,
    int                 width,
    int                 height,
    int                 angle,
    std::string&        result);

} // namespace MC

#endif // CONTROLLER_BASE_API_H_
