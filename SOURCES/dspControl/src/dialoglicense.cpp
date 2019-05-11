
/****************************************************************************
**
** Copyright (C) 2015 Johannus Orgelbouw - All Rights Reserved
** Contact: http://www.johannus.com/
**
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
**
****************************************************************************/

#include "dialoglicense.hpp"
#include "ui_dialoglicense.h"

#include <QFile>

DialogLicense::DialogLicense(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogLicense)
{
  ui->setupUi(this);

  QFile f(":/LICENSE.txt");
  f.open( QIODevice::ReadOnly );
  QString s( f.readAll() );
  ui->textBrowser->insertPlainText( s );
  f.close();

  ui->textBrowser->moveCursor( QTextCursor::Start );
}

DialogLicense::~DialogLicense()
{
  delete ui;
}
