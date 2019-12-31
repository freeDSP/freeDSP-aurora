#include <QtWidgets>

#include "WizardImportRewPeq.hpp"

WizardImportRewPeq::WizardImportRewPeq( QWidget* )
{
  setPage( PAGE_WELCOME, new PageWelcomeRewPeq );
  setPage( PAGE_SELECTFILE, new PageSelectFileRewPeq );
  setStartId( PAGE_WELCOME );

  setWizardStyle( QWizard::ClassicStyle );

  QPalette p(palette());
  p.setColor(QPalette::Mid, p.color(QPalette::Window));
  setPalette(p);

  setOption( HaveHelpButton, false );
  //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

  setWindowTitle( tr("Importing REW PEQs") );
}
