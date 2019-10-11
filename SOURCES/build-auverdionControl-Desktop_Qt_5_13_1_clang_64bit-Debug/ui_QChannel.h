/********************************************************************************
** Form generated from reading UI file 'QChannel.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCHANNEL_H
#define UI_QCHANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QFigure.h"

QT_BEGIN_NAMESPACE

class Ui_QChannel
{
public:
    QVBoxLayout *verticalLayout;
    QFigure *figVoltageMagnitude;
    QScrollArea *scrollArea;
    QWidget *widgetChannel;

    void setupUi(QWidget *QChannel)
    {
        if (QChannel->objectName().isEmpty())
            QChannel->setObjectName(QString::fromUtf8("QChannel"));
        QChannel->resize(643, 441);
        verticalLayout = new QVBoxLayout(QChannel);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        figVoltageMagnitude = new QFigure(QChannel);
        figVoltageMagnitude->setObjectName(QString::fromUtf8("figVoltageMagnitude"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(figVoltageMagnitude->sizePolicy().hasHeightForWidth());
        figVoltageMagnitude->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(figVoltageMagnitude);

        scrollArea = new QScrollArea(QChannel);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(0, 205));
        scrollArea->setWidgetResizable(true);
        widgetChannel = new QWidget();
        widgetChannel->setObjectName(QString::fromUtf8("widgetChannel"));
        widgetChannel->setGeometry(QRect(0, 0, 641, 203));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetChannel->sizePolicy().hasHeightForWidth());
        widgetChannel->setSizePolicy(sizePolicy2);
        scrollArea->setWidget(widgetChannel);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(QChannel);

        QMetaObject::connectSlotsByName(QChannel);
    } // setupUi

    void retranslateUi(QWidget *QChannel)
    {
        QChannel->setWindowTitle(QCoreApplication::translate("QChannel", "Form", nullptr));
#if QT_CONFIG(tooltip)
        figVoltageMagnitude->setToolTip(QCoreApplication::translate("QChannel", "Select displayed channels by context menu", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class QChannel: public Ui_QChannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCHANNEL_H
