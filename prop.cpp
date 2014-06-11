#include "prop.h"
#include "ui_prop.h"

prop::prop(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::prop)
{
    m_ui->setupUi(this);
        //////prop->setWindowFlags(Qt::Dialog |  Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint);
}

prop::~prop()
{
    delete m_ui;
}

void prop::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void prop::on_buttonBox_rejected()
{
    prpstate =-1;
}

void prop::on_buttonBox_accepted()
{       // проверяем, не изменился ли движок перевода
  if (prpstate != m_ui->boxEngine->currentIndex()) {
      prpstate = m_ui->boxEngine->currentIndex();
  }
  else
  {
      prpstate = 300;
  }
}

