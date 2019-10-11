/********************************************************************************
** Form generated from reading UI file 'QFir.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFIR_H
#define UI_QFIR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QFir
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QLineEdit *lineEditResponseFile;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *pushButtonBypass;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *QFir)
    {
        if (QFir->objectName().isEmpty())
            QFir->setObjectName(QString::fromUtf8("QFir"));
        QFir->resize(400, 300);
        QFir->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QFir);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QFir);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: rgba( 225, 191, 140, 255 );"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_2 = new QLabel(QFir);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEditResponseFile = new QLineEdit(QFir);
        lineEditResponseFile->setObjectName(QString::fromUtf8("lineEditResponseFile"));
        lineEditResponseFile->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout->addWidget(lineEditResponseFile);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(QFir);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("FIR"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButtonBypass = new QPushButton(QFir);
        pushButtonBypass->setObjectName(QString::fromUtf8("pushButtonBypass"));
        pushButtonBypass->setText(QString::fromUtf8("Bypass"));
        pushButtonBypass->setCheckable(true);

        verticalLayout->addWidget(pushButtonBypass);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(QFir);

        QMetaObject::connectSlotsByName(QFir);
    } // setupUi

    void retranslateUi(QWidget *QFir)
    {
        QFir->setWindowTitle(QCoreApplication::translate("QFir", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("QFir", "IR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QFir: public Ui_QFir {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFIR_H
