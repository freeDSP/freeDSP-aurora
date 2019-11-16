#ifndef QDSPBLOCK_HPP
#define QDSPBLOCK_HPP

#include <QWidget>
#include <QString>
#include <QTimer>

#include <cstdint>

#include "typedefs.h"
#include "tvector.h"

#define DSPUPDATELATENCY (200)

namespace Ui {
class QDspBlock;
}

class QDspBlock : public QWidget
{
  Q_OBJECT

public:
  enum tdspblocktype
  {
    NONE,
    CROSSOVER,
    DELAY,
    FIR,
    GAIN,
    HIGHPASS,
    HIGHSHELV,
    INPUTSELECT,
    LOWPASS,
    LOWSHELV,
    OUTPUTSELECT,
    PEQ,
    PHASE
  };

public:
  explicit QDspBlock(QWidget *parent = nullptr);
  ~QDspBlock();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void ) = 0;

  virtual void update( Vektorraum::tvector<Vektorraum::tfloat> f ) = 0;

  tdspblocktype getType( void ) { return type; }

  virtual QByteArray getUserParams( void ) = 0;

  virtual void setUserParams( QByteArray& userParams, int& idx ) = 0;

  virtual void sendDspParameter( void ) = 0;

  virtual uint32_t getNumBytes( void ) = 0;

  virtual QByteArray getDspParams( void ) = 0;

protected:
  void paintEvent(QPaintEvent *);

  virtual void updateCoeffs( void ) = 0;

protected slots:
  virtual void updateDsp( void ) = 0;
  void delayDspUpdate( void );

signals:
  void valueChanged( void );

protected:
  Vektorraum::tvector<Vektorraum::tcomplex> H;
  Vektorraum::tfloat fs;
  bool bypass = false;
  QString name;
  tdspblocktype type;
  QTimer timerDspUpdate;

private:
  Ui::QDspBlock *ui;

};

#endif // QDSPBLOCK_HPP
