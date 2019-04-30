#ifndef QDSPBLOCK_HPP
#define QDSPBLOCK_HPP

#include <QWidget>
#include <QString>
#include <cstdint>

#include "typedefs.h"
#include "tvector.h"

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

  virtual void getUserParams( QByteArray* userParams ) = 0;

  virtual void setUserParams( QByteArray& userParams, int& idx ) = 0;

  virtual void sendDspParameter( void ) = 0;

  virtual uint32_t getNumBytes( void ) = 0;

  //virtual void writeDspParameter( void ) = 0;

  virtual QByteArray getDspParams( void ) = 0;

protected:
  void paintEvent(QPaintEvent *);

signals:
  void valueChanged( void );

protected:
  Vektorraum::tvector<Vektorraum::tcomplex> H;
  Vektorraum::tfloat fs;
  bool bypass = false;
  QString name;
  tdspblocktype type;

private:
  Ui::QDspBlock *ui;

};

#endif // QDSPBLOCK_HPP
