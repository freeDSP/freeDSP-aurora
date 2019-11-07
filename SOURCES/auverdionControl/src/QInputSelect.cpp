#include <QAbstractItemView>
#include <QDebug>
#include <QStandardItemModel>

#include "QInputSelect.hpp"
#include "ui_QInputSelect.h"

using namespace Vektorraum;

extern void enableGui( bool enable );

//==============================================================================
/*!
 *
 */
QInputSelect::QInputSelect( uint32_t selection, uint16_t inputaddr, CFreeDspAurora* ptrdsp, QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QInputSelect)
{
  addr[kInput] = inputaddr;
  dsp = ptrdsp;

  ui->setupUi(this);

  ui->comboBoxInput->blockSignals( true );
  ui->comboBoxInput->addItem( "Analog 1", 0 );
  ui->comboBoxInput->addItem( "Analog 2", 1 );
  ui->comboBoxInput->addItem( "Analog 3", 2 );
  ui->comboBoxInput->addItem( "Analog 4", 3 );
  ui->comboBoxInput->addItem( "Analog 5", 4 );
  ui->comboBoxInput->addItem( "Analog 6", 5 );
  ui->comboBoxInput->addItem( "Analog 7", 6 );
  ui->comboBoxInput->addItem( "Analog 8", 7 );
  ui->comboBoxInput->addItem( "USB 1", 8 );
  ui->comboBoxInput->addItem( "USB 2", 9 );
  ui->comboBoxInput->addItem( "USB 3", 10 );
  ui->comboBoxInput->addItem( "USB 4", 11 );
  ui->comboBoxInput->addItem( "USB 5", 12 );
  ui->comboBoxInput->addItem( "USB 6", 13 );
  ui->comboBoxInput->addItem( "USB 7", 14 );
  ui->comboBoxInput->addItem( "USB 8", 15 );
  ui->comboBoxInput->setCurrentIndex( static_cast<int32_t>(selection) );
  ui->comboBoxInput->blockSignals( false );
  //ui->comboBoxInput->setMaxVisibleItems( 16 );

  type = INPUTSELECT;
}

//==============================================================================
/*!
 *
 */
QInputSelect::QInputSelect( uint32_t selection, 
                            uint16_t addrADC, uint16_t addrUAC2, uint16_t addrESP32, uint16_t addrExp, uint16_t addrSPDIF,
                            uint16_t addrPort, 
                            CFreeDspAurora* ptrdsp, QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QInputSelect)
{
  addr[kChannelADC] = addrADC;
  addr[kChannelUAC2] = addrUAC2;
  addr[kChannelESP32] = addrESP32;
  addr[kChannelEXP] = addrExp;
  addr[kChannelSPDIF] = addrSPDIF;
  addr[kSelectPort] = addrPort;

  dsp = ptrdsp;

  ui->setupUi(this);
  
  ui->comboBoxInput->blockSignals( true );
  ui->comboBoxInput->addItem( "Analog 1",     0 );
  ui->comboBoxInput->addItem( "Analog 2",     1 );
  ui->comboBoxInput->addItem( "Analog 3",     2 );
  ui->comboBoxInput->addItem( "Analog 4",     3 );
  ui->comboBoxInput->addItem( "Analog 5",     4 );
  ui->comboBoxInput->addItem( "Analog 6",     5 );
  ui->comboBoxInput->addItem( "Analog 7",     6 );
  ui->comboBoxInput->addItem( "Analog 8",     7 );
  ui->comboBoxInput->addItem( "USB 1",        8 );
  ui->comboBoxInput->addItem( "USB 2",        9 );
  ui->comboBoxInput->addItem( "USB 3",       10 );
  ui->comboBoxInput->addItem( "USB 4",       11 );
  ui->comboBoxInput->addItem( "USB 5",       12 );
  ui->comboBoxInput->addItem( "USB 6",       13 );
  ui->comboBoxInput->addItem( "USB 7",       14 );
  ui->comboBoxInput->addItem( "USB 8",       15 );
  ui->comboBoxInput->addItem( "Expansion 1", 16 );
  ui->comboBoxInput->addItem( "Expansion 2", 17 );
  ui->comboBoxInput->addItem( "Expansion 3", 18 );
  ui->comboBoxInput->addItem( "Expansion 4", 19 );
  ui->comboBoxInput->addItem( "Expansion 5", 20 );
  ui->comboBoxInput->addItem( "Expansion 6", 21 );
  ui->comboBoxInput->addItem( "Expansion 7", 22 );
  ui->comboBoxInput->addItem( "Expansion 8", 23 );
  ui->comboBoxInput->addItem( "SPDIF 1",     24 );
  ui->comboBoxInput->addItem( "SPDIF 2",     25 );
  ui->comboBoxInput->setCurrentIndex( static_cast<int32_t>(selection) );
  ui->comboBoxInput->blockSignals( false );
  //ui->comboBoxInput->setMaxVisibleItems( 16 );
  
  if( dsp->getFirmwareVersion() == "1.0.0" )
    ui->comboBoxInput->setEnabled( false );

  type = INPUTSELECT;
}

//==============================================================================
/*!
 *
 */
QInputSelect::~QInputSelect()
{
  delete ui;
}

//==============================================================================
/*! \brief Updates the filter.
 *
 */
void QInputSelect::update( tvector<tfloat> f )
{
  H = tvector<tcomplex>( length(f) );
  for( tuint ii = 0; ii < length(f); ii++ )
    H[ii] = 1.0;
}

//==============================================================================
/*!
 *
 */
void QInputSelect::sendDspParameter( void )
{
  enableGui( false );

  qDebug()<<"QInputSelect::sendDspParameter";

  if( dsp->getFirmwareVersion() != "1.0.0" )
  {
    QByteArray content;
    content.append( dsp->muteSequence() );
    content.append( getDspParams() );
    content.append( dsp->unmuteSequence() );
    dsp->sendParameterWifi( content );
  }

  enableGui( true );
}

//==============================================================================
/*!
 *
 */
uint32_t QInputSelect::getNumBytes( void )
{
  return (2 + 4) * 2;
}

//==============================================================================
/*!
 *
 */
void QInputSelect::on_comboBoxInput_currentIndexChanged( int  )
{
  qDebug()<<"***on_comboBoxInput_currentIndexChanged";
  sendDspParameter();
  emit valueChanged();
}

//==============================================================================
/*!
 */
QByteArray QInputSelect::getUserParams( void )
{
  QByteArray content;
  if( dsp->getFirmwareVersion() != "1.0.0" )
    content.append( static_cast<char>(ui->comboBoxInput->currentIndex()) );
  return content;
}

//==============================================================================
/*!
 */
void QInputSelect::setUserParams( QByteArray& userParams, int& idx )
{
  QByteArray param;

  if( dsp->getFirmwareVersion() != "1.0.0" )
  {
    if( userParams.size() >= idx + 1 )
    {
      uint8_t inputSelect = static_cast<uint8_t>(userParams.at(idx));
      idx++;

      ui->comboBoxInput->blockSignals( true );
      int index = ui->comboBoxInput->findData( inputSelect );
      if ( index != -1 )
        ui->comboBoxInput->setCurrentIndex(index);
      ui->comboBoxInput->blockSignals( false );
    }
    else
      qDebug()<<"QInputSelect::setUserParams: Not enough data";
  }
}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray QInputSelect::getDspParams( void )
{
  qDebug()<<"QInputSelect::getDspParam";

  QByteArray content;

  //if( dsp->getFirmwareVersion() != "1.0.0" )
  //{
    //--- Analog Inputs ---
    if( ui->comboBoxInput->currentText() == QString( "Analog 1" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000000 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 2" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000001 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 3" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000002 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 4" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000003 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 5" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000004 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 6" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000005 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 7" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000006 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Analog 8" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelADC], 0x00000007 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortAnalog ) );
    }

    //--- USB Audio Inputs ---
    else if( ui->comboBoxInput->currentText() == QString( "USB 1" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000000 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 2" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000001 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 3" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000002 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 4" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000003 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 5" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000004 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 6" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000005 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 7" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000006 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "USB 8" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelUAC2], 0x00000007 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortUSB ) );
    }

    //--- Expansion Inputs ---
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 1" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000000 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 2" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000001 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 3" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000002 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 4" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000003 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 5" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000004 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 6" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000005 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 7" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000006 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }
    else if( ui->comboBoxInput->currentText() == QString( "Expansion 8" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelEXP], 0x00000007 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kPortEXP ) );
    }

    //--- SPDIF Inputs ---
    else if( ui->comboBoxInput->currentText() == QString( "SPDIF 1" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelSPDIF], 0x00000000 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kChannelSPDIF ) );
      qDebug()<<"addr[kChannelSPDIF]"<<addr[kChannelSPDIF];
    }
    else if( ui->comboBoxInput->currentText() == QString( "SPDIF 2" ) )
    {
      content.append( dsp->makeParameterForWifi( addr[kChannelSPDIF], 0x00000001 ) );
      content.append( dsp->makeParameterForWifi( addr[kSelectPort], kChannelSPDIF ) );
      qDebug()<<"addr[kChannelSPDIF]"<<addr[kChannelSPDIF];
    }
  //}
  return content;
}
