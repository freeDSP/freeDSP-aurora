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

private:
  //============================================================================
  /*!
   *
   */
  void enableGui( bool state );

private slots:
  void on_pushButtonInstallPlugin_clicked();

  void on_pushButtonVerifyPlugin_clicked();

  //void on_pushButtonDetect_clicked();

  void on_pushButtonStoreWiFiConfig_clicked();

  void on_pushButtonPing_clicked();

  void on_radioButtonAP_toggled(bool checked);

  void on_radioButtonLocalWifi_toggled(bool checked);

  void on_lineEditIpAddress_editingFinished();

  void on_comboBoxAddOnId_currentIndexChanged(int index);

private:
  Ui::DialogSettings* ui;
  CFreeDspAurora* dsp = nullptr;
};

#endif // DIALOGSETTINGS_HPP
