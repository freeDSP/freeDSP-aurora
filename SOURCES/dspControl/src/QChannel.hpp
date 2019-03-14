#ifndef QCHANNEL_H
#define QCHANNEL_H

#include <QWidget>
#include <QMenu>
#include <QVector>
#include <QString>

#include "QDspBlock.hpp"
#include "QFigure.h"

#include "vektorraum.h"

namespace Ui {
class QChannel;
}

class QPeq;

class QChannel : public QWidget
{
  Q_OBJECT

public:
  explicit QChannel( QString chnname = QString(""), QWidget *parent = nullptr );
  ~QChannel();

  void addDspBlock( QDspBlock* dspblock )
  {
    dspBlocks.append( dspblock );
  }

  void addPeq( QPeq* newpeq )
  {
    peqs.append( newpeq );
  }

  QDspBlock* getDspBlock( unsigned int n )
  {
    return dspBlocks.at(n);
  }

  QString getName( void )
  {
    return name;
  }

  unsigned int getNumDspBlocks( void )
  {
    return dspBlocks.size();
  }

  QVector<QPeq*> getPeqs( void )
  {
    return peqs;
  }

  Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void setName( QString chnname )
  {
    name = chnname;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f )
  {
    H = Vektorraum::tvector<Vektorraum::tcomplex>( Vektorraum::length(f) );
    for( Vektorraum::tuint ii = 0; ii < Vektorraum::length(f); ii++ )
      H[ii] = 1.0;
    for( int ii = 0; ii < dspBlocks.size(); ii++ )
    {
      dspBlocks.at(ii)->update( f );
      H = H * dspBlocks.at(ii)->getTransferFunction();
    }
  }

  uint32_t getNumBytes( void )
  {
    uint32_t ret = 0;
    for( int ii = 0; ii < dspBlocks.size(); ii++ )
      ret += dspBlocks.at(ii)->getNumBytes();
    return ret;
  }

  void writeDspParameter( void )
  {
    for( int ii = 0; ii < dspBlocks.size(); ii++ )
      dspBlocks.at(ii)->writeDspParameter();
  }

signals:
  void selectionChanged( void );

private slots:
  void on_showContextMenu( const QPoint &pos );

public:
  QWidget* widgetChannel;
  QFigure* figVoltageMagnitude;

  QMenu contextMenu;
  QVector<QAction*> actionsContextMenu;

protected:
  

private:
  Ui::QChannel *ui;
  QVector<QDspBlock*> dspBlocks;
  Vektorraum::tvector<Vektorraum::tcomplex> H;
  QVector<QPeq*> peqs;
  QString name;

};

#endif // QCHANNEL_H
