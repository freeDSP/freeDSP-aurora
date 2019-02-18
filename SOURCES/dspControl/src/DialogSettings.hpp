#ifndef DIALOGSETTINGS_HPP
#define DIALOGSETTINGS_HPP

#include <QDialog>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSettings(QWidget *parent = nullptr);
  ~DialogSettings();

  QString getPortName( void );

  void setPortName( const QString portname );

private:
  Ui::DialogSettings *ui;
};

#endif // DIALOGSETTINGS_HPP
