/********************************************************************************
** Form generated from reading UI file 'dial_load_save_par.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAL_LOAD_SAVE_PAR_H
#define UI_DIAL_LOAD_SAVE_PAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include "lineeditreturn.h"
#include "paramlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog_load_save_par
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_ip_descr;
    QLabel *label_ip;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lab_npar;
    ParamLineEdit *ed_num_par;
    QSpacerItem *horizontalSpacer_4;
    QTableView *tableView_files;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_path;
    LineEditReturn *lineEdit_path;
    QPushButton *pushButt_dir;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Dialog_load_save_par)
    {
        if (Dialog_load_save_par->objectName().isEmpty())
            Dialog_load_save_par->setObjectName(QStringLiteral("Dialog_load_save_par"));
        Dialog_load_save_par->resize(1052, 502);
        verticalLayout = new QVBoxLayout(Dialog_load_save_par);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, -1, 10, -1);
        label_ip_descr = new QLabel(Dialog_load_save_par);
        label_ip_descr->setObjectName(QStringLiteral("label_ip_descr"));
        QFont font;
        font.setPointSize(9);
        label_ip_descr->setFont(font);

        horizontalLayout_2->addWidget(label_ip_descr);

        label_ip = new QLabel(Dialog_load_save_par);
        label_ip->setObjectName(QStringLiteral("label_ip"));
        label_ip->setFont(font);

        horizontalLayout_2->addWidget(label_ip);

        horizontalSpacer_3 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        lab_npar = new QLabel(Dialog_load_save_par);
        lab_npar->setObjectName(QStringLiteral("lab_npar"));
        lab_npar->setFont(font);

        horizontalLayout_2->addWidget(lab_npar);

        ed_num_par = new ParamLineEdit(Dialog_load_save_par);
        ed_num_par->setObjectName(QStringLiteral("ed_num_par"));
        ed_num_par->setMinimumSize(QSize(30, 0));
        ed_num_par->setMaximumSize(QSize(30, 16777215));
        ed_num_par->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ed_num_par);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView_files = new QTableView(Dialog_load_save_par);
        tableView_files->setObjectName(QStringLiteral("tableView_files"));
        tableView_files->setFocusPolicy(Qt::NoFocus);
        tableView_files->setContextMenuPolicy(Qt::NoContextMenu);
        tableView_files->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView_files->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView_files->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView_files->setTextElideMode(Qt::ElideMiddle);
        tableView_files->setCornerButtonEnabled(false);
        tableView_files->horizontalHeader()->setCascadingSectionResizes(true);
        tableView_files->horizontalHeader()->setStretchLastSection(true);
        tableView_files->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView_files);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        lab_path = new QLabel(Dialog_load_save_par);
        lab_path->setObjectName(QStringLiteral("lab_path"));
        lab_path->setFont(font);

        horizontalLayout->addWidget(lab_path);

        lineEdit_path = new LineEditReturn(Dialog_load_save_par);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setMinimumSize(QSize(500, 0));

        horizontalLayout->addWidget(lineEdit_path);

        pushButt_dir = new QPushButton(Dialog_load_save_par);
        pushButt_dir->setObjectName(QStringLiteral("pushButt_dir"));
        pushButt_dir->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(pushButt_dir);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(Dialog_load_save_par);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setFocusPolicy(Qt::TabFocus);

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(Dialog_load_save_par);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setFocusPolicy(Qt::TabFocus);

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, lineEdit_path);
        QWidget::setTabOrder(lineEdit_path, pushButt_dir);

        retranslateUi(Dialog_load_save_par);
        QObject::connect(okButton, SIGNAL(clicked()), Dialog_load_save_par, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Dialog_load_save_par, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_load_save_par);
    } // setupUi

    void retranslateUi(QDialog *Dialog_load_save_par)
    {
        Dialog_load_save_par->setWindowTitle(QApplication::translate("Dialog_load_save_par", "\320\244\320\260\320\271\320\273 \320\275\320\260\321\201\321\202\321\200\320\276\320\265\320\272", 0));
        label_ip_descr->setText(QApplication::translate("Dialog_load_save_par", "IP", 0));
        label_ip->setText(QApplication::translate("Dialog_load_save_par", "192.168.1.33", 0));
        lab_npar->setText(QApplication::translate("Dialog_load_save_par", "\320\275\320\276\320\274\320\265\321\200 \320\277\320\260\321\200.", 0));
        lab_path->setText(QApplication::translate("Dialog_load_save_par", "\320\277\321\203\321\202\321\214:", 0));
        pushButt_dir->setText(QApplication::translate("Dialog_load_save_par", "...", 0));
        okButton->setText(QApplication::translate("Dialog_load_save_par", "OK", 0));
        cancelButton->setText(QApplication::translate("Dialog_load_save_par", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_load_save_par: public Ui_Dialog_load_save_par {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAL_LOAD_SAVE_PAR_H
