#include "DialogReleaseNotes.h"
#include "ui_DialogReleaseNotes.h"

//==============================================================================
/*!
 */
DialogReleaseNotes::DialogReleaseNotes(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogReleaseNotes)
{
  ui->setupUi(this);
}

//==============================================================================
/*!
 */
DialogReleaseNotes::~DialogReleaseNotes()
{
  delete ui;
}

//==============================================================================
/*!
 */
void DialogReleaseNotes::setReleaseNote( QString str )
{
  ui->textReleaseNotes->insertPlainText( str );
  ui->textReleaseNotes->moveCursor( QTextCursor::Start );
}

//==============================================================================
/*!
 */
bool DialogReleaseNotes::getDontShowAgain( void )
{
  if( ui->checkBoxDontShowAgain->checkState() == Qt::Unchecked )
    return false;
  else
    return true;
}