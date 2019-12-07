#ifndef QFIR_HPP
#define QFIR_HPP

#include <QWidget>
#include <QListView>

#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QFir;
}

class QFir : public QDspBlock
{
  Q_OBJECT

  enum
  {
    kImpulseResponse = 0,
    kNumParams
  };

public:
  explicit QFir( uint16_t firaddr, Vektorraum::tuint filterlength, Vektorraum::tfloat samplerate, CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QFir();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  void updateCoeffs( void );

  virtual QByteArray getUserParams( void );

  virtual void setUserParams( QByteArray& userParams, int& idx );

  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  virtual QByteArray getDspParams( void );

  bool eventFilter( QObject* object, QEvent* event );

private slots:

protected slots:
  //============================================================================
  /*! 
   *
   */
  virtual void updateDsp( void )
  {
    updateCoeffs();
    sendDspParameter();
  }

private:
  Ui::QFir *ui;

  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;

  Vektorraum::tvector<Vektorraum::tfloat> ir;
  Vektorraum::tvector<Vektorraum::tfloat> freq;
  Vektorraum::tuint taps;
  Vektorraum::tuint nfft;
};

#endif // QFIR_HPP
