/********************************************************************************
** Form generated from reading UI file 'QInputSelect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QINPUTSELECT_H
#define UI_QINPUTSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QInputSelect
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBoxInput;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *QInputSelect)
    {
        if (QInputSelect->objectName().isEmpty())
            QInputSelect->setObjectName(QString::fromUtf8("QInputSelect"));
        QInputSelect->resize(400, 300);
        QInputSelect->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(QInputSelect);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        line = new QFrame(QInputSelect);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: #ffffff;"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(4);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        comboBoxInput = new QComboBox(QInputSelect);
        comboBoxInput->setObjectName(QString::fromUtf8("comboBoxInput"));
        comboBoxInput->setContextMenuPolicy(Qt::NoContextMenu);
        comboBoxInput->setCurrentText(QString::fromUtf8(""));

        verticalLayout->addWidget(comboBoxInput);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(QInputSelect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Input"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(QInputSelect);

        QMetaObject::connectSlotsByName(QInputSelect);
    } // setupUi

    void retranslateUi(QWidget *QInputSelect)
    {
        QInputSelect->setWindowTitle(QApplication::translate("QInputSelect", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QInputSelect: public Ui_QInputSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QINPUTSELECT_H
