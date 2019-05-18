#ifndef QDIALOGAXISPROPERTIES_H
#define QDIALOGAXISPROPERTIES_H

#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleValidator>

#include "QFigure.h"

class QDialogAxisProperties  : public QDialog
{
  Q_OBJECT

  //------------------------------------------------------------------------------
  // Methods
  //------------------------------------------------------------------------------
public:
  explicit QDialogAxisProperties( QFigure* parent = 0 ) : QDialog( (QWidget*)parent )
  {
    _figure = parent;

    QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
    #if defined( __IOS__ )
    buttonBox->setFocusPolicy( Qt::NoFocus );
    #endif

    QGridLayout* layoutProperties = new QGridLayout;
    layoutProperties->addWidget( new QLabel( tr("X-Axis") ),     0, 0 );
    layoutProperties->addWidget( new QLabel( tr("Min:") ),       1, 0 );
    layoutProperties->addWidget( &_lineEditXmin,                 1, 1 );
    if( _figure->getPlotType() == QFigure::SEMILOGX )
      layoutProperties->addWidget( new QLabel( tr("Grid [ticks/dec]:") ), 1, 2 );
    else
      layoutProperties->addWidget( new QLabel( tr("Grid:") ), 1, 2 );
    layoutProperties->addWidget( &_lineEditXtick,                1, 3 );
    layoutProperties->addWidget( new QLabel( tr("Max:") ),       1, 4 );
    layoutProperties->addWidget( &_lineEditXmax,                 1, 5 );
    layoutProperties->addWidget( new QLabel( tr("Y-Axis") ),     2, 0 );
    layoutProperties->addWidget( new QLabel( tr("Min:") ),       3, 0 );
    layoutProperties->addWidget( &_lineEditYmin,                 3, 1 );
    layoutProperties->addWidget( new QLabel( tr("Grid:") ),      3, 2 );
    layoutProperties->addWidget( &_lineEditYtick,                3, 3 );
    layoutProperties->addWidget( new QLabel( tr("Max:") ),       3, 4 );
    layoutProperties->addWidget( &_lineEditYmax,                 3, 5 );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout( layoutProperties );
    layout->addWidget( buttonBox );

    QWidget* empty = new QWidget();
    empty->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    layout->addWidget(empty);

    setLayout( layout );
    setWindowTitle( tr("Axis Properties") );

    _lineEditXmin.setText(  QString::number(_figure->getXAxisMin(),  'f', 2) );
    _lineEditXtick.setText( QString::number(_figure->getXGridTick(), 'f', 2) );
    _lineEditXmax.setText(  QString::number(_figure->getXAxisMax(),  'f', 2) );
    _lineEditYmin.setText(  QString::number(_figure->getYAxisMin(),  'f', 2) );
    _lineEditYtick.setText( QString::number(_figure->getYGridTick(), 'f', 2) );
    _lineEditYmax.setText(  QString::number(_figure->getYAxisMax(),  'f', 2) );

    // Set a validator for semilogx (only values greater then zero)
    if( _figure->getPlotType() == QFigure::SEMILOGX ) {
      QDoubleValidator* validatorXmin = new QDoubleValidator( std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), 2, &_lineEditXmin );
      _lineEditXmin.setValidator( validatorXmin );
      QDoubleValidator* validatorXmax = new QDoubleValidator( std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), 2, &_lineEditXmax );
      _lineEditXmax.setValidator( validatorXmax );

      //! \TODO Make this value configurable
      _lowerLimitSemilogx = 10.0;

      connect( &_lineEditXmin, SIGNAL(editingFinished()), this, SLOT(checkLimits()) );
    }


    connect( buttonBox, SIGNAL(accepted()), this, SLOT(accept()) );
    connect( buttonBox, SIGNAL(rejected()), this, SLOT(reject()) );
  }


  ~QDialogAxisProperties( void ) {}

  //------------------------------------------------------------------------------
  /*! \brief
   *
   */
  double getXAxisMin( void ) { return _lineEditXmin.text().toDouble(); }

  //------------------------------------------------------------------------------
  /*! \brief
   *
   */
  double getXAxisMax( void ) { return _lineEditXmax.text().toDouble(); }

  //------------------------------------------------------------------------------
  /*! \brief
   *
   */
  double getYAxisMin( void ) { return _lineEditYmin.text().toDouble(); }

  //------------------------------------------------------------------------------
  /*! \brief
   *
   */
  double getYAxisMax( void ) { return _lineEditYmax.text().toDouble(); }

  //------------------------------------------------------------------------------
  /*! \brief
   *
   */
  double getXTick( void ) { return _lineEditXtick.text().toDouble(); }

  //------------------------------------------------------------------------------
  /*! \brief
   *
   */
  double getYTick( void ) { return _lineEditYtick.text().toDouble(); }

protected:
  //------------------------------------------------------------------------------
  /*! \brief Override the key event handler.
   *
   */
  void keyPressEvent( QKeyEvent* event )
  {
    switch( event->key() ) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        // Avoid closing the dialog by pressing return/enter.
        break;
    default:
        QDialog::keyPressEvent( event );
    }
  }

private slots:
  //------------------------------------------------------------------------------
  /*! \brief Checks, wether axis limits are compatible with current plot type.
   *
   */
  void checkLimits( void )
  {
    if( _figure->getPlotType() == QFigure::SEMILOGX ) {

      if( _lineEditXmin.text().toDouble() < _lowerLimitSemilogx )
        _lineEditXmin.setText( "10.0" );

      if( _lineEditXmax.text().toDouble() < _lowerLimitSemilogx )
        _lineEditXmax.setText( "10.0" );

    }
  }

  //------------------------------------------------------------------------------
  // Variables
  //------------------------------------------------------------------------------
private:
  QLineEdit _lineEditXmin;
  QLineEdit _lineEditXtick;
  QLineEdit _lineEditXmax;
  QLineEdit _lineEditYmin;
  QLineEdit _lineEditYtick;
  QLineEdit _lineEditYmax;
  QFigure* _figure;
  double _lowerLimitSemilogx;
};


#endif
