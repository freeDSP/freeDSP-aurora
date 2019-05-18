/********************************************************************************
** Form generated from reading UI file 'QDspBlock.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDSPBLOCK_H
#define UI_QDSPBLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDspBlock
{
public:

    void setupUi(QWidget *QDspBlock)
    {
        if (QDspBlock->objectName().isEmpty())
            QDspBlock->setObjectName(QString::fromUtf8("QDspBlock"));
        QDspBlock->resize(400, 300);

        retranslateUi(QDspBlock);

        QMetaObject::connectSlotsByName(QDspBlock);
    } // setupUi

    void retranslateUi(QWidget *QDspBlock)
    {
        QDspBlock->setWindowTitle(QApplication::translate("QDspBlock", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QDspBlock: public Ui_QDspBlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDSPBLOCK_H
