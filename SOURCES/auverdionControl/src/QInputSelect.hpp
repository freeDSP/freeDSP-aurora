#ifndef QINPUTSELECT_HPP
#define QINPUTSELECT_HPP

#include <QWidget>
#include <QListView>

#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QInputSelect;
}

class QInputSelect : public QDspBlock
{
  Q_OBJECT

public:

  enum
  {
    kChannelADC = 0,
    kChannelUAC2,
    kChannelESP32,
    kChannelEXP,
    kChannelSPDIF,
    kSelectPort,
    kInput,
    kNumParams
  };

  enum
  {
    kPortAnalog = 0x00000000,
    kPortUSB = 0x00000001,
    kPortESP32 = 0x00000002,
    kPortEXP = 0x00000003,
    kPortSPDIF = 0x00000004
  };

public:
  explicit QInputSelect( uint32_t selection, uint16_t inputaddr, CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  explicit QInputSelect( uint32_t selection, 
                         uint16_t addrADC, uint16_t addrUAC2, uint16_t addrESP32, uint16_t addrExp, uint16_t addrSPDIF,
                         uint16_t addrPort, 
                         CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QInputSelect();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  virtual QByteArray getUserParams( void );

  virtual void setUserParams( QByteArray& userParams, int& idx );

  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  virtual QByteArray getDspParams( void );

protected:
  void updateCoeffs( void ) { }

private slots:
  void on_comboBoxInput_currentIndexChanged( int  );

protected slots:
  //============================================================================
  /*! 
   *
   */
  virtual void updateDsp( void )
  {

  }

private:
  Ui::QInputSelect *ui;

  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;
};

#endif // QINPUTSELECT_HPP
