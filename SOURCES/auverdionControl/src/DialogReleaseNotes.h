#ifndef DIALOGRELEASENOTES_H
#define DIALOGRELEASENOTES_H

#include <QDialog>

namespace Ui {
class DialogReleaseNotes;
}

class DialogReleaseNotes : public QDialog
{
  Q_OBJECT

public:
  //============================================================================
  /*!
   */
  explicit DialogReleaseNotes(QWidget *parent = nullptr);

  //============================================================================
  /*!
   */
  ~DialogReleaseNotes();

  //============================================================================
  /*!
   */
  void setReleaseNote( QString str );

  //============================================================================
  /*!
   */
  bool getDontShowAgain( void );

private:
  Ui::DialogReleaseNotes *ui;
};

#endif // DIALOGRELEASENOTES_H
