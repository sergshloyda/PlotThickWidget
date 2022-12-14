/********************************************************************************
** Form generated from reading UI file 'plottickwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTICKWIDGET_H
#define UI_PLOTTICKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chanindicwidget.h"
#include "oscplotterview.h"

QT_BEGIN_NAMESPACE

class Ui_PlotTickWidgetClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *writeBtn;
    QPushButton *readBtn;
    QPushButton *add_vrch_point;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QFrame *main_widget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    ChanIndicWidget *channel_indic;
    QHBoxLayout *horizontalLayout;
    QLabel *label_gens;
    QLabel *label_uss;
    QLabel *label_t_izm;
    QLabel *label_y_izm;
    QLabel *label_x_izm;
    OscPlotterView *osc_view;
    QFrame *OscWidget;
    QFrame *settings_frame;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;

    void setupUi(QWidget *PlotTickWidgetClass)
    {
        if (PlotTickWidgetClass->objectName().isEmpty())
            PlotTickWidgetClass->setObjectName(QStringLiteral("PlotTickWidgetClass"));
        PlotTickWidgetClass->resize(1238, 800);
        PlotTickWidgetClass->setMinimumSize(QSize(1200, 800));
        verticalLayout_2 = new QVBoxLayout(PlotTickWidgetClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton = new QPushButton(PlotTickWidgetClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        writeBtn = new QPushButton(PlotTickWidgetClass);
        writeBtn->setObjectName(QStringLiteral("writeBtn"));

        horizontalLayout_4->addWidget(writeBtn);

        readBtn = new QPushButton(PlotTickWidgetClass);
        readBtn->setObjectName(QStringLiteral("readBtn"));

        horizontalLayout_4->addWidget(readBtn);

        add_vrch_point = new QPushButton(PlotTickWidgetClass);
        add_vrch_point->setObjectName(QStringLiteral("add_vrch_point"));

        horizontalLayout_4->addWidget(add_vrch_point);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        splitter = new QSplitter(PlotTickWidgetClass);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        main_widget = new QFrame(splitter);
        main_widget->setObjectName(QStringLiteral("main_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(main_widget->sizePolicy().hasHeightForWidth());
        main_widget->setSizePolicy(sizePolicy);
        main_widget->setMinimumSize(QSize(200, 0));
        main_widget->setFrameShape(QFrame::Box);
        main_widget->setFrameShadow(QFrame::Sunken);
        splitter->addWidget(main_widget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        channel_indic = new ChanIndicWidget(layoutWidget);
        channel_indic->setObjectName(QStringLiteral("channel_indic"));
        channel_indic->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(channel_indic);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 10, -1);
        label_gens = new QLabel(layoutWidget);
        label_gens->setObjectName(QStringLiteral("label_gens"));
        QFont font;
        font.setPointSize(13);
        label_gens->setFont(font);
        label_gens->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_gens);

        label_uss = new QLabel(layoutWidget);
        label_uss->setObjectName(QStringLiteral("label_uss"));
        label_uss->setFont(font);
        label_uss->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_uss);

        label_t_izm = new QLabel(layoutWidget);
        label_t_izm->setObjectName(QStringLiteral("label_t_izm"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        label_t_izm->setFont(font1);

        horizontalLayout->addWidget(label_t_izm);

        label_y_izm = new QLabel(layoutWidget);
        label_y_izm->setObjectName(QStringLiteral("label_y_izm"));
        label_y_izm->setFont(font1);

        horizontalLayout->addWidget(label_y_izm);

        label_x_izm = new QLabel(layoutWidget);
        label_x_izm->setObjectName(QStringLiteral("label_x_izm"));
        label_x_izm->setFont(font1);

        horizontalLayout->addWidget(label_x_izm);


        verticalLayout->addLayout(horizontalLayout);

        osc_view = new OscPlotterView(layoutWidget);
        osc_view->setObjectName(QStringLiteral("osc_view"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(osc_view->sizePolicy().hasHeightForWidth());
        osc_view->setSizePolicy(sizePolicy1);
        osc_view->setMinimumSize(QSize(600, 0));

        verticalLayout->addWidget(osc_view);

        OscWidget = new QFrame(layoutWidget);
        OscWidget->setObjectName(QStringLiteral("OscWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(OscWidget->sizePolicy().hasHeightForWidth());
        OscWidget->setSizePolicy(sizePolicy2);
        OscWidget->setFrameShape(QFrame::Box);
        OscWidget->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(OscWidget);

        splitter->addWidget(layoutWidget);

        horizontalLayout_2->addWidget(splitter);

        settings_frame = new QFrame(PlotTickWidgetClass);
        settings_frame->setObjectName(QStringLiteral("settings_frame"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(settings_frame->sizePolicy().hasHeightForWidth());
        settings_frame->setSizePolicy(sizePolicy3);
        settings_frame->setMinimumSize(QSize(199, 0));
        settings_frame->setFrameShape(QFrame::Box);
        settings_frame->setFrameShadow(QFrame::Plain);
        horizontalLayout_3 = new QHBoxLayout(settings_frame);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);

        horizontalLayout_3->addLayout(verticalLayout_4);


        horizontalLayout_2->addWidget(settings_frame);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(1, 1);

        retranslateUi(PlotTickWidgetClass);

        QMetaObject::connectSlotsByName(PlotTickWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *PlotTickWidgetClass)
    {
        PlotTickWidgetClass->setWindowTitle(QApplication::translate("PlotTickWidgetClass", "PlotTickWidget", 0));
        pushButton->setText(QApplication::translate("PlotTickWidgetClass", "Start", 0));
        writeBtn->setText(QApplication::translate("PlotTickWidgetClass", "Write", 0));
        readBtn->setText(QApplication::translate("PlotTickWidgetClass", "Read", 0));
        add_vrch_point->setText(QApplication::translate("PlotTickWidgetClass", "Add VRCh", 0));
        label_t_izm->setText(QApplication::translate("PlotTickWidgetClass", "\320\242\320\270: \320\274\320\272\321\201", 0));
        label_y_izm->setText(QApplication::translate("PlotTickWidgetClass", "Y: \320\274\320\274", 0));
        label_x_izm->setText(QApplication::translate("PlotTickWidgetClass", "X: \320\274\320\274", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotTickWidgetClass: public Ui_PlotTickWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTICKWIDGET_H
