/********************************************************************************
** Form generated from reading UI file 'QDelay.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDELAY_H
#define UI_QDELAY_H

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

class Ui_QDelay
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *doubleSpinBoxDelay;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *QDelay)
    {
        if (QDelay->objectName().isEmpty())
            QDelay->setObjectName(QString::fromUtf8("QDelay"));
        QDelay->resize(400, 300);
        QDelay->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QDelay);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QDelay);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #73EC6F;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        doubleSpinBoxDelay = new QDoubleSpinBox(QDelay);
        doubleSpinBoxDelay->setObjectName(QString::fromUtf8("doubleSpinBoxDelay"));
        doubleSpinBoxDelay->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxDelay->setAlignment(Qt::AlignCenter);
        doubleSpinBoxDelay->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxDelay->setMaximum(100.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxDelay);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(QDelay);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Delay"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QDelay);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(QDelay);

        QMetaObject::connectSlotsByName(QDelay);
    } // setupUi

    void retranslateUi(QWidget *QDelay)
    {
        QDelay->setWindowTitle(QCoreApplication::translate("QDelay", "Form", nullptr));
        doubleSpinBoxDelay->setSuffix(QCoreApplication::translate("QDelay", " ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QDelay: public Ui_QDelay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDELAY_H
