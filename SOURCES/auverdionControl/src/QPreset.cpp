#include "QPreset.h"
#include "ui_QPreset.h"

QPreset::QPreset(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QPreset)
{
  ui->setupUi(this);

  tabChannels = ui->tabChannels;
}

QPreset::~QPreset()
{
  delete ui;
}
