/********************************************************************************
** Form generated from reading UI file 'QHighShelv.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHIGHSHELV_H
#define UI_QHIGHSHELV_H

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

class Ui_QHighShelv
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

    void setupUi(QWidget *QHighShelv)
    {
        if (QHighShelv->objectName().isEmpty())
            QHighShelv->setObjectName(QString::fromUtf8("QHighShelv"));
        QHighShelv->resize(400, 300);
        QHighShelv->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QHighShelv);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QHighShelv);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #005EF0;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        doubleSpinBoxGain = new QDoubleSpinBox(QHighShelv);
        doubleSpinBoxGain->setObjectName(QString::fromUtf8("doubleSpinBoxGain"));
        doubleSpinBoxGain->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxGain->setAlignment(Qt::AlignCenter);
        doubleSpinBoxGain->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxGain->setMinimum(-10.000000000000000);
        doubleSpinBoxGain->setMaximum(10.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxGain);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        doubleSpinBoxFc = new QDoubleSpinBox(QHighShelv);
        doubleSpinBoxFc->setObjectName(QString::fromUtf8("doubleSpinBoxFc"));
        doubleSpinBoxFc->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFc->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFc->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFc->setMinimum(1.000000000000000);
        doubleSpinBoxFc->setMaximum(20000.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxFc);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        doubleSpinBoxS = new QDoubleSpinBox(QHighShelv);
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

        label = new QLabel(QHighShelv);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("High Shelv"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QHighShelv);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);


        retranslateUi(QHighShelv);

        QMetaObject::connectSlotsByName(QHighShelv);
    } // setupUi

    void retranslateUi(QWidget *QHighShelv)
    {
        QHighShelv->setWindowTitle(QApplication::translate("QHighShelv", "Form", nullptr));
        doubleSpinBoxGain->setSuffix(QApplication::translate("QHighShelv", " dB", nullptr));
        doubleSpinBoxFc->setSuffix(QApplication::translate("QHighShelv", " Hz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QHighShelv: public Ui_QHighShelv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHIGHSHELV_H
