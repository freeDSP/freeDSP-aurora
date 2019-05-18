#ifndef QFIGURE_H
#define QFIGURE_H

#include <limits>

#include <QtGui>
#include <QWidget>
#include <QtMath>
#include <QDebug>
#include <QColor>
#include <QGesture>
#include <QGestureEvent>
#include <QLabel>

#include "typedefs.h"
#include "tvector.h"
#include "ccolormap.h"

class QFigure  : public QWidget
{
  Q_OBJECT
  Q_PROPERTY( QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor DESIGNABLE true )
  Q_PROPERTY( QColor colorLabel READ getColorLabel WRITE setColorLabel DESIGNABLE true )
  Q_PROPERTY( QColor colorGridCoarse READ getColorGridCoarse WRITE setColorGridCoarse DESIGNABLE true )
  Q_PROPERTY( QColor colorGridFine READ getColorGridFine WRITE setColorGridFine DESIGNABLE true )
  Q_PROPERTY( QColor colorTitle READ getColorTitle WRITE setColorTitle DESIGNABLE true )
  Q_PROPERTY( QColor colorPlotFrame READ getColorPlotFrame WRITE setColorPlotFrame DESIGNABLE true )

private:
  // Datentypen der Klasse
  typedef struct _tplot2D
  {
    std::vector<double> x;
    std::vector<double> y;
  }tplot2D;

public:
  enum tplottypes
  {
    //PLOT=0,
    SEMILOGX
    //SEMILOGY,
    //LOGLOG
  };

  static const unsigned int kMaxColors = 12;

  static QColor colorPlot[kMaxColors];

public:
  explicit QFigure(QWidget *parent = 0);
  ~QFigure() {  }; //! \todo
  QSize sizeHint() const override;

  //----------------------------------------------------------------------------
  QColor getBackgroundColor( void ) const { return backgroundColor; }

  //----------------------------------------------------------------------------
  void setBackgroundColor( const QColor color ) { backgroundColor = color; }

  //----------------------------------------------------------------------------
  QColor getColorLabel( void ) const { return colorLabel; }

  //----------------------------------------------------------------------------
  void setColorLabel( const QColor color ) { colorLabel = color; }

  //----------------------------------------------------------------------------
  QColor getColorGridCoarse( void ) const { return colorGridCoarse; }

  //----------------------------------------------------------------------------
  void setColorGridCoarse( const QColor color ) { colorGridCoarse = color; }

  //----------------------------------------------------------------------------
  QColor getColorGridFine( void ) const { return colorGridFine; }

  //----------------------------------------------------------------------------
  void setColorGridFine( const QColor color ) { colorGridFine = color; }

  //----------------------------------------------------------------------------
  QColor getColorTitle( void ) const { return colorTitle; }

  //----------------------------------------------------------------------------
  void setColorTitle( const QColor color ) { colorTitle = color; }

  //----------------------------------------------------------------------------
  QColor getColorPlotFrame( void ) const { return colorPlotFrame; }

  //----------------------------------------------------------------------------
  void setColorPlotFrame( const QColor color ) { colorPlotFrame = color; }

  //----------------------------------------------------------------------------
  QColor getColorMarker( void ) const { return colorMarker; }

  //----------------------------------------------------------------------------
  void setColorMarker( const QColor color ) { colorMarker = color; }


  void holdon( void ) { holdonoff = true; }

  void holdoff( void ) { holdonoff = false; }

  //----------------------------------------------------------------------------
  /*! \brief Setzt die Wertebereiche für die Achsen.
   *
   * \param xmin Minimaler Wert der x-Achse
   * \param xmax Maximaler Wert der x-Achse
   * \param ymin Minimaler Wert der y-Achse
   * \param ymax Maximaler Wert der y-Achse
   */
  void axis(double xmin, double xmax, double ymin, double ymax)
  {
    xaxismin = xmin;
    xaxismax = xmax;
    yaxismin = ymin;
    yaxismax = ymax;

    if( xgridtick != 0.0 ) {
      for( int i=(int)xaxismin; i<=(int)xaxismax; i=i+static_cast<int>(xgridtick+0.5) )
        xaxistick.push_back( static_cast<double>(i) );
    }

    if( ygridtick != 0.0 ) {
      for( int i=(int)yaxismin; i<=(int)yaxismax; i=i+static_cast<int>(ygridtick+0.5) )
        yaxistick.push_back( static_cast<double>(i) );
    }
  }

  //----------------------------------------------------------------------------
  /*! \brief Setzt den Raster der y-Achse.
   *
   *  \param tick Neuer Raster der y-Achse.
   */
  void xtick( double xtick )
  {
    xgridtick = xtick;
    if( xtick != 0.0 ) {
      for( double i=xaxismin; i<=xaxismax; i=i+xtick )
        xaxistick.push_back( qRound(i) );
      frameOnOff = false;
    }
    else
      frameOnOff = true;
  }

  //----------------------------------------------------------------------------
  /*! \brief Setzt den Raster der y-Achse.
   *
   *  \param tick Neuer Raster der y-Achse.
   */
  void ytick( double ytick )
  {
    ygridtick = ytick;
    if( ytick != 0.0 ) {
      for( double i=yaxismin; i<=yaxismax; i=i+ytick )
        yaxistick.push_back( qRound(i) );
      frameOnOff = false;
    }
    else
      frameOnOff = true;
  }

  //----------------------------------------------------------------------------
  /*! \brief Setzt die X-Achsenbeschriftung.
   *
   *  \param str Achsenbeschriftung.
   */
  void xlabel( QString str )
  {
    strXLabel = str;
  }

  //----------------------------------------------------------------------------
  /*! \brief Setzt die Y-Achsenbeschriftung.
   *
   *  \param str Achsenbeschriftung.
   */
  void ylabel( QString str )
  {
    strYLabel = str;
  }

  //----------------------------------------------------------------------------
  /*! \brief Dem Diagramm einen Titel zuweisen.
   *
   *  \param str Neuer Titel.
   */
  void title( QString str )
  {
    strTitle = str;
  }

  //----------------------------------------------------------------------------
  /*! \brief Wählt einen Diagrammtyp aus.
   *
   *  \param newtype Ausgewählter Diagrammtyp.
   */
  void setType( tplottypes newtype )
  {
    plottype = newtype;
  }

  //----------------------------------------------------------------------------
  /*! \brief Returns the plot type of the figure.
   *
   */
  tplottypes getPlotType( void ) { return plottype; }

  //----------------------------------------------------------------------------
  /*! \brief Turns the zoom function on or off.
   *
   */
  void setZoomable( bool zoomable ) { _zoomable = zoomable; }

  //----------------------------------------------------------------------------
  /*! Resets the current zoom and pan factors.
   *
   */
  void resetZoomPan( void  )
  {
    _zoomX = 1.0;
    _zoomY = 1.0;
    _panX = 0.0;
    _panY = 0.0;
    _sourcePos = QPointF( 0, 0 );
    update();
  }

  //----------------------------------------------------------------------------
  /*! \brief Zeichnet die ein x-y-Diargamm mit logarithmischer x-Achse.
   *
   *  \param x x-Werte als Vektor
   *  \param y y-Werte als Vektor
   */
  //void semilogx( tvector<double> x, tvector<double> y );

  //----------------------------------------------------------------------------
  /*! \brief Zeichnet die ein x-y-Diargamm mit logarithmischer x-Achse.
   *
   *  \param x x-Werte als Vektor
   *  \param y y-Werte als Vektor
   *  \param color Farbe des Plots
   *  \param width Breite des Plots.
   *  \param fill Den Bereich zwischn x-Achse und Kurve füllen?
   */
  void semilogx( Vektorraum::tvector<double> x, Vektorraum::tvector<double> y, QColor color = Qt::blue, uint32_t width = 1, bool fill = false );

  //----------------------------------------------------------------------------
  /*! \brief Clear all plots.
   *
   */
  void clear( void )
  {
    plot2d.clear();
    update();
  }

  //----------------------------------------------------------------------------
  /*! \brief Returns the minimum value of x-axis.
   *
   */
  double getXAxisMin( void ) { return xaxismin; }

  //----------------------------------------------------------------------------
  /*! \brief Returns the maximum value of x-axis.
   *
   */
  double getXAxisMax( void ) { return xaxismax; }

  //----------------------------------------------------------------------------
  /*! \brief Returns the maximum value of x-axis.
   *
   */
  double getXGridTick( void ) { return xgridtick; }

  //----------------------------------------------------------------------------
  /*! \brief Returns the minimum value of x-axis.
   *
   */
  double getYAxisMin( void ) { return yaxismin; }

  //----------------------------------------------------------------------------
  /*! \brief Returns the maximum value of x-axis.
   *
   */
  double getYAxisMax( void ) { return yaxismax; }

  //----------------------------------------------------------------------------
  /*! \brief Returns the maximum value of x-axis.
   *
   */
  double getYGridTick( void ) { return ygridtick; }

  //----------------------------------------------------------------------------
  /*! \brief TODO
   *
   */
  void grabGestures( const QList<Qt::GestureType>& gestures );

  //----------------------------------------------------------------------------
  /*! \brief TODO
   *
   */
  void legend( QStringList strlist )
  {
    labels = strlist;
  }


protected:
  void paintEvent( QPaintEvent* event ) override;
  bool event( QEvent* event ) override;
  void wheelEvent( QWheelEvent* event ) override;
  void keyPressEvent( QKeyEvent* event ) override;
  void mouseMoveEvent( QMouseEvent* event ) override;
  void mousePressEvent( QMouseEvent* event ) override;

private:
  void paintsemilogx( QPainter* painter );

  //----------------------------------------------------------------------------
  /*! \brief Examines the gestures supplied by the pointer event.
   *
   *  \param Pointer to gesture event.
   */
  bool gestureEvent( QGestureEvent* event );

  //----------------------------------------------------------------------------
  /*! \brief Handles the pinch gesture.
   *
   *  \param gesture Pointer to handled pinch gesture.
   */
  void pinchTriggered( QPinchGesture* gesture );

  //----------------------------------------------------------------------------
  /*! \brief Handles the pan gesture.
   *
   *  \param gesture Pointer to handled pan gesture.
   */
  void panTriggered( QPanGesture* gesture );

  //------------------------------------------------------------------------------
  /*! \brief Moves the markers to the new positions.
   *
   *  \param pos New position of marker.
   */
  void moveMarker( QPoint pos );

  //------------------------------------------------------------------------------
  /*! \brief Stops marker movement.
   *
   */
  void stopMarkerMove( void );

  qreal xlog( qreal x, qreal width )
  {
    if( x <= 0 )
      x = std::numeric_limits<double>::epsilon();
    qreal xvalue = ( std::log10(x) - std::log10(xaxismin) );
    xvalue /= std::log10(xaxismax) - std::log10(xaxismin);
    xvalue *= width;
    return xvalue;
  }

  qreal xlin( qreal x, qreal width )
  {
    qreal xvalue = xaxismin+x;
    xvalue /= (xaxismax-xaxismin);
    xvalue *= width;
    return xvalue;
  }

  qreal ylin( qreal y, qreal height )
  {
    qreal yvalue = yaxismax-y;
    yvalue /= (yaxismax-yaxismin);
    yvalue *= height;
    return yvalue;
  }



signals:
  void showContextMenu( void );

public slots:

private slots:
  //void showContextMenu( const QPoint &pos );
  void changeAxisProperties( void );
  void setHorizontalMarker( void );
  void setVerticalMarker( void );
  void removeHorizontalMarker( void );
  void removeVerticalMarker( void );

private:
  double xaxismin;
  double xaxismax;
  double yaxismin;
  double yaxismax;
  double xgridtick;
  double ygridtick;

  std::vector<double> xaxistick;
  std::vector<double> yaxistick;

  bool bGridOn;
  bool holdonoff;
  bool frameOnOff;
  bool integrateOnOff;

  tplottypes plottype;

  std::vector<tplot2D> plot2d;
  std::vector<QColor> plotColor;
  std::vector<uint32_t> plotWidth;
  std::vector<bool> plotFill;

  QString strTitle;
  QString strXLabel;
  QString strYLabel;

  // ------ plot geometrics ------
  qreal _plotwidth;
  qreal _plotheight;
  qreal _xplotorigin;
  qreal _yplotorigin;

  // ------ Zoom and pan factors ------
  qreal _zoomX, _zoomY;
  qreal _currentStepScaleFactor;
  qreal _panX, _panY;
  qreal _zoomFactor;
  qreal _scrollFactor;

  QPointF _sourcePos;
  QPointF _centerPos;
  qreal _centerX;
  qreal _centerY;

  bool _zoomable;

  // ------ Marker Positions ------
  bool _drawHMarker;
  bool _drawVMarker;
  qreal _posVMarker;
  qreal _posHMarker;
  bool _moveVMarker;
  bool _moveHMarker;
  QPoint _touchBeginPos;
  QPoint _touchUpdatePos;
  QPoint _touchEndPos;

  // ------ UI ------
  bool _wasGesture;
  bool _showContextMenu;

  // ------ Properties for stylesheet ------
  QColor backgroundColor;
  QColor colorLabel;
  QColor colorGridCoarse;
  QColor colorGridFine;
  QColor colorTitle;
  QColor colorPlotFrame;
  QColor colorMarker;

  // ------ Plot labels ------
  QStringList labels;
  QLabel* labelLegend;

};

#endif
