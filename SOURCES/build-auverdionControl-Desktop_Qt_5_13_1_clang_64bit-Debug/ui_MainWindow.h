/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVolumeSlider.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWrite_to_DSP;
    QAction *actionRead_from_DSP;
    QAction *actionAbout;
    QAction *actionSettings;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabPresets;
    QWidget *tabPresetA;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVolumeSlider *volumeSliderMain;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionWrite_to_DSP = new QAction(MainWindow);
        actionWrite_to_DSP->setObjectName(QString::fromUtf8("actionWrite_to_DSP"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/upload_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWrite_to_DSP->setIcon(icon);
        actionRead_from_DSP = new QAction(MainWindow);
        actionRead_from_DSP->setObjectName(QString::fromUtf8("actionRead_from_DSP"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/reload_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRead_from_DSP->setIcon(icon1);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/info_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon2);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/kcmsystem.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabPresets = new QTabWidget(centralWidget);
        tabPresets->setObjectName(QString::fromUtf8("tabPresets"));
        tabPresets->setTabPosition(QTabWidget::South);
        tabPresetA = new QWidget();
        tabPresetA->setObjectName(QString::fromUtf8("tabPresetA"));
        tabPresets->addTab(tabPresetA, QString());

        horizontalLayout_2->addWidget(tabPresets);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        volumeSliderMain = new QVolumeSlider(centralWidget);
        volumeSliderMain->setObjectName(QString::fromUtf8("volumeSliderMain"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(volumeSliderMain->sizePolicy().hasHeightForWidth());
        volumeSliderMain->setSizePolicy(sizePolicy);
        volumeSliderMain->setMinimumSize(QSize(80, 0));
        volumeSliderMain->setBaseSize(QSize(100, 0));

        horizontalLayout->addWidget(volumeSliderMain);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("dBfs"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setOrientation(Qt::Vertical);
        MainWindow->addToolBar(Qt::RightToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionRead_from_DSP);
        mainToolBar->addAction(actionWrite_to_DSP);
        mainToolBar->addAction(actionSettings);
        mainToolBar->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabPresets->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "auverdionControl", nullptr));
        actionWrite_to_DSP->setText(QCoreApplication::translate("MainWindow", "Write to DSP", nullptr));
#if QT_CONFIG(tooltip)
        actionWrite_to_DSP->setToolTip(QCoreApplication::translate("MainWindow", "Write parameter to DSP", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRead_from_DSP->setText(QCoreApplication::translate("MainWindow", "Read from DSP", nullptr));
#if QT_CONFIG(tooltip)
        actionRead_from_DSP->setToolTip(QCoreApplication::translate("MainWindow", "Read all parameter from DSP", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        tabPresets->setTabText(tabPresets->indexOf(tabPresetA), QCoreApplication::translate("MainWindow", "Preset A", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Volume", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
