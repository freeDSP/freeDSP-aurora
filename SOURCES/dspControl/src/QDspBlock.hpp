#ifndef QDSPBLOCK_HPP
#define QDSPBLOCK_HPP

#include <QWidget>
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
  explicit QDspBlock(QWidget *parent = nullptr);
  ~QDspBlock();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void ) = 0;

  virtual void update( Vektorraum::tvector<Vektorraum::tfloat> f ) = 0;

  virtual void sendDspParameter( void ) = 0;

  virtual uint32_t getNumBytes( void ) = 0;

  virtual void writeDspParameter( void ) = 0;

protected:
  void paintEvent(QPaintEvent *);

signals:
  void valueChanged( void );

protected:
  Vektorraum::tvector<Vektorraum::tcomplex> H;
  Vektorraum::tfloat fs;
  bool bypass = false;

private:
  Ui::QDspBlock *ui;


};

#endif // QDSPBLOCK_HPP
