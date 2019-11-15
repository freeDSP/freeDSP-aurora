#include <QtWidgets>

#include "WizardConnect.hpp"

//==============================================================================
/*!
 */
WizardConnect::WizardConnect( CFreeDspAurora* ptrdsp, QWidget* parent ) : QWizard( parent )
{
  dsp = ptrdsp;

  setPage( Page_Connect, new PageConnect );
  setPage( Page_SSID, new PageSSID );
  setPage( PAGE_SUCCESS, new PageSuccess( dsp ) );
  setPage( PAGE_CONNECTION, new PageConnection( dsp ) );
  setStartId( Page_Connect );

  setWizardStyle( QWizard::ClassicStyle );

  QPalette p(palette());
  p.setColor(QPalette::Mid, p.color(QPalette::Window));
  setPalette(p);

  setOption( HaveHelpButton, false );
  //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

  setWindowTitle( tr("Connecting to Aurora") );
  setStyleSheet("background-color:#111111");
}
