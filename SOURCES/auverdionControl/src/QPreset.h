#ifndef QPRESET_H
#define QPRESET_H

#include <QWidget>
#include <QTabWidget>

namespace Ui {
class QPreset;
}

class QPreset : public QWidget
{
  Q_OBJECT

public:
  explicit QPreset(QWidget *parent = nullptr);
  ~QPreset();

public:
  QTabWidget* tabChannels;

private:
  Ui::QPreset *ui;

};

#endif // QPRESET_H
