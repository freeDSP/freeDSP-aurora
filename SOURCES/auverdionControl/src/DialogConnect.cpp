#include "DialogConnect.h"
#include "ui_DialogConnect.h"

DialogConnect::DialogConnect(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogConnect)
{
  ui->setupUi(this);
}

DialogConnect::~DialogConnect()
{
  delete ui;
}
