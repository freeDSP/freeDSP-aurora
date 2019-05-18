/********************************************************************************
** Form generated from reading UI file 'DialogSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSETTINGS_H
#define UI_DIALOGSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSettings
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxPlugIn;
    QPushButton *pushButtonInstallPlugin;
    QPushButton *pushButtonVerifyPlugin;
    QGroupBox *groupBoxWifiConfiguration;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButtonAP;
    QRadioButton *radioButtonLocalWifi;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditSSID;
    QLabel *label_2;
    QLineEdit *lineEditPassword;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonStoreWiFiConfig;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEditIpAddress;
    QPushButton *pushButtonPing;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSettings)
    {
        if (DialogSettings->objectName().isEmpty())
            DialogSettings->setObjectName(QString::fromUtf8("DialogSettings"));
        DialogSettings->resize(580, 463);
        verticalLayout = new QVBoxLayout(DialogSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(DialogSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBoxPlugIn = new QComboBox(groupBox);
        comboBoxPlugIn->setObjectName(QString::fromUtf8("comboBoxPlugIn"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxPlugIn->sizePolicy().hasHeightForWidth());
        comboBoxPlugIn->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBoxPlugIn);

        pushButtonInstallPlugin = new QPushButton(groupBox);
        pushButtonInstallPlugin->setObjectName(QString::fromUtf8("pushButtonInstallPlugin"));

        horizontalLayout->addWidget(pushButtonInstallPlugin);

        pushButtonVerifyPlugin = new QPushButton(groupBox);
        pushButtonVerifyPlugin->setObjectName(QString::fromUtf8("pushButtonVerifyPlugin"));

        horizontalLayout->addWidget(pushButtonVerifyPlugin);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        groupBoxWifiConfiguration = new QGroupBox(DialogSettings);
        groupBoxWifiConfiguration->setObjectName(QString::fromUtf8("groupBoxWifiConfiguration"));
        verticalLayout_3 = new QVBoxLayout(groupBoxWifiConfiguration);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButtonAP = new QRadioButton(groupBoxWifiConfiguration);
        radioButtonAP->setObjectName(QString::fromUtf8("radioButtonAP"));

        horizontalLayout_4->addWidget(radioButtonAP);

        radioButtonLocalWifi = new QRadioButton(groupBoxWifiConfiguration);
        radioButtonLocalWifi->setObjectName(QString::fromUtf8("radioButtonLocalWifi"));

        horizontalLayout_4->addWidget(radioButtonLocalWifi);


        verticalLayout_3->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBoxWifiConfiguration);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditSSID = new QLineEdit(groupBoxWifiConfiguration);
        lineEditSSID->setObjectName(QString::fromUtf8("lineEditSSID"));
        lineEditSSID->setInputMask(QString::fromUtf8(""));

        gridLayout->addWidget(lineEditSSID, 0, 1, 1, 1);

        label_2 = new QLabel(groupBoxWifiConfiguration);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditPassword = new QLineEdit(groupBoxWifiConfiguration);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setInputMask(QString::fromUtf8(""));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditPassword, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonStoreWiFiConfig = new QPushButton(groupBoxWifiConfiguration);
        pushButtonStoreWiFiConfig->setObjectName(QString::fromUtf8("pushButtonStoreWiFiConfig"));

        horizontalLayout_3->addWidget(pushButtonStoreWiFiConfig);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBoxWifiConfiguration);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        lineEditIpAddress = new QLineEdit(groupBoxWifiConfiguration);
        lineEditIpAddress->setObjectName(QString::fromUtf8("lineEditIpAddress"));
        lineEditIpAddress->setEnabled(true);
        lineEditIpAddress->setText(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(lineEditIpAddress);

        pushButtonPing = new QPushButton(groupBoxWifiConfiguration);
        pushButtonPing->setObjectName(QString::fromUtf8("pushButtonPing"));

        horizontalLayout_5->addWidget(pushButtonPing);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout->addWidget(groupBoxWifiConfiguration);

        buttonBox = new QDialogButtonBox(DialogSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSettings)
    {
        DialogSettings->setWindowTitle(QApplication::translate("DialogSettings", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("DialogSettings", "PlugIn", nullptr));
        pushButtonInstallPlugin->setText(QApplication::translate("DialogSettings", "Install", nullptr));
        pushButtonVerifyPlugin->setText(QApplication::translate("DialogSettings", "Verify", nullptr));
        groupBoxWifiConfiguration->setTitle(QApplication::translate("DialogSettings", "Wifi Configuration", nullptr));
        radioButtonAP->setText(QApplication::translate("DialogSettings", "Access Point", nullptr));
        radioButtonLocalWifi->setText(QApplication::translate("DialogSettings", "Local WiFi", nullptr));
        label->setText(QApplication::translate("DialogSettings", "SSID:", nullptr));
        label_2->setText(QApplication::translate("DialogSettings", "Password:", nullptr));
        pushButtonStoreWiFiConfig->setText(QApplication::translate("DialogSettings", "Store", nullptr));
        label_3->setText(QApplication::translate("DialogSettings", "IP Address:", nullptr));
        pushButtonPing->setText(QApplication::translate("DialogSettings", "Ping", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSettings: public Ui_DialogSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSETTINGS_H
