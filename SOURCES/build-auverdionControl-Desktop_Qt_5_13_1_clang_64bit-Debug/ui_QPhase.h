/********************************************************************************
** Form generated from reading UI file 'QPhase.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPHASE_H
#define UI_QPHASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QPhase
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer_3;
    QDoubleSpinBox *doubleSpinBoxFc;
    QSpacerItem *verticalSpacer_2;
    QDoubleSpinBox *doubleSpinBoxQ;
    QSpacerItem *verticalSpacer_4;
    QCheckBox *checkBoxInvert;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *QPhase)
    {
        if (QPhase->objectName().isEmpty())
            QPhase->setObjectName(QString::fromUtf8("QPhase"));
        QPhase->resize(400, 300);
        QPhase->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QPhase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QPhase);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #FD8E28;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        doubleSpinBoxFc = new QDoubleSpinBox(QPhase);
        doubleSpinBoxFc->setObjectName(QString::fromUtf8("doubleSpinBoxFc"));
        doubleSpinBoxFc->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFc->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFc->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFc->setMinimum(1.000000000000000);
        doubleSpinBoxFc->setMaximum(20000.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxFc);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        doubleSpinBoxQ = new QDoubleSpinBox(QPhase);
        doubleSpinBoxQ->setObjectName(QString::fromUtf8("doubleSpinBoxQ"));
        doubleSpinBoxQ->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxQ->setAlignment(Qt::AlignCenter);
        doubleSpinBoxQ->setButtonSymbols(QAbstractSpinBox::NoButtons);

        verticalLayout->addWidget(doubleSpinBoxQ);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        checkBoxInvert = new QCheckBox(QPhase);
        checkBoxInvert->setObjectName(QString::fromUtf8("checkBoxInvert"));
        checkBoxInvert->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout->addWidget(checkBoxInvert);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(QPhase);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Phase"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QPhase);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);


        retranslateUi(QPhase);

        QMetaObject::connectSlotsByName(QPhase);
    } // setupUi

    void retranslateUi(QWidget *QPhase)
    {
        QPhase->setWindowTitle(QCoreApplication::translate("QPhase", "Form", nullptr));
        doubleSpinBoxFc->setSuffix(QCoreApplication::translate("QPhase", " Hz", nullptr));
        checkBoxInvert->setText(QCoreApplication::translate("QPhase", "Invert", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QPhase: public Ui_QPhase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPHASE_H
