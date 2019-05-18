/********************************************************************************
** Form generated from reading UI file 'QLowShelv.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLOWSHELV_H
#define UI_QLOWSHELV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QLowShelv
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer_4;
    QDoubleSpinBox *doubleSpinBoxGain;
    QSpacerItem *verticalSpacer_3;
    QDoubleSpinBox *doubleSpinBoxFc;
    QSpacerItem *verticalSpacer_2;
    QDoubleSpinBox *doubleSpinBoxS;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *QLowShelv)
    {
        if (QLowShelv->objectName().isEmpty())
            QLowShelv->setObjectName(QString::fromUtf8("QLowShelv"));
        QLowShelv->resize(400, 300);
        QLowShelv->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QLowShelv);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QLowShelv);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #005EF0;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        doubleSpinBoxGain = new QDoubleSpinBox(QLowShelv);
        doubleSpinBoxGain->setObjectName(QString::fromUtf8("doubleSpinBoxGain"));
        doubleSpinBoxGain->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxGain->setAlignment(Qt::AlignCenter);
        doubleSpinBoxGain->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxGain->setMinimum(-10.000000000000000);
        doubleSpinBoxGain->setMaximum(10.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxGain);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        doubleSpinBoxFc = new QDoubleSpinBox(QLowShelv);
        doubleSpinBoxFc->setObjectName(QString::fromUtf8("doubleSpinBoxFc"));
        doubleSpinBoxFc->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFc->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFc->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFc->setMinimum(1.000000000000000);
        doubleSpinBoxFc->setMaximum(20000.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxFc);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        doubleSpinBoxS = new QDoubleSpinBox(QLowShelv);
        doubleSpinBoxS->setObjectName(QString::fromUtf8("doubleSpinBoxS"));
        doubleSpinBoxS->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxS->setAlignment(Qt::AlignCenter);
        doubleSpinBoxS->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxS->setMaximum(2.000000000000000);
        doubleSpinBoxS->setSingleStep(0.010000000000000);
        doubleSpinBoxS->setValue(1.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxS);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(QLowShelv);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Low Shelv"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QLowShelv);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);


        retranslateUi(QLowShelv);

        QMetaObject::connectSlotsByName(QLowShelv);
    } // setupUi

    void retranslateUi(QWidget *QLowShelv)
    {
        QLowShelv->setWindowTitle(QApplication::translate("QLowShelv", "Form", nullptr));
        doubleSpinBoxGain->setSuffix(QApplication::translate("QLowShelv", " dB", nullptr));
        doubleSpinBoxFc->setSuffix(QApplication::translate("QLowShelv", " Hz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QLowShelv: public Ui_QLowShelv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLOWSHELV_H
