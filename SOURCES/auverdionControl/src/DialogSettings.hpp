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
  explicit DialogSettings( CFreeDspAurora* ptrdsp, bool bypassVolumePoti, QWidget* parent = nullptr );
  ~DialogSettings();

  //============================================================================
  /*!
   */
  unsigned int getSpdifInput( void );

  //============================================================================
  /*!
   */
  unsigned int getConnection( void );

  //============================================================================
  /*!
   */
  bool getEnableVolumePoti( void );

private:
  //============================================================================
  /*!
   *
   */
  void enableGui( bool state );

private slots:
  void on_pushButtonInstallPlugin_clicked();

  void on_pushButtonVerifyPlugin_clicked();

  //void on_pushButtonStoreWiFiConfig_clicked();

  void on_comboBoxAddOnId_currentIndexChanged(int index);

  void on_comboBoxSpdifInput_currentIndexChanged(int index);

  void on_pushButtonConfigureWiFi_clicked();

  void on_comboBoxConnection_currentIndexChanged(const QString &arg1);

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
