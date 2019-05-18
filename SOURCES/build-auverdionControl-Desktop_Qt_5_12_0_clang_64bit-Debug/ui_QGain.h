/********************************************************************************
** Form generated from reading UI file 'QGain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGAIN_H
#define UI_QGAIN_H

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

class Ui_QGain
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *doubleSpinBoxGain;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *QGain)
    {
        if (QGain->objectName().isEmpty())
            QGain->setObjectName(QString::fromUtf8("QGain"));
        QGain->resize(400, 300);
        QGain->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QGain);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QGain);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #FC527F;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        doubleSpinBoxGain = new QDoubleSpinBox(QGain);
        doubleSpinBoxGain->setObjectName(QString::fromUtf8("doubleSpinBoxGain"));
        doubleSpinBoxGain->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxGain->setMinimum(-80.000000000000000);
        doubleSpinBoxGain->setMaximum(0.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxGain);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(QGain);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Gain"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QGain);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(QGain);

        QMetaObject::connectSlotsByName(QGain);
    } // setupUi

    void retranslateUi(QWidget *QGain)
    {
        QGain->setWindowTitle(QApplication::translate("QGain", "Form", nullptr));
        doubleSpinBoxGain->setSuffix(QApplication::translate("QGain", " dB", nullptr));
        pushButtonBypass->setText(QApplication::translate("QGain", "Bypass", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QGain: public Ui_QGain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGAIN_H
