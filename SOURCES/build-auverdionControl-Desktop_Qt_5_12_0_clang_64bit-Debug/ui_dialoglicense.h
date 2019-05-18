/********************************************************************************
** Form generated from reading UI file 'dialoglicense.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLICENSE_H
#define UI_DIALOGLICENSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogLicense
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogLicense)
    {
        if (DialogLicense->objectName().isEmpty())
            DialogLicense->setObjectName(QString::fromUtf8("DialogLicense"));
        DialogLicense->resize(460, 324);
        verticalLayout = new QVBoxLayout(DialogLicense);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(DialogLicense);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setOpenExternalLinks(true);

        verticalLayout->addWidget(textBrowser);

        buttonBox = new QDialogButtonBox(DialogLicense);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogLicense);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogLicense, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogLicense, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogLicense);
    } // setupUi

    void retranslateUi(QDialog *DialogLicense)
    {
        DialogLicense->setWindowTitle(QApplication::translate("DialogLicense", "License", nullptr));
        textBrowser->setHtml(QApplication::translate("DialogLicense", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLicense: public Ui_DialogLicense {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLICENSE_H
