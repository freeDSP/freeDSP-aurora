/********************************************************************************
** Form generated from reading UI file 'QCrossover.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCROSSOVER_H
#define UI_QCROSSOVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCrossover
{
public:
    QVBoxLayout *verticalLayout_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBoxTypeLp;
    QSpacerItem *verticalSpacer_3;
    QDoubleSpinBox *doubleSpinBoxFcLp;
    QSpacerItem *verticalSpacer_7;
    QDoubleSpinBox *doubleSpinBoxGainLp;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_5;
    QComboBox *comboBoxTypeHp;
    QSpacerItem *verticalSpacer_6;
    QDoubleSpinBox *doubleSpinBoxFcHp;
    QSpacerItem *verticalSpacer_8;
    QDoubleSpinBox *doubleSpinBox;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_9;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *QCrossover)
    {
        if (QCrossover->objectName().isEmpty())
            QCrossover->setObjectName(QString::fromUtf8("QCrossover"));
        QCrossover->resize(399, 300);
        QCrossover->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout_3 = new QVBoxLayout(QCrossover);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QCrossover);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #54F4F9;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_3->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(QCrossover);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        comboBoxTypeLp = new QComboBox(QCrossover);
        comboBoxTypeLp->setObjectName(QString::fromUtf8("comboBoxTypeLp"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxTypeLp->sizePolicy().hasHeightForWidth());
        comboBoxTypeLp->setSizePolicy(sizePolicy);
        comboBoxTypeLp->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout->addWidget(comboBoxTypeLp);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        doubleSpinBoxFcLp = new QDoubleSpinBox(QCrossover);
        doubleSpinBoxFcLp->setObjectName(QString::fromUtf8("doubleSpinBoxFcLp"));
        doubleSpinBoxFcLp->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFcLp->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFcLp->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFcLp->setSuffix(QString::fromUtf8(" Hz"));
        doubleSpinBoxFcLp->setMinimum(1.000000000000000);
        doubleSpinBoxFcLp->setMaximum(20000.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxFcLp);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        doubleSpinBoxGainLp = new QDoubleSpinBox(QCrossover);
        doubleSpinBoxGainLp->setObjectName(QString::fromUtf8("doubleSpinBoxGainLp"));
        doubleSpinBoxGainLp->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxGainLp->setAlignment(Qt::AlignCenter);
        doubleSpinBoxGainLp->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxGainLp->setSuffix(QString::fromUtf8(" dB"));
        doubleSpinBoxGainLp->setMinimum(-60.000000000000000);
        doubleSpinBoxGainLp->setMaximum(0.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxGainLp);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(QCrossover);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        comboBoxTypeHp = new QComboBox(QCrossover);
        comboBoxTypeHp->setObjectName(QString::fromUtf8("comboBoxTypeHp"));
        sizePolicy.setHeightForWidth(comboBoxTypeHp->sizePolicy().hasHeightForWidth());
        comboBoxTypeHp->setSizePolicy(sizePolicy);
        comboBoxTypeHp->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout_2->addWidget(comboBoxTypeHp);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        doubleSpinBoxFcHp = new QDoubleSpinBox(QCrossover);
        doubleSpinBoxFcHp->setObjectName(QString::fromUtf8("doubleSpinBoxFcHp"));
        doubleSpinBoxFcHp->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBoxFcHp->setAlignment(Qt::AlignCenter);
        doubleSpinBoxFcHp->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxFcHp->setSuffix(QString::fromUtf8(" Hz"));
        doubleSpinBoxFcHp->setMinimum(1.000000000000000);
        doubleSpinBoxFcHp->setMaximum(20000.000000000000000);

        verticalLayout_2->addWidget(doubleSpinBoxFcHp);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);

        doubleSpinBox = new QDoubleSpinBox(QCrossover);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBox->setAlignment(Qt::AlignCenter);
        doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox->setSuffix(QString::fromUtf8(" dB"));
        doubleSpinBox->setMinimum(-60.000000000000000);
        doubleSpinBox->setMaximum(0.000000000000000);

        verticalLayout_2->addWidget(doubleSpinBox);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_9);

        label = new QLabel(QCrossover);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        pushButtonBypass = new QPushButton(QCrossover);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout_3->addWidget(pushButtonBypass);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);


        retranslateUi(QCrossover);

        QMetaObject::connectSlotsByName(QCrossover);
    } // setupUi

    void retranslateUi(QWidget *QCrossover)
    {
        QCrossover->setWindowTitle(QApplication::translate("QCrossover", "Form", nullptr));
        label_2->setText(QApplication::translate("QCrossover", "Sub", nullptr));
        label_3->setText(QApplication::translate("QCrossover", "Sat", nullptr));
        label->setText(QApplication::translate("QCrossover", "Crossover", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QCrossover: public Ui_QCrossover {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCROSSOVER_H
