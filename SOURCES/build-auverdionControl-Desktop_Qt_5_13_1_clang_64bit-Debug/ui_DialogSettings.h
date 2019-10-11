/********************************************************************************
** Form generated from reading UI file 'DialogSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSettings
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidgetSettings;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxPlugIn;
    QPushButton *pushButtonInstallPlugin;
    QPushButton *pushButtonVerifyPlugin;
    QSpacerItem *verticalSpacer;
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
    QFormLayout *formLayoutIPs;
    QLabel *label_4;
    QLabel *labelFirmwareVersion;
    QLabel *label_5;
    QComboBox *comboBoxAddOnId;
    QLabel *label_6;
    QLabel *labelAccessPointIP;
    QLabel *label_7;
    QLabel *labelLocalWiFiIP;
    QWidget *tabAddOn;
    QFormLayout *formLayout;
    QLabel *label_8;
    QComboBox *comboBoxSpdifInput;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSettings)
    {
        if (DialogSettings->objectName().isEmpty())
            DialogSettings->setObjectName(QString::fromUtf8("DialogSettings"));
        DialogSettings->resize(580, 561);
        verticalLayout = new QVBoxLayout(DialogSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 12, -1);
        tabWidgetSettings = new QTabWidget(DialogSettings);
        tabWidgetSettings->setObjectName(QString::fromUtf8("tabWidgetSettings"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, 0, -1);
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 0));
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
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxPlugIn->sizePolicy().hasHeightForWidth());
        comboBoxPlugIn->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(comboBoxPlugIn);

        pushButtonInstallPlugin = new QPushButton(groupBox);
        pushButtonInstallPlugin->setObjectName(QString::fromUtf8("pushButtonInstallPlugin"));

        horizontalLayout->addWidget(pushButtonInstallPlugin);

        pushButtonVerifyPlugin = new QPushButton(groupBox);
        pushButtonVerifyPlugin->setObjectName(QString::fromUtf8("pushButtonVerifyPlugin"));

        horizontalLayout->addWidget(pushButtonVerifyPlugin);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout_4->addWidget(groupBox);

        groupBoxWifiConfiguration = new QGroupBox(tab);
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


        verticalLayout_4->addWidget(groupBoxWifiConfiguration);

        formLayoutIPs = new QFormLayout();
        formLayoutIPs->setObjectName(QString::fromUtf8("formLayoutIPs"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayoutIPs->setWidget(1, QFormLayout::LabelRole, label_4);

        labelFirmwareVersion = new QLabel(tab);
        labelFirmwareVersion->setObjectName(QString::fromUtf8("labelFirmwareVersion"));

        formLayoutIPs->setWidget(1, QFormLayout::FieldRole, labelFirmwareVersion);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayoutIPs->setWidget(0, QFormLayout::LabelRole, label_5);

        comboBoxAddOnId = new QComboBox(tab);
        comboBoxAddOnId->setObjectName(QString::fromUtf8("comboBoxAddOnId"));

        formLayoutIPs->setWidget(0, QFormLayout::FieldRole, comboBoxAddOnId);

        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayoutIPs->setWidget(2, QFormLayout::LabelRole, label_6);

        labelAccessPointIP = new QLabel(tab);
        labelAccessPointIP->setObjectName(QString::fromUtf8("labelAccessPointIP"));

        formLayoutIPs->setWidget(2, QFormLayout::FieldRole, labelAccessPointIP);

        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayoutIPs->setWidget(3, QFormLayout::LabelRole, label_7);

        labelLocalWiFiIP = new QLabel(tab);
        labelLocalWiFiIP->setObjectName(QString::fromUtf8("labelLocalWiFiIP"));

        formLayoutIPs->setWidget(3, QFormLayout::FieldRole, labelLocalWiFiIP);


        verticalLayout_4->addLayout(formLayoutIPs);

        tabWidgetSettings->addTab(tab, QString());
        tabAddOn = new QWidget();
        tabAddOn->setObjectName(QString::fromUtf8("tabAddOn"));
        formLayout = new QFormLayout(tabAddOn);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_8 = new QLabel(tabAddOn);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        comboBoxSpdifInput = new QComboBox(tabAddOn);
        comboBoxSpdifInput->setObjectName(QString::fromUtf8("comboBoxSpdifInput"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxSpdifInput);

        tabWidgetSettings->addTab(tabAddOn, QString());

        verticalLayout->addWidget(tabWidgetSettings);

        buttonBox = new QDialogButtonBox(DialogSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSettings, SLOT(reject()));

        tabWidgetSettings->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSettings)
    {
        DialogSettings->setWindowTitle(QCoreApplication::translate("DialogSettings", "Settings", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DialogSettings", "PlugIn", nullptr));
        pushButtonInstallPlugin->setText(QCoreApplication::translate("DialogSettings", "Install", nullptr));
        pushButtonVerifyPlugin->setText(QCoreApplication::translate("DialogSettings", "Verify", nullptr));
        groupBoxWifiConfiguration->setTitle(QCoreApplication::translate("DialogSettings", "Wifi Configuration", nullptr));
        radioButtonAP->setText(QCoreApplication::translate("DialogSettings", "Access Point", nullptr));
        radioButtonLocalWifi->setText(QCoreApplication::translate("DialogSettings", "Local WiFi", nullptr));
        label->setText(QCoreApplication::translate("DialogSettings", "SSID:", nullptr));
        label_2->setText(QCoreApplication::translate("DialogSettings", "Password:", nullptr));
        pushButtonStoreWiFiConfig->setText(QCoreApplication::translate("DialogSettings", "Store", nullptr));
        label_3->setText(QCoreApplication::translate("DialogSettings", "IP Address:", nullptr));
        pushButtonPing->setText(QCoreApplication::translate("DialogSettings", "Ping", nullptr));
        label_4->setText(QCoreApplication::translate("DialogSettings", "Firmware Version:", nullptr));
        labelFirmwareVersion->setText(QString());
        label_5->setText(QCoreApplication::translate("DialogSettings", "Installed AddOn:", nullptr));
        label_6->setText(QCoreApplication::translate("DialogSettings", "Access Point IP:", nullptr));
        labelAccessPointIP->setText(QString());
        label_7->setText(QCoreApplication::translate("DialogSettings", "Local WiFi IP:", nullptr));
        labelLocalWiFiIP->setText(QString());
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tab), QCoreApplication::translate("DialogSettings", "Configuration", nullptr));
        label_8->setText(QCoreApplication::translate("DialogSettings", "S/P-DIF Input:", nullptr));
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tabAddOn), QCoreApplication::translate("DialogSettings", "AddOn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSettings: public Ui_DialogSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSETTINGS_H
