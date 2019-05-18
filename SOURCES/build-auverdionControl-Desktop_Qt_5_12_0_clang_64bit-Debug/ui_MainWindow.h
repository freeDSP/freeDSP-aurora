/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
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
    QTabWidget *tabChannels;
    QWidget *tab;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayoutVolume;
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
        tabChannels = new QTabWidget(centralWidget);
        tabChannels->setObjectName(QString::fromUtf8("tabChannels"));
        tabChannels->setTabPosition(QTabWidget::West);
        tabChannels->setUsesScrollButtons(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabChannels->addTab(tab, QString());

        horizontalLayout_2->addWidget(tabChannels);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayoutVolume = new QVBoxLayout();
        verticalLayoutVolume->setSpacing(6);
        verticalLayoutVolume->setObjectName(QString::fromUtf8("verticalLayoutVolume"));
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


        verticalLayoutVolume->addLayout(horizontalLayout);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("dBfs"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayoutVolume->addWidget(label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayoutVolume->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayoutVolume);

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

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "auverdionControl", nullptr));
        actionWrite_to_DSP->setText(QApplication::translate("MainWindow", "Write to DSP", nullptr));
#ifndef QT_NO_TOOLTIP
        actionWrite_to_DSP->setToolTip(QApplication::translate("MainWindow", "Write parameter to DSP", nullptr));
#endif // QT_NO_TOOLTIP
        actionRead_from_DSP->setText(QApplication::translate("MainWindow", "Read from DSP", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRead_from_DSP->setToolTip(QApplication::translate("MainWindow", "Read all parameter from DSP", nullptr));
#endif // QT_NO_TOOLTIP
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        tabChannels->setTabText(tabChannels->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Volume", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
