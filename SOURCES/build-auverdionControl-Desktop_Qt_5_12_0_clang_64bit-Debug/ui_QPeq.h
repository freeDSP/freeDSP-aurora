/********************************************************************************
** Form generated from reading UI file 'QPeq.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPEQ_H
#define UI_QPEQ_H

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

class Ui_QPeq
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer_3;
    QDoubleSpinBox *doubleSpinBoxGain;
    QSpacerItem *verticalSpacer_2;
    QDoubleSpinBox *doubleSpinBoxFc;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *doubleSpinBoxQ;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *QPeq)
    {
        if (QPeq->objectName().isEmpty())
            QPeq->setObjectName(QString::fromUtf8("QPeq"));
        QPeq->resize(400, 300);
        QPeq->setContextMenuPolicy(Qt::CustomContextMenu);
        verticalLayout = new QVBoxLayout(QPeq);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QPeq);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #A05EF0;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        doubleSpinBoxGain = new QDoubleSpinBox(QPeq);
        doubleSpinBoxGain->setObjectName(QString::fromUtf8("doubleSpinBoxGain"));
        doubleSpinBoxGain->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxGain->setAlignment(Qt::AlignCenter);
        doubleSpinBoxGain->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxGain->setMinimum(-120.000000000000000);
        doubleSpinBoxGain->setMaximum(30.000000000000000);
        doubleSpinBoxGain->setValue(0.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxGain);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        doubleSpinBoxFc = new QDoubleSpinBox(QPeq);
        doubleSpinBoxFc->setObjectName(QString::fromUtf8("doubleSpinBoxFc"));
        doubleSpinBoxFc->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFc->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFc->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFc->setMinimum(1.000000000000000);
        doubleSpinBoxFc->setMaximum(20000.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxFc);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        doubleSpinBoxQ = new QDoubleSpinBox(QPeq);
        doubleSpinBoxQ->setObjectName(QString::fromUtf8("doubleSpinBoxQ"));
        doubleSpinBoxQ->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxQ->setAlignment(Qt::AlignCenter);
        doubleSpinBoxQ->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxQ->setMinimum(0.100000000000000);
        doubleSpinBoxQ->setMaximum(50.000000000000000);
        doubleSpinBoxQ->setSingleStep(0.010000000000000);
        doubleSpinBoxQ->setValue(0.700000000000000);

        verticalLayout->addWidget(doubleSpinBoxQ);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label = new QLabel(QPeq);
        label->setObjectName(QString::fromUtf8("label"));
        label->setContextMenuPolicy(Qt::NoContextMenu);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QPeq);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setContextMenuPolicy(Qt::NoContextMenu);
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);


        retranslateUi(QPeq);

        QMetaObject::connectSlotsByName(QPeq);
    } // setupUi

    void retranslateUi(QWidget *QPeq)
    {
        QPeq->setWindowTitle(QApplication::translate("QPeq", "Form", nullptr));
        doubleSpinBoxGain->setSuffix(QApplication::translate("QPeq", " dB", nullptr));
        doubleSpinBoxFc->setSuffix(QApplication::translate("QPeq", " Hz", nullptr));
        label->setText(QApplication::translate("QPeq", "Param EQ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QPeq: public Ui_QPeq {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPEQ_H
