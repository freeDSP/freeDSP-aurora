#include <cmath>
#include <complex>
#include <vector>
#include <numeric>

#include <iostream>

#include <QStyle>
#include <QStyleOption>
#include <QMenu>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleValidator>

#include "QFigure.h"
#include "QDialogAxisProperties.h"

class QPaintEvent;
class QWidget;

using namespace std;
using namespace Vektorraum;

QColor QFigure::colorPlot[QFigure::kMaxColors] = { Qt::blue,
                                                   Qt::red,
                                                   Qt::green,
                                                   Qt::cyan,
                                                   Qt::magenta,
                                                   Qt::yellow,
                                                   Qt::darkBlue,
                                                   Qt::darkRed,
                                                   Qt::darkGreen,
                                                   Qt::darkCyan,
                                                   Qt::darkMagenta,
                                                   Qt::darkYellow
                                                 };

QFigure::QFigure( QWidget* parent ) : QWidget( parent ) //QGLWidget(parent)
{
  backgroundColor = QColor( 255, 255, 255 );
  colorLabel = QColor( 0, 0, 0 );
  colorGridCoarse = QColor( 200, 200, 200 );
  colorGridFine = QColor( 200, 200, 200 );
  colorTitle = QColor( 125, 125, 125 );
  colorPlotFrame = QColor( 200, 200, 200 );
  colorMarker = QColor( 255, 128, 0 );

  xaxismin = 1.0;
  xaxismax = 20000.0;
  xgridtick = 100.0;
  yaxismin =  60.0;
  yaxismax =  100.0;
  ygridtick = 10.0;

  bGridOn = true;
  holdonoff = false;
  frameOnOff = true;
  integrateOnOff = false;

  plottype = SEMILOGX;

  _zoomX = 1.0;
  _zoomY = 1.0;
  _panX = 0.0;
  _panY = 0.0;
  _zoomable = true;
  _sourcePos = QPointF( 0, 0 );
  _zoomFactor = 1.1;
  _scrollFactor = 10.0;

  _drawHMarker = false;
  _drawVMarker = false;
  _posVMarker = 0.0;
  _posHMarker = 0.0;
  _moveVMarker = false;
  _moveHMarker = false;

  _wasGesture = false;
  _showContextMenu = false;

  labelLegend = new QLabel( this );
  labelLegend->setMinimumWidth( 50 );
  labelLegend->setStyleSheet( "border: 1px solid rgba( 25, 25, 25, 255 ); border-radius: 0px; background-color : rgba( 255, 255, 255, 255 );" );
  labelLegend->hide();

  for( int i=(int)xaxismin; i<=(int)xaxismax; i=i+100 )
    xaxistick.push_back( static_cast<double>(i) );

  for( int i=(int)yaxismin; i<=(int)yaxismax; i=i+10 )
    yaxistick.push_back( static_cast<double>(i) );

  #if defined( __MACOSX__ ) || defined( __LINUX__ ) || defined( __WIN__ )
  grabGesture( Qt::PinchGesture );
  #endif

  #if defined( __IOS__ )
  grabGesture( Qt::PinchGesture );
  grabGesture( Qt::PanGesture );
  #endif

  setFocusPolicy( Qt::StrongFocus );
  setContextMenuPolicy( Qt::CustomContextMenu );
  setMouseTracking( true );

  //connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
  //        this, SLOT(showContextMenu(const QPoint &)));

}

QSize QFigure::sizeHint() const
{
  return QWidget::sizeHint();
}


void QFigure::paintEvent(QPaintEvent *event)
{
  QStyleOption opt;
  opt.init( this );
  QPainter painter( this );
  style()->drawPrimitive( QStyle::PE_Widget, &opt, &painter, this );

  //QPainter painter;

  if( xgridtick != 0.0 ) {
    _xplotorigin = 50;
    _yplotorigin = 15+14;
    _plotwidth = (qreal)(width()) - 60;
    _plotheight = (qreal)(height())  - 30 - 14 - 12;
  }
  else {
    _xplotorigin = 0;
    _yplotorigin = 0;
    _plotwidth = (qreal)(width());
    _plotheight = (qreal)(height());
  }

  if( _plotwidth > 4096.0 )
    _plotwidth = 4096.0;
  if( _plotheight > 4096.0 )
    _plotheight = 4096.0;


  //painter.begin( this );
  painter.fillRect( event->rect(), QBrush( backgroundColor ) );

  switch( plottype )
  {
//  case PLOT:
//    paintplot( &painter );
//    break;
  case SEMILOGX:
    paintsemilogx( &painter );
    break;
  }
  painter.end();
}

#if _MSC_VER == 1600

template<typename T> bool isfinite(T arg)
{
  return arg == arg &&
      arg != std::numeric_limits<T>::infinity() &&
      arg != -std::numeric_limits<T>::infinity();
}

#endif

void QFigure::paintsemilogx( QPainter* painter )
{
  QString str;

  qreal imageWidth = _plotwidth * _zoomX;
  qreal imageHeight = _plotheight * _zoomY;
  if( imageWidth > 4096.0 )
    imageWidth = 4096.0;
  if( imageHeight > 4096.0 )
    imageHeight = 4096.0;

  QImage imagePlot = QImage( imageWidth, imageHeight, QImage::Format_RGB32 );
  QImage imageXAxis = QImage( imageWidth, 20, QImage::Format_RGB32 );
  QImage imageYAxis = QImage( 40, imageHeight, QImage::Format_RGB32 );

  QPainter painterPlot( &imagePlot );                                           // create painters
  painterPlot.setRenderHint( QPainter::Antialiasing, true );
  QPainter painterXAxis( &imageXAxis );
  painterXAxis.setRenderHint( QPainter::Antialiasing, true );
  QPainter painterYAxis( &imageYAxis );
  painterYAxis.setRenderHint( QPainter::Antialiasing, true );
  painter->setRenderHint( QPainter::Antialiasing, true );

  QPen penPlotFrame = painterPlot.pen();                                        // frame pen
  penPlotFrame.setColor( colorPlotFrame );
  penPlotFrame.setWidth( 1 );

  QPen penGridCoarse = painterPlot.pen();                                       // coarse grid pen
  penGridCoarse.setColor( colorGridCoarse );
  penGridCoarse.setWidth( 1 );

  QPen penGitter2 = painterPlot.pen();                                          // Pen für Gitterlinien zur feinen Unterteilung
  penGitter2.setColor( colorGridFine );
  penGitter2.setWidth( 1 );

  painterPlot.setPen( penGridCoarse );
  painterPlot.fillRect( imagePlot.rect(), QBrush( backgroundColor ) );

  painter->setPen( colorLabel );                                                // Farbe Beschirftung
  QFont fontLabel = painter->font();
  #if defined( __MACOSX__ )
  fontLabel.setPointSize(10);
  #elif defined( __WIN__ )
  fontLabel.setPointSize(8);
  #elif defined( __LINUX__ )
  fontLabel.setPointSize(8);
  #elif defined( __IOS__ )
  fontLabel.setPointSize(10);
  #endif
  painter->setFont(fontLabel);

  if( bGridOn ) {
    // ------ draw vertical grid lines ------
    int decade = 10;
    if( xgridtick != 0.0 ) {
      qreal incr = xgridtick/10.0;
      for( qreal idx = xaxismin; idx <= xaxismax; idx = idx + incr ) {
        qreal xvalue = xlog( idx, imageWidth );
        if( ( ((int)idx)%decade) == 0 ) {                                       // next decade?
          if( ((int)idx) < 1000 )
            str.sprintf("%.0fHz", static_cast<float>(idx));                     // Achsenbeschriftung erzeugen
          else if( ((int)idx)==1000 )
            str.sprintf( "1kHz" );
          else
            str.sprintf("%.0fkHz", static_cast<float>(idx)/1000.f);             // Achsenbeschriftung erzeugen

          QFontMetrics fontMetrics = painter->fontMetrics();
          qreal xpos = _xplotorigin + xvalue - fontMetrics.width(str)/2 - _sourcePos.x();
          #if defined( __LINUX__ )
          qreal ypos = _yplotorigin + _plotheight + fontMetrics.height()/4;
          #else
          qreal ypos = _yplotorigin + _plotheight + fontMetrics.height()/2;
          #endif
          if( xpos > _xplotorigin - fontMetrics.width(str) )
            painter->drawText( QRectF( xpos, ypos, fontMetrics.width(str), fontMetrics.height() ),
                               Qt::AlignCenter, str );
          incr *= 10.0;
          decade *= 10;
          painterPlot.setPen( penGridCoarse );
          painterPlot.drawLine( QPointF( xvalue, 0.0 ),
                                QPointF( xvalue, imageHeight ) );               // draw vertical grid line
        }
        else {
          painterPlot.setPen(penGitter2);
          painterPlot.drawLine( QPointF( xvalue, 0.0 ),
                                QPointF( xvalue, imageHeight ) );               // draw vertical grid line
        }
      }
    }

    // ------ draw horizontal grid lines ------
    if( ygridtick != 0.0 ) {
      for( qreal ystep = yaxismin; ystep < yaxismax + ygridtick; ystep = ystep + ygridtick ) {
        qreal yvalue = ylin( ystep, imageHeight );
        bool flagLabel = false;

        for( unsigned int i=0; i<yaxistick.size(); i++ ) {
          if( ((int)(yaxistick[i] - ystep)) == 0 )
            flagLabel = true;
        }

        if( flagLabel == true ) {
          painterPlot.setPen(penGitter2);                                       // durchgezogenen Stift wählen
          painterPlot.drawLine( QPointF( 0.0, yvalue ),
                                QPointF( imageWidth, yvalue ) );                // draw horizontal grid line
          if( ygridtick > 1.f )
            str.sprintf("%.1f", ystep );                                        // Achsenbeschriftung erzeugen
          else
            str.sprintf("%.2f", ystep );                                        // Achsenbeschriftung erzeugen

          QFontMetrics fontMetrics = painter->fontMetrics();
          qreal xpos = _xplotorigin - 40;
          qreal ypos = _yplotorigin + yvalue - fontMetrics.height()/2 - _sourcePos.y();

          if( (ypos > _yplotorigin - fontMetrics.height()) && (ypos + fontMetrics.height()/2  <= _yplotorigin + _plotheight) )
            painter->drawText( QRectF( xpos, ypos, 40.0, fontMetrics.height() ),
                               Qt::AlignRight, str );
        }
        else {
          painterPlot.setPen( penGridCoarse );                                  // gestrichelten Stift wählen
          painterPlot.drawLine( QPointF( 0.0, yvalue ),
                                QPointF( imageWidth, yvalue ) );                // draw horizontal grid line
        }
      }
    }
  }

  // ------ draw grid frame ------
  painterPlot.setPen( penPlotFrame );
  painterPlot.drawLine( QPointF(        0.0,         0.0 ), QPointF(        0.0, imageHeight ) );
  painterPlot.drawLine( QPointF( imageWidth,         0.0 ), QPointF( imageWidth, imageHeight ) );
  painterPlot.drawLine( QPointF(        0.0,         0.0 ), QPointF( imageWidth,         0.0 ) );
  painterPlot.drawLine( QPointF(        0.0, imageHeight ), QPointF( imageWidth, imageHeight ) );

  // ------ Data Curve ------
  for ( unsigned int idx = 0; idx < plot2d.size(); idx++ )
  {
    QPointF* curve = new QPointF[ plot2d[idx].x.size() ];
    QPainterPath path;
    QPen pen = painterPlot.pen();
    pen.setColor( plotColor[idx] );
    pen.setWidth( (int)(plotWidth[idx]) );
    pen.setStyle( Qt::SolidLine );
    painterPlot.setPen( pen );
    unsigned int ii = 0;
    path.moveTo( xlog( (qreal)xaxismin, imageWidth ), ylin( 0.0, imageHeight ) );
    qreal x, y;
    for( unsigned int n = 0; n < plot2d[idx].x.size(); n++ )
    {
      if( isfinite(plot2d[idx].x[n]) && isfinite(plot2d[idx].y[n]) )
      {
        x = xlog( plot2d[idx].x[n], imageWidth );
        y = ylin( plot2d[idx].y[n], imageHeight );
        curve[ii] = QPointF( x, y );
        path.lineTo( xlog( plot2d[idx].x[n], imageWidth ), ylin( plot2d[idx].y[n], imageHeight ) );
        ii++;
      }
    }
    path.lineTo( x, ylin( 0.0, imageHeight ) );
    path.closeSubpath();

    painterPlot.drawPolyline( curve, ii );                                      // draw data curve

    if( plotFill[idx] ) {
      painterPlot.setPen( QColor( plotColor[idx].red(), plotColor[idx].green(), plotColor[idx].blue(), 64 ) );
      painterPlot.setBrush( QColor( plotColor[idx].red(), plotColor[idx].green(), plotColor[idx].blue(), 64 ) );
      painterPlot.drawPath( path );
    }
  }

  if( frameOnOff )
  {
    painterPlot.setRenderHint(QPainter::Antialiasing, false);
    QPen pen = painterPlot.pen();
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::lightGray);
    painterPlot.setPen(pen);
    //painterPlot.drawRect( 0, 0, pxmDiagramm.width()-1, pxmDiagramm.height()-1 );
    painterPlot.drawRect( 0, 0, imagePlot.width()-1, imagePlot.height()-1 );
  }

  // ------ Marker ------
  QString strMarkerPos;
  painterPlot.setPen( colorMarker );
  if( (_moveVMarker) || (_drawVMarker) ) {
    qreal xpos = xlog(_posVMarker, imageWidth);
    painterPlot.drawLine( QPointF(xpos, 0.0),
                          QPointF(xpos, imageHeight) );
    strMarkerPos += "x: " + QString::number( _posVMarker, 'f', 1 ) + " ";
  }
  if( (_moveHMarker) || (_drawHMarker) ) {
    qreal ypos = ylin(_posHMarker, imageHeight);
    painterPlot.drawLine( QPointF(0.0, ypos),
                          QPointF(imageWidth, ypos) );
    strMarkerPos += "y: " + QString::number( _posHMarker, 'f', 1 ) + " ";
  }
  if( !strMarkerPos.isEmpty() ) {
    QFontMetrics fontMetrics = painter->fontMetrics();
    painter->drawText( QRectF( _xplotorigin+_plotwidth-fontMetrics.width(strMarkerPos), _yplotorigin-fontMetrics.height()-2,
                       fontMetrics.width(strMarkerPos), fontMetrics.height() ),
                       Qt::AlignLeft, strMarkerPos );
  }

  painter->drawImage( QPointF( _xplotorigin, _yplotorigin ), imagePlot,
                      QRectF( _sourcePos.x(), _sourcePos.y(), _plotwidth, _plotheight ) );

  // --- Draw Title ---
  QFont fontTitle = painter->font();
  #if defined( __MACOSX__ )
  fontTitle.setPointSize(14);
  #elif defined( __WIN__ )
  fontTitle.setPointSize(12);
  #elif defined( __LINUX__ )
  fontTitle.setPointSize(12);
  #elif defined( __IOS__ )
  fontTitle.setPointSize(14);
  #endif
  painter->setFont( fontTitle );
  QPen penTitle = painter->pen();
  penTitle.setColor( colorTitle );
  painter->setPen( penTitle );
  painter->drawText( QRect(0, 3, width(), 20), Qt::AlignCenter, strTitle );

  // --- Draw Axis Labels ---
  QFont fontYLabel = painter->font();
  #if defined( __MACOSX__ )
  fontYLabel.setPointSize(12);
  #elif defined( __WIN__ )
  fontYLabel.setPointSize(10);
  #elif defined( __LINUX__ )
  fontYLabel.setPointSize(10);
  #elif defined( __IOS__ )
  fontYLabel.setPointSize(12);
  #endif
  painter->setFont( fontYLabel );
  QPen penYLabel = painter->pen();
  penYLabel.setColor( QColor(0, 0, 0, 255) );
  painter->setPen( penYLabel );
  #if defined( __LINUX__ )
  painter->drawText( QRect( _xplotorigin, _yplotorigin+_plotheight+12.0, _plotwidth, 16), Qt::AlignCenter, strXLabel );
  #else
  painter->drawText( QRect( _xplotorigin, _yplotorigin+_plotheight+12.0, _plotwidth, 16), Qt::AlignCenter, strXLabel );
  #endif
  painter->save();
  painter->translate( QPoint(width()/2, height()/2) );
  painter->rotate( -90 );
  painter->drawText( QRectF(-_plotheight/2.0, -(qreal)(width())/2.0, _plotheight, 20.0), Qt::AlignCenter, strYLabel );
  painter->restore();

  //--- Legende anzeigen
  if( !labels.isEmpty() )
  {
    QString str;
    for( int ii = 0; ii < labels.size(); ii++ )
    {
      if( ii < labels.size() - 1 )
        str += "<font color=" + plotColor[ii].name() + ">" + labels.at(ii) + "</font><br>";
      else
        str += "<font color=" + plotColor[ii].name() + ">" + labels.at(ii) + "</font>";
    }

    labelLegend->setText( str );
    labelLegend->show();
    labelLegend->move( _xplotorigin + _plotwidth - labelLegend->width() - 5, _yplotorigin + 5 );
  }





}
#if 0
/*! Zeichnet die ein x-y-Diargamm mit logarithmischer x-Achse.
 *
 * \param x x-Werte als Vektor
 * \param y y-Werte als Vektor
 */
void QFigure::semilogx( tvector<double> x, tvector<double> y )
{
  tplot2D newplot;

  if( length(x) != length(y) )
  {
    std::cout<<"semilogx: Vektorlängen stimmen nicht überein."<<std::endl;
    return;
  }

  newplot.x.resize( length(x) );
  newplot.y.resize( length(y) );
  for( unsigned int i=0; i<length(x); i++ )
  {
    newplot.x[i] = x[i];
    newplot.y[i] = std::real(y[i]);
  }

  if( holdonoff==true ) {
    plot2d.resize( plot2d.size()+1 );
    plotColor.resize( plot2d.size()+1 );
    plotWidth.resize( plot2d.size()+1 );
  }
  else {
    plot2d.resize( 1 );
    plotColor.resize( 1 );
    plotWidth.resize( 1 );
  }

  uint32_t idx = plot2d.size()-1;
  plot2d[idx] = newplot;
  plotColor[idx] = colorPlot[idx%kMaxColors];
  plotWidth[idx] = 1;

  plottype = SEMILOGX;
  this->update();
}
#endif

/*! Zeichnet die ein x-y-Diargamm mit logarithmischer x-Achse.
 *
 * \param x x-Werte als Vektor
 * \param y y-Werte als Vektor
 * \param color Farbe des Plots
 * \param width Breite des Plots.
 */
void QFigure::semilogx( tvector<double> x, tvector<double> y, QColor color, uint32_t width, bool fill )
{
  tplot2D newplot;

  if( length(x) != length(y) )
  {
    std::cout<<"semilogx: Vektorlängen stimmen nicht überein."<<std::endl;
    return;
  }

  newplot.x.resize( length(x) );
  newplot.y.resize( length(y) );
  for( unsigned int i=0; i<length(x); i++ )
  {
    newplot.x[i] = x[i];
    newplot.y[i] = y[i];
  }

  if( holdonoff==true ) {
    plot2d.resize( plot2d.size()+1 );
    plotColor.resize( plot2d.size()+1 );
    plotWidth.resize( plot2d.size()+1 );
    plotFill.resize( plot2d.size()+1 );
  }
  else {
    plot2d.resize( 1 );
    plotColor.resize( 1 );
    plotWidth.resize( 1 );
    plotFill.resize( 1 );
  }
  uint32_t idx = plot2d.size()-1;
  plot2d[plot2d.size()-1] = newplot;
  plotColor[idx] = color;
  plotWidth[idx] = width;
  plotFill[idx] = fill;

  plottype = SEMILOGX;
  this->update();
}

//------------------------------------------------------------------------------
/*! \brief Reimplementation of event handler delegates gesture events to a
 *         private function of QFigure class.
 *
 * \param event Pointer to event
 */
bool QFigure::event( QEvent* event )
{
  /*if( event->type() == QEvent::Gesture ) {
    return gestureEvent( static_cast<QGestureEvent*>(event) );
  }*/
  switch( event->type() ) {
  case QEvent::Gesture:
    return gestureEvent( static_cast<QGestureEvent*>(event) );

  #if defined( __IOS__ )
  case QEvent::TouchBegin:
  {
    QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
    if( touchPoints.size() == 1 ) {
      QTouchEvent::TouchPoint touchpoint = touchPoints.last();
      _touchBeginPos = QPoint(touchpoint.pos().x(), touchpoint.pos().y());

      if( _drawHMarker ) {
        _moveHMarker = true;
        moveMarker( _touchBeginPos );
      }

      if( _drawVMarker ) {
        _moveVMarker = true;
        moveMarker( _touchBeginPos );
      }

      return true;
    }
    else
      return QWidget::event( event );
  }
  case QEvent::TouchUpdate:
  {
    QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
    if( touchPoints.size() == 1 ) {
      QTouchEvent::TouchPoint touchpoint = touchPoints.last();
      _touchUpdatePos = QPoint(touchpoint.pos().x(), touchpoint.pos().y());

      // User wants to set a new vertical marker by sliding from left into plot with one finger
      if( _moveVMarker == false ) {
        if( (_touchBeginPos.x() < _xplotorigin) && (_touchUpdatePos.x() > _xplotorigin) ) {
          setVerticalMarker();
          moveMarker( _touchUpdatePos );
        }
      }

      // User wants to set a new horizontal marker by sliding from left into plot with one finger
      if( _moveHMarker == false ) {
        if( (_touchBeginPos.y() < _yplotorigin) && (_touchUpdatePos.y() > _yplotorigin) ) {
          setHorizontalMarker();
          moveMarker( _touchUpdatePos );
        }
      }

      // if at least one marker is present update the marker position
      if( _moveHMarker )
        moveMarker( _touchUpdatePos );
      if( _moveVMarker )
        moveMarker( _touchUpdatePos );

      return true;
    }
    else
      return QWidget::event( event );

  }
  case QEvent::TouchEnd:
  {
    QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
    if( touchPoints.size() == 1 ) {
      QTouchEvent::TouchPoint touchpoint = touchPoints.last();
      _touchEndPos = QPoint(touchpoint.pos().x(), touchpoint.pos().y());

      if( (_touchBeginPos.x() < _xplotorigin) && (_touchEndPos.x() < _xplotorigin) ) {
        changeAxisProperties();
        update();
      }
      else if( (_touchBeginPos.y() > _yplotorigin+_plotheight) && (_touchEndPos.y() > _yplotorigin+_plotheight) ) {
        changeAxisProperties();
        update();
      }
      else {
        // User has moved vertical marker outside plot on left side
        if( (_touchBeginPos.x() > _xplotorigin) && (_touchEndPos.x() < _xplotorigin) ) {
          _drawVMarker = false;
          _moveVMarker = false;
          update();
        }

        // User has moved vertical marker outside plot on top side
        if( (_touchBeginPos.y() > _yplotorigin) && (_touchEndPos.y() < _yplotorigin) ) {
          _drawHMarker = false;
          _moveHMarker = false;
          update();
        }
      }

      // stop marker movement
      stopMarkerMove();

      return true;
    }
    else
      return QWidget::event( event );

  }
  #endif
  default:
    return QWidget::event( event );
  }

}

//------------------------------------------------------------------------------
/*! \brief Examines the gestures supplied by the pointer event.
 *
 * \param Pointer to gesture event.
 */
bool QFigure::gestureEvent( QGestureEvent* event )
{
  if( QGesture* pinch = event->gesture( Qt::PinchGesture ) )
    pinchTriggered( static_cast<QPinchGesture*>(pinch) );
  #if defined( __IOS__ )
  else if( QGesture* pan = event->gesture( Qt::PanGesture ) )
    panTriggered( static_cast<QPanGesture*>(pan) );
  #endif
  return true;
}

//------------------------------------------------------------------------------
/*! \brief Handles the pinch gesture.
 *
 * \param gesture Pointer to handled pinch gesture.
 */
void QFigure::pinchTriggered( QPinchGesture* gesture )
{
  QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
  /*if (changeFlags & QPinchGesture::RotationAngleChanged) {
     qreal rotationDelta = gesture->rotationAngle() - gesture->lastRotationAngle();
     rotationAngle += rotationDelta;
     qCDebug(lcExample) << "pinchTriggered(): rotate by" <<
         rotationDelta << "->" << rotationAngle;
  }*/
  if( changeFlags & QPinchGesture::ScaleFactorChanged ) {
    _currentStepScaleFactor = gesture->scaleFactor();
  }

  if( gesture->state() == Qt::GestureStarted ) {
    if( _zoomable ) {
      _centerPos = gesture->centerPoint();
      qreal imageWidth = _plotwidth * _zoomX;
      qreal imageHeight = _plotheight * _zoomY;
      if( imageWidth > 4096.0 )
        imageWidth = 4096.0;
      if( imageHeight > 4096.0 )
        imageHeight = 4096.0;
      QPointF mousePos = _centerPos - QPointF( _xplotorigin, _yplotorigin ) + _sourcePos;
      qreal xvalue = mousePos.x() / imageWidth;
      xvalue *= std::log10(xaxismax) - std::log10(xaxismin);
      _centerX = std::pow( 10.0, xvalue + std::log10(xaxismin) );
      qreal yvalue = mousePos.y() / imageHeight;
      yvalue *= (yaxismax-yaxismin);
      _centerY = yaxismax - yvalue;
    }
  }

  if( gesture->state() == Qt::GestureUpdated ) {
    if( _zoomable ) {
      _zoomX *= _currentStepScaleFactor;
      if( _zoomX < 1.0 )
        _zoomX = 1.0;
      if( _zoomX > 4096.0/((qreal)width()) )
        _zoomX = 4096.0/((qreal)width());
      _zoomY *= _currentStepScaleFactor;
      if( _zoomY < 1.0 )
        _zoomY = 1.0;
      if( _zoomY > 4096.0/((qreal)height()) )
        _zoomY = 4096.0/((qreal)height());
      qreal imageWidth = _plotwidth * _zoomX;
      qreal imageHeight = _plotheight * _zoomY;
      if( imageWidth > 4096.0 )
        imageWidth = 4096.0;
      if( imageHeight > 4096.0 )
        imageHeight = 4096.0;
      qreal x = xlog( _centerX, imageWidth );
      qreal y = ylin( _centerY, imageHeight );
      QPointF mousePos = _centerPos - QPointF( _xplotorigin, _yplotorigin ) + _sourcePos;
      _sourcePos += QPointF( x - mousePos.x(), y - mousePos.y() );
      if( _sourcePos.x() < 0.0 )
        _sourcePos.setX( 0.0 );
      if( _sourcePos.x() + _plotwidth > imageWidth )
        _sourcePos.setX( imageWidth - _plotwidth );
      if( _sourcePos.y() < 0.0 )
        _sourcePos.setY( 0.0 );
      if( _sourcePos.y() + _plotheight > imageHeight )
        _sourcePos.setY( imageHeight - _plotheight );
    }
    _currentStepScaleFactor = 1.0;
  }

  if( gesture->state() == Qt::GestureFinished ) {
    if( _zoomable ) {
      _zoomX *= _currentStepScaleFactor;
      if( _zoomX < 1.0 )
        _zoomX = 1.0;
      if( _zoomX > 4096.0/((qreal)width()) )
        _zoomX = 4096.0/((qreal)width());
      _zoomY *= _currentStepScaleFactor;
      if( _zoomY < 1.0 )
        _zoomY = 1.0;
      if( _zoomY > 4096.0/((qreal)height()) )
        _zoomY = 4096.0/((qreal)height());
      qreal imageWidth = _plotwidth * _zoomX;
      qreal imageHeight = _plotheight * _zoomY;
      if( imageWidth > 4096.0 )
        imageWidth = 4096.0;
      if( imageHeight > 4096.0 )
        imageHeight = 4096.0;
      qreal x = xlog( _centerX, imageWidth );
      qreal y = ylin( _centerY, imageHeight );
      QPointF mousePos = _centerPos - QPointF( _xplotorigin, _yplotorigin ) + _sourcePos;
      _sourcePos += QPointF( x - mousePos.x(), y - mousePos.y() );
      if( _sourcePos.x() < 0.0 )
        _sourcePos.setX( 0.0 );
      if( _sourcePos.x() + _plotwidth > imageWidth )
        _sourcePos.setX( imageWidth - _plotwidth );
      if( _sourcePos.y() < 0.0 )
        _sourcePos.setY( 0.0 );
      if( _sourcePos.y() + _plotheight > imageHeight )
        _sourcePos.setY( imageHeight - _plotheight );
    }
    _currentStepScaleFactor = 1.0;
  }
  update();
}

//------------------------------------------------------------------------------
/*! \brief Handles the pan gesture.
 *
 * \param gesture Pointer to handled pan gesture.
 */
#if defined( __IOS__ )
void QFigure::panTriggered( QPanGesture* gesture )
#else
void QFigure::panTriggered( QPanGesture* )
#endif
{
  #if defined( __IOS__ )

  QPointF numPixels = gesture->delta();
  if( !numPixels.isNull() ) {
    _sourcePos -= numPixels;
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() < 0.0 )
      _sourcePos.setX( 0.0 );
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos.setX( imageWidth - _plotwidth );
    if( _sourcePos.y() < 0.0 )
      _sourcePos.setY( 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos.setY( imageHeight - _plotheight );
    update();
  }

  #endif
}

//------------------------------------------------------------------------------
/*! \brief Reimplements the mouse wheel event handler.
 *
 * \param event Ponter to event.
 */
void QFigure::wheelEvent( QWheelEvent* event )
{
  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;

  if( !numPixels.isNull() ) {
    _sourcePos -= numPixels;
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() < 0.0 )
      _sourcePos.setX( 0.0 );
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos.setX( imageWidth - _plotwidth );
    if( _sourcePos.y() < 0.0 )
      _sourcePos.setY( 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos.setY( imageHeight - _plotheight );
    update();
  }
  else if( !numDegrees.isNull() ) {
    qDebug()<<"Scroll with degrees not implemented";
        //QPoint numSteps = numDegrees / 15;
        //scrollWithDegrees(numSteps);
  }
  event->accept();
}

//------------------------------------------------------------------------------
/*! \brief Reimplements the key press event handler.
 *
 * \param event Pointer to event.
 */
void QFigure::keyPressEvent( QKeyEvent* event )
{
  if( event->key() == Qt::Key_PageUp ) {
    _zoomX *= _zoomFactor;
    _zoomY *= _zoomFactor;
    if( _zoomX < 1.0 )
      _zoomX = 1.0;
    if( _zoomX > 4096.0/((qreal)width()) )
      _zoomX = 4096.0/((qreal)width());
    if( _zoomY < 1.0 )
      _zoomY = 1.0;
    if( _zoomY > 4096.0/((qreal)height()) )
      _zoomY = 4096.0/((qreal)height());
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos -= QPointF( _sourcePos.x() + _plotwidth - imageWidth, 0.0 );
    if( _sourcePos.x() < 0 )
      _sourcePos -= QPointF( _sourcePos.x(), 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos -= QPointF( 0.0, _sourcePos.y() + _plotheight - imageHeight );
    if( _sourcePos.y() < 0 )
      _sourcePos -= QPointF( 0.0, _sourcePos.y() );
    event->accept();
    update();
  }
  if( event->key() == Qt::Key_PageDown ) {
    _zoomX /= _zoomFactor;
    _zoomY /= _zoomFactor;
    if( _zoomX < 1.0 )
      _zoomX = 1.0;
    if( _zoomX > 4096.0/((qreal)width()) )
      _zoomX = 4096.0/((qreal)width());
    if( _zoomY < 1.0 )
      _zoomY = 1.0;
    if( _zoomY > 4096.0/((qreal)height()) )
      _zoomY = 4096.0/((qreal)height());
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos -= QPointF( _sourcePos.x() + _plotwidth - imageWidth, 0.0 );
    if( _sourcePos.x() < 0 )
      _sourcePos -= QPointF( _sourcePos.x(), 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos -= QPointF( 0.0, _sourcePos.y() + _plotheight - imageHeight );
    if( _sourcePos.y() < 0 )
      _sourcePos -= QPointF( 0.0, _sourcePos.y() );
    event->accept();
    update();
  }
  if( (event->key() == Qt::Key_Left) && ( QGuiApplication::queryKeyboardModifiers() == Qt::ShiftModifier) ) {
    _sourcePos += QPointF( _scrollFactor, 0.0 );
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() < 0.0 )
      _sourcePos.setX( 0.0 );
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos.setX( imageWidth - _plotwidth );
    if( _sourcePos.y() < 0.0 )
      _sourcePos.setY( 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos.setY( imageHeight - _plotheight );
    update();
  }
  if( (event->key() == Qt::Key_Right) && ( QGuiApplication::queryKeyboardModifiers() == Qt::ShiftModifier) ) {
    _sourcePos -= QPointF( _scrollFactor, 0.0 );
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() < 0.0 )
      _sourcePos.setX( 0.0 );
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos.setX( imageWidth - _plotwidth );
    if( _sourcePos.y() < 0.0 )
      _sourcePos.setY( 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos.setY( imageHeight - _plotheight );
    update();
  }
  if( (event->key() == Qt::Key_Up) && ( QGuiApplication::queryKeyboardModifiers() == Qt::ShiftModifier) ) {
    _sourcePos += QPointF( 0.0, _scrollFactor );
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() < 0.0 )
      _sourcePos.setX( 0.0 );
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos.setX( imageWidth - _plotwidth );
    if( _sourcePos.y() < 0.0 )
      _sourcePos.setY( 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos.setY( imageHeight - _plotheight );
    update();
  }
  if( (event->key() == Qt::Key_Down) && ( QGuiApplication::queryKeyboardModifiers() == Qt::ShiftModifier) ) {
    _sourcePos -= QPointF( 0.0, _scrollFactor );
    qreal imageWidth = _plotwidth * _zoomX;
    qreal imageHeight = _plotheight * _zoomY;
    if( _sourcePos.x() < 0.0 )
      _sourcePos.setX( 0.0 );
    if( _sourcePos.x() + _plotwidth > imageWidth )
      _sourcePos.setX( imageWidth - _plotwidth );
    if( _sourcePos.y() < 0.0 )
      _sourcePos.setY( 0.0 );
    if( _sourcePos.y() + _plotheight > imageHeight )
      _sourcePos.setY( imageHeight - _plotheight );
    update();
  }
  QWidget::keyPressEvent(event);
}

//------------------------------------------------------------------------------
/*! \brief Opens the context menu of QFigure.
 *
 * \param pos Position where to open the context menu.
 */
/*void QFigure::showContextMenu( const QPoint &pos )
{

  QMenu contextMenu( tr("Context menu"), this );

  QAction actionAxis( tr("Axis Properties"), this );
  QAction actionSetHMarker( tr("Set Horizontal Marker"), this );
  QAction actionSetVMarker( tr("Set Vertical Marker"), this );
  QAction actionRemoveHMarker( tr("Remove Horizontal Marker"), this );
  QAction actionRemoveVMarker( tr("Remove Vertical Marker"), this );
  connect( &actionAxis, SIGNAL(triggered()), this, SLOT(changeAxisProperties()) );
  connect( &actionSetHMarker, SIGNAL(triggered()), this, SLOT(setHorizontalMarker()) );
  connect( &actionSetVMarker, SIGNAL(triggered()), this, SLOT(setVerticalMarker()) );
  connect( &actionRemoveHMarker, SIGNAL(triggered()), this, SLOT(removeHorizontalMarker()) );
  connect( &actionRemoveVMarker, SIGNAL(triggered()), this, SLOT(removeVerticalMarker()) );
  contextMenu.addAction( &actionAxis );
  contextMenu.addAction( &actionSetHMarker );
  contextMenu.addAction( &actionSetVMarker );
  contextMenu.addAction( &actionRemoveHMarker );
  contextMenu.addAction( &actionRemoveVMarker );

  _moveVMarker = false;
  _moveHMarker = false;

  contextMenu.exec( mapToGlobal(pos) );

}
*/
//------------------------------------------------------------------------------
/*! \brief Opens the dialog to change the axis properties.
 *
 */
void QFigure::changeAxisProperties( void )
{
  QDialogAxisProperties* dlg = new QDialogAxisProperties( this );
  int dialogCode = dlg->exec();
  if( dialogCode == QDialog::Accepted ) {
    axis( dlg->getXAxisMin(), dlg->getXAxisMax(), dlg->getYAxisMin(), dlg->getYAxisMax() );
    xtick( dlg->getXTick() );
    ytick( dlg->getYTick() );
  }
  update();
}

//------------------------------------------------------------------------------
/*! \brief Sets a horizontal marker.
 *
 */
void QFigure::setHorizontalMarker( void )
{
  _moveHMarker = true;
  _drawHMarker = false;
}

//------------------------------------------------------------------------------
/*! \brief Sets a vertical marker.
 *
 */
void QFigure::setVerticalMarker( void )
{
  _moveVMarker = true;
  _drawVMarker = false;
}

//------------------------------------------------------------------------------
/*! \brief Sets a horizontal marker.
 *
 */
void QFigure::removeHorizontalMarker( void )
{
  _moveHMarker = false;
  _drawHMarker = false;
}

//------------------------------------------------------------------------------
/*! \brief Sets a vertical marker.
 *
 */
void QFigure::removeVerticalMarker( void )
{
  _moveVMarker = false;
  _drawVMarker = false;
}

//------------------------------------------------------------------------------
/*! \brief Reimplements the mouse move event handler.
 *
 *  \param event Pointer to event.
 */
void QFigure::mouseMoveEvent( QMouseEvent* event )
{
  moveMarker( event->pos() );
}

//------------------------------------------------------------------------------
/*! \brief Reimplements the mouse press event handler.
 *
 *  \param event Pointer to event.
 */
void QFigure::mousePressEvent( QMouseEvent* event )
{
  if( event->button() == Qt::LeftButton )
    stopMarkerMove();
}

//------------------------------------------------------------------------------
/*! \brief Moves the markers to the new positions.
 *
 *  \param pos New position of marker.
 */
void QFigure::moveMarker( QPoint pos )
{
  if( plottype == SEMILOGX ) {
    if( (pos.x() >= _xplotorigin) &&  (pos.x() <= _xplotorigin + _plotwidth)
    && (pos.y() >= _yplotorigin) &&  (pos.y() <= _yplotorigin + _plotheight) ) {
      qreal imageWidth = _plotwidth * _zoomX;
      qreal imageHeight = _plotheight * _zoomY;
      if( imageWidth > 4096.0 )
        imageWidth = 4096.0;
      if( imageHeight > 4096.0 )
        imageHeight = 4096.0;
      QPointF mousePos = QPointF( pos ) - QPointF( _xplotorigin, _yplotorigin ) + _sourcePos;
      qreal xvalue = mousePos.x() / imageWidth;
      xvalue *= std::log10(xaxismax) - std::log10(xaxismin);
      if( _moveVMarker )
        _posVMarker = std::pow( 10.0, xvalue + std::log10(xaxismin) );
      qreal yvalue = mousePos.y() / imageHeight;
      yvalue *= (yaxismax-yaxismin);
      if( _moveHMarker )
        _posHMarker = yaxismax - yvalue;
      if( (_moveVMarker) || (_moveHMarker) )
        update();
    }
  }
}

//------------------------------------------------------------------------------
/*! \brief Stops marker movement.
 *
 */
void QFigure::stopMarkerMove( void )
{
  if( _moveVMarker == true ) {
    _moveVMarker = false;
    _drawVMarker = true;
  }
  if( _moveHMarker == true ) {
    _moveHMarker = false;
    _drawHMarker = true;
  }
}
