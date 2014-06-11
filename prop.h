#ifndef PROP_H
#define PROP_H

#include <QtGui/QDialog>

namespace Ui {
    class prop;
}

class prop : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(prop)
public:
    explicit prop(QWidget *parent = 0);
    virtual ~prop();
    Ui::prop *m_ui;
    int prpstate;
    int lngstate;

protected:
    virtual void changeEvent(QEvent *e);

private:

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // PROP_H
