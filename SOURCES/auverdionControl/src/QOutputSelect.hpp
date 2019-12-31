#ifndef QOUTPUTSELECT_HPP
#define QOUTPUTSELECT_HPP

#include <QWidget>
#include <QListView>

#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QOutputSelect;
}

class QOutputSelect : public QDspBlock
{
  Q_OBJECT

  enum
  {
    kOutput = 0,
    kNumParams
  };

public:
  explicit QOutputSelect( uint32_t selection, uint16_t outputaddr, CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QOutputSelect();

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

  bool eventFilter( QObject* object, QEvent* event );

protected:
  void updateCoeffs( void ) { }

private slots:
  
protected slots:
  //============================================================================
  /*! 
   *
   */
  virtual void updateDsp( void )
  {

  }

private:
  Ui::QOutputSelect *ui;

  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;
  QString fileName;

  Vektorraum::tvector<Vektorraum::tfloat> freq;
  Vektorraum::tvector<Vektorraum::tcomplex> FR;
  Vektorraum::tfloat refSpl;
};

#endif // QOUTPUTSELECT_HPP
