#ifndef QDIALOGDEMOSELECTOR_HPP
#define QDIALOGDEMOSELECTOR_HPP

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class QDialogDemoSelector : public QDialog
{
  Q_OBJECT

public:
    QDialogDemoSelector( QString mess, const QStringList& items )
    {
      setLayout( new QHBoxLayout );

      comboboxPlugins = new QComboBox;
      comboboxPlugins->addItems(items);
      layout()->addWidget( new QLabel( mess ) );
      layout()->addWidget( comboboxPlugins );
      
      QPushButton* pushButtonOk = new QPushButton( "OK" );
      layout()->addWidget( pushButtonOk );
      connect( pushButtonOk, &QPushButton::clicked, this, [this]()
      {
        accept();
      });
    }

    QComboBox* comboBox() { return comboboxPlugins; }

private:
  QComboBox* comboboxPlugins;
};

#endif
