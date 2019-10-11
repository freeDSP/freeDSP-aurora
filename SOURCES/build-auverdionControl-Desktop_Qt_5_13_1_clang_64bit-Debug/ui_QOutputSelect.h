/********************************************************************************
** Form generated from reading UI file 'QOutputSelect.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QOUTPUTSELECT_H
#define UI_QOUTPUTSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QOutputSelect
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QLineEdit *lineEditResponseFile;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *QOutputSelect)
    {
        if (QOutputSelect->objectName().isEmpty())
            QOutputSelect->setObjectName(QString::fromUtf8("QOutputSelect"));
        QOutputSelect->resize(400, 300);
        QOutputSelect->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QOutputSelect);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QOutputSelect);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #ffffff;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_2 = new QLabel(QOutputSelect);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEditResponseFile = new QLineEdit(QOutputSelect);
        lineEditResponseFile->setObjectName(QString::fromUtf8("lineEditResponseFile"));
        lineEditResponseFile->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout->addWidget(lineEditResponseFile);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(QOutputSelect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Output"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(QOutputSelect);

        QMetaObject::connectSlotsByName(QOutputSelect);
    } // setupUi

    void retranslateUi(QWidget *QOutputSelect)
    {
        QOutputSelect->setWindowTitle(QCoreApplication::translate("QOutputSelect", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("QOutputSelect", "Driver Resp.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QOutputSelect: public Ui_QOutputSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QOUTPUTSELECT_H
