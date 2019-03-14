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

  enum
  {
    kInput = 0,
    kNumParams
  };

public:
  explicit QInputSelect( uint32_t selection, uint16_t inputaddr, CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QInputSelect();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  virtual void getUserParams( QByteArray* userParams );

  virtual void setUserParams( QByteArray& userParams, int& idx );


  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  virtual void writeDspParameter( void );

private slots:
  void on_comboBoxInput_currentIndexChanged( int  );

private:
  Ui::QInputSelect *ui;

  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;
};

#endif // QINPUTSELECT_HPP
