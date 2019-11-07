#ifndef DIALOGSETTINGS_HPP
#define DIALOGSETTINGS_HPP

#include <QDialog>
#include <QVector>

#include "freeDSP-Aurora.hpp"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
  Q_OBJECT

public:
  enum AddOnId
  {
    ADDONA = 0x01,
    ADDONB = 0x02,
    ADDONC = 0x03,
    ADDOND = 0x04
  };

public:
  explicit DialogSettings( CFreeDspAurora* ptrdsp, QWidget* parent = nullptr );
  ~DialogSettings();

  //============================================================================
  /*!
   */
  unsigned int getSpdifInput( void );

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

  void on_comboBoxSpdifInput_currentIndexChanged(int index);

private:
  class CDspPluginMetaData
  {
  public:
    QString name;
    int pid;
    QString path;
  };

  Ui::DialogSettings* ui;
  CFreeDspAurora* dsp = nullptr;

  QVector<CDspPluginMetaData> dspPluginMetaData;
};

#endif // DIALOGSETTINGS_HPP
