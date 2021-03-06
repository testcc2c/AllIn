/********************************************************************************
** Form generated from reading UI file 'qtdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDEMO_H
#define UI_QTDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtDemoClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_control_dev;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_9;
    QPushButton *pb_beep_on_;
    QPushButton *pb_beep_off_;
    QGroupBox *groupBox_7;
    QPushButton *pb_paper_status_;
    QGroupBox *groupBox_13;
    QPushButton *pb_read_local_mac_;
    QLineEdit *le_mac_;
    QPushButton *pb_binding_mac_;
    QPushButton *pb_mac_unbinding_;
    QPushButton *pb_query_mac_;
    QLineEdit *le_mac1_;
    QLineEdit *le_mac2_;
    QPushButton *pb_dev_type_;
    QPushButton *pb_system_;
    QGroupBox *groupBox_21;
    QPushButton *pb_open_safe_door_alarm_;
    QPushButton *pb_close_safe_door_alarm_;
    QPushButton *pb_open_vibration_alarm_;
    QPushButton *pb_close_vibration_alarm_;
    QGroupBox *groupBox_6;
    QPushButton *pb_open_safe_door_;
    QPushButton *pb_close_safe_door_;
    QPushButton *pb_safe_status_;
    QPushButton *pb_query_stamper_;
    QPushButton *pb_dev_status_;
    QGroupBox *groupBox_4;
    QPushButton *pb_query_slots_;
    QGroupBox *groupBox_8;
    QLineEdit *le_stamper_idx_;
    QPushButton *pb_cali_stamp_;
    QLabel *label;
    QGroupBox *groupBox_22;
    QLabel *label_2;
    QLineEdit *le_err_code_;
    QLineEdit *le_show_err_msg_;
    QLineEdit *le_show_err_resolver_;
    QLabel *label_9;
    QLineEdit *le_cam_width_;
    QPushButton *pb_set_resolution_;
    QLabel *label_10;
    QGroupBox *groupBox_26;
    QPushButton *pb_get_sn_;
    QLineEdit *le_show_sn_;
    QPushButton *pb_set_sn_;
    QLineEdit *le_set_sn_;
    QLineEdit *le_cam_height_;
    QPushButton *pb_set_dpi_;
    QLabel *label_7;
    QPushButton *pb_open_paper_;
    QPushButton *pb_cnn_status_;
    QPushButton *pb_open_;
    QPushButton *pb_close_;
    QLineEdit *le_paper_timeout_;
    QLabel *label_8;
    QLineEdit *le_led_val_;
    QPushButton *pb_enter_main_;
    QPushButton *pb_open_paper_led_;
    QPushButton *pb_close_paper_led_;
    QPushButton *pb_open_safe_led_;
    QPushButton *pb_close_safe_led_;
    QPushButton *pb_exit_main_;
    QPushButton *pb_top_status_;
    QPushButton *pb_reset_;
    QPushButton *pb_restart_;
    QWidget *tab_stamper;
    QPushButton *pb_capture_;
    QPushButton *pb_select_picture_;
    QLabel *ori_image_;
    QLabel *cut_image_;
    QPushButton *pb_ori_img_;
    QPushButton *pb_cut_img_;
    QGroupBox *groupBox;
    QLabel *label_5;
    QLabel *label_11;
    QLineEdit *le_x_in_img_;
    QLineEdit *le_y_in_img_;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *le_input_width_;
    QLineEdit *le_input_height_;
    QPushButton *pb_illustrate_;
    QLabel *label_12;
    QLabel *label_27;
    QGroupBox *groupBox_2;
    QComboBox *combo_img_sel_;
    QPushButton *pb_recog_code_;
    QLabel *la_code_result_;
    QPushButton *pb_recog_ele_;
    QLabel *le_ele_result_;
    QGroupBox *groupBox_23;
    QLineEdit *le_y_in_dev_;
    QLabel *label_6;
    QLabel *label_13;
    QLineEdit *le_x_in_dev_;
    QPushButton *pb_check_stamp_;
    QGroupBox *groupBox_24;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *le_ori_path_;
    QLineEdit *le_cut_path_;
    QComboBox *cb_cam_list_;
    QPushButton *pb_open_cam_;
    QPushButton *pb_close_cam_;
    QPushButton *pb_status_cam_;
    QPushButton *pb_cvt_coord_;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_5;
    QGroupBox *groupBox_3;
    QPushButton *pb_prepare_;
    QLineEdit *le_task_id_;
    QLineEdit *le_paper_door_timeout_;
    QLabel *label_30;
    QLabel *label_31;
    QGroupBox *groupBox_16;
    QRadioButton *radio_stamper6_;
    QRadioButton *radio_stamper4_;
    QRadioButton *radio_stamper1_;
    QRadioButton *radio_stamper2_;
    QRadioButton *radio_stamper3_;
    QRadioButton *radio_stamper5_;
    QPushButton *pb_stamp_read_stampers_;
    QCheckBox *cb_stamp_stamp_ink_;
    QGroupBox *groupBox_20;
    QPushButton *pb_ordinary_stamp_;
    QPushButton *pb_auto_stamp_;
    QGroupBox *groupBox_25;
    QPushButton *pb_release_machine_;
    QPushButton *pb_finish_stamp_;
    QLabel *camera_preview_;
    QPushButton *pb_start_preview_;
    QPushButton *pb_stop_preview_;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QPushButton *pb_stamper_lock_;
    QLabel *label_16;
    QPushButton *pb_read_rfid_;
    QPushButton *pb_unlock_;
    QLabel *label_14;
    QLineEdit *le_video_path_;
    QLineEdit *le_rfid_slot_;
    QPushButton *pb_stop_record_;
    QPushButton *pb_lock_;
    QPushButton *pb_start_record_;
    QLineEdit *le_ratio_x_;
    QLineEdit *le_ratio_y_;
    QPushButton *pb_factory_disable_;
    QPushButton *pb_read_ratio_;
    QPushButton *pb_read_cal_pts_;
    QPushButton *pb_factory_enable_;
    QPushButton *pb_write_ratio_;
    QPushButton *pb_write_cal_pts_;
    QGroupBox *groupBox_12;
    QLabel *label_15;
    QLabel *label_17;
    QLineEdit *le_sidedoor_close_;
    QPushButton *pb_set_sidedoor_;
    QLineEdit *le_sidedoor_timeout_;
    QGroupBox *groupBox_17;
    QLabel *label_19;
    QLineEdit *le_x_coord_;
    QLabel *label_23;
    QLineEdit *le_y_coord_;
    QPushButton *pb_check_param_;
    QLineEdit *le_angle_;
    QLabel *label_24;
    QGroupBox *groupBox_19;
    QLabel *label_46;
    QLabel *label_door_alarm_;
    QLabel *label_48;
    QLabel *label_vibration_alarm_;
    QPushButton *pb_read_alarm_;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtDemoClass)
    {
        if (QtDemoClass->objectName().isEmpty())
            QtDemoClass->setObjectName(QStringLiteral("QtDemoClass"));
        QtDemoClass->resize(1706, 1041);
        centralWidget = new QWidget(QtDemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        tabWidget->setFont(font);
        tabWidget->setAutoFillBackground(true);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setMovable(false);
        tab_control_dev = new QWidget();
        tab_control_dev->setObjectName(QStringLiteral("tab_control_dev"));
        gridLayout = new QGridLayout(tab_control_dev);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_9 = new QGroupBox(tab_control_dev);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_9->setFont(font1);
        pb_beep_on_ = new QPushButton(groupBox_9);
        pb_beep_on_->setObjectName(QStringLiteral("pb_beep_on_"));
        pb_beep_on_->setGeometry(QRect(20, 30, 91, 28));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        pb_beep_on_->setFont(font2);
        pb_beep_off_ = new QPushButton(groupBox_9);
        pb_beep_off_->setObjectName(QStringLiteral("pb_beep_off_"));
        pb_beep_off_->setGeometry(QRect(160, 30, 91, 28));
        pb_beep_off_->setFont(font2);

        gridLayout->addWidget(groupBox_9, 0, 0, 2, 2);

        groupBox_7 = new QGroupBox(tab_control_dev);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setFont(font1);
        pb_paper_status_ = new QPushButton(groupBox_7);
        pb_paper_status_->setObjectName(QStringLiteral("pb_paper_status_"));
        pb_paper_status_->setGeometry(QRect(60, 30, 93, 28));
        pb_paper_status_->setFont(font2);

        gridLayout->addWidget(groupBox_7, 0, 2, 2, 4);

        groupBox_13 = new QGroupBox(tab_control_dev);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setFont(font1);
        pb_read_local_mac_ = new QPushButton(groupBox_13);
        pb_read_local_mac_->setObjectName(QStringLiteral("pb_read_local_mac_"));
        pb_read_local_mac_->setGeometry(QRect(10, 30, 111, 28));
        pb_read_local_mac_->setFont(font2);
        le_mac_ = new QLineEdit(groupBox_13);
        le_mac_->setObjectName(QStringLiteral("le_mac_"));
        le_mac_->setGeometry(QRect(140, 30, 221, 31));
        le_mac_->setFont(font2);
        pb_binding_mac_ = new QPushButton(groupBox_13);
        pb_binding_mac_->setObjectName(QStringLiteral("pb_binding_mac_"));
        pb_binding_mac_->setGeometry(QRect(10, 70, 111, 28));
        pb_binding_mac_->setFont(font2);
        pb_mac_unbinding_ = new QPushButton(groupBox_13);
        pb_mac_unbinding_->setObjectName(QStringLiteral("pb_mac_unbinding_"));
        pb_mac_unbinding_->setGeometry(QRect(10, 110, 111, 28));
        pb_mac_unbinding_->setFont(font2);
        pb_query_mac_ = new QPushButton(groupBox_13);
        pb_query_mac_->setObjectName(QStringLiteral("pb_query_mac_"));
        pb_query_mac_->setGeometry(QRect(10, 160, 111, 28));
        pb_query_mac_->setFont(font2);
        le_mac1_ = new QLineEdit(groupBox_13);
        le_mac1_->setObjectName(QStringLiteral("le_mac1_"));
        le_mac1_->setGeometry(QRect(140, 150, 221, 22));
        le_mac2_ = new QLineEdit(groupBox_13);
        le_mac2_->setObjectName(QStringLiteral("le_mac2_"));
        le_mac2_->setGeometry(QRect(140, 170, 221, 22));

        gridLayout->addWidget(groupBox_13, 0, 6, 4, 4);

        pb_dev_type_ = new QPushButton(tab_control_dev);
        pb_dev_type_->setObjectName(QStringLiteral("pb_dev_type_"));

        gridLayout->addWidget(pb_dev_type_, 0, 11, 1, 2);

        pb_system_ = new QPushButton(tab_control_dev);
        pb_system_->setObjectName(QStringLiteral("pb_system_"));

        gridLayout->addWidget(pb_system_, 1, 13, 2, 1);

        groupBox_21 = new QGroupBox(tab_control_dev);
        groupBox_21->setObjectName(QStringLiteral("groupBox_21"));
        QFont font3;
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        groupBox_21->setFont(font3);
        pb_open_safe_door_alarm_ = new QPushButton(groupBox_21);
        pb_open_safe_door_alarm_->setObjectName(QStringLiteral("pb_open_safe_door_alarm_"));
        pb_open_safe_door_alarm_->setGeometry(QRect(20, 30, 91, 28));
        pb_open_safe_door_alarm_->setFont(font2);
        pb_close_safe_door_alarm_ = new QPushButton(groupBox_21);
        pb_close_safe_door_alarm_->setObjectName(QStringLiteral("pb_close_safe_door_alarm_"));
        pb_close_safe_door_alarm_->setGeometry(QRect(160, 30, 91, 28));
        pb_close_safe_door_alarm_->setFont(font2);
        pb_open_vibration_alarm_ = new QPushButton(groupBox_21);
        pb_open_vibration_alarm_->setObjectName(QStringLiteral("pb_open_vibration_alarm_"));
        pb_open_vibration_alarm_->setGeometry(QRect(20, 70, 91, 28));
        pb_open_vibration_alarm_->setFont(font2);
        pb_close_vibration_alarm_ = new QPushButton(groupBox_21);
        pb_close_vibration_alarm_->setObjectName(QStringLiteral("pb_close_vibration_alarm_"));
        pb_close_vibration_alarm_->setGeometry(QRect(160, 70, 91, 28));
        pb_close_vibration_alarm_->setFont(font2);

        gridLayout->addWidget(groupBox_21, 2, 0, 2, 2);

        groupBox_6 = new QGroupBox(tab_control_dev);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setFont(font1);
        pb_open_safe_door_ = new QPushButton(groupBox_6);
        pb_open_safe_door_->setObjectName(QStringLiteral("pb_open_safe_door_"));
        pb_open_safe_door_->setGeometry(QRect(10, 30, 81, 28));
        pb_open_safe_door_->setFont(font2);
        pb_close_safe_door_ = new QPushButton(groupBox_6);
        pb_close_safe_door_->setObjectName(QStringLiteral("pb_close_safe_door_"));
        pb_close_safe_door_->setGeometry(QRect(10, 70, 81, 28));
        pb_close_safe_door_->setFont(font2);
        pb_safe_status_ = new QPushButton(groupBox_6);
        pb_safe_status_->setObjectName(QStringLiteral("pb_safe_status_"));
        pb_safe_status_->setGeometry(QRect(110, 40, 93, 28));
        pb_safe_status_->setFont(font2);

        gridLayout->addWidget(groupBox_6, 2, 2, 2, 4);

        pb_query_stamper_ = new QPushButton(tab_control_dev);
        pb_query_stamper_->setObjectName(QStringLiteral("pb_query_stamper_"));

        gridLayout->addWidget(pb_query_stamper_, 2, 11, 1, 2);

        pb_dev_status_ = new QPushButton(tab_control_dev);
        pb_dev_status_->setObjectName(QStringLiteral("pb_dev_status_"));

        gridLayout->addWidget(pb_dev_status_, 3, 11, 1, 2);

        groupBox_4 = new QGroupBox(tab_control_dev);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFont(font1);
        pb_query_slots_ = new QPushButton(groupBox_4);
        pb_query_slots_->setObjectName(QStringLiteral("pb_query_slots_"));
        pb_query_slots_->setGeometry(QRect(40, 40, 101, 28));
        pb_query_slots_->setFont(font2);

        gridLayout->addWidget(groupBox_4, 4, 0, 3, 2);

        groupBox_8 = new QGroupBox(tab_control_dev);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setEnabled(true);
        groupBox_8->setFont(font1);
        le_stamper_idx_ = new QLineEdit(groupBox_8);
        le_stamper_idx_->setObjectName(QStringLiteral("le_stamper_idx_"));
        le_stamper_idx_->setGeometry(QRect(90, 30, 41, 22));
        le_stamper_idx_->setFont(font2);
        pb_cali_stamp_ = new QPushButton(groupBox_8);
        pb_cali_stamp_->setObjectName(QStringLiteral("pb_cali_stamp_"));
        pb_cali_stamp_->setGeometry(QRect(70, 60, 81, 28));
        pb_cali_stamp_->setFont(font2);
        label = new QLabel(groupBox_8);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 53, 16));
        label->setFont(font2);

        gridLayout->addWidget(groupBox_8, 4, 2, 3, 4);

        groupBox_22 = new QGroupBox(tab_control_dev);
        groupBox_22->setObjectName(QStringLiteral("groupBox_22"));
        groupBox_22->setFont(font1);
        label_2 = new QLabel(groupBox_22);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 91, 16));
        label_2->setFont(font2);
        le_err_code_ = new QLineEdit(groupBox_22);
        le_err_code_->setObjectName(QStringLiteral("le_err_code_"));
        le_err_code_->setGeometry(QRect(10, 60, 113, 22));
        le_err_code_->setFont(font2);
        le_show_err_msg_ = new QLineEdit(groupBox_22);
        le_show_err_msg_->setObjectName(QStringLiteral("le_show_err_msg_"));
        le_show_err_msg_->setGeometry(QRect(170, 10, 201, 41));
        le_show_err_msg_->setFont(font2);
        le_show_err_resolver_ = new QLineEdit(groupBox_22);
        le_show_err_resolver_->setObjectName(QStringLiteral("le_show_err_resolver_"));
        le_show_err_resolver_->setGeometry(QRect(170, 50, 201, 41));
        le_show_err_resolver_->setFont(font2);

        gridLayout->addWidget(groupBox_22, 4, 6, 3, 4);

        label_9 = new QLabel(tab_control_dev);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 4, 10, 1, 2);

        le_cam_width_ = new QLineEdit(tab_control_dev);
        le_cam_width_->setObjectName(QStringLiteral("le_cam_width_"));

        gridLayout->addWidget(le_cam_width_, 5, 10, 1, 2);

        pb_set_resolution_ = new QPushButton(tab_control_dev);
        pb_set_resolution_->setObjectName(QStringLiteral("pb_set_resolution_"));

        gridLayout->addWidget(pb_set_resolution_, 5, 12, 1, 2);

        label_10 = new QLabel(tab_control_dev);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 6, 10, 1, 2);

        groupBox_26 = new QGroupBox(tab_control_dev);
        groupBox_26->setObjectName(QStringLiteral("groupBox_26"));
        groupBox_26->setFont(font1);
        pb_get_sn_ = new QPushButton(groupBox_26);
        pb_get_sn_->setObjectName(QStringLiteral("pb_get_sn_"));
        pb_get_sn_->setGeometry(QRect(10, 30, 61, 28));
        pb_get_sn_->setFont(font2);
        le_show_sn_ = new QLineEdit(groupBox_26);
        le_show_sn_->setObjectName(QStringLiteral("le_show_sn_"));
        le_show_sn_->setGeometry(QRect(80, 30, 181, 22));
        le_show_sn_->setFont(font2);
        pb_set_sn_ = new QPushButton(groupBox_26);
        pb_set_sn_->setObjectName(QStringLiteral("pb_set_sn_"));
        pb_set_sn_->setGeometry(QRect(10, 70, 61, 28));
        pb_set_sn_->setFont(font2);
        le_set_sn_ = new QLineEdit(groupBox_26);
        le_set_sn_->setObjectName(QStringLiteral("le_set_sn_"));
        le_set_sn_->setGeometry(QRect(80, 70, 181, 22));
        le_set_sn_->setFont(font2);

        gridLayout->addWidget(groupBox_26, 7, 0, 3, 2);

        le_cam_height_ = new QLineEdit(tab_control_dev);
        le_cam_height_->setObjectName(QStringLiteral("le_cam_height_"));

        gridLayout->addWidget(le_cam_height_, 7, 10, 1, 2);

        pb_set_dpi_ = new QPushButton(tab_control_dev);
        pb_set_dpi_->setObjectName(QStringLiteral("pb_set_dpi_"));

        gridLayout->addWidget(pb_set_dpi_, 7, 12, 1, 2);

        label_7 = new QLabel(tab_control_dev);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 8, 7, 1, 1);

        pb_open_paper_ = new QPushButton(tab_control_dev);
        pb_open_paper_->setObjectName(QStringLiteral("pb_open_paper_"));

        gridLayout->addWidget(pb_open_paper_, 8, 8, 2, 2);

        pb_cnn_status_ = new QPushButton(tab_control_dev);
        pb_cnn_status_->setObjectName(QStringLiteral("pb_cnn_status_"));

        gridLayout->addWidget(pb_cnn_status_, 9, 2, 1, 1);

        pb_open_ = new QPushButton(tab_control_dev);
        pb_open_->setObjectName(QStringLiteral("pb_open_"));

        gridLayout->addWidget(pb_open_, 9, 3, 1, 2);

        pb_close_ = new QPushButton(tab_control_dev);
        pb_close_->setObjectName(QStringLiteral("pb_close_"));

        gridLayout->addWidget(pb_close_, 9, 5, 1, 2);

        le_paper_timeout_ = new QLineEdit(tab_control_dev);
        le_paper_timeout_->setObjectName(QStringLiteral("le_paper_timeout_"));

        gridLayout->addWidget(le_paper_timeout_, 9, 7, 1, 1);

        label_8 = new QLabel(tab_control_dev);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 10, 0, 1, 1);

        le_led_val_ = new QLineEdit(tab_control_dev);
        le_led_val_->setObjectName(QStringLiteral("le_led_val_"));

        gridLayout->addWidget(le_led_val_, 10, 1, 1, 1);

        pb_enter_main_ = new QPushButton(tab_control_dev);
        pb_enter_main_->setObjectName(QStringLiteral("pb_enter_main_"));

        gridLayout->addWidget(pb_enter_main_, 10, 7, 1, 2);

        pb_open_paper_led_ = new QPushButton(tab_control_dev);
        pb_open_paper_led_->setObjectName(QStringLiteral("pb_open_paper_led_"));

        gridLayout->addWidget(pb_open_paper_led_, 11, 0, 1, 1);

        pb_close_paper_led_ = new QPushButton(tab_control_dev);
        pb_close_paper_led_->setObjectName(QStringLiteral("pb_close_paper_led_"));

        gridLayout->addWidget(pb_close_paper_led_, 11, 1, 1, 1);

        pb_open_safe_led_ = new QPushButton(tab_control_dev);
        pb_open_safe_led_->setObjectName(QStringLiteral("pb_open_safe_led_"));

        gridLayout->addWidget(pb_open_safe_led_, 11, 2, 1, 2);

        pb_close_safe_led_ = new QPushButton(tab_control_dev);
        pb_close_safe_led_->setObjectName(QStringLiteral("pb_close_safe_led_"));

        gridLayout->addWidget(pb_close_safe_led_, 11, 4, 1, 3);

        pb_exit_main_ = new QPushButton(tab_control_dev);
        pb_exit_main_->setObjectName(QStringLiteral("pb_exit_main_"));

        gridLayout->addWidget(pb_exit_main_, 11, 7, 1, 2);

        pb_top_status_ = new QPushButton(tab_control_dev);
        pb_top_status_->setObjectName(QStringLiteral("pb_top_status_"));

        gridLayout->addWidget(pb_top_status_, 11, 9, 1, 1);

        pb_reset_ = new QPushButton(tab_control_dev);
        pb_reset_->setObjectName(QStringLiteral("pb_reset_"));

        gridLayout->addWidget(pb_reset_, 11, 10, 1, 1);

        pb_restart_ = new QPushButton(tab_control_dev);
        pb_restart_->setObjectName(QStringLiteral("pb_restart_"));

        gridLayout->addWidget(pb_restart_, 11, 11, 1, 1);

        tabWidget->addTab(tab_control_dev, QString());
        tab_stamper = new QWidget();
        tab_stamper->setObjectName(QStringLiteral("tab_stamper"));
        pb_capture_ = new QPushButton(tab_stamper);
        pb_capture_->setObjectName(QStringLiteral("pb_capture_"));
        pb_capture_->setGeometry(QRect(380, 30, 93, 31));
        pb_select_picture_ = new QPushButton(tab_stamper);
        pb_select_picture_->setObjectName(QStringLiteral("pb_select_picture_"));
        pb_select_picture_->setGeometry(QRect(270, 30, 93, 28));
        ori_image_ = new QLabel(tab_stamper);
        ori_image_->setObjectName(QStringLiteral("ori_image_"));
        ori_image_->setGeometry(QRect(0, 120, 581, 481));
        QFont font4;
        font4.setStrikeOut(false);
        ori_image_->setFont(font4);
        ori_image_->setFrameShape(QFrame::Box);
        cut_image_ = new QLabel(tab_stamper);
        cut_image_->setObjectName(QStringLiteral("cut_image_"));
        cut_image_->setGeometry(QRect(590, 120, 581, 481));
        cut_image_->setFont(font4);
        cut_image_->setFrameShape(QFrame::Box);
        pb_ori_img_ = new QPushButton(tab_stamper);
        pb_ori_img_->setObjectName(QStringLiteral("pb_ori_img_"));
        pb_ori_img_->setGeometry(QRect(0, 120, 581, 481));
        pb_ori_img_->setAutoFillBackground(true);
        pb_ori_img_->setAutoDefault(false);
        pb_ori_img_->setFlat(false);
        pb_cut_img_ = new QPushButton(tab_stamper);
        pb_cut_img_->setObjectName(QStringLiteral("pb_cut_img_"));
        pb_cut_img_->setGeometry(QRect(590, 120, 581, 481));
        pb_cut_img_->setAutoFillBackground(true);
        groupBox = new QGroupBox(tab_stamper);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(480, 0, 351, 80));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 21, 16));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 50, 21, 16));
        le_x_in_img_ = new QLineEdit(groupBox);
        le_x_in_img_->setObjectName(QStringLiteral("le_x_in_img_"));
        le_x_in_img_->setGeometry(QRect(50, 20, 113, 22));
        le_y_in_img_ = new QLineEdit(groupBox);
        le_y_in_img_->setObjectName(QStringLiteral("le_y_in_img_"));
        le_y_in_img_->setGeometry(QRect(50, 50, 113, 22));
        label_28 = new QLabel(groupBox);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(180, 20, 31, 16));
        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(180, 50, 31, 16));
        le_input_width_ = new QLineEdit(groupBox);
        le_input_width_->setObjectName(QStringLiteral("le_input_width_"));
        le_input_width_->setGeometry(QRect(210, 20, 71, 22));
        le_input_height_ = new QLineEdit(groupBox);
        le_input_height_->setObjectName(QStringLiteral("le_input_height_"));
        le_input_height_->setGeometry(QRect(210, 50, 71, 22));
        pb_illustrate_ = new QPushButton(groupBox);
        pb_illustrate_->setObjectName(QStringLiteral("pb_illustrate_"));
        pb_illustrate_->setGeometry(QRect(290, 30, 51, 28));
        label_12 = new QLabel(tab_stamper);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(250, 100, 53, 16));
        label_12->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        label_27 = new QLabel(tab_stamper);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(850, 100, 53, 16));
        label_27->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        groupBox_2 = new QGroupBox(tab_stamper);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 610, 351, 141));
        combo_img_sel_ = new QComboBox(groupBox_2);
        combo_img_sel_->setObjectName(QStringLiteral("combo_img_sel_"));
        combo_img_sel_->setGeometry(QRect(0, 20, 111, 22));
        pb_recog_code_ = new QPushButton(groupBox_2);
        pb_recog_code_->setObjectName(QStringLiteral("pb_recog_code_"));
        pb_recog_code_->setGeometry(QRect(170, 50, 129, 29));
        la_code_result_ = new QLabel(groupBox_2);
        la_code_result_->setObjectName(QStringLiteral("la_code_result_"));
        la_code_result_->setGeometry(QRect(170, 90, 34, 20));
        pb_recog_ele_ = new QPushButton(groupBox_2);
        pb_recog_ele_->setObjectName(QStringLiteral("pb_recog_ele_"));
        pb_recog_ele_->setGeometry(QRect(0, 50, 131, 29));
        le_ele_result_ = new QLabel(groupBox_2);
        le_ele_result_->setObjectName(QStringLiteral("le_ele_result_"));
        le_ele_result_->setGeometry(QRect(0, 90, 34, 20));
        groupBox_23 = new QGroupBox(tab_stamper);
        groupBox_23->setObjectName(QStringLiteral("groupBox_23"));
        groupBox_23->setGeometry(QRect(840, 0, 331, 80));
        le_y_in_dev_ = new QLineEdit(groupBox_23);
        le_y_in_dev_->setObjectName(QStringLiteral("le_y_in_dev_"));
        le_y_in_dev_->setGeometry(QRect(60, 50, 113, 22));
        label_6 = new QLabel(groupBox_23);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 20, 21, 16));
        label_13 = new QLabel(groupBox_23);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 50, 21, 16));
        le_x_in_dev_ = new QLineEdit(groupBox_23);
        le_x_in_dev_->setObjectName(QStringLiteral("le_x_in_dev_"));
        le_x_in_dev_->setGeometry(QRect(60, 20, 113, 22));
        pb_check_stamp_ = new QPushButton(groupBox_23);
        pb_check_stamp_->setObjectName(QStringLiteral("pb_check_stamp_"));
        pb_check_stamp_->setGeometry(QRect(210, 30, 93, 28));
        groupBox_24 = new QGroupBox(tab_stamper);
        groupBox_24->setObjectName(QStringLiteral("groupBox_24"));
        groupBox_24->setGeometry(QRect(380, 610, 791, 131));
        label_3 = new QLabel(groupBox_24);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 53, 16));
        label_4 = new QLabel(groupBox_24);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 80, 53, 16));
        le_ori_path_ = new QLineEdit(groupBox_24);
        le_ori_path_->setObjectName(QStringLiteral("le_ori_path_"));
        le_ori_path_->setGeometry(QRect(70, 40, 701, 22));
        le_cut_path_ = new QLineEdit(groupBox_24);
        le_cut_path_->setObjectName(QStringLiteral("le_cut_path_"));
        le_cut_path_->setGeometry(QRect(70, 80, 701, 22));
        cb_cam_list_ = new QComboBox(tab_stamper);
        cb_cam_list_->setObjectName(QStringLiteral("cb_cam_list_"));
        cb_cam_list_->setGeometry(QRect(0, 10, 131, 31));
        pb_open_cam_ = new QPushButton(tab_stamper);
        pb_open_cam_->setObjectName(QStringLiteral("pb_open_cam_"));
        pb_open_cam_->setGeometry(QRect(150, 10, 61, 31));
        pb_close_cam_ = new QPushButton(tab_stamper);
        pb_close_cam_->setObjectName(QStringLiteral("pb_close_cam_"));
        pb_close_cam_->setGeometry(QRect(150, 60, 61, 31));
        pb_status_cam_ = new QPushButton(tab_stamper);
        pb_status_cam_->setObjectName(QStringLiteral("pb_status_cam_"));
        pb_status_cam_->setGeometry(QRect(30, 60, 61, 31));
        pb_cvt_coord_ = new QPushButton(tab_stamper);
        pb_cvt_coord_->setObjectName(QStringLiteral("pb_cvt_coord_"));
        pb_cvt_coord_->setGeometry(QRect(380, 70, 91, 31));
        tabWidget->addTab(tab_stamper, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(270, 100, 301, 151));
        pb_prepare_ = new QPushButton(groupBox_3);
        pb_prepare_->setObjectName(QStringLiteral("pb_prepare_"));
        pb_prepare_->setGeometry(QRect(190, 70, 93, 28));
        le_task_id_ = new QLineEdit(groupBox_3);
        le_task_id_->setObjectName(QStringLiteral("le_task_id_"));
        le_task_id_->setGeometry(QRect(10, 110, 161, 22));
        le_paper_door_timeout_ = new QLineEdit(groupBox_3);
        le_paper_door_timeout_->setObjectName(QStringLiteral("le_paper_door_timeout_"));
        le_paper_door_timeout_->setGeometry(QRect(10, 50, 161, 22));
        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(10, 30, 151, 16));
        label_30->setWordWrap(true);
        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 90, 53, 16));
        groupBox_16 = new QGroupBox(groupBox_5);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        groupBox_16->setGeometry(QRect(20, 40, 231, 281));
        radio_stamper6_ = new QRadioButton(groupBox_16);
        radio_stamper6_->setObjectName(QStringLiteral("radio_stamper6_"));
        radio_stamper6_->setGeometry(QRect(30, 180, 71, 20));
        radio_stamper4_ = new QRadioButton(groupBox_16);
        radio_stamper4_->setObjectName(QStringLiteral("radio_stamper4_"));
        radio_stamper4_->setGeometry(QRect(30, 120, 81, 20));
        radio_stamper1_ = new QRadioButton(groupBox_16);
        radio_stamper1_->setObjectName(QStringLiteral("radio_stamper1_"));
        radio_stamper1_->setGeometry(QRect(30, 30, 81, 20));
        radio_stamper2_ = new QRadioButton(groupBox_16);
        radio_stamper2_->setObjectName(QStringLiteral("radio_stamper2_"));
        radio_stamper2_->setGeometry(QRect(30, 60, 71, 20));
        radio_stamper3_ = new QRadioButton(groupBox_16);
        radio_stamper3_->setObjectName(QStringLiteral("radio_stamper3_"));
        radio_stamper3_->setGeometry(QRect(30, 90, 71, 20));
        radio_stamper5_ = new QRadioButton(groupBox_16);
        radio_stamper5_->setObjectName(QStringLiteral("radio_stamper5_"));
        radio_stamper5_->setGeometry(QRect(30, 150, 81, 20));
        pb_stamp_read_stampers_ = new QPushButton(groupBox_16);
        pb_stamp_read_stampers_->setObjectName(QStringLiteral("pb_stamp_read_stampers_"));
        pb_stamp_read_stampers_->setGeometry(QRect(10, 230, 93, 28));
        cb_stamp_stamp_ink_ = new QCheckBox(groupBox_16);
        cb_stamp_stamp_ink_->setObjectName(QStringLiteral("cb_stamp_stamp_ink_"));
        cb_stamp_stamp_ink_->setGeometry(QRect(120, 230, 81, 31));
        groupBox_20 = new QGroupBox(groupBox_5);
        groupBox_20->setObjectName(QStringLiteral("groupBox_20"));
        groupBox_20->setGeometry(QRect(610, 100, 221, 151));
        pb_ordinary_stamp_ = new QPushButton(groupBox_20);
        pb_ordinary_stamp_->setObjectName(QStringLiteral("pb_ordinary_stamp_"));
        pb_ordinary_stamp_->setGeometry(QRect(70, 50, 81, 28));
        pb_auto_stamp_ = new QPushButton(groupBox_20);
        pb_auto_stamp_->setObjectName(QStringLiteral("pb_auto_stamp_"));
        pb_auto_stamp_->setGeometry(QRect(70, 100, 81, 28));
        groupBox_25 = new QGroupBox(groupBox_5);
        groupBox_25->setObjectName(QStringLiteral("groupBox_25"));
        groupBox_25->setGeometry(QRect(870, 100, 221, 151));
        pb_release_machine_ = new QPushButton(groupBox_25);
        pb_release_machine_->setObjectName(QStringLiteral("pb_release_machine_"));
        pb_release_machine_->setGeometry(QRect(60, 100, 93, 28));
        pb_finish_stamp_ = new QPushButton(groupBox_25);
        pb_finish_stamp_->setObjectName(QStringLiteral("pb_finish_stamp_"));
        pb_finish_stamp_->setGeometry(QRect(60, 40, 93, 28));
        camera_preview_ = new QLabel(groupBox_5);
        camera_preview_->setObjectName(QStringLiteral("camera_preview_"));
        camera_preview_->setGeometry(QRect(30, 350, 351, 331));
        camera_preview_->setFrameShape(QFrame::WinPanel);
        camera_preview_->setFrameShadow(QFrame::Sunken);
        pb_start_preview_ = new QPushButton(groupBox_5);
        pb_start_preview_->setObjectName(QStringLiteral("pb_start_preview_"));
        pb_start_preview_->setGeometry(QRect(420, 440, 111, 46));
        pb_stop_preview_ = new QPushButton(groupBox_5);
        pb_stop_preview_->setObjectName(QStringLiteral("pb_stop_preview_"));
        pb_stop_preview_->setGeometry(QRect(420, 520, 111, 46));

        gridLayout_3->addWidget(groupBox_5, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pb_stamper_lock_ = new QPushButton(tab_3);
        pb_stamper_lock_->setObjectName(QStringLiteral("pb_stamper_lock_"));

        gridLayout_4->addWidget(pb_stamper_lock_, 2, 0, 1, 1);

        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_4->addWidget(label_16, 0, 5, 1, 3);

        pb_read_rfid_ = new QPushButton(tab_3);
        pb_read_rfid_->setObjectName(QStringLiteral("pb_read_rfid_"));

        gridLayout_4->addWidget(pb_read_rfid_, 1, 7, 1, 1);

        pb_unlock_ = new QPushButton(tab_3);
        pb_unlock_->setObjectName(QStringLiteral("pb_unlock_"));

        gridLayout_4->addWidget(pb_unlock_, 0, 1, 2, 1);

        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 4, 5, 1, 1);

        le_video_path_ = new QLineEdit(tab_3);
        le_video_path_->setObjectName(QStringLiteral("le_video_path_"));

        gridLayout_4->addWidget(le_video_path_, 5, 5, 1, 3);

        le_rfid_slot_ = new QLineEdit(tab_3);
        le_rfid_slot_->setObjectName(QStringLiteral("le_rfid_slot_"));

        gridLayout_4->addWidget(le_rfid_slot_, 1, 5, 1, 2);

        pb_stop_record_ = new QPushButton(tab_3);
        pb_stop_record_->setObjectName(QStringLiteral("pb_stop_record_"));

        gridLayout_4->addWidget(pb_stop_record_, 6, 6, 1, 2);

        pb_lock_ = new QPushButton(tab_3);
        pb_lock_->setObjectName(QStringLiteral("pb_lock_"));

        gridLayout_4->addWidget(pb_lock_, 0, 0, 1, 1);

        pb_start_record_ = new QPushButton(tab_3);
        pb_start_record_->setObjectName(QStringLiteral("pb_start_record_"));

        gridLayout_4->addWidget(pb_start_record_, 6, 5, 1, 1);

        le_ratio_x_ = new QLineEdit(tab_3);
        le_ratio_x_->setObjectName(QStringLiteral("le_ratio_x_"));

        gridLayout_4->addWidget(le_ratio_x_, 7, 0, 1, 1);

        le_ratio_y_ = new QLineEdit(tab_3);
        le_ratio_y_->setObjectName(QStringLiteral("le_ratio_y_"));

        gridLayout_4->addWidget(le_ratio_y_, 8, 0, 1, 1);

        pb_factory_disable_ = new QPushButton(tab_3);
        pb_factory_disable_->setObjectName(QStringLiteral("pb_factory_disable_"));

        gridLayout_4->addWidget(pb_factory_disable_, 7, 4, 2, 1);

        pb_read_ratio_ = new QPushButton(tab_3);
        pb_read_ratio_->setObjectName(QStringLiteral("pb_read_ratio_"));

        gridLayout_4->addWidget(pb_read_ratio_, 8, 1, 1, 1);

        pb_read_cal_pts_ = new QPushButton(tab_3);
        pb_read_cal_pts_->setObjectName(QStringLiteral("pb_read_cal_pts_"));

        gridLayout_4->addWidget(pb_read_cal_pts_, 8, 2, 1, 1);

        pb_factory_enable_ = new QPushButton(tab_3);
        pb_factory_enable_->setObjectName(QStringLiteral("pb_factory_enable_"));

        gridLayout_4->addWidget(pb_factory_enable_, 7, 3, 2, 1);

        pb_write_ratio_ = new QPushButton(tab_3);
        pb_write_ratio_->setObjectName(QStringLiteral("pb_write_ratio_"));

        gridLayout_4->addWidget(pb_write_ratio_, 7, 1, 1, 1);

        pb_write_cal_pts_ = new QPushButton(tab_3);
        pb_write_cal_pts_->setObjectName(QStringLiteral("pb_write_cal_pts_"));

        gridLayout_4->addWidget(pb_write_cal_pts_, 7, 2, 1, 1);

        groupBox_12 = new QGroupBox(tab_3);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        label_15 = new QLabel(groupBox_12);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 50, 141, 16));
        label_17 = new QLabel(groupBox_12);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 120, 121, 16));
        le_sidedoor_close_ = new QLineEdit(groupBox_12);
        le_sidedoor_close_->setObjectName(QStringLiteral("le_sidedoor_close_"));
        le_sidedoor_close_->setGeometry(QRect(160, 40, 71, 31));
        pb_set_sidedoor_ = new QPushButton(groupBox_12);
        pb_set_sidedoor_->setObjectName(QStringLiteral("pb_set_sidedoor_"));
        pb_set_sidedoor_->setGeometry(QRect(260, 80, 51, 28));
        le_sidedoor_timeout_ = new QLineEdit(groupBox_12);
        le_sidedoor_timeout_->setObjectName(QStringLiteral("le_sidedoor_timeout_"));
        le_sidedoor_timeout_->setGeometry(QRect(160, 110, 71, 31));

        gridLayout_4->addWidget(groupBox_12, 0, 2, 3, 3);

        groupBox_17 = new QGroupBox(tab_3);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        label_19 = new QLabel(groupBox_17);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 40, 91, 16));
        le_x_coord_ = new QLineEdit(groupBox_17);
        le_x_coord_->setObjectName(QStringLiteral("le_x_coord_"));
        le_x_coord_->setGeometry(QRect(10, 70, 101, 22));
        label_23 = new QLabel(groupBox_17);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(130, 40, 131, 16));
        le_y_coord_ = new QLineEdit(groupBox_17);
        le_y_coord_->setObjectName(QStringLiteral("le_y_coord_"));
        le_y_coord_->setGeometry(QRect(130, 70, 101, 22));
        pb_check_param_ = new QPushButton(groupBox_17);
        pb_check_param_->setObjectName(QStringLiteral("pb_check_param_"));
        pb_check_param_->setGeometry(QRect(140, 110, 93, 28));
        le_angle_ = new QLineEdit(groupBox_17);
        le_angle_->setObjectName(QStringLiteral("le_angle_"));
        le_angle_->setGeometry(QRect(260, 70, 101, 22));
        label_24 = new QLabel(groupBox_17);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(260, 40, 131, 16));

        gridLayout_4->addWidget(groupBox_17, 3, 0, 1, 1);

        groupBox_19 = new QGroupBox(tab_3);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        label_46 = new QLabel(groupBox_19);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(10, 70, 71, 16));
        label_door_alarm_ = new QLabel(groupBox_19);
        label_door_alarm_->setObjectName(QStringLiteral("label_door_alarm_"));
        label_door_alarm_->setGeometry(QRect(10, 100, 55, 16));
        label_48 = new QLabel(groupBox_19);
        label_48->setObjectName(QStringLiteral("label_48"));
        label_48->setGeometry(QRect(10, 130, 71, 16));
        label_vibration_alarm_ = new QLabel(groupBox_19);
        label_vibration_alarm_->setObjectName(QStringLiteral("label_vibration_alarm_"));
        label_vibration_alarm_->setGeometry(QRect(10, 160, 55, 16));
        pb_read_alarm_ = new QPushButton(groupBox_19);
        pb_read_alarm_->setObjectName(QStringLiteral("pb_read_alarm_"));
        pb_read_alarm_->setGeometry(QRect(80, 30, 111, 28));

        gridLayout_4->addWidget(groupBox_19, 3, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        QtDemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtDemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1706, 38));
        QtDemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtDemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtDemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtDemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtDemoClass->setStatusBar(statusBar);

        retranslateUi(QtDemoClass);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(QtDemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtDemoClass)
    {
        QtDemoClass->setWindowTitle(QApplication::translate("QtDemoClass", "QtDemo", 0));
        groupBox_9->setTitle(QApplication::translate("QtDemoClass", "\350\234\202\351\270\243\345\231\250\345\274\200\345\205\263", 0));
        pb_beep_on_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\220\257", 0));
        pb_beep_off_->setText(QApplication::translate("QtDemoClass", "\345\205\263\351\227\255", 0));
        groupBox_7->setTitle(QApplication::translate("QtDemoClass", "\350\277\233\347\272\270\351\227\250", 0));
        pb_paper_status_->setText(QApplication::translate("QtDemoClass", "\350\277\233\347\272\270\351\227\250\347\212\266\346\200\201", 0));
        groupBox_13->setTitle(QApplication::translate("QtDemoClass", "MAC", 0));
        pb_read_local_mac_->setText(QApplication::translate("QtDemoClass", "\346\234\254\346\234\272MAC\345\234\260\345\235\200", 0));
        pb_binding_mac_->setText(QApplication::translate("QtDemoClass", "\347\273\221\345\256\232", 0));
        pb_mac_unbinding_->setText(QApplication::translate("QtDemoClass", "\350\247\243\347\273\221", 0));
        pb_query_mac_->setText(QApplication::translate("QtDemoClass", "\346\237\245\350\257\242MAC", 0));
        pb_dev_type_->setText(QApplication::translate("QtDemoClass", "\350\256\276\345\244\207\345\236\213\345\217\267", 0));
        pb_system_->setText(QApplication::translate("QtDemoClass", "\347\263\273\347\273\237\344\277\241\346\201\257", 0));
        groupBox_21->setTitle(QApplication::translate("QtDemoClass", "\346\212\245\350\255\246\345\212\237\350\203\275\345\274\200\345\205\263", 0));
        pb_open_safe_door_alarm_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\274\200\351\227\250\346\212\245\350\255\246", 0));
        pb_close_safe_door_alarm_->setText(QApplication::translate("QtDemoClass", "\345\205\263\345\274\200\351\227\250\346\212\245\350\255\246", 0));
        pb_open_vibration_alarm_->setText(QApplication::translate("QtDemoClass", "\345\274\200\346\214\257\345\212\250\346\212\245\350\255\246", 0));
        pb_close_vibration_alarm_->setText(QApplication::translate("QtDemoClass", "\345\205\263\346\214\257\345\212\250\346\212\245\350\255\246", 0));
        groupBox_6->setTitle(QApplication::translate("QtDemoClass", "\345\256\211\345\205\250\351\227\250", 0));
        pb_open_safe_door_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\256\211\345\205\250\351\227\250", 0));
        pb_close_safe_door_->setText(QApplication::translate("QtDemoClass", "\345\205\263\345\256\211\345\205\250\351\227\250", 0));
        pb_safe_status_->setText(QApplication::translate("QtDemoClass", "\345\256\211\345\205\250\351\227\250\347\212\266\346\200\201", 0));
        pb_query_stamper_->setText(QApplication::translate("QtDemoClass", "\345\215\260\347\253\240\347\212\266\346\200\201", 0));
        pb_dev_status_->setText(QApplication::translate("QtDemoClass", "\350\256\276\345\244\207\347\212\266\346\200\201", 0));
        groupBox_4->setTitle(QApplication::translate("QtDemoClass", "\345\215\260\347\253\240\347\256\241\347\220\206", 0));
        pb_query_slots_->setText(QApplication::translate("QtDemoClass", "\345\215\241\346\247\275\346\225\260\351\207\217\346\237\245\350\257\242", 0));
        groupBox_8->setTitle(QApplication::translate("QtDemoClass", "\346\240\241\345\207\206\345\215\260\347\253\240", 0));
        pb_cali_stamp_->setText(QApplication::translate("QtDemoClass", "\346\240\241\346\255\243", 0));
        label->setText(QApplication::translate("QtDemoClass", "\345\215\241\346\247\275\345\217\267:", 0));
        groupBox_22->setTitle(QApplication::translate("QtDemoClass", "\351\224\231\350\257\257\347\240\201", 0));
        label_2->setText(QApplication::translate("QtDemoClass", "\350\276\223\345\205\245\351\224\231\350\257\257\347\240\201\357\274\232", 0));
        label_9->setText(QApplication::translate("QtDemoClass", "\345\256\275\345\272\246\357\274\232", 0));
        pb_set_resolution_->setText(QApplication::translate("QtDemoClass", "\350\256\276\347\275\256\345\210\206\350\276\250\347\216\207", 0));
        label_10->setText(QApplication::translate("QtDemoClass", "\351\253\230\345\272\246\357\274\232", 0));
        groupBox_26->setTitle(QApplication::translate("QtDemoClass", "\350\256\276\345\244\207\347\274\226\345\217\267", 0));
        pb_get_sn_->setText(QApplication::translate("QtDemoClass", "\350\216\267\345\217\226", 0));
        pb_set_sn_->setText(QApplication::translate("QtDemoClass", "\350\256\276\347\275\256", 0));
        pb_set_dpi_->setText(QApplication::translate("QtDemoClass", "\350\256\276\347\275\256DPI", 0));
        label_7->setText(QApplication::translate("QtDemoClass", "\350\266\205\346\227\266\357\274\210\347\247\222\357\274\211", 0));
        pb_open_paper_->setText(QApplication::translate("QtDemoClass", "\345\274\200\347\272\270\351\227\250", 0));
        pb_cnn_status_->setText(QApplication::translate("QtDemoClass", "\350\277\236\346\216\245\347\212\266\346\200\201", 0));
        pb_open_->setText(QApplication::translate("QtDemoClass", "\346\211\223\345\274\200\350\256\276\345\244\207", 0));
        pb_close_->setText(QApplication::translate("QtDemoClass", "\345\205\263\351\227\255\350\256\276\345\244\207", 0));
        label_8->setText(QApplication::translate("QtDemoClass", "\344\272\256\345\272\246\345\200\274\357\274\232", 0));
        pb_enter_main_->setText(QApplication::translate("QtDemoClass", "\350\277\233\345\205\245\347\273\264\346\212\244\346\250\241\345\274\217", 0));
        pb_open_paper_led_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\207\255\350\257\201LED", 0));
        pb_close_paper_led_->setText(QApplication::translate("QtDemoClass", "\345\205\263\345\207\255\350\257\201LED", 0));
        pb_open_safe_led_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\256\211\345\205\250\351\227\250LED", 0));
        pb_close_safe_led_->setText(QApplication::translate("QtDemoClass", "\345\205\263\345\256\211\345\205\250\351\227\250LED", 0));
        pb_exit_main_->setText(QApplication::translate("QtDemoClass", "\351\200\200\345\207\272\347\273\264\346\212\244\346\250\241\345\274\217", 0));
        pb_top_status_->setText(QApplication::translate("QtDemoClass", "\351\241\266\347\233\226\351\227\250\347\212\266\346\200\201", 0));
        pb_reset_->setText(QApplication::translate("QtDemoClass", "\345\244\215\344\275\215", 0));
        pb_restart_->setText(QApplication::translate("QtDemoClass", "\351\207\215\345\220\257", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_control_dev), QApplication::translate("QtDemoClass", "\350\256\276\345\244\207\346\216\247\345\210\266", 0));
        pb_capture_->setText(QApplication::translate("QtDemoClass", "\346\213\215\347\205\247", 0));
        pb_select_picture_->setText(QApplication::translate("QtDemoClass", "\351\200\211\345\217\226\345\233\276\347\211\207", 0));
        ori_image_->setText(QString());
        cut_image_->setText(QString());
        pb_ori_img_->setText(QString());
        pb_cut_img_->setText(QString());
        groupBox->setTitle(QApplication::translate("QtDemoClass", "\345\233\276\345\203\217\345\235\220\346\240\207\347\263\273", 0));
        label_5->setText(QApplication::translate("QtDemoClass", "X:", 0));
        label_11->setText(QApplication::translate("QtDemoClass", "Y:", 0));
        label_28->setText(QApplication::translate("QtDemoClass", "\345\256\275:", 0));
        label_29->setText(QApplication::translate("QtDemoClass", "\351\253\230:", 0));
        pb_illustrate_->setText(QApplication::translate("QtDemoClass", "\345\233\276\347\244\272", 0));
        label_12->setText(QApplication::translate("QtDemoClass", "\345\216\237\345\233\276", 0));
        label_27->setText(QApplication::translate("QtDemoClass", "\345\210\207\345\233\276", 0));
        groupBox_2->setTitle(QApplication::translate("QtDemoClass", "\350\257\206\345\210\253", 0));
        pb_recog_code_->setText(QApplication::translate("QtDemoClass", "\347\211\210\351\235\242\343\200\201\351\252\214\350\257\201\347\240\201\350\257\206\345\210\253", 0));
        la_code_result_->setText(QApplication::translate("QtDemoClass", "...", 0));
        pb_recog_ele_->setText(QApplication::translate("QtDemoClass", "\350\246\201\347\264\240\350\257\206\345\210\253", 0));
        le_ele_result_->setText(QApplication::translate("QtDemoClass", "...", 0));
        groupBox_23->setTitle(QApplication::translate("QtDemoClass", "\350\256\276\345\244\207\345\235\220\346\240\207\347\263\273", 0));
        label_6->setText(QApplication::translate("QtDemoClass", "X:", 0));
        label_13->setText(QApplication::translate("QtDemoClass", "Y:", 0));
        pb_check_stamp_->setText(QApplication::translate("QtDemoClass", "\346\240\241\345\207\206\347\233\226\347\253\240", 0));
        groupBox_24->setTitle(QApplication::translate("QtDemoClass", "\345\233\276\347\211\207\350\267\257\345\276\204", 0));
        label_3->setText(QApplication::translate("QtDemoClass", "\345\216\237\345\233\276\357\274\232", 0));
        label_4->setText(QApplication::translate("QtDemoClass", "\345\210\207\345\233\276:", 0));
        pb_open_cam_->setText(QApplication::translate("QtDemoClass", "\346\211\223\345\274\200", 0));
        pb_close_cam_->setText(QApplication::translate("QtDemoClass", "\345\205\263\351\227\255", 0));
        pb_status_cam_->setText(QApplication::translate("QtDemoClass", "\347\212\266\346\200\201", 0));
        pb_cvt_coord_->setText(QApplication::translate("QtDemoClass", "\345\235\220\346\240\207\350\275\254\346\215\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_stamper), QApplication::translate("QtDemoClass", "\346\213\215\347\205\247/\350\257\206\345\210\253", 0));
        groupBox_5->setTitle(QApplication::translate("QtDemoClass", "\347\233\226\347\253\240", 0));
        groupBox_3->setTitle(QApplication::translate("QtDemoClass", "\347\224\250\345\215\260\345\211\215\345\207\206\345\244\207", 0));
        pb_prepare_->setText(QApplication::translate("QtDemoClass", "\345\207\206\345\244\207\347\224\250\345\215\260", 0));
        label_30->setText(QApplication::translate("QtDemoClass", "\350\277\233\347\272\270\351\227\250\350\266\205\346\227\266\346\234\252\345\205\263\351\227\255(\347\247\222):", 0));
        label_31->setText(QApplication::translate("QtDemoClass", "\344\273\273\345\212\241\345\217\267:", 0));
        groupBox_16->setTitle(QApplication::translate("QtDemoClass", "\351\200\211\347\253\240", 0));
        radio_stamper6_->setText(QApplication::translate("QtDemoClass", "6\345\217\267\347\253\240", 0));
        radio_stamper4_->setText(QApplication::translate("QtDemoClass", "4\345\217\267\347\253\240", 0));
        radio_stamper1_->setText(QApplication::translate("QtDemoClass", "1\345\217\267\347\253\240", 0));
        radio_stamper2_->setText(QApplication::translate("QtDemoClass", "2\345\217\267\347\253\240", 0));
        radio_stamper3_->setText(QApplication::translate("QtDemoClass", "3\345\217\267\347\253\240", 0));
        radio_stamper5_->setText(QApplication::translate("QtDemoClass", "5\345\217\267\347\253\240", 0));
        pb_stamp_read_stampers_->setText(QApplication::translate("QtDemoClass", "\350\257\273\345\217\226\347\253\240\347\212\266\346\200\201", 0));
        cb_stamp_stamp_ink_->setText(QApplication::translate("QtDemoClass", "\350\230\270\345\215\260\346\262\271", 0));
        groupBox_20->setTitle(QApplication::translate("QtDemoClass", "\347\224\250\345\215\260", 0));
        pb_ordinary_stamp_->setText(QApplication::translate("QtDemoClass", "\346\231\256\351\200\232\347\224\250\345\215\260", 0));
        pb_auto_stamp_->setText(QApplication::translate("QtDemoClass", "\350\207\252\345\212\250\347\224\250\345\215\260", 0));
        groupBox_25->setTitle(QApplication::translate("QtDemoClass", "\347\224\250\345\215\260\347\273\223\346\235\237", 0));
        pb_release_machine_->setText(QApplication::translate("QtDemoClass", "\351\207\212\346\224\276\345\215\260\346\216\247\346\234\272", 0));
        pb_finish_stamp_->setText(QApplication::translate("QtDemoClass", "\347\273\223\346\235\237\347\224\250\345\215\260", 0));
        camera_preview_->setText(QString());
        pb_start_preview_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\247\213\351\242\204\350\247\210", 0));
        pb_stop_preview_->setText(QApplication::translate("QtDemoClass", "\345\201\234\346\255\242\351\242\204\350\247\210", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QtDemoClass", "\347\233\226\347\253\240", 0));
        pb_stamper_lock_->setText(QApplication::translate("QtDemoClass", "\345\215\260\346\216\247\344\273\252\347\212\266\346\200\201", 0));
        label_16->setText(QApplication::translate("QtDemoClass", "\345\215\241\346\247\275\345\217\267\357\274\2101\357\274\211\357\274\232", 0));
        pb_read_rfid_->setText(QApplication::translate("QtDemoClass", "\350\257\273RFID", 0));
        pb_unlock_->setText(QApplication::translate("QtDemoClass", "\350\247\243\351\224\201\345\215\260\346\216\247\344\273\252", 0));
        label_14->setText(QApplication::translate("QtDemoClass", "\350\247\206\351\242\221\345\205\250\350\267\257\345\276\204\357\274\232", 0));
        pb_stop_record_->setText(QApplication::translate("QtDemoClass", "\345\201\234\346\255\242\345\275\225\345\203\217", 0));
        pb_lock_->setText(QApplication::translate("QtDemoClass", "\351\224\201\345\256\232\345\215\260\346\216\247\344\273\252", 0));
        pb_start_record_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\247\213\345\275\225\345\203\217", 0));
        pb_factory_disable_->setText(QApplication::translate("QtDemoClass", "\345\205\263\351\227\255\345\267\245\345\216\202", 0));
        pb_read_ratio_->setText(QApplication::translate("QtDemoClass", "\350\257\273\345\200\215\347\216\207", 0));
        pb_read_cal_pts_->setText(QApplication::translate("QtDemoClass", "\350\257\273\346\240\241\345\207\206\347\202\271", 0));
        pb_factory_enable_->setText(QApplication::translate("QtDemoClass", "\345\274\200\345\220\257\345\267\245\345\216\202", 0));
        pb_write_ratio_->setText(QApplication::translate("QtDemoClass", "\345\206\231\345\200\215\347\216\207", 0));
        pb_write_cal_pts_->setText(QApplication::translate("QtDemoClass", "\345\206\231\346\240\241\345\207\206\347\202\271", 0));
        groupBox_12->setTitle(QApplication::translate("QtDemoClass", "\345\256\211\345\205\250\351\227\250", 0));
        label_15->setText(QApplication::translate("QtDemoClass", "\344\276\247\351\227\250\351\224\201\345\205\263\351\227\255\346\227\266\351\227\264(s)\357\274\232", 0));
        label_17->setText(QApplication::translate("QtDemoClass", "\344\276\247\351\227\250\346\217\220\347\244\272\350\266\205\346\227\266(s)\357\274\232", 0));
        pb_set_sidedoor_->setText(QApplication::translate("QtDemoClass", "\350\256\276\347\275\256", 0));
        groupBox_17->setTitle(QApplication::translate("QtDemoClass", "\347\233\226\347\253\240\347\211\251\347\220\206\345\260\272\345\257\270", 0));
        label_19->setText(QApplication::translate("QtDemoClass", "x\345\235\220\346\240\207\357\274\232", 0));
        label_23->setText(QApplication::translate("QtDemoClass", "y\345\235\220\346\240\207\357\274\232", 0));
        pb_check_param_->setText(QApplication::translate("QtDemoClass", "\345\217\202\346\225\260\346\243\200\346\237\245", 0));
        label_24->setText(QApplication::translate("QtDemoClass", "\350\247\222\345\272\246\357\274\232", 0));
        groupBox_19->setTitle(QApplication::translate("QtDemoClass", "\346\212\245\350\255\246\345\231\250\347\212\266\346\200\201", 0));
        label_46->setText(QApplication::translate("QtDemoClass", "\351\227\250\346\212\245\350\255\246\357\274\232", 0));
        label_door_alarm_->setText(QString());
        label_48->setText(QApplication::translate("QtDemoClass", "\346\214\257\345\212\250\346\212\245\350\255\246\357\274\232", 0));
        label_vibration_alarm_->setText(QString());
        pb_read_alarm_->setText(QApplication::translate("QtDemoClass", "\350\257\273\346\212\245\350\255\246\345\231\250", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("QtDemoClass", "\345\205\266\344\273\226\346\216\245\345\217\243", 0));
    } // retranslateUi

};

namespace Ui {
    class QtDemoClass: public Ui_QtDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDEMO_H
