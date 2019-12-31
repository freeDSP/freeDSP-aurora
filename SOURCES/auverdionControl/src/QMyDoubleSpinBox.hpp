#ifndef QMYDOUBLESPINBOX_HPP
#define QMYDOUBLESPINBOX_HPP

#include <QWidget>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QWheelEvent>

class QMyDoubleSpinBox : public QDoubleSpinBox
{
  Q_OBJECT

public:
  explicit QMyDoubleSpinBox( QWidget* parent = nullptr ) : QDoubleSpinBox( parent )
  {
  }

protected:
  void wheelEvent( QWheelEvent* event )
  {  
    blockSignals( true );
    QAbstractSpinBox::wheelEvent( event );
    blockSignals( false );
    emit wheelMoved();
  }

signals:
  void wheelMoved (void );

private:

};

#endif
