/********************************************************************************
** Form generated from reading UI file 'DialogReleaseNotes.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGRELEASENOTES_H
#define UI_DIALOGRELEASENOTES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogReleaseNotes
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textReleaseNotes;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxDontShowAgain;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogReleaseNotes)
    {
        if (DialogReleaseNotes->objectName().isEmpty())
            DialogReleaseNotes->setObjectName(QString::fromUtf8("DialogReleaseNotes"));
        DialogReleaseNotes->resize(400, 300);
        verticalLayout = new QVBoxLayout(DialogReleaseNotes);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textReleaseNotes = new QTextBrowser(DialogReleaseNotes);
        textReleaseNotes->setObjectName(QString::fromUtf8("textReleaseNotes"));

        verticalLayout->addWidget(textReleaseNotes);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxDontShowAgain = new QCheckBox(DialogReleaseNotes);
        checkBoxDontShowAgain->setObjectName(QString::fromUtf8("checkBoxDontShowAgain"));

        horizontalLayout->addWidget(checkBoxDontShowAgain);

        buttonBox = new QDialogButtonBox(DialogReleaseNotes);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogReleaseNotes);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogReleaseNotes, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogReleaseNotes, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogReleaseNotes);
    } // setupUi

    void retranslateUi(QDialog *DialogReleaseNotes)
    {
        DialogReleaseNotes->setWindowTitle(QCoreApplication::translate("DialogReleaseNotes", "Dialog", nullptr));
        checkBoxDontShowAgain->setText(QCoreApplication::translate("DialogReleaseNotes", "Don't show again", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogReleaseNotes: public Ui_DialogReleaseNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRELEASENOTES_H
