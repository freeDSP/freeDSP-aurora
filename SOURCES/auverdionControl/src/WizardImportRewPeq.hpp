#ifndef WIZARDREWPEQ_H
#define WIZARDREWPEQ_H

#include <QWizard>
#include <QtWidgets>

#include "freeDSP-Aurora.hpp"


//==============================================================================
/*!
 */
class WizardImportRewPeq : public QWizard
{
  Q_OBJECT

public:
  enum
  { 
    PAGE_WELCOME,
    PAGE_SELECTFILE
  };

  WizardImportRewPeq( QWidget* parent = nullptr );

private slots:

public:

private:

};

//==============================================================================
/*!
 */
class PageWelcomeRewPeq : public QWizardPage
{
  Q_OBJECT

public:
  PageWelcomeRewPeq( QWidget* = nullptr )
  {
    setTitle( tr("Export the PEQs in REW.") );
    //setStyleSheet("background-color:#111111");

    QLabel* label = new QLabel( tr("In REW select \"File -> Export -> Filter Settings as text\" and make sure, that REW uses dot as the decimal delimiter and no digit grouping.") );
    label->setWordWrap( true );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing( 20 );
    layout->addWidget( label );
    
    setLayout( layout );
  }

  int nextId( void ) const override
  {
    return WizardImportRewPeq::PAGE_SELECTFILE;
  }

private:

};

//==============================================================================
/*!
 */
class PageSelectFileRewPeq : public QWizardPage
{
  Q_OBJECT

public:
  PageSelectFileRewPeq( QWidget* = nullptr )
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

  int nextId( void ) const override
  {
    return -1;
  }

  bool eventFilter( QObject* object, QEvent* event ) override
  {
    if( object == lineEditFile && event->type() == QEvent::MouseButtonDblClick )
    {
      QString fileName = QFileDialog::getOpenFileName( this, tr("Open REW PEQ file"), 
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                     tr("REW Files (*.txt)") );
      if( !fileName.isEmpty() )
        lineEditFile->setText( fileName );
      
      return true;
    }
    return false;
  }

private:
  QLineEdit* lineEditFile;

};

#endif
