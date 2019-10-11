/********************************************************************************
** Form generated from reading UI file 'QPreset.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPRESET_H
#define UI_QPRESET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QPreset
{
public:
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabChannels;
    QWidget *tab;

    void setupUi(QWidget *QPreset)
    {
        if (QPreset->objectName().isEmpty())
            QPreset->setObjectName(QString::fromUtf8("QPreset"));
        QPreset->resize(800, 600);
        horizontalLayout_2 = new QHBoxLayout(QPreset);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabChannels = new QTabWidget(QPreset);
        tabChannels->setObjectName(QString::fromUtf8("tabChannels"));
        tabChannels->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabChannels->addTab(tab, QString());

        horizontalLayout_2->addWidget(tabChannels);


        retranslateUi(QPreset);

        QMetaObject::connectSlotsByName(QPreset);
    } // setupUi

    void retranslateUi(QWidget *QPreset)
    {
        QPreset->setWindowTitle(QCoreApplication::translate("QPreset", "Form", nullptr));
        tabChannels->setTabText(tabChannels->indexOf(tab), QCoreApplication::translate("QPreset", "Tab 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QPreset: public Ui_QPreset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPRESET_H
