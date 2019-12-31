#ifndef WIZARDREWFRD_H
#define WIZARDREWFRD_H

#include <QWizard>
#include <QtWidgets>

#include "freeDSP-Aurora.hpp"

class PageReferenceLevel;

//==============================================================================
/*!
 */
class WizardImportRewFrq : public QWizard
{
  Q_OBJECT

public:
  enum
  { 
    PAGE_WELCOME,
    PAGE_SELECTFILE,
    PAGE_REFERENCELEVEL
  };

  WizardImportRewFrq( CFreeDspAurora* ptrdsp, QWidget* parent = nullptr );

private slots:

public:
  PageReferenceLevel* pageReferenceLevel;

private:
  CFreeDspAurora* dsp = nullptr;

};

//==============================================================================
/*!
 */
class PageWelcome : public QWizardPage
{
  Q_OBJECT

public:
  PageWelcome( QWidget* parent = nullptr );

  int nextId( void ) const override
  {
    return WizardImportRewFrq::PAGE_SELECTFILE;
  }

private:

};

//==============================================================================
/*!
 */
class PageSelectFile : public QWizardPage
{
  Q_OBJECT

public:
  PageSelectFile( QWidget* parent = nullptr );

  int nextId( void ) const override
  {
    return WizardImportRewFrq::PAGE_REFERENCELEVEL;
  }

  bool eventFilter( QObject* object, QEvent* event ) override;

private:
  QLineEdit* lineEditFile;

};

//==============================================================================
/*!
 */
class PageReferenceLevel : public QWizardPage
{
  Q_OBJECT

public:
  PageReferenceLevel( QWidget* parent = nullptr );

  int nextId( void ) const override
  {
    return -1;
  }

private slots:
  void doubleSpinBoxReferenceLevel_valueChanged( double val );

public:
  double targetLevel = 80.0;

private:
  QDoubleSpinBox* doubleSpinBoxReferenceLevel;

};

#endif
