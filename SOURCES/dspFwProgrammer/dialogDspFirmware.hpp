#ifndef DIALOGDSPFIRMWARE_HPP
#define DIALOGDSPFIRMWARE_HPP

#include <QDialog>

#include "freeDSP-Aurora.hpp"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();

private slots:
  void on_toolButtonSelectHexFile_triggered( QAction* );

  void on_pushButtonHexFile_clicked();

  void on_pushButtonFlash_clicked();

  void on_pushButtonVerify_clicked();

private:
  Ui::Dialog *ui;

  CFreeDspAurora board;

  QString pathHexFile;

};

#endif // DIALOGDSPFIRMWARE_HPP
