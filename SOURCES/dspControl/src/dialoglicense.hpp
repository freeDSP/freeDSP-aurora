
/****************************************************************************
**
** Copyright (C) 2015 Johannus Orgelbouw - All Rights Reserved
** Contact: http://www.johannus.com/
**
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
**
****************************************************************************/

#ifndef DIALOGLICENSE_H
#define DIALOGLICENSE_H

#include <QDialog>

namespace Ui {
class DialogLicense;
}

class DialogLicense : public QDialog
{
  Q_OBJECT

public:
  explicit DialogLicense(QWidget *parent = 0);
  ~DialogLicense();

private:
  Ui::DialogLicense *ui;
};

#endif // DIALOGLICENSE_H
