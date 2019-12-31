#include <QDebug>
#include <QAbstractItemView>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QProgressDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

#if defined( __MACOSX__ )
#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFBundle.h>
#endif

#include "WizardConnect.hpp"

#include "DialogSettings.hpp"
#include "ui_DialogSettings.h"

#include "LogFile.h"

#include "customdefines.hpp"

extern CLogFile myLog;

DialogSettings::DialogSettings( CFreeDspAurora* ptrdsp, bool bypassVolumePoti, QWidget* parent ) :
  QDialog(parent),
  ui(new Ui::DialogSettings)
{
  ui->setupUi(this);
  //ui->pushButtonPing->setVisible( false );
  dsp = ptrdsp;

  #if defined( __MACOSX__ )
  QDir appPath = QDir( QCoreApplication::applicationDirPath() );
  appPath.cdUp();
  appPath.cd( "Resources" );
  //qDebug()<<appPath.absolutePath() + "/dspplugins.json";
  #elif defined( __WIN__ )
  QDir appPath = QDir( QCoreApplication::applicationDirPath() );
  //qDebug()<<appPath.absolutePath() + "/dspplugins.json";

  #else
  #error Platform not supported.
  #endif

  ui->comboBoxPlugIn->blockSignals( true );
  QFile fileDspPlugins( appPath.absolutePath() + "/dspplugins.json" );
  if( fileDspPlugins.open( QIODevice::ReadOnly ) )
  {
    QJsonDocument jsonDoc( QJsonDocument::fromJson( fileDspPlugins.readAll() ) );
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonDspPlugins = jsonObj["dspplugins"].toArray();
    for( int ii = 0; ii < jsonDspPlugins.size(); ii++ )
    {
      QJsonObject plugin = jsonDspPlugins[ii].toObject();
      ui->comboBoxPlugIn->addItem( plugin["name"].toString(), plugin["pid"].toInt() );

      CDspPluginMetaData newMetaData;
      newMetaData.name = plugin["name"].toString();
      newMetaData.pid = plugin["pid"].toInt();
      #if defined( __MACOSX__ )
      newMetaData.path = appPath.absolutePath() +  "/" + plugin["path"].toString();
      #elif defined( __WIN__ )
      newMetaData.path = appPath.absolutePath() +  "/dspplugins/" + plugin["path"].toString();
      #else
      #error Platform not supported.
      #endif
      dspPluginMetaData.append( newMetaData );

      //qDebug()<<plugin["name"].toString()<<plugin["pid"].toInt()<<plugin["path"].toString();
    }
    fileDspPlugins.close();
  }
  ui->comboBoxPlugIn->addItem( "Custom", CFreeDspAurora::PLUGIN_CUSTOM );
  ui->comboBoxPlugIn->blockSignals( false );

  ui->checkBoxEnableVolumePoti->setChecked( bypassVolumePoti );

  ui->comboBoxConnection->blockSignals( true );
  ui->comboBoxConnection->addItem( "Access Point", CFreeDspAurora::ACCESS_POINT );
  ui->comboBoxConnection->addItem( "Local WiFi Network", CFreeDspAurora::LOCAL_WIFI );
  ui->comboBoxConnection->addItem( "Offline Mode", CFreeDspAurora::OFFLINE );
  int index = ui->comboBoxConnection->findData( dsp->getConnectionTypeWifi() );
  if( index != -1 )
    ui->comboBoxConnection->setCurrentIndex( index );
  ui->comboBoxConnection->blockSignals( false );

  ui->comboBoxAddOnId->blockSignals( true );
  ui->comboBoxAddOnId->addItem( "None or Custom", 0x00 );
  ui->comboBoxAddOnId->addItem( "A Woodworker's friend", CFreeDspAurora::ADDONA );
  ui->comboBoxAddOnId->addItem( "B Down with developers", CFreeDspAurora::ADDONB );
  ui->comboBoxAddOnId->addItem( "C Control over the crowd", CFreeDspAurora::ADDONC );
  ui->comboBoxAddOnId->addItem( "D Balanced life", CFreeDspAurora::ADDOND );
  index = ui->comboBoxAddOnId->findData( dsp->getAddOnId() );
  if( index != -1 )
    ui->comboBoxAddOnId->setCurrentIndex( index );
  ui->comboBoxAddOnId->blockSignals( false );

  ui->labelFirmwareVersion->setText( dsp->getFirmwareVersion() );
  ui->labelAccessPointIP->setText( dsp->getIpAddressAP() );
  ui->labelLocalWiFiIP->setText( dsp->getIpAddressLocalWifi() );

  if( dsp->getAddOnId() == CFreeDspAurora::ADDONB )
  {
    ui->comboBoxSpdifInput->clear();

    ui->comboBoxSpdifInput->blockSignals( true );
    ui->comboBoxSpdifInput->addItem( "Coax 1", 0x00 );
    ui->comboBoxSpdifInput->addItem( "Coax 2", 0x01 );
    ui->comboBoxSpdifInput->addItem( "Coax 3", 0x02 );
    ui->comboBoxSpdifInput->addItem( "Coax 4", 0x03 );
    ui->comboBoxSpdifInput->addItem( "Optical 1", 0x04 );
    ui->comboBoxSpdifInput->addItem( "Optical 2", 0x05 );
    ui->comboBoxSpdifInput->addItem( "Optical 3", 0x06 );
    ui->comboBoxSpdifInput->addItem( "Optical 4", 0x07 );
    
    dsp->requestAddOnConfig();
    QString cfg = dsp->getAddOnConfig();
    qDebug()<<"cfg "<<cfg;
    
    if( cfg == "03820104" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x00 ) );
    else if( cfg == "03820105" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x01 ) );
    else if( cfg == "03820106" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x02 ) );
    else if( cfg == "03820107" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x03 ) );
    else if( cfg == "03820100" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x04 ) );
    else if( cfg == "03820101" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x05 ) );
    else if( cfg == "03820102" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x06 ) );
    else if( cfg == "03820103" )
      ui->comboBoxSpdifInput->setCurrentIndex( ui->comboBoxSpdifInput->findData( 0x07 ) );

    ui->comboBoxSpdifInput->blockSignals( false );
  }
  else
    ui->tabWidgetSettings->removeTab( 1 );

}

DialogSettings::~DialogSettings()
{
  delete ui;
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonInstallPlugin_clicked()
{
  QMessageBox::warning( this, tr("Warning"), tr("Please mute your amplifiers before you continue."), QMessageBox::Ok ); 

  enableGui( false );

  QString pathTxBuffer;
  QString pathNumBytes;

  if( ui->comboBoxPlugIn->currentData().toInt() == CFreeDspAurora::PLUGIN_CUSTOM )
  {
    QString fileName = QFileDialog::getOpenFileName( this, tr("Select SigmaStudio project"), 
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                     tr("IR Files (*.dspproj)") );
    if( fileName.isEmpty() )
    {
      enableGui( true );
      return;
    }

    QFile fileDspProj( fileName );
    QFileInfo fileInfoDspProj( fileDspProj );
    QDir dir = fileInfoDspProj.absoluteDir();
    pathTxBuffer = dir.absolutePath() + QString( "/TxBuffer_IC_1.dat" );
    pathNumBytes = dir.absolutePath() + QString( "/NumBytes_IC_1.dat" );
    if( !QFile( pathTxBuffer ).exists() )
    {
      QMessageBox::critical( this, tr("Error"), pathTxBuffer + tr("does not exist."), QMessageBox::Ok );
      enableGui( true );
      return;
    }
    if( !QFile( pathNumBytes ).exists() )
    {
      QMessageBox::critical( this, tr("Error"), pathNumBytes + tr("does not exist."), QMessageBox::Ok );
      enableGui( true );
      return;
    }
  }
  else
  {
    for( int ii = 0; ii < dspPluginMetaData.size(); ii++ )
    {
      if( dspPluginMetaData.at(ii).pid == ui->comboBoxPlugIn->currentData().toInt() )
      {
        pathTxBuffer = dspPluginMetaData.at(ii).path + "/TxBuffer_IC_1.dat";
        pathNumBytes = dspPluginMetaData.at(ii).path + "/NumBytes_IC_1.dat";
        break;
      }
    }
  }
  
  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  QFile fileTxBuffer( pathTxBuffer );
  if( !fileTxBuffer.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open selected file";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not open ") + pathTxBuffer + tr(". Was the file deleted?"), QMessageBox::Ok );
    enableGui( true );
    return;
  }

  QTextStream in( &fileTxBuffer );
  QStringList listTxBuffer;

  while( !in.atEnd() )
  {
    QString line = in.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( str.startsWith( "0x" ) )
        listTxBuffer<<str;
    }
  }

  fileTxBuffer.close();

  //----------------------------------------------------------------------------
  //--- Read and convert the NumBytes_IC_1.dat file
  //----------------------------------------------------------------------------
  QFile fileNumBytes( pathNumBytes );
  if( !fileNumBytes.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open corresponding dat file";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not open ") + pathNumBytes + tr(". Was the file deleted?"), QMessageBox::Ok );
    enableGui( true );
    return;
  }

  QTextStream indat( &fileNumBytes );
  QStringList listNumBytes;

  while( !indat.atEnd() )
  {
    QString line = indat.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( !str.isEmpty() )
        listNumBytes<<str;
    }
  }

  fileNumBytes.close();

  //----------------------------------------------------------------------------
  //--- Send plugin id via WiFi
  //----------------------------------------------------------------------------
  dsp->storePidWifi( static_cast<uint8_t>(ui->comboBoxPlugIn->currentData().toInt()) );

  //----------------------------------------------------------------------------
  //--- Send plugin version via WiFi
  //----------------------------------------------------------------------------
  dsp->storePluginVersionWifi( VERSION_STR );

  //----------------------------------------------------------------------------
  //--- Send data to ESP32 via WiFi
  //----------------------------------------------------------------------------
  QByteArray content;
  int32_t offset = 0;
  for( int ii = 0; ii < listNumBytes.size(); ii++ )
  {
    uint32_t numbytes = listNumBytes[ii].toUInt( nullptr, 10 );

    content.append( static_cast<char>((numbytes >> 24) & 0xFF) );
    content.append( static_cast<char>((numbytes >> 16) & 0xFF) );
    content.append( static_cast<char>((numbytes >>  8) & 0xFF) );
    content.append( static_cast<char>(        numbytes & 0xFF) );

    for( uint32_t n = 0; n < numbytes; n++ )
    {
      if( offset >= listTxBuffer.size() )
      {
        qDebug()<<"TxBuffer too small";
        enableGui( true );
        return;
      }

      char data = static_cast<char>( listTxBuffer[offset].toUInt( nullptr, 16 ) & 0xff );
      content.append( data );
      offset++;
    }
  }

  ui->progressBar->setMaximum( content.size() );
  ui->progressBar->setValue( 0 );

  offset = 0;
  int npckt = 0;
  uint32_t totalTransmittedBytes = 0;
  while( offset < content.size() )
  {
    QByteArray packet;
    for( int ii = 0; ii < 64; ii++ )
    {
      if( offset < content.size() )
        packet.append( content.at(static_cast<int>(offset)) );
      else
        packet.append( static_cast<char>(0) );
      offset++;
    }
    //if( npckt == 0 )
    dsp->sendDspFirmwareWifi( packet );
    //if( !dsp->sendDspFirmwareWifi( packet ) )
    //  QMessageBox::critical( this, tr("Error"), tr("Did not receive an ACK. Please check your WiFi"), QMessageBox::Ok );
    totalTransmittedBytes += static_cast<uint32_t>(packet.size());

    if( offset < content.size() )
      ui->progressBar->setValue( offset );
    else
      ui->progressBar->setValue( content.size() );  
    npckt++;
  }

  if( dsp->finishDspFirmwareWifi( totalTransmittedBytes * 2 ) )
  {
    QMessageBox::information( this, tr("Success"), tr("You have successfully installed the new DSP-Plugin!"), QMessageBox::Ok );
    myLog()<<"Success";
    QMessageBox::information( this, tr("Success"), tr("Please reboot your Aurora DSP and reconnect auverdionControl to it and rewrite your parameters settings."), QMessageBox::Ok );
  }
  else
  {
    QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong. Please double check everythind and try again."), QMessageBox::Ok );  
    myLog()<<"Failed";
  }

  enableGui( true );
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonVerifyPlugin_clicked()
{
  enableGui( false );

  QString pathTxBuffer;
  QString pathNumBytes;

  #if defined( __MACOSX__ )
  CFURLRef appUrlRef = CFBundleCopyBundleURL( CFBundleGetMainBundle() );
  CFStringRef macPath = CFURLCopyFileSystemPath( appUrlRef, kCFURLPOSIXPathStyle );
  QString pathAppBundle = QString( CFStringGetCStringPtr( macPath, CFStringGetSystemEncoding() ) );
  CFRelease(appUrlRef);
  CFRelease(macPath);
  /*if( ui->comboBoxPlugIn->currentData().toInt() == CFreeDspAurora::PLUGIN_8CHANNELS )
  {
    pathTxBuffer = pathAppBundle + QString( "/Contents/Resources/8channels/TxBuffer_IC_1.dat");
    pathNumBytes = pathAppBundle + QString( "/Contents/Resources/8channels/NumBytes_IC_1.dat");
  }
  else
  {
    qDebug()<<"[ERROR] Unknown plugin id"<<ui->comboBoxPlugIn->currentData().toInt();
  }*/
  #elif defined( __WIN__ )
  /*QString pathAppBundle = QCoreApplication::applicationDirPath();
  if( ui->comboBoxPlugIn->currentData().toInt() == CFreeDspAurora::PLUGIN_8CHANNELS )
  {
    pathTxBuffer = pathAppBundle + QString( "/dspplugins/8channels/TxBuffer_IC_1.dat");
    pathNumBytes = pathAppBundle + QString( "/dspplugins/8channels/NumBytes_IC_1.dat");
  }
  else
  {
    qDebug()<<"[ERROR] Unknown plugin id"<<ui->comboBoxPlugIn->currentData().toInt();
  }*/
  #endif

  for( int ii = 0; ii < dspPluginMetaData.size(); ii++ )
  {
    qDebug()<<dspPluginMetaData.at(ii).pid<<ui->comboBoxPlugIn->currentData().toInt();
    if( dspPluginMetaData.at(ii).pid == ui->comboBoxPlugIn->currentData().toInt() )
    {
      pathTxBuffer = dspPluginMetaData.at(ii).path + "/TxBuffer_IC_1.dat";
      pathNumBytes = dspPluginMetaData.at(ii).path + "/NumBytes_IC_1.dat";
      break;
    }
  }

  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  QFile fileTxBuffer( pathTxBuffer );
  if( !fileTxBuffer.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open selected file";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not open ") + pathTxBuffer + tr(". Was the file deleted?"), QMessageBox::Ok );
    enableGui( true );
    return;
  }

  QTextStream in( &fileTxBuffer );
  QStringList listTxBuffer;

  while( !in.atEnd() )
  {
    QString line = in.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( str.startsWith( "0x" ) )
        listTxBuffer<<str;
    }
  }
  fileTxBuffer.close();

  //----------------------------------------------------------------------------
  //--- Read and convert the NumBytes_IC_1.dat file
  //----------------------------------------------------------------------------
  QFile fileNumBytes( pathNumBytes );
  if( !fileNumBytes.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open corresponding dat file";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not open ") + pathNumBytes + tr(". Was the file deleted?"), QMessageBox::Ok );
    enableGui( true );
    return;
  }

  QTextStream indat( &fileNumBytes );
  QStringList listNumBytes;

  while( !indat.atEnd() )
  {
    QString line = indat.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( !str.isEmpty() )
        listNumBytes<<str;
    }
  }
  fileNumBytes.close();

  QByteArray content;
  int32_t offset = 0;
  for( int ii = 0; ii < listNumBytes.size(); ii++ )
  {
    uint32_t numbytes = listNumBytes[ii].toUInt( nullptr, 10 );

    content.append( static_cast<char>((numbytes >> 24) & 0xFF) );
    content.append( static_cast<char>((numbytes >> 16) & 0xFF) );
    content.append( static_cast<char>((numbytes >>  8) & 0xFF) );
    content.append( static_cast<char>(        numbytes & 0xFF) );

    for( uint32_t n = 0; n < numbytes; n++ )
    {
      if( offset >= listTxBuffer.size() )
      {
        qDebug()<<"TxBuffer too small";
        enableGui( true );
        return;
      }

      char data = static_cast<char>( listTxBuffer[offset].toUInt( nullptr, 16 ) & 0xff );
      content.append( data );
      offset++;
    }
  }

  //----------------------------------------------------------------------------
  //--- Receive data from ESP32 via WiFi
  //----------------------------------------------------------------------------
  ui->progressBar->setMaximum( content.size()*3 );
  ui->progressBar->setValue( 0 );

  QByteArray firmware;
  dsp->requestDspFirmwareWifi( firmware, ui->progressBar );
  ui->progressBar->setValue( content.size()*2 );

  //----------------------------------------------------------------------------
  //--- Verify DSP firmware
  //----------------------------------------------------------------------------
  bool verified = true;
  for( int ii = 0; ii < content.size(); ii++ )
  {
    if( content.at(ii) != firmware.at(ii) )
    {
      verified = false;
      ui->progressBar->setValue( ii );
      //qDebug()<<ii<<":"<<QString::number( content.at(ii), 16 )<<QString::number( firmware.at(ii), 16 );
    }
  }

  ui->progressBar->setValue( content.size()*3 );

  if( !verified )
    QMessageBox::critical( this, tr("Error"), tr("DSP Plugin not verfied. You may want to reinstall the DSP plugin."), QMessageBox::Ok ); 
  else
    QMessageBox::information( this, tr("Information"), tr("Super! DSP plugin successfully verified."), QMessageBox::Ok ); 

  enableGui( true );  
}

//==============================================================================
/*!
 *
 */
/*
void DialogSettings::on_pushButtonStoreWiFiConfig_clicked()
{
  enableGui( false );
  //if( !ui->lineEditSSID->text().isEmpty() )
  //{
    // --- Send WiFi configuration to DSP ---
    //dsp->storeSettingsWifi( ui->lineEditSSID->text(), ui->lineEditPassword->text() );
    ui->labelLocalWiFiIP->setText( dsp->getIpAddressLocalWifi() );
  //}
  enableGui( true );
}
*/

//==============================================================================
/*!
 *
 */
void DialogSettings::enableGui( bool state )
{
  if( state )
  {
    ui->pushButtonInstallPlugin->setEnabled( true );
    ui->pushButtonVerifyPlugin->setEnabled( true );
    ui->buttonBox->setEnabled( true );
  }
  else
  {
    ui->pushButtonInstallPlugin->setEnabled( false );
    ui->pushButtonVerifyPlugin->setEnabled( false );
    ui->buttonBox->setEnabled( false );
  }

}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_comboBoxAddOnId_currentIndexChanged( int index )
{
  dsp->storeAddOnIdWifi( ui->comboBoxAddOnId->itemData( index ).toUInt() );

  if( ui->comboBoxAddOnId->itemData( index ).toUInt() == CFreeDspAurora::ADDONB )
  {
    ui->comboBoxSpdifInput->clear();

    ui->comboBoxSpdifInput->blockSignals( true );
    ui->comboBoxSpdifInput->addItem( "Coax 1", 0x00 );
    ui->comboBoxSpdifInput->addItem( "Coax 2", 0x01 );
    ui->comboBoxSpdifInput->addItem( "Coax 3", 0x02 );
    ui->comboBoxSpdifInput->addItem( "Coax 4", 0x03 );
    ui->comboBoxSpdifInput->addItem( "Optical 1", 0x04 );
    ui->comboBoxSpdifInput->addItem( "Optical 2", 0x05 );
    ui->comboBoxSpdifInput->addItem( "Optical 3", 0x06 );
    ui->comboBoxSpdifInput->addItem( "Optical 4", 0x07 );
    ui->comboBoxSpdifInput->blockSignals( false );

    ui->tabWidgetSettings->insertTab( 1, ui->tabAddOn, "AddOn" );
  }
  else if( ui->tabWidgetSettings->tabText( 1 ) == QString("AddOn") )
    ui->tabWidgetSettings->removeTab( 1 );
  
}

//==============================================================================
/*!
 */
void DialogSettings::on_comboBoxSpdifInput_currentIndexChanged(int index)
{
  dsp->muteDAC();
  QThread::msleep( 400 );

  if( dsp->getAddOnId() == CFreeDspAurora::ADDONB )
  {
    if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x00 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x04 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x01 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x05 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x02 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x06 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x03 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x07 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x04 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x00 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x05 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x01 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x06 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x02 );
    else if( ui->comboBoxSpdifInput->itemData( index ).toUInt() == 0x07 )
      dsp->writeI2C( int8_t(0x82), 0x01, 0x03 );
  }

  dsp->unmuteDAC();
}

//==============================================================================
/*!
 */
unsigned int DialogSettings::getSpdifInput( void )
{
  return ui->comboBoxSpdifInput->itemData( ui->comboBoxSpdifInput->currentIndex() ).toUInt();
}

//==============================================================================
/*!
 */
void DialogSettings::on_pushButtonConfigureWiFi_clicked()
{
  WizardConnect wizardConnect( dsp );
  int result = wizardConnect.exec();
  if( result != QDialog::Accepted )
    return;
  
  int index = ui->comboBoxConnection->findData( wizardConnect.field( "connection" ) );
  if( index != -1 )
    ui->comboBoxConnection->setCurrentIndex( index );

  ui->labelLocalWiFiIP->setText( dsp->getIpAddressLocalWifi() );

}

//==============================================================================
/*!
 */
unsigned int DialogSettings::getConnection( void )
{
  return ui->comboBoxConnection->itemData( ui->comboBoxConnection->currentIndex() ).toUInt();
}

//==============================================================================
/*!
 */
void DialogSettings::on_comboBoxConnection_currentIndexChanged(const QString &arg1)
{
  dsp->setConnectionTypeWifi( static_cast<int>(getConnection()) );
  
  if( arg1 == QString( "Local WiFi Network" ) )
  {
    bool ok;
    QString text = QInputDialog::getText( this, tr("Set IP address"),
                                          tr("What is the IP of your Aurora in your local network?:"), QLineEdit::Normal,
                                          dsp->getIpAddressLocalWifi(), &ok );
    if( ok && !text.isEmpty() )
    {
      dsp->setIpAddressLocalWifi( text );
      ui->labelLocalWiFiIP->setText( text );
    }
  }
}

//==============================================================================
/*!
 */
bool DialogSettings::getEnableVolumePoti( void )
{
  return ui->checkBoxEnableVolumePoti->isChecked();
}
