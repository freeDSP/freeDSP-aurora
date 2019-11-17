#include <QtWidgets>

#include "WizardImportRewFrq.hpp"

//==============================================================================
/*!
 */
WizardImportRewFrq::WizardImportRewFrq( CFreeDspAurora* ptrdsp, QWidget* )
{
  dsp = ptrdsp;

  pageReferenceLevel = new PageReferenceLevel;

  setPage( PAGE_WELCOME, new PageWelcome );
  setPage( PAGE_SELECTFILE, new PageSelectFile );
  setPage( PAGE_REFERENCELEVEL, pageReferenceLevel );
  setStartId( PAGE_WELCOME );

  setWizardStyle( QWizard::ClassicStyle );

  QPalette p(palette());
  p.setColor(QPalette::Mid, p.color(QPalette::Window));
  setPalette(p);

  setOption( HaveHelpButton, false );
  //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

  setWindowTitle( tr("Importing REW Measurement") );
  //setStyleSheet("background-color:#111111");
  setStyleSheet( "QDoubleSpinBox {background-color: transparent; color: white; border: 1px solid white; border-radius: 2px; selection-background-color: transparent; selection-color: white;}" );
  
}

//==============================================================================
/*!
 */
PageWelcome::PageWelcome( QWidget* )
{
  setTitle( tr("Export the measured frequency response in REW.") );
  //setStyleSheet("background-color:#111111");

  QLabel* label = new QLabel( tr("In REW select \"File -> Export -> Measurement as text\" and enable the option \"Use REW export number format\" ") );
  label->setWordWrap( true );

  QVBoxLayout* layout = new QVBoxLayout;
  layout->setSpacing( 20 );
  layout->addWidget( label );
  
  setLayout( layout );
}

//==============================================================================
/*!
 */
PageSelectFile::PageSelectFile( QWidget* )
{
  setTitle( tr("Select the file with frequency response values that REW has exported.") );
  //setStyleSheet("background-color:#111111");

  lineEditFile = new QLineEdit;
  lineEditFile->installEventFilter( this );

  QFormLayout* formLayout = new QFormLayout;
  formLayout->addRow( tr("File:"), lineEditFile );
  formLayout->setFieldGrowthPolicy( QFormLayout::ExpandingFieldsGrow );

  setLayout( formLayout );

  registerField( "file", lineEditFile );
}

//==============================================================================
/*!
 */
bool PageSelectFile::eventFilter( QObject* object, QEvent* event )
{
  if( object == lineEditFile && event->type() == QEvent::MouseButtonDblClick )
  {
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open Frequency Response"), 
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                     tr("FRD Files (*.frd, *.txt)") );
    if( !fileName.isEmpty() )
      lineEditFile->setText( fileName );
    
    return true;
  }
  return false;
}

//==============================================================================
/*!
 */
PageReferenceLevel::PageReferenceLevel( QWidget* )
{
  setTitle( tr("Select the target level of your measurement.") );
  //setStyleSheet("background-color:#111111");

  doubleSpinBoxReferenceLevel = new QDoubleSpinBox;
  doubleSpinBoxReferenceLevel->setSuffix(" dB");
  doubleSpinBoxReferenceLevel->setMinimum( 0.0 );
  doubleSpinBoxReferenceLevel->setMaximum( 200.0 );
  doubleSpinBoxReferenceLevel->setValue( targetLevel );

  connect( doubleSpinBoxReferenceLevel, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinBoxReferenceLevel_valueChanged(double)) );
  
  QFormLayout* formLayout = new QFormLayout;
  formLayout->addRow( tr("Target Level:"), doubleSpinBoxReferenceLevel );
  formLayout->setFieldGrowthPolicy( QFormLayout::ExpandingFieldsGrow );

  setLayout( formLayout );
}

//==============================================================================
/*!
 */
void PageReferenceLevel::doubleSpinBoxReferenceLevel_valueChanged( double val )
{
  targetLevel = val;
}
