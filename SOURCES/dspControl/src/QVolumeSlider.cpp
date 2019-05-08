#include <QApplication>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QtGui>
#include <QString>

#include "QVolumeSlider.hpp"

class QPaintEvent;
class QWidget;

QVolumeSlider::QVolumeSlider( QWidget* parent ) : QWidget( parent )
{
  backgroundColor = QApplication::palette().color( QPalette::Background );
  textColor       = QApplication::palette().color( QPalette::Text );
  sliderColor     = QApplication::palette().color( QPalette::Text );

  QFont fontLabel;
  fontLabel.setPointSize( 10 );
  QFontMetrics fontMetrics( fontLabel );
  fontHeight = fontMetrics.height();
}

void QVolumeSlider::paintEvent( QPaintEvent* event )
{
  QStyleOption opt;
  opt.init( this );
  QPainter painter( this );
  style()->drawPrimitive( QStyle::PE_Widget, &opt, &painter, this );

  //painter.begin( this );
  painter.setRenderHint( QPainter::Antialiasing, true );

  painter.fillRect( event->rect(), QBrush( backgroundColor ) );

  QFont fontLabel = painter.font();
  fontLabel.setPointSize( 10 );

  painter.setPen( textColor );
  painter.setFont( fontLabel );

  QFontMetrics fontMetrics = painter.fontMetrics();
  fontHeight = fontMetrics.height();
  qreal sliderHeight = height()-2*fontMetrics.height();
  qreal scaleFactor = sliderHeight / (minVal - maxVal);

  for( int yy = static_cast<int>(minVal); yy <= static_cast<int>(maxVal); yy++ )
  {
    qreal ypos = static_cast<qreal>(yy)*scaleFactor + fontMetrics.height()/2;
    if( yy % 10 == 0 )
    {
      painter.drawText( QRectF( 0, ypos, width()/2.0 - 15.0, fontMetrics.height() ),
                         Qt::AlignRight, QString::number(yy) );
      painter.drawLine( QPointF( width()/2.0 - 10.0, ypos + fontMetrics.height()/2 ), QPointF( width()/2.0 + 10.0, ypos + fontMetrics.height()/2 ) );
    }
    else if( yy % 5 == 0 )
      painter.drawLine( QPointF( width()/2.0 - 10.0, ypos + fontMetrics.height()/2 ), QPointF( width()/2.0 + 10.0, ypos + fontMetrics.height()/2 ) );
    else
      painter.drawLine( QPointF( width()/2.0 - 5.0, ypos + fontMetrics.height()/2 ), QPointF( width()/2.0 + 5.0, ypos + fontMetrics.height()/2 ) );

  }

  // ------ draw the handler ------
  qreal ypos = static_cast<qreal>(sliderPos)*scaleFactor + fontMetrics.height();
  QColor lineColor = sliderColor;
  lineColor.setAlphaF( 0.5 );
  painter.setPen( QPen( lineColor, 3) );
  painter.drawLine( QPointF( 0.0, ypos ), QPointF( width(), ypos ) );
  QPointF points[3] = {
      QPointF( width(), ypos-5 ),
      QPointF( width(), ypos+5 ),
      QPointF( width()-7.0, ypos )
  };
  painter.setPen( QPen( sliderColor, 3) );
  painter.setBrush( QBrush( sliderColor) );
  painter.drawPolygon( points, 3 );

  painter.end();

}

//------------------------------------------------------------------------------
/*! \brief Reimplements the mouse press event handler.
 *
 *  \param event Pointer to event.
 */
void QVolumeSlider::mousePressEvent( QMouseEvent* event )
{
  if( event->type() == QEvent::MouseButtonPress )
  {
    qreal sliderHeight = height()-2*fontHeight;
    qreal scaleFactor = sliderHeight / (minVal - maxVal);
    #ifdef __MACOSX__
    sliderPos = (event->y()-8-fontHeight/2) / scaleFactor;
    #else
    sliderPos = (event->y()-8-fontHeight/2) / scaleFactor;
    #endif
    if( sliderPos < minVal )
      sliderPos = minVal;
    if( sliderPos > maxVal )
      sliderPos = maxVal;
    emit valueChanged( sliderPos );
    update();
  }
}

//------------------------------------------------------------------------------
/*! \brief Reimplements the mouse move event handler.
 *
 *  \param event Pointer to event.
 */
void QVolumeSlider::mouseMoveEvent( QMouseEvent* event )
{
  if( event->buttons() & Qt::LeftButton )
  {
    qreal sliderHeight = height()-2*fontHeight;
    qreal scaleFactor = sliderHeight / (minVal - maxVal);
    #ifdef __MACOSX__
    sliderPos = (event->y()-8-fontHeight/2) / scaleFactor;
    #else
    sliderPos = (event->y()-8-fontHeight/2) / scaleFactor;
    #endif
    if( sliderPos < minVal )
      sliderPos = minVal;
    if( sliderPos > maxVal )
      sliderPos = maxVal;
    emit valueChanged( sliderPos );
    update();
  }
}
