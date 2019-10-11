/********************************************************************************
** Form generated from reading UI file 'QHighPass.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHIGHPASS_H
#define UI_QHIGHPASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QHighPass
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBoxType;
    QSpacerItem *verticalSpacer_3;
    QDoubleSpinBox *doubleSpinBoxFc;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *QHighPass)
    {
        if (QHighPass->objectName().isEmpty())
            QHighPass->setObjectName(QString::fromUtf8("QHighPass"));
        QHighPass->resize(400, 300);
        QHighPass->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout_2 = new QVBoxLayout(QHighPass);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QHighPass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #54F4F9;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        comboBoxType = new QComboBox(QHighPass);
        comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxType->sizePolicy().hasHeightForWidth());
        comboBoxType->setSizePolicy(sizePolicy);
        comboBoxType->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout_2->addWidget(comboBoxType);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        doubleSpinBoxFc = new QDoubleSpinBox(QHighPass);
        doubleSpinBoxFc->setObjectName(QString::fromUtf8("doubleSpinBoxFc"));
        doubleSpinBoxFc->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFc->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFc->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFc->setSuffix(QString::fromUtf8(" Hz"));
        doubleSpinBoxFc->setMinimum(1.000000000000000);
        doubleSpinBoxFc->setMaximum(20000.000000000000000);

        verticalLayout_2->addWidget(doubleSpinBoxFc);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label = new QLabel(QHighPass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        pushButtonBypass = new QPushButton(QHighPass);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout_2->addWidget(pushButtonBypass);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);


        retranslateUi(QHighPass);

        QMetaObject::connectSlotsByName(QHighPass);
    } // setupUi

    void retranslateUi(QWidget *QHighPass)
    {
        QHighPass->setWindowTitle(QCoreApplication::translate("QHighPass", "Form", nullptr));
        label->setText(QCoreApplication::translate("QHighPass", "High Pass", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QHighPass: public Ui_QHighPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHIGHPASS_H
