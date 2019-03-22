#ifndef DIALOGSETTINGS_HPP
#define DIALOGSETTINGS_HPP

#include <QDialog>

#include "freeDSP-Aurora.hpp"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSettings( CFreeDspAurora* ptrdsp, QWidget* parent = nullptr );
  ~DialogSettings();

  QString getPortName( void );

  void setPortName( const QString portname );

private slots:
  void on_pushButtonInstallPlugin_clicked();

private:
  Ui::DialogSettings* ui;
  CFreeDspAurora* dsp = nullptr;
};

#endif // DIALOGSETTINGS_HPP
