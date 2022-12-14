/********************************************************************************
** Form generated from reading UI file 'dial_par.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAL_PAR_H
#define UI_DIAL_PAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "paramlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog_par
{
public:
    QLineEdit *lineEdit_ip;
    QLabel *lab_chans;
    QLabel *lab_tacts;
    QLabel *lab_0;
    ParamLineEdit *line_tact0;
    ParamLineEdit *line_tact1;
    ParamLineEdit *line_tact2;
    ParamLineEdit *line_tact3;
    ParamLineEdit *line_tact4;
    QLabel *lab_1;
    QLabel *lab_2;
    QLabel *lab_3;
    QLabel *lab_4;
    QPushButton *pushButton_colors;
    QLabel *label_zond_freq;
    QLabel *label_zond_freq_unit;
    QLineEdit *line_zond_freq;
    QLabel *lab_5;
    ParamLineEdit *line_tact5;
    QLabel *lab_ninp;
    ParamLineEdit *line_ed_ninp0;
    ParamLineEdit *line_ed_ninp3;
    ParamLineEdit *line_ed_ninp2;
    ParamLineEdit *line_ed_ninp5;
    ParamLineEdit *line_ed_ninp1;
    ParamLineEdit *line_ed_ninp4;
    QLabel *lab_rej;
    QComboBox *comboBox_rej0;
    QComboBox *comboBox_rej1;
    QComboBox *comboBox_rej2;
    QComboBox *comboBox_rej3;
    QComboBox *comboBox_rej4;
    QComboBox *comboBox_rej5;
    QLabel *label_num_tacts;
    ParamLineEdit *line_num_tacts;
    QCheckBox *checkBox_logarithm_capt;
    QGroupBox *groupBox_filtr;
    QLabel *label_filtr_def_descr;
    QLabel *label_filtr_def_descr_2;
    ParamLineEdit *line_filtr_thick;
    ParamLineEdit *line_filtr_def;
    ParamLineEdit *line_num_per_elem;
    QLabel *label_num_per_elem;
    QCheckBox *checkBox_axis_x_mm;
    QLabel *label_resolution_koef;
    QComboBox *comboBox_resolution_koef;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QLabel *label_IP;
    ParamLineEdit *line_ed_ninp7;
    ParamLineEdit *line_tact6;
    QLabel *lab_6;
    QComboBox *comboBox_rej7;
    QLabel *lab_7;
    QComboBox *comboBox_rej6;
    ParamLineEdit *line_ed_ninp6;
    ParamLineEdit *line_tact7;
    QLabel *lab_14;
    ParamLineEdit *line_ed_ninp12;
    QComboBox *comboBox_rej13;
    ParamLineEdit *line_tact10;
    QLabel *lab_tacts_2;
    QLabel *lab_ninp_2;
    ParamLineEdit *line_ed_ninp14;
    ParamLineEdit *line_tact13;
    ParamLineEdit *line_tact9;
    ParamLineEdit *line_tact11;
    QComboBox *comboBox_rej12;
    QLabel *lab_chans_2;
    QLabel *lab_10;
    ParamLineEdit *line_tact8;
    QLabel *lab_11;
    ParamLineEdit *line_tact12;
    QLabel *lab_rej_2;
    QLabel *lab_12;
    QComboBox *comboBox_rej14;
    QComboBox *comboBox_rej15;
    ParamLineEdit *line_ed_ninp8;
    QLabel *lab_15;
    ParamLineEdit *line_ed_ninp11;
    ParamLineEdit *line_tact15;
    ParamLineEdit *line_ed_ninp13;
    QLabel *lab_13;
    QComboBox *comboBox_rej11;
    ParamLineEdit *line_ed_ninp9;
    QComboBox *comboBox_rej8;
    QComboBox *comboBox_rej9;
    ParamLineEdit *line_ed_ninp15;
    QLabel *lab_8;
    ParamLineEdit *line_tact14;
    QLabel *lab_9;
    ParamLineEdit *line_ed_ninp10;
    QComboBox *comboBox_rej10;
    ParamLineEdit *line_num_chan;
    QLabel *label_num_chan;
    QGroupBox *groupBox_speed;
    ParamLineEdit *ed_time_interval;
    QLabel *label_time_interval;
    ParamLineEdit *ed_update_interval;
    ParamLineEdit *ed_normal_speed;
    QLabel *label_update_interval;
    QLabel *label_normal_speed;
    QLabel *label_normal_speed_units;
    QGroupBox *groupBox_mnemo_flags;
    QCheckBox *checkBox_layer_0;
    QCheckBox *checkBox_layer_1;
    QCheckBox *checkBox_layer_2;
    QCheckBox *checkBox_layer_thick;
    QLineEdit *lineEdit_setting_name;
    QLabel *label_setting_name;
    QGroupBox *groupBox;
    ParamLineEdit *ed_coef_coord;
    QGroupBox *groupBox_vdp;
    ParamLineEdit *ed_vdp;
    QCheckBox *checkBox_vdp;

    void setupUi(QDialog *Dialog_par)
    {
        if (Dialog_par->objectName().isEmpty())
            Dialog_par->setObjectName(QStringLiteral("Dialog_par"));
        Dialog_par->resize(518, 535);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        Dialog_par->setFont(font);
        Dialog_par->setLayoutDirection(Qt::RightToLeft);
        lineEdit_ip = new QLineEdit(Dialog_par);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(38, 8, 111, 21));
        QFont font1;
        font1.setPointSize(10);
        lineEdit_ip->setFont(font1);
        lab_chans = new QLabel(Dialog_par);
        lab_chans->setObjectName(QStringLiteral("lab_chans"));
        lab_chans->setGeometry(QRect(13, 101, 51, 21));
        lab_chans->setFont(font1);
        lab_tacts = new QLabel(Dialog_par);
        lab_tacts->setObjectName(QStringLiteral("lab_tacts"));
        lab_tacts->setGeometry(QRect(13, 153, 41, 16));
        lab_tacts->setFont(font1);
        lab_0 = new QLabel(Dialog_par);
        lab_0->setObjectName(QStringLiteral("lab_0"));
        lab_0->setGeometry(QRect(83, 101, 16, 21));
        lab_0->setFont(font1);
        lab_0->setAlignment(Qt::AlignCenter);
        line_tact0 = new ParamLineEdit(Dialog_par);
        line_tact0->setObjectName(QStringLiteral("line_tact0"));
        line_tact0->setGeometry(QRect(63, 150, 49, 22));
        line_tact0->setFont(font1);
        line_tact0->setAlignment(Qt::AlignCenter);
        line_tact1 = new ParamLineEdit(Dialog_par);
        line_tact1->setObjectName(QStringLiteral("line_tact1"));
        line_tact1->setGeometry(QRect(114, 150, 49, 22));
        line_tact1->setFont(font1);
        line_tact1->setAlignment(Qt::AlignCenter);
        line_tact2 = new ParamLineEdit(Dialog_par);
        line_tact2->setObjectName(QStringLiteral("line_tact2"));
        line_tact2->setGeometry(QRect(165, 150, 49, 22));
        line_tact2->setFont(font1);
        line_tact2->setAlignment(Qt::AlignCenter);
        line_tact3 = new ParamLineEdit(Dialog_par);
        line_tact3->setObjectName(QStringLiteral("line_tact3"));
        line_tact3->setGeometry(QRect(216, 150, 49, 22));
        line_tact3->setFont(font1);
        line_tact3->setAlignment(Qt::AlignCenter);
        line_tact4 = new ParamLineEdit(Dialog_par);
        line_tact4->setObjectName(QStringLiteral("line_tact4"));
        line_tact4->setGeometry(QRect(267, 150, 49, 22));
        line_tact4->setFont(font1);
        line_tact4->setAlignment(Qt::AlignCenter);
        lab_1 = new QLabel(Dialog_par);
        lab_1->setObjectName(QStringLiteral("lab_1"));
        lab_1->setGeometry(QRect(133, 101, 16, 21));
        lab_1->setFont(font1);
        lab_1->setAlignment(Qt::AlignCenter);
        lab_2 = new QLabel(Dialog_par);
        lab_2->setObjectName(QStringLiteral("lab_2"));
        lab_2->setGeometry(QRect(184, 101, 16, 21));
        lab_2->setFont(font1);
        lab_2->setAlignment(Qt::AlignCenter);
        lab_3 = new QLabel(Dialog_par);
        lab_3->setObjectName(QStringLiteral("lab_3"));
        lab_3->setGeometry(QRect(233, 101, 16, 21));
        lab_3->setFont(font1);
        lab_3->setAlignment(Qt::AlignCenter);
        lab_4 = new QLabel(Dialog_par);
        lab_4->setObjectName(QStringLiteral("lab_4"));
        lab_4->setGeometry(QRect(283, 101, 16, 21));
        lab_4->setFont(font1);
        lab_4->setAlignment(Qt::AlignCenter);
        pushButton_colors = new QPushButton(Dialog_par);
        pushButton_colors->setObjectName(QStringLiteral("pushButton_colors"));
        pushButton_colors->setGeometry(QRect(20, 500, 121, 24));
        label_zond_freq = new QLabel(Dialog_par);
        label_zond_freq->setObjectName(QStringLiteral("label_zond_freq"));
        label_zond_freq->setGeometry(QRect(10, 36, 211, 52));
        label_zond_freq->setFrameShape(QFrame::Panel);
        label_zond_freq->setFrameShadow(QFrame::Sunken);
        label_zond_freq_unit = new QLabel(Dialog_par);
        label_zond_freq_unit->setObjectName(QStringLiteral("label_zond_freq_unit"));
        label_zond_freq_unit->setGeometry(QRect(200, 55, 21, 16));
        line_zond_freq = new QLineEdit(Dialog_par);
        line_zond_freq->setObjectName(QStringLiteral("line_zond_freq"));
        line_zond_freq->setGeometry(QRect(140, 53, 51, 20));
        line_zond_freq->setAlignment(Qt::AlignCenter);
        lab_5 = new QLabel(Dialog_par);
        lab_5->setObjectName(QStringLiteral("lab_5"));
        lab_5->setGeometry(QRect(333, 102, 16, 21));
        lab_5->setFont(font1);
        lab_5->setAlignment(Qt::AlignCenter);
        line_tact5 = new ParamLineEdit(Dialog_par);
        line_tact5->setObjectName(QStringLiteral("line_tact5"));
        line_tact5->setGeometry(QRect(318, 150, 49, 22));
        line_tact5->setFont(font1);
        line_tact5->setAlignment(Qt::AlignCenter);
        lab_ninp = new QLabel(Dialog_par);
        lab_ninp->setObjectName(QStringLiteral("lab_ninp"));
        lab_ninp->setGeometry(QRect(13, 124, 41, 21));
        lab_ninp->setFont(font1);
        line_ed_ninp0 = new ParamLineEdit(Dialog_par);
        line_ed_ninp0->setObjectName(QStringLiteral("line_ed_ninp0"));
        line_ed_ninp0->setGeometry(QRect(63, 126, 49, 22));
        line_ed_ninp0->setFont(font1);
        line_ed_ninp0->setAlignment(Qt::AlignCenter);
        line_ed_ninp3 = new ParamLineEdit(Dialog_par);
        line_ed_ninp3->setObjectName(QStringLiteral("line_ed_ninp3"));
        line_ed_ninp3->setGeometry(QRect(216, 126, 49, 22));
        line_ed_ninp3->setFont(font1);
        line_ed_ninp3->setAlignment(Qt::AlignCenter);
        line_ed_ninp2 = new ParamLineEdit(Dialog_par);
        line_ed_ninp2->setObjectName(QStringLiteral("line_ed_ninp2"));
        line_ed_ninp2->setGeometry(QRect(165, 126, 49, 22));
        line_ed_ninp2->setFont(font1);
        line_ed_ninp2->setAlignment(Qt::AlignCenter);
        line_ed_ninp5 = new ParamLineEdit(Dialog_par);
        line_ed_ninp5->setObjectName(QStringLiteral("line_ed_ninp5"));
        line_ed_ninp5->setGeometry(QRect(318, 126, 49, 22));
        line_ed_ninp5->setFont(font1);
        line_ed_ninp5->setAlignment(Qt::AlignCenter);
        line_ed_ninp1 = new ParamLineEdit(Dialog_par);
        line_ed_ninp1->setObjectName(QStringLiteral("line_ed_ninp1"));
        line_ed_ninp1->setGeometry(QRect(114, 126, 49, 22));
        line_ed_ninp1->setFont(font1);
        line_ed_ninp1->setAlignment(Qt::AlignCenter);
        line_ed_ninp4 = new ParamLineEdit(Dialog_par);
        line_ed_ninp4->setObjectName(QStringLiteral("line_ed_ninp4"));
        line_ed_ninp4->setGeometry(QRect(267, 126, 49, 22));
        line_ed_ninp4->setFont(font1);
        line_ed_ninp4->setAlignment(Qt::AlignCenter);
        lab_rej = new QLabel(Dialog_par);
        lab_rej->setObjectName(QStringLiteral("lab_rej"));
        lab_rej->setGeometry(QRect(13, 174, 41, 21));
        lab_rej->setFont(font1);
        comboBox_rej0 = new QComboBox(Dialog_par);
        comboBox_rej0->setObjectName(QStringLiteral("comboBox_rej0"));
        comboBox_rej0->setGeometry(QRect(63, 174, 50, 22));
        comboBox_rej1 = new QComboBox(Dialog_par);
        comboBox_rej1->setObjectName(QStringLiteral("comboBox_rej1"));
        comboBox_rej1->setGeometry(QRect(114, 174, 50, 22));
        comboBox_rej2 = new QComboBox(Dialog_par);
        comboBox_rej2->setObjectName(QStringLiteral("comboBox_rej2"));
        comboBox_rej2->setGeometry(QRect(165, 174, 50, 22));
        comboBox_rej3 = new QComboBox(Dialog_par);
        comboBox_rej3->setObjectName(QStringLiteral("comboBox_rej3"));
        comboBox_rej3->setGeometry(QRect(216, 174, 50, 22));
        comboBox_rej4 = new QComboBox(Dialog_par);
        comboBox_rej4->setObjectName(QStringLiteral("comboBox_rej4"));
        comboBox_rej4->setGeometry(QRect(267, 174, 50, 22));
        comboBox_rej5 = new QComboBox(Dialog_par);
        comboBox_rej5->setObjectName(QStringLiteral("comboBox_rej5"));
        comboBox_rej5->setGeometry(QRect(318, 174, 50, 22));
        label_num_tacts = new QLabel(Dialog_par);
        label_num_tacts->setObjectName(QStringLiteral("label_num_tacts"));
        label_num_tacts->setGeometry(QRect(230, 35, 121, 26));
        label_num_tacts->setFrameShape(QFrame::Panel);
        label_num_tacts->setFrameShadow(QFrame::Sunken);
        line_num_tacts = new ParamLineEdit(Dialog_par);
        line_num_tacts->setObjectName(QStringLiteral("line_num_tacts"));
        line_num_tacts->setGeometry(QRect(327, 38, 21, 20));
        line_num_tacts->setFont(font1);
        line_num_tacts->setAlignment(Qt::AlignCenter);
        checkBox_logarithm_capt = new QCheckBox(Dialog_par);
        checkBox_logarithm_capt->setObjectName(QStringLiteral("checkBox_logarithm_capt"));
        checkBox_logarithm_capt->setGeometry(QRect(197, 452, 151, 31));
        checkBox_logarithm_capt->setFont(font1);
        groupBox_filtr = new QGroupBox(Dialog_par);
        groupBox_filtr->setObjectName(QStringLiteral("groupBox_filtr"));
        groupBox_filtr->setGeometry(QRect(360, 25, 143, 65));
        groupBox_filtr->setLayoutDirection(Qt::LeftToRight);
        label_filtr_def_descr = new QLabel(groupBox_filtr);
        label_filtr_def_descr->setObjectName(QStringLiteral("label_filtr_def_descr"));
        label_filtr_def_descr->setGeometry(QRect(6, 20, 101, 16));
        label_filtr_def_descr_2 = new QLabel(groupBox_filtr);
        label_filtr_def_descr_2->setObjectName(QStringLiteral("label_filtr_def_descr_2"));
        label_filtr_def_descr_2->setGeometry(QRect(6, 41, 111, 16));
        line_filtr_thick = new ParamLineEdit(groupBox_filtr);
        line_filtr_thick->setObjectName(QStringLiteral("line_filtr_thick"));
        line_filtr_thick->setGeometry(QRect(113, 39, 20, 20));
        line_filtr_thick->setAlignment(Qt::AlignCenter);
        line_filtr_def = new ParamLineEdit(groupBox_filtr);
        line_filtr_def->setObjectName(QStringLiteral("line_filtr_def"));
        line_filtr_def->setGeometry(QRect(113, 18, 20, 20));
        line_filtr_def->setAlignment(Qt::AlignCenter);
        line_num_per_elem = new ParamLineEdit(Dialog_par);
        line_num_per_elem->setObjectName(QStringLiteral("line_num_per_elem"));
        line_num_per_elem->setGeometry(QRect(327, 65, 21, 20));
        line_num_per_elem->setFont(font1);
        line_num_per_elem->setAlignment(Qt::AlignCenter);
        label_num_per_elem = new QLabel(Dialog_par);
        label_num_per_elem->setObjectName(QStringLiteral("label_num_per_elem"));
        label_num_per_elem->setGeometry(QRect(230, 62, 121, 26));
        label_num_per_elem->setFrameShape(QFrame::Panel);
        label_num_per_elem->setFrameShadow(QFrame::Sunken);
        checkBox_axis_x_mm = new QCheckBox(Dialog_par);
        checkBox_axis_x_mm->setObjectName(QStringLiteral("checkBox_axis_x_mm"));
        checkBox_axis_x_mm->setGeometry(QRect(187, 425, 161, 21));
        checkBox_axis_x_mm->setFont(font1);
        label_resolution_koef = new QLabel(Dialog_par);
        label_resolution_koef->setObjectName(QStringLiteral("label_resolution_koef"));
        label_resolution_koef->setGeometry(QRect(10, 401, 81, 31));
        comboBox_resolution_koef = new QComboBox(Dialog_par);
        comboBox_resolution_koef->setObjectName(QStringLiteral("comboBox_resolution_koef"));
        comboBox_resolution_koef->setGeometry(QRect(96, 405, 62, 22));
        comboBox_resolution_koef->setLayoutDirection(Qt::LeftToRight);
        comboBox_resolution_koef->setMaxCount(4);
        comboBox_resolution_koef->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        cancelButton = new QPushButton(Dialog_par);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(277, 500, 92, 24));
        cancelButton->setFont(font);
        okButton = new QPushButton(Dialog_par);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(180, 500, 91, 24));
        okButton->setMinimumSize(QSize(85, 0));
        okButton->setFont(font);
        label_IP = new QLabel(Dialog_par);
        label_IP->setObjectName(QStringLiteral("label_IP"));
        label_IP->setGeometry(QRect(12, 2, 21, 31));
        QFont font2;
        font2.setPointSize(11);
        label_IP->setFont(font2);
        line_ed_ninp7 = new ParamLineEdit(Dialog_par);
        line_ed_ninp7->setObjectName(QStringLiteral("line_ed_ninp7"));
        line_ed_ninp7->setGeometry(QRect(420, 126, 49, 22));
        line_ed_ninp7->setFont(font1);
        line_ed_ninp7->setAlignment(Qt::AlignCenter);
        line_tact6 = new ParamLineEdit(Dialog_par);
        line_tact6->setObjectName(QStringLiteral("line_tact6"));
        line_tact6->setGeometry(QRect(369, 150, 49, 22));
        line_tact6->setFont(font1);
        line_tact6->setAlignment(Qt::AlignCenter);
        lab_6 = new QLabel(Dialog_par);
        lab_6->setObjectName(QStringLiteral("lab_6"));
        lab_6->setGeometry(QRect(385, 101, 16, 21));
        lab_6->setFont(font1);
        lab_6->setAlignment(Qt::AlignCenter);
        comboBox_rej7 = new QComboBox(Dialog_par);
        comboBox_rej7->setObjectName(QStringLiteral("comboBox_rej7"));
        comboBox_rej7->setGeometry(QRect(420, 174, 50, 22));
        lab_7 = new QLabel(Dialog_par);
        lab_7->setObjectName(QStringLiteral("lab_7"));
        lab_7->setGeometry(QRect(435, 102, 16, 21));
        lab_7->setFont(font1);
        lab_7->setAlignment(Qt::AlignCenter);
        comboBox_rej6 = new QComboBox(Dialog_par);
        comboBox_rej6->setObjectName(QStringLiteral("comboBox_rej6"));
        comboBox_rej6->setGeometry(QRect(369, 174, 50, 22));
        line_ed_ninp6 = new ParamLineEdit(Dialog_par);
        line_ed_ninp6->setObjectName(QStringLiteral("line_ed_ninp6"));
        line_ed_ninp6->setGeometry(QRect(369, 126, 49, 22));
        line_ed_ninp6->setFont(font1);
        line_ed_ninp6->setAlignment(Qt::AlignCenter);
        line_tact7 = new ParamLineEdit(Dialog_par);
        line_tact7->setObjectName(QStringLiteral("line_tact7"));
        line_tact7->setGeometry(QRect(420, 150, 49, 22));
        line_tact7->setFont(font1);
        line_tact7->setAlignment(Qt::AlignCenter);
        lab_14 = new QLabel(Dialog_par);
        lab_14->setObjectName(QStringLiteral("lab_14"));
        lab_14->setGeometry(QRect(386, 207, 18, 21));
        lab_14->setFont(font1);
        lab_14->setAlignment(Qt::AlignCenter);
        line_ed_ninp12 = new ParamLineEdit(Dialog_par);
        line_ed_ninp12->setObjectName(QStringLiteral("line_ed_ninp12"));
        line_ed_ninp12->setGeometry(QRect(268, 232, 49, 22));
        line_ed_ninp12->setFont(font1);
        line_ed_ninp12->setAlignment(Qt::AlignCenter);
        comboBox_rej13 = new QComboBox(Dialog_par);
        comboBox_rej13->setObjectName(QStringLiteral("comboBox_rej13"));
        comboBox_rej13->setGeometry(QRect(319, 280, 50, 22));
        line_tact10 = new ParamLineEdit(Dialog_par);
        line_tact10->setObjectName(QStringLiteral("line_tact10"));
        line_tact10->setGeometry(QRect(166, 256, 49, 22));
        line_tact10->setFont(font1);
        line_tact10->setAlignment(Qt::AlignCenter);
        lab_tacts_2 = new QLabel(Dialog_par);
        lab_tacts_2->setObjectName(QStringLiteral("lab_tacts_2"));
        lab_tacts_2->setGeometry(QRect(14, 259, 41, 16));
        lab_tacts_2->setFont(font1);
        lab_ninp_2 = new QLabel(Dialog_par);
        lab_ninp_2->setObjectName(QStringLiteral("lab_ninp_2"));
        lab_ninp_2->setGeometry(QRect(14, 230, 41, 21));
        lab_ninp_2->setFont(font1);
        line_ed_ninp14 = new ParamLineEdit(Dialog_par);
        line_ed_ninp14->setObjectName(QStringLiteral("line_ed_ninp14"));
        line_ed_ninp14->setGeometry(QRect(370, 232, 49, 22));
        line_ed_ninp14->setFont(font1);
        line_ed_ninp14->setAlignment(Qt::AlignCenter);
        line_tact13 = new ParamLineEdit(Dialog_par);
        line_tact13->setObjectName(QStringLiteral("line_tact13"));
        line_tact13->setGeometry(QRect(319, 256, 49, 22));
        line_tact13->setFont(font1);
        line_tact13->setAlignment(Qt::AlignCenter);
        line_tact9 = new ParamLineEdit(Dialog_par);
        line_tact9->setObjectName(QStringLiteral("line_tact9"));
        line_tact9->setGeometry(QRect(115, 256, 49, 22));
        line_tact9->setFont(font1);
        line_tact9->setAlignment(Qt::AlignCenter);
        line_tact11 = new ParamLineEdit(Dialog_par);
        line_tact11->setObjectName(QStringLiteral("line_tact11"));
        line_tact11->setGeometry(QRect(217, 256, 49, 22));
        line_tact11->setFont(font1);
        line_tact11->setAlignment(Qt::AlignCenter);
        comboBox_rej12 = new QComboBox(Dialog_par);
        comboBox_rej12->setObjectName(QStringLiteral("comboBox_rej12"));
        comboBox_rej12->setGeometry(QRect(268, 280, 50, 22));
        lab_chans_2 = new QLabel(Dialog_par);
        lab_chans_2->setObjectName(QStringLiteral("lab_chans_2"));
        lab_chans_2->setGeometry(QRect(14, 207, 51, 21));
        lab_chans_2->setFont(font1);
        lab_10 = new QLabel(Dialog_par);
        lab_10->setObjectName(QStringLiteral("lab_10"));
        lab_10->setGeometry(QRect(185, 207, 18, 21));
        lab_10->setFont(font1);
        lab_10->setAlignment(Qt::AlignCenter);
        line_tact8 = new ParamLineEdit(Dialog_par);
        line_tact8->setObjectName(QStringLiteral("line_tact8"));
        line_tact8->setGeometry(QRect(64, 256, 49, 22));
        line_tact8->setFont(font1);
        line_tact8->setAlignment(Qt::AlignCenter);
        lab_11 = new QLabel(Dialog_par);
        lab_11->setObjectName(QStringLiteral("lab_11"));
        lab_11->setGeometry(QRect(234, 207, 18, 21));
        lab_11->setFont(font1);
        lab_11->setAlignment(Qt::AlignCenter);
        line_tact12 = new ParamLineEdit(Dialog_par);
        line_tact12->setObjectName(QStringLiteral("line_tact12"));
        line_tact12->setGeometry(QRect(268, 256, 49, 22));
        line_tact12->setFont(font1);
        line_tact12->setAlignment(Qt::AlignCenter);
        lab_rej_2 = new QLabel(Dialog_par);
        lab_rej_2->setObjectName(QStringLiteral("lab_rej_2"));
        lab_rej_2->setGeometry(QRect(14, 280, 41, 21));
        lab_rej_2->setFont(font1);
        lab_12 = new QLabel(Dialog_par);
        lab_12->setObjectName(QStringLiteral("lab_12"));
        lab_12->setGeometry(QRect(284, 207, 18, 21));
        lab_12->setFont(font1);
        lab_12->setAlignment(Qt::AlignCenter);
        comboBox_rej14 = new QComboBox(Dialog_par);
        comboBox_rej14->setObjectName(QStringLiteral("comboBox_rej14"));
        comboBox_rej14->setGeometry(QRect(370, 280, 50, 22));
        comboBox_rej15 = new QComboBox(Dialog_par);
        comboBox_rej15->setObjectName(QStringLiteral("comboBox_rej15"));
        comboBox_rej15->setGeometry(QRect(421, 280, 50, 22));
        line_ed_ninp8 = new ParamLineEdit(Dialog_par);
        line_ed_ninp8->setObjectName(QStringLiteral("line_ed_ninp8"));
        line_ed_ninp8->setGeometry(QRect(64, 232, 49, 22));
        line_ed_ninp8->setFont(font1);
        line_ed_ninp8->setAlignment(Qt::AlignCenter);
        lab_15 = new QLabel(Dialog_par);
        lab_15->setObjectName(QStringLiteral("lab_15"));
        lab_15->setGeometry(QRect(436, 208, 18, 21));
        lab_15->setFont(font1);
        lab_15->setAlignment(Qt::AlignCenter);
        line_ed_ninp11 = new ParamLineEdit(Dialog_par);
        line_ed_ninp11->setObjectName(QStringLiteral("line_ed_ninp11"));
        line_ed_ninp11->setGeometry(QRect(217, 232, 49, 22));
        line_ed_ninp11->setFont(font1);
        line_ed_ninp11->setAlignment(Qt::AlignCenter);
        line_tact15 = new ParamLineEdit(Dialog_par);
        line_tact15->setObjectName(QStringLiteral("line_tact15"));
        line_tact15->setGeometry(QRect(421, 256, 49, 22));
        line_tact15->setFont(font1);
        line_tact15->setAlignment(Qt::AlignCenter);
        line_ed_ninp13 = new ParamLineEdit(Dialog_par);
        line_ed_ninp13->setObjectName(QStringLiteral("line_ed_ninp13"));
        line_ed_ninp13->setGeometry(QRect(319, 232, 49, 22));
        line_ed_ninp13->setFont(font1);
        line_ed_ninp13->setAlignment(Qt::AlignCenter);
        lab_13 = new QLabel(Dialog_par);
        lab_13->setObjectName(QStringLiteral("lab_13"));
        lab_13->setGeometry(QRect(334, 208, 18, 21));
        lab_13->setFont(font1);
        lab_13->setAlignment(Qt::AlignCenter);
        comboBox_rej11 = new QComboBox(Dialog_par);
        comboBox_rej11->setObjectName(QStringLiteral("comboBox_rej11"));
        comboBox_rej11->setGeometry(QRect(217, 280, 50, 22));
        line_ed_ninp9 = new ParamLineEdit(Dialog_par);
        line_ed_ninp9->setObjectName(QStringLiteral("line_ed_ninp9"));
        line_ed_ninp9->setGeometry(QRect(115, 232, 49, 22));
        line_ed_ninp9->setFont(font1);
        line_ed_ninp9->setAlignment(Qt::AlignCenter);
        comboBox_rej8 = new QComboBox(Dialog_par);
        comboBox_rej8->setObjectName(QStringLiteral("comboBox_rej8"));
        comboBox_rej8->setGeometry(QRect(64, 280, 50, 22));
        comboBox_rej9 = new QComboBox(Dialog_par);
        comboBox_rej9->setObjectName(QStringLiteral("comboBox_rej9"));
        comboBox_rej9->setGeometry(QRect(115, 280, 50, 22));
        line_ed_ninp15 = new ParamLineEdit(Dialog_par);
        line_ed_ninp15->setObjectName(QStringLiteral("line_ed_ninp15"));
        line_ed_ninp15->setGeometry(QRect(421, 232, 49, 22));
        line_ed_ninp15->setFont(font1);
        line_ed_ninp15->setAlignment(Qt::AlignCenter);
        lab_8 = new QLabel(Dialog_par);
        lab_8->setObjectName(QStringLiteral("lab_8"));
        lab_8->setGeometry(QRect(84, 207, 16, 21));
        lab_8->setFont(font1);
        lab_8->setAlignment(Qt::AlignCenter);
        line_tact14 = new ParamLineEdit(Dialog_par);
        line_tact14->setObjectName(QStringLiteral("line_tact14"));
        line_tact14->setGeometry(QRect(370, 256, 49, 22));
        line_tact14->setFont(font1);
        line_tact14->setAlignment(Qt::AlignCenter);
        lab_9 = new QLabel(Dialog_par);
        lab_9->setObjectName(QStringLiteral("lab_9"));
        lab_9->setGeometry(QRect(134, 207, 18, 21));
        lab_9->setFont(font1);
        lab_9->setAlignment(Qt::AlignCenter);
        line_ed_ninp10 = new ParamLineEdit(Dialog_par);
        line_ed_ninp10->setObjectName(QStringLiteral("line_ed_ninp10"));
        line_ed_ninp10->setGeometry(QRect(166, 232, 49, 22));
        line_ed_ninp10->setFont(font1);
        line_ed_ninp10->setAlignment(Qt::AlignCenter);
        comboBox_rej10 = new QComboBox(Dialog_par);
        comboBox_rej10->setObjectName(QStringLiteral("comboBox_rej10"));
        comboBox_rej10->setGeometry(QRect(166, 280, 50, 22));
        line_num_chan = new ParamLineEdit(Dialog_par);
        line_num_chan->setObjectName(QStringLiteral("line_num_chan"));
        line_num_chan->setGeometry(QRect(327, 9, 21, 20));
        line_num_chan->setFont(font1);
        line_num_chan->setAlignment(Qt::AlignCenter);
        label_num_chan = new QLabel(Dialog_par);
        label_num_chan->setObjectName(QStringLiteral("label_num_chan"));
        label_num_chan->setGeometry(QRect(230, 6, 121, 26));
        label_num_chan->setFrameShape(QFrame::Panel);
        label_num_chan->setFrameShadow(QFrame::Sunken);
        groupBox_speed = new QGroupBox(Dialog_par);
        groupBox_speed->setObjectName(QStringLiteral("groupBox_speed"));
        groupBox_speed->setGeometry(QRect(10, 319, 247, 71));
        groupBox_speed->setLayoutDirection(Qt::LeftToRight);
        ed_time_interval = new ParamLineEdit(groupBox_speed);
        ed_time_interval->setObjectName(QStringLiteral("ed_time_interval"));
        ed_time_interval->setGeometry(QRect(203, 44, 41, 21));
        ed_time_interval->setAlignment(Qt::AlignCenter);
        label_time_interval = new QLabel(groupBox_speed);
        label_time_interval->setObjectName(QStringLiteral("label_time_interval"));
        label_time_interval->setGeometry(QRect(127, 45, 81, 21));
        ed_update_interval = new ParamLineEdit(groupBox_speed);
        ed_update_interval->setObjectName(QStringLiteral("ed_update_interval"));
        ed_update_interval->setGeometry(QRect(79, 44, 41, 21));
        ed_update_interval->setAlignment(Qt::AlignCenter);
        ed_normal_speed = new ParamLineEdit(groupBox_speed);
        ed_normal_speed->setObjectName(QStringLiteral("ed_normal_speed"));
        ed_normal_speed->setGeometry(QRect(155, 19, 41, 21));
        ed_normal_speed->setAlignment(Qt::AlignCenter);
        label_update_interval = new QLabel(groupBox_speed);
        label_update_interval->setObjectName(QStringLiteral("label_update_interval"));
        label_update_interval->setGeometry(QRect(7, 44, 71, 21));
        label_normal_speed = new QLabel(groupBox_speed);
        label_normal_speed->setObjectName(QStringLiteral("label_normal_speed"));
        label_normal_speed->setGeometry(QRect(7, 19, 141, 21));
        label_normal_speed_units = new QLabel(groupBox_speed);
        label_normal_speed_units->setObjectName(QStringLiteral("label_normal_speed_units"));
        label_normal_speed_units->setGeometry(QRect(200, 22, 41, 16));
        groupBox_mnemo_flags = new QGroupBox(Dialog_par);
        groupBox_mnemo_flags->setObjectName(QStringLiteral("groupBox_mnemo_flags"));
        groupBox_mnemo_flags->setGeometry(QRect(360, 320, 151, 111));
        groupBox_mnemo_flags->setLayoutDirection(Qt::LeftToRight);
        checkBox_layer_0 = new QCheckBox(groupBox_mnemo_flags);
        checkBox_layer_0->setObjectName(QStringLiteral("checkBox_layer_0"));
        checkBox_layer_0->setGeometry(QRect(10, 20, 121, 21));
        checkBox_layer_0->setFont(font1);
        checkBox_layer_1 = new QCheckBox(groupBox_mnemo_flags);
        checkBox_layer_1->setObjectName(QStringLiteral("checkBox_layer_1"));
        checkBox_layer_1->setGeometry(QRect(10, 40, 141, 21));
        checkBox_layer_1->setFont(font1);
        checkBox_layer_2 = new QCheckBox(groupBox_mnemo_flags);
        checkBox_layer_2->setObjectName(QStringLiteral("checkBox_layer_2"));
        checkBox_layer_2->setGeometry(QRect(10, 60, 121, 21));
        checkBox_layer_2->setFont(font1);
        checkBox_layer_thick = new QCheckBox(groupBox_mnemo_flags);
        checkBox_layer_thick->setObjectName(QStringLiteral("checkBox_layer_thick"));
        checkBox_layer_thick->setGeometry(QRect(10, 80, 121, 21));
        checkBox_layer_thick->setFont(font1);
        lineEdit_setting_name = new QLineEdit(Dialog_par);
        lineEdit_setting_name->setObjectName(QStringLiteral("lineEdit_setting_name"));
        lineEdit_setting_name->setGeometry(QRect(10, 459, 161, 21));
        lineEdit_setting_name->setFont(font1);
        lineEdit_setting_name->setMaxLength(50);
        label_setting_name = new QLabel(Dialog_par);
        label_setting_name->setObjectName(QStringLiteral("label_setting_name"));
        label_setting_name->setGeometry(QRect(10, 439, 161, 21));
        label_setting_name->setFont(font1);
        groupBox = new QGroupBox(Dialog_par);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(267, 319, 86, 51));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        ed_coef_coord = new ParamLineEdit(groupBox);
        ed_coef_coord->setObjectName(QStringLiteral("ed_coef_coord"));
        ed_coef_coord->setGeometry(QRect(9, 20, 67, 21));
        ed_coef_coord->setAlignment(Qt::AlignCenter);
        groupBox_vdp = new QGroupBox(Dialog_par);
        groupBox_vdp->setObjectName(QStringLiteral("groupBox_vdp"));
        groupBox_vdp->setGeometry(QRect(267, 370, 86, 51));
        groupBox_vdp->setLayoutDirection(Qt::LeftToRight);
        ed_vdp = new ParamLineEdit(groupBox_vdp);
        ed_vdp->setObjectName(QStringLiteral("ed_vdp"));
        ed_vdp->setGeometry(QRect(20, 20, 61, 21));
        ed_vdp->setAlignment(Qt::AlignCenter);
        checkBox_vdp = new QCheckBox(groupBox_vdp);
        checkBox_vdp->setObjectName(QStringLiteral("checkBox_vdp"));
        checkBox_vdp->setGeometry(QRect(5, 22, 16, 17));
        checkBox_vdp->setLayoutDirection(Qt::LeftToRight);
        label_num_chan->raise();
        label_num_per_elem->raise();
        label_zond_freq->raise();
        lineEdit_ip->raise();
        lab_chans->raise();
        lab_tacts->raise();
        lab_0->raise();
        line_tact0->raise();
        line_tact1->raise();
        line_tact2->raise();
        line_tact3->raise();
        line_tact4->raise();
        lab_1->raise();
        lab_2->raise();
        lab_3->raise();
        lab_4->raise();
        pushButton_colors->raise();
        label_zond_freq_unit->raise();
        line_zond_freq->raise();
        lab_5->raise();
        line_tact5->raise();
        lab_ninp->raise();
        line_ed_ninp0->raise();
        line_ed_ninp3->raise();
        line_ed_ninp2->raise();
        line_ed_ninp5->raise();
        line_ed_ninp1->raise();
        line_ed_ninp4->raise();
        lab_rej->raise();
        comboBox_rej0->raise();
        comboBox_rej1->raise();
        comboBox_rej2->raise();
        comboBox_rej3->raise();
        comboBox_rej4->raise();
        comboBox_rej5->raise();
        label_num_tacts->raise();
        line_num_tacts->raise();
        checkBox_logarithm_capt->raise();
        groupBox_filtr->raise();
        line_num_per_elem->raise();
        checkBox_axis_x_mm->raise();
        label_resolution_koef->raise();
        comboBox_resolution_koef->raise();
        cancelButton->raise();
        okButton->raise();
        label_IP->raise();
        line_ed_ninp7->raise();
        line_tact6->raise();
        lab_6->raise();
        comboBox_rej7->raise();
        lab_7->raise();
        comboBox_rej6->raise();
        line_ed_ninp6->raise();
        line_tact7->raise();
        lab_14->raise();
        line_ed_ninp12->raise();
        comboBox_rej13->raise();
        line_tact10->raise();
        lab_tacts_2->raise();
        lab_ninp_2->raise();
        line_ed_ninp14->raise();
        line_tact13->raise();
        line_tact9->raise();
        line_tact11->raise();
        comboBox_rej12->raise();
        lab_chans_2->raise();
        lab_10->raise();
        line_tact8->raise();
        lab_11->raise();
        line_tact12->raise();
        lab_rej_2->raise();
        lab_12->raise();
        comboBox_rej14->raise();
        comboBox_rej15->raise();
        line_ed_ninp8->raise();
        lab_15->raise();
        line_ed_ninp11->raise();
        line_tact15->raise();
        line_ed_ninp13->raise();
        lab_13->raise();
        comboBox_rej11->raise();
        line_ed_ninp9->raise();
        comboBox_rej8->raise();
        comboBox_rej9->raise();
        line_ed_ninp15->raise();
        lab_8->raise();
        line_tact14->raise();
        lab_9->raise();
        line_ed_ninp10->raise();
        comboBox_rej10->raise();
        line_num_chan->raise();
        groupBox_speed->raise();
        groupBox_mnemo_flags->raise();
        lineEdit_setting_name->raise();
        label_setting_name->raise();
        groupBox->raise();
        groupBox_vdp->raise();
        QWidget::setTabOrder(lineEdit_ip, line_num_chan);
        QWidget::setTabOrder(line_num_chan, checkBox_axis_x_mm);
        QWidget::setTabOrder(checkBox_axis_x_mm, checkBox_logarithm_capt);
        QWidget::setTabOrder(checkBox_logarithm_capt, line_zond_freq);
        QWidget::setTabOrder(line_zond_freq, line_num_tacts);
        QWidget::setTabOrder(line_num_tacts, line_num_per_elem);
        QWidget::setTabOrder(line_num_per_elem, line_ed_ninp0);
        QWidget::setTabOrder(line_ed_ninp0, line_tact0);
        QWidget::setTabOrder(line_tact0, comboBox_rej0);
        QWidget::setTabOrder(comboBox_rej0, line_ed_ninp1);
        QWidget::setTabOrder(line_ed_ninp1, line_tact1);
        QWidget::setTabOrder(line_tact1, comboBox_rej1);
        QWidget::setTabOrder(comboBox_rej1, line_ed_ninp2);
        QWidget::setTabOrder(line_ed_ninp2, line_tact2);
        QWidget::setTabOrder(line_tact2, comboBox_rej2);
        QWidget::setTabOrder(comboBox_rej2, line_ed_ninp3);
        QWidget::setTabOrder(line_ed_ninp3, line_tact3);
        QWidget::setTabOrder(line_tact3, comboBox_rej3);
        QWidget::setTabOrder(comboBox_rej3, line_ed_ninp4);
        QWidget::setTabOrder(line_ed_ninp4, line_tact4);
        QWidget::setTabOrder(line_tact4, comboBox_rej4);
        QWidget::setTabOrder(comboBox_rej4, line_ed_ninp5);
        QWidget::setTabOrder(line_ed_ninp5, line_tact5);
        QWidget::setTabOrder(line_tact5, comboBox_rej5);
        QWidget::setTabOrder(comboBox_rej5, line_ed_ninp6);
        QWidget::setTabOrder(line_ed_ninp6, line_tact6);
        QWidget::setTabOrder(line_tact6, comboBox_rej6);
        QWidget::setTabOrder(comboBox_rej6, line_ed_ninp7);
        QWidget::setTabOrder(line_ed_ninp7, line_tact7);
        QWidget::setTabOrder(line_tact7, comboBox_rej7);
        QWidget::setTabOrder(comboBox_rej7, line_ed_ninp8);
        QWidget::setTabOrder(line_ed_ninp8, line_tact8);
        QWidget::setTabOrder(line_tact8, comboBox_rej8);
        QWidget::setTabOrder(comboBox_rej8, line_ed_ninp9);
        QWidget::setTabOrder(line_ed_ninp9, line_tact9);
        QWidget::setTabOrder(line_tact9, comboBox_rej9);
        QWidget::setTabOrder(comboBox_rej9, line_ed_ninp10);
        QWidget::setTabOrder(line_ed_ninp10, line_tact10);
        QWidget::setTabOrder(line_tact10, comboBox_rej10);
        QWidget::setTabOrder(comboBox_rej10, line_ed_ninp11);
        QWidget::setTabOrder(line_ed_ninp11, line_tact11);
        QWidget::setTabOrder(line_tact11, comboBox_rej11);
        QWidget::setTabOrder(comboBox_rej11, line_ed_ninp12);
        QWidget::setTabOrder(line_ed_ninp12, line_tact12);
        QWidget::setTabOrder(line_tact12, comboBox_rej12);
        QWidget::setTabOrder(comboBox_rej12, line_ed_ninp13);
        QWidget::setTabOrder(line_ed_ninp13, line_tact13);
        QWidget::setTabOrder(line_tact13, comboBox_rej13);
        QWidget::setTabOrder(comboBox_rej13, line_ed_ninp14);
        QWidget::setTabOrder(line_ed_ninp14, line_tact14);
        QWidget::setTabOrder(line_tact14, comboBox_rej14);
        QWidget::setTabOrder(comboBox_rej14, line_ed_ninp15);
        QWidget::setTabOrder(line_ed_ninp15, line_tact15);
        QWidget::setTabOrder(line_tact15, comboBox_rej15);
        QWidget::setTabOrder(comboBox_rej15, line_filtr_def);
        QWidget::setTabOrder(line_filtr_def, line_filtr_thick);
        QWidget::setTabOrder(line_filtr_thick, pushButton_colors);
        QWidget::setTabOrder(pushButton_colors, comboBox_resolution_koef);
        QWidget::setTabOrder(comboBox_resolution_koef, cancelButton);
        QWidget::setTabOrder(cancelButton, lineEdit_setting_name);
        QWidget::setTabOrder(lineEdit_setting_name, ed_time_interval);
        QWidget::setTabOrder(ed_time_interval, ed_update_interval);
        QWidget::setTabOrder(ed_update_interval, ed_normal_speed);
        QWidget::setTabOrder(ed_normal_speed, checkBox_layer_0);
        QWidget::setTabOrder(checkBox_layer_0, checkBox_layer_1);
        QWidget::setTabOrder(checkBox_layer_1, checkBox_layer_2);
        QWidget::setTabOrder(checkBox_layer_2, checkBox_layer_thick);
        QWidget::setTabOrder(checkBox_layer_thick, ed_coef_coord);
        QWidget::setTabOrder(ed_coef_coord, ed_vdp);
        QWidget::setTabOrder(ed_vdp, checkBox_vdp);
        QWidget::setTabOrder(checkBox_vdp, okButton);

        retranslateUi(Dialog_par);
        QObject::connect(okButton, SIGNAL(clicked()), Dialog_par, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Dialog_par, SLOT(reject()));

        comboBox_resolution_koef->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog_par);
    } // setupUi

    void retranslateUi(QDialog *Dialog_par)
    {
        Dialog_par->setWindowTitle(QApplication::translate("Dialog_par", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0));
        lab_chans->setText(QApplication::translate("Dialog_par", "\320\232\320\260\320\275\320\260\320\273", 0));
        lab_tacts->setText(QApplication::translate("Dialog_par", "\320\242\320\260\320\272\321\202", 0));
        lab_0->setText(QApplication::translate("Dialog_par", "1", 0));
        lab_1->setText(QApplication::translate("Dialog_par", "2", 0));
        lab_2->setText(QApplication::translate("Dialog_par", "3", 0));
        lab_3->setText(QApplication::translate("Dialog_par", "4", 0));
        lab_4->setText(QApplication::translate("Dialog_par", "5", 0));
        pushButton_colors->setText(QApplication::translate("Dialog_par", "\320\246\320\262\320\265\321\202\320\276\320\262\320\260\321\217 \321\201\321\205\320\265\320\274\320\260", 0));
        label_zond_freq->setText(QApplication::translate("Dialog_par", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\277\320\276\320\262\321\202\320\276\321\200\320\265\320\275\320\270\321\217<br> \320\267\320\276\320\275\320\264\320\270\321\200. \320\270\320\274\320\277\321\203\320\273\321\214\321\201\320\276\320\262", 0));
        label_zond_freq_unit->setText(QApplication::translate("Dialog_par", "\320\223\321\206", 0));
        line_zond_freq->setText(QApplication::translate("Dialog_par", "1000", 0));
        lab_5->setText(QApplication::translate("Dialog_par", "6", 0));
        lab_ninp->setText(QApplication::translate("Dialog_par", "\320\243\321\201\320\270\320\273", 0));
        lab_rej->setText(QApplication::translate("Dialog_par", "\320\240\320\265\320\266\320\270\320\274", 0));
        comboBox_rej0->clear();
        comboBox_rej0->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej1->clear();
        comboBox_rej1->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej2->clear();
        comboBox_rej2->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej3->clear();
        comboBox_rej3->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej4->clear();
        comboBox_rej4->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej5->clear();
        comboBox_rej5->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        label_num_tacts->setText(QApplication::translate("Dialog_par", "\320\247\320\270\321\201\320\273\320\276 \321\202\320\260\320\272\321\202\320\276\320\262", 0));
        line_num_tacts->setText(QApplication::translate("Dialog_par", "4", 0));
        checkBox_logarithm_capt->setText(QApplication::translate("Dialog_par", "\320\250\320\272\320\260\320\273\320\260 \320\262 \320\264\320\221 \320\276\321\202 \320\277\320\276\321\200\320\276\320\263\320\260\n"
"\320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\263\320\276 \321\201\321\202\321\200\320\276\320\261\320\260", 0));
        groupBox_filtr->setTitle(QApplication::translate("Dialog_par", "\320\237\320\276\320\274\320\265\321\205\320\276\321\203\321\201\321\202\320\276\320\271\321\207\320\270\320\262\320\276\321\201\321\202\321\214:", 0));
        label_filtr_def_descr->setText(QApplication::translate("Dialog_par", "\320\264\320\265\321\204\320\265\320\272\321\202\320\276\321\201\320\272\320\276\320\277\320\270\320\270", 0));
        label_filtr_def_descr_2->setText(QApplication::translate("Dialog_par", "\321\202\320\276\320\273\321\211\320\270\320\275\320\275\320\276\320\274\320\265\321\202\321\200\320\270\320\270", 0));
        line_filtr_thick->setText(QApplication::translate("Dialog_par", "1", 0));
        line_filtr_def->setText(QApplication::translate("Dialog_par", "0", 0));
        line_num_per_elem->setText(QApplication::translate("Dialog_par", "2", 0));
        label_num_per_elem->setText(QApplication::translate("Dialog_par", "\320\237\321\200\320\270\321\221\320\274 \320\262 1 \320\277\320\260\320\272.", 0));
        checkBox_axis_x_mm->setText(QApplication::translate("Dialog_par", "\320\250\320\272\320\260\320\273\320\260 \321\200\320\260\320\267\320\262\321\221\321\200\321\202\320\272\320\270 \320\262 \320\274\320\274", 0));
        label_resolution_koef->setText(QApplication::translate("Dialog_par", "\320\240\320\260\320\267\321\200\320\265\321\210\320\265\320\275\320\270\320\265\n"
"\321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", 0));
        comboBox_resolution_koef->clear();
        comboBox_resolution_koef->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "1 \320\274\320\274", 0)
         << QApplication::translate("Dialog_par", "2 \320\274\320\274", 0)
         << QApplication::translate("Dialog_par", "5 \320\274\320\274", 0)
         << QApplication::translate("Dialog_par", "10 \320\274\320\274", 0)
        );
        cancelButton->setText(QApplication::translate("Dialog_par", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
        okButton->setText(QApplication::translate("Dialog_par", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0));
        label_IP->setText(QApplication::translate("Dialog_par", "IP:", 0));
        lab_6->setText(QApplication::translate("Dialog_par", "7", 0));
        comboBox_rej7->clear();
        comboBox_rej7->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        lab_7->setText(QApplication::translate("Dialog_par", "8", 0));
        comboBox_rej6->clear();
        comboBox_rej6->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        lab_14->setText(QApplication::translate("Dialog_par", "15", 0));
        comboBox_rej13->clear();
        comboBox_rej13->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        lab_tacts_2->setText(QApplication::translate("Dialog_par", "\320\242\320\260\320\272\321\202", 0));
        lab_ninp_2->setText(QApplication::translate("Dialog_par", "\320\243\321\201\320\270\320\273", 0));
        comboBox_rej12->clear();
        comboBox_rej12->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        lab_chans_2->setText(QApplication::translate("Dialog_par", "\320\232\320\260\320\275\320\260\320\273", 0));
        lab_10->setText(QApplication::translate("Dialog_par", "11", 0));
        lab_11->setText(QApplication::translate("Dialog_par", "12", 0));
        lab_rej_2->setText(QApplication::translate("Dialog_par", "\320\240\320\265\320\266\320\270\320\274", 0));
        lab_12->setText(QApplication::translate("Dialog_par", "13", 0));
        comboBox_rej14->clear();
        comboBox_rej14->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej15->clear();
        comboBox_rej15->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        lab_15->setText(QApplication::translate("Dialog_par", "16", 0));
        lab_13->setText(QApplication::translate("Dialog_par", "14", 0));
        comboBox_rej11->clear();
        comboBox_rej11->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej8->clear();
        comboBox_rej8->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        comboBox_rej9->clear();
        comboBox_rej9->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        lab_8->setText(QApplication::translate("Dialog_par", "9", 0));
        lab_9->setText(QApplication::translate("Dialog_par", "10", 0));
        comboBox_rej10->clear();
        comboBox_rej10->insertItems(0, QStringList()
         << QApplication::translate("Dialog_par", "\320\224\320\237\321\200", 0)
         << QApplication::translate("Dialog_par", "\320\224\320\237\320\276", 0)
         << QApplication::translate("Dialog_par", "\320\240/\320\242\320\273", 0)
         << QApplication::translate("Dialog_par", "B \321\201\320\272", 0)
         << QApplication::translate("Dialog_par", "\320\242\320\273", 0)
        );
        line_num_chan->setText(QApplication::translate("Dialog_par", "16", 0));
        label_num_chan->setText(QApplication::translate("Dialog_par", "\320\247\320\270\321\201\320\273\320\276 \320\272\320\260\320\275\320\260\320\273\320\276\320\262", 0));
        groupBox_speed->setTitle(QApplication::translate("Dialog_par", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\321\217", 0));
        label_time_interval->setText(QApplication::translate("Dialog_par", "\320\230\320\275\321\202.\320\267\320\260\320\274\320\265\321\200\320\276\320\262", 0));
        label_update_interval->setText(QApplication::translate("Dialog_par", "\320\230\320\275\321\202.\320\276\320\261\320\275\320\276\320\262\320\273.", 0));
        label_normal_speed->setText(QApplication::translate("Dialog_par", "\320\235\320\276\320\274\320\270\320\275\320\260\320\273\321\214\320\275\320\260\321\217 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214", 0));
        label_normal_speed_units->setText(QApplication::translate("Dialog_par", "\320\274\320\274/\321\201", 0));
        groupBox_mnemo_flags->setTitle(QApplication::translate("Dialog_par", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0));
        checkBox_layer_0->setText(QApplication::translate("Dialog_par", "\320\264\320\265\321\204\320\265\320\272\321\202\321\213 \320\262\320\265\321\200\321\205", 0));
        checkBox_layer_1->setText(QApplication::translate("Dialog_par", "\320\264\320\265\321\204\320\265\320\272\321\202\321\213 \321\201\320\265\321\200\320\265\320\264\320\270\320\275\320\260", 0));
        checkBox_layer_2->setText(QApplication::translate("Dialog_par", "\320\264\320\265\321\204\320\265\320\272\321\202\321\213 \320\275\320\270\320\267", 0));
        checkBox_layer_thick->setText(QApplication::translate("Dialog_par", "\321\202\320\276\320\273\321\211\320\270\320\275\320\260", 0));
        lineEdit_setting_name->setText(QString());
        label_setting_name->setText(QApplication::translate("Dialog_par", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        groupBox->setTitle(QApplication::translate("Dialog_par", "\320\232\320\276\321\215\321\204.\320\272\320\276\320\276\321\200\320\264", 0));
        groupBox_vdp->setTitle(QApplication::translate("Dialog_par", "\320\222\320\224\320\237", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_par: public Ui_Dialog_par {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAL_PAR_H
