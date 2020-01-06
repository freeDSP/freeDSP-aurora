#ifndef WIZARDCONNECT_H
#define WIZARDCONNECT_H

#include <QWizard>
#include <QtWidgets>

#include "freeDSP-Aurora.hpp"

//==============================================================================
/*!
 */
class QWaitingBox : public QMessageBox
{
  Q_OBJECT

public:
  QWaitingBox( QMessageBox::Icon icon, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint)
  : QMessageBox( icon, title, text, buttons, parent, f )
  { 
    connect( &timerWait, SIGNAL(timeout()), this, SLOT(rotateIcon()) );
    timerWait.start( 100 );
    currentWaitRotation = 0;

    QImage srcImg = QImage(":/reload_128x128.png").scaled(64,64);
    srcImg = srcImg.copy( 0, 0, 70, 70 );
    setIconPixmap( QPixmap::fromImage( srcImg ) );
  }

private slots:
  void rotateIcon( void )
  {
    currentWaitRotation -= 10;

    QImage srcImg(":/reload_128x128.png");
    srcImg = srcImg.scaled( 64, 64 );
    QPoint center = srcImg.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate( currentWaitRotation );
    QImage dstImg = srcImg.transformed(matrix, Qt::SmoothTransformation);
    dstImg = dstImg.copy( (dstImg.width()-64)/2, (dstImg.height()-64)/2, 70, 70 );
    setIconPixmap( QPixmap::fromImage(dstImg) );
  }

private:
  QTimer timerWait;
  int currentWaitRotation;

};

//==============================================================================
/*!
 */
class WizardConnect : public QWizard
{
  Q_OBJECT

public:
  enum
  { 
    Page_Connect,
    Page_SSID,
    PAGE_SUCCESS,
    PAGE_CONNECTION
  };

  WizardConnect( CFreeDspAurora* ptrdsp, QWidget* parent = nullptr );

private slots:

private:
  CFreeDspAurora* dsp = nullptr;

};

//==============================================================================
/*!
 */
class PageConnect : public QWizardPage
{
  Q_OBJECT

public:
  PageConnect( QWidget* = nullptr )
  {
    setTitle( tr("Please connect your computer to the access point AP-freeDSP-aurora.") );
    //setStyleSheet("background-color:#111111");
  }

  int nextId( void ) const override
  {
    return WizardConnect::Page_SSID;
  }

private:

};

//==============================================================================
/*!
 */
class PageSSID : public QWizardPage
{
  Q_OBJECT

public:
  PageSSID( QWidget* = nullptr )
  {
    setTitle( tr("Please type in the SSID and the password for your WiFi network.") );
    //setStyleSheet("background-color:#111111");

    QLabel* label = new QLabel( tr("Leave this empty, if you don't want to connect your Aurora to your WiFi network.") );
    label->setWordWrap( true );

    lineEditSSID = new QLineEdit;
    lineEditPassword = new QLineEdit;
    lineEditPassword->setEchoMode( QLineEdit::Password );

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow( tr("SSID:"), lineEditSSID );
    formLayout->addRow( tr("Password:"), lineEditPassword );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing( 20 );
    layout->addWidget( label );
    layout->addLayout( formLayout );

    setLayout( layout );

    registerField( "ssid", lineEditSSID );
    registerField( "password", lineEditPassword );

  }

  int nextId( void ) const override
  {
    return WizardConnect::PAGE_SUCCESS;
  }

private:
  QLineEdit* lineEditSSID;
  QLineEdit* lineEditPassword;

};

//==============================================================================
/*!
 */
class PageSuccess : public QWizardPage
{
  Q_OBJECT

public:
  PageSuccess( CFreeDspAurora* ptrdsp, QWidget* = nullptr )
  {
    dsp = ptrdsp;

    setTitle( tr("Please type in the SSID and the password for your WiFi network.") );
    //setStyleSheet("background-color:#111111");
  }

  void initializePage( void ) override
  {
    setEnabled( false );
    QWaitingBox* msgBox = new QWaitingBox( QMessageBox::Information, tr("Waiting"), tr("Aurora is trying to connect to your WiFi network..."), QMessageBox::Cancel, this );
    msgBox->setStandardButtons( nullptr );
    msgBox->open();
    dsp->setConnectionTypeWifi( CFreeDspAurora::ACCESS_POINT );
    bool connected = dsp->storeSettingsWifi( field("ssid").toString(), field("password").toString(), 60000 ); 
    setEnabled( true );
    msgBox->accept();
    if( connected )
      setTitle( "Your Aurora is now connected to your WiFi network!" );
    else
      setTitle( "Aurora cannot connect to your WiFi network." );
  }

  int nextId( void ) const override
  {
    return WizardConnect::PAGE_CONNECTION;
  }

private:
  CFreeDspAurora* dsp;
  //QLabel* labelResult;

};

//==============================================================================
/*!
 */
class PageConnection : public QWizardPage
{
  Q_OBJECT

public:
  PageConnection( CFreeDspAurora* ptrdsp, QWidget* = nullptr )
  {
    dsp = ptrdsp;

    setTitle( tr("How do you want to connect to your Aurora?") );

    QComboBox* comboBoxConnection = new QComboBox( this );

    registerField( "connection", comboBoxConnection );

    comboBoxConnection->addItem( "Access Point", CFreeDspAurora::ACCESS_POINT );
    comboBoxConnection->addItem( "Local WiFi Network", CFreeDspAurora::LOCAL_WIFI );
    comboBoxConnection->addItem( "Offline Mode", CFreeDspAurora::OFFLINE );
    comboBoxConnection->setCurrentIndex( 0 );
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing( 20 );
    layout->addWidget( comboBoxConnection );
    layout->addWidget( new QLabel( tr("You can change your selection at any time in the settings dialog.") ) );
    setLayout( layout );
  }

  void initializePage( void ) override
  {

  }

  int nextId( void ) const override
  {
    return -1;
  }

private:
  CFreeDspAurora* dsp;

};

#endif
