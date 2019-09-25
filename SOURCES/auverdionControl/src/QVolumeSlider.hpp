#ifndef QVOLUMESLIDER_H
#define QVOLUMESLIDER_H

#include <QWidget>

class QVolumeSlider : public QWidget
{
  Q_OBJECT
  Q_PROPERTY( QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor DESIGNABLE true )
  Q_PROPERTY( QColor textColor       READ getTextColor       WRITE setTextColor       DESIGNABLE true )
  Q_PROPERTY( QColor sliderColor     READ getSliderColor     WRITE setSliderColor     DESIGNABLE true )

public:
  explicit QVolumeSlider( QWidget* parent = nullptr );
  ~QVolumeSlider() override {  }

  //============================================================================
  /*!
   */
  QColor getBackgroundColor( void ) const { return backgroundColor; }

  //============================================================================
  /*!
   */
  void setBackgroundColor( const QColor color ) { backgroundColor = color; }

  //============================================================================
  /*!
   */
  QColor getTextColor( void ) const { return textColor; }

  //============================================================================
  /*!
   */
  void setTextColor( const QColor color ) { textColor = color; }

  //============================================================================
  /*!
   */
  QColor getSliderColor( void ) const { return sliderColor; }

  //============================================================================
  /*!
   */
  void setSliderColor( const QColor color ) { sliderColor = color; }

  //============================================================================
  /*!
   */
  qreal value( void ) { return sliderPos; }

  //============================================================================
  /*!
   */
  void setValue( qreal val, bool doNotification = false )
  { 
    sliderPos = val;
    update();
    if( doNotification )
      emit valueChanged( sliderPos );
  }

  //============================================================================
  /*!
   */
  QByteArray getUserParams( void );

protected:
  void paintEvent( QPaintEvent* event ) override;
  void mousePressEvent( QMouseEvent* event ) override;
  void mouseMoveEvent( QMouseEvent* event ) override;
  void mouseReleaseEvent( QMouseEvent* event ) override;

signals:
  void valueChanged( double val );

private slots:

private:
  // ------ Properties for stylesheet ------
  QColor backgroundColor;
  QColor textColor;
  QColor sliderColor;

  // ------ Value ------
  qreal sliderPos = -60;
  qreal minVal = -120;
  qreal maxVal = 0;

  qreal fontHeight;

};

#endif
