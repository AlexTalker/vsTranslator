#ifndef VSTRANSLATOR_H
#define VSTRANSLATOR_H

#include <QtGui/QMainWindow>
#include <QtNetwork/QHttp>
#include <QBuffer>
#include <QEventLoop>
#include <QtGui/QMessageBox>
#include <prop.h>
#include <ui_prop.h>
#include <QSettings>
#include <QUrl>

namespace Ui
{
    class vsTranslator;
}

class vsTranslator : public QMainWindow
{
    Q_OBJECT

public:
    vsTranslator(QWidget *parent = 0);
    ~vsTranslator();
    //QFileInfo finfo;

private:
    Ui::vsTranslator *ui;
    bool eventFilter( QObject* o, QEvent* e );
    //SyncHTTP http;
    QBuffer buffer;
    prop prp;
    void loadsettings();
    void savesettings();
    void transl ();
    void setgoogle();
    void setpromt();
    void google();
    QString dat;
    QString substr;
    QString localBuff;
    QAction *cmdEnter;
    QStringList translates, list;
    QStringList* langs;
    QHttp *htp;
    QString debugstr;
    QEventLoop loop;

private slots:
    void on_swap_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    //void httpDone(bool error);

public slots:
    void doneH();

protected:
    void closeEvent(QCloseEvent * event);

};

#endif // VSTRANSLATOR_H
