#include "vstranslator.h"
#include "ui_vstranslator.h"
#include "prop.h"
#include "ui_prop.h"
#include<QtDebug>

vsTranslator::vsTranslator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::vsTranslator)
{
    ui->setupUi(this);
    qApp->installEventFilter( this );
    vsTranslator::loadsettings();
    cmdEnter = new QAction(tr("&PushButton"), this);   // добавляем перевод по Ctrl-Enter
    cmdEnter->setShortcut( Qt::CTRL + Qt::Key_Return );
    ui->textEdit1->addAction(cmdEnter);
    connect(cmdEnter, SIGNAL(triggered()), this, SLOT(on_pushButton_clicked()));
    // состояние настроек. 0+ сменился движок, 100+ сменился язык, -1 менялись настройки, отмена в конце,
    // -2 ничего не менялось, 300  нажато ОК, 200 старт программы
    prp.prpstate = 200;
    list
    <<"sq"  <<"ar"  <<"bg"  <<"ca"
    <<"zh-CN"   <<"zh-TW"   <<"hr"
    <<"cs"  <<"da"  <<"nl"  <<"en"
    <<"et"  <<"tl"  <<"fi"  <<"fr"
    <<"gl"  <<"de"  <<"el"  <<"iw"
    <<"hi"  <<"hu"  <<"id"  <<"it"
    <<"ja"  <<"ko"  <<"lv"  <<"lt"
    <<"mt"  <<"no"  <<"pl"  <<"pt"
    <<"ro"  <<"ru"  <<"sr"  <<"sk"
    <<"sl"  <<"es"  <<"sv"  <<"th"
    <<"tr"  <<"uk"  <<"vi";

//    if (prp.m_ui->comboBox_2->currentIndex() == 1) {
        translates
        <<trUtf8("Албанский")  <<trUtf8("Арабский")  <<trUtf8("Болгарский")  <<trUtf8("Каталонский")
        <<trUtf8("Китайский упр.")   <<trUtf8("Китайский трад.")   <<trUtf8("Хорватский")
        <<trUtf8("Чешский")  <<trUtf8("Датский")  <<trUtf8("Голландский")  <<trUtf8("Английский")
        <<trUtf8("Эстонский")  <<trUtf8("Филипинский")  <<trUtf8("Финский")  <<trUtf8("Французский")
        <<trUtf8("Галисийский")  <<trUtf8("Немецкий")  <<trUtf8("Греческий")  <<trUtf8("Иврит")
        <<trUtf8("Хинди")  <<trUtf8("Венгерский")  <<trUtf8("Индонезийский")  <<trUtf8("Итальянский")
        <<trUtf8("Японский")  <<trUtf8("Корейский")  <<trUtf8("Латвийский")  <<trUtf8("Литовский")
        <<trUtf8("Мальтийский")  <<trUtf8("Норвежский")  <<trUtf8("Польский")  <<trUtf8("Португальский")
        <<trUtf8("Румынский")  <<trUtf8("Русский")  <<trUtf8("Сербский")  <<trUtf8("Словацкий")
        <<trUtf8("Словенский")  <<trUtf8("Испанский")  <<trUtf8("Шведский")  <<trUtf8("Тайский")
        <<trUtf8("Турецкий")  <<trUtf8("Украинский")  <<trUtf8("Вьетнамский");
//           }
//    else {
//        translates
//        <<"Albanian"  <<"Arabic"  <<"Bulgarian"  <<"Catalan"
//        <<"Chinese simpl."   <<"Chinese trad."   <<"Croatian"
//        <<"Czech"  <<"Danish"  <<"Dutch"  <<"English"
//        <<"Estonian"  <<"Filipino"  <<"Finnish"  <<"French"
//       <<"Galician"  <<"German"  <<"Greek"  <<"Hebrew"
//       <<"Hindi"  <<"Hungarian"  <<"Indonesian"  <<"Italian"
//        <<"Japanese"  <<"Korean"  <<"Latvian"  <<"Lithuanian"
//        <<"Maltese"  <<"Norwegian"  <<"Polish"  <<"Portuguese"
//        <<"Romanian"  <<"Russian"  <<"Serbian"  <<"Slovak"
//        <<"Slovenian"  <<"Spanish"  <<"Swedish"  <<"Thai"
//        <<"Turkish"  <<"Ukrainian"  <<"Vietnamese";
//    }
    langs = new QStringList(list);
    ui->comboBox_2->addItems(translates);
    htp = new QHttp(this);
    connect(htp, SIGNAL(done(bool)), this, SLOT(doneH()));

}

vsTranslator::~vsTranslator()
{
    delete ui;
}

void vsTranslator::setgoogle()
{
    ui->comboBox->resize(131,31);
    ui->comboBox_2->show();
    ui->swap->setEnabled(TRUE);
    ui->swap->show();
    ui->comboBox->clear();
    ui->comboBox->addItems(translates);

if (prp.prpstate > -2) {
        ui->comboBox->setCurrentIndex(10);
        ui->comboBox_2->setCurrentIndex(32);
} else {
    if (!(prp.m_ui->translatedir->isChecked())) {
        ui->comboBox->setCurrentIndex(10);
        ui->comboBox_2->setCurrentIndex(32);
   } else {
        QSettings settings("vsTranslator");
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,"$HOME/.config");
        settings.beginGroup("/Window_settings");
        if (settings.contains("translateDir")) {
            ui->comboBox->setCurrentIndex(settings.value("translateDir").toInt());
        }
        if (settings.contains("translat0Dir")) {
            ui->comboBox_2->setCurrentIndex(settings.value("translat0Dir").toInt());
        }
        settings.endGroup();

    }
}
}

void vsTranslator::setpromt()
{
    ui->comboBox->resize(291,31);
    ui->comboBox_2->hide();
    ui->swap->hide();
    ui->swap->setEnabled(FALSE);
    ui->comboBox->clear();
    ui->comboBox->addItem(trUtf8("Англо-русский"));
    ui->comboBox->addItem(trUtf8("Русско-английский"));
    ui->comboBox->addItem(trUtf8("Немецко-русский"));
    ui->comboBox->addItem(trUtf8("Русско-немецкий"));
    ui->comboBox->addItem(trUtf8("Французско-русский"));
    ui->comboBox->addItem(trUtf8("Русско-французский"));
    ui->comboBox->addItem(trUtf8("Испано-русский"));
    ui->comboBox->addItem(trUtf8("Русско-испанский"));
    ui->comboBox->addItem(trUtf8("Итальяно-русский"));

if (prp.prpstate > -2) {
       ui->comboBox->setCurrentIndex(0);
} else {
   if (!(prp.m_ui->translatedir->isChecked())) {
        ui->comboBox->setCurrentIndex(0);
   } else {
        QSettings settings("vsTranslator");
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,"$HOME/.config");
        settings.beginGroup("/Window_settings");
        if (settings.contains("translateDir")) {
            ui->comboBox->setCurrentIndex(settings.value("translateDir").toInt());
        }
        settings.endGroup();
    }
}
}

void vsTranslator::google()
{
    QString from, to;
    from = langs->at( ui->comboBox->currentIndex() );
    to = langs->at( ui->comboBox_2->currentIndex() );
    QString url = QString("/translate_a/t?client=t&sl=" + from + "&tl=" + to);
    QHttpRequestHeader header = QHttpRequestHeader("POST", url, 1, 1);
        header.setValue("Host", "www.google.com");
        header.setValue("User-Agent", "Mozilla/5.0");
        header.setValue("Accept-Encoding", "deflate");
        header.setContentLength(substr.length());
        header.setValue("Connection", "Close");

    QByteArray ba("text=");
        ba.append( substr.toUtf8() );

    if (prp.m_ui->gbProxy->isChecked()) {       // работа с прокси
        if ((prp.m_ui->lineServer->text() != "") && (prp.m_ui->linePort->text() != "")) {
            bool ok;
            if (prp.m_ui->lineLogin->text() != "") {
                QString prt = prp.m_ui->linePort->text();
                htp->setProxy(prp.m_ui->lineServer->text(), prt.toInt(&ok, 10),prp.m_ui->lineLogin->text(),prp.m_ui->linePass->text());
            } else {
                QString prt = prp.m_ui->linePort->text();
                htp->setProxy(prp.m_ui->lineServer->text(), prt.toInt(&ok, 10));
            }

        } else {
            QMessageBox::information(this, tr("Sorry"),
                tr("Set proxy server name|port in settings"
                "<br>or uncheck \"PROXY\""));
        }
    }

    htp->setHost("www.google.com");
    htp->request(header,ba);
}

void vsTranslator::doneH()
{
//int asd = prp.m_ui->boxEngine->currentIndex();

//qDebug();
if (prp.m_ui->boxEngine->currentIndex() == 1 ) {    //если Гугл-движок
    dat = dat.fromUtf8( htp->readAll() );

    dat = dat.replace(QString("\\\""),QString("\""));
    dat = dat.replace(QString("\\n"),QString("\n"));
    dat = dat.replace(QString("\n "),QString("\n"));
    dat = dat.replace(QString("\\x3c"),QString("<"));
    dat = dat.replace(QString("\\x3e"),QString(">"));

    if( dat.startsWith( QString("\"") ) ) {
        dat = dat.remove( dat.length()-1, 1).remove(0,1);
    } else if( dat.startsWith( QString("[") ) && dat.endsWith( QString("]") ) ) {
        QStringList tra;
        //tra = dat.split(QRegExp(QString("\"(.*)\"")));
        dat = dat.replace(QString("]"),QString(""));
        tra = dat.split(QString("["));
        dat = QString("");
        for(int i=0,j=0;i<tra.count();i++)
        {
            if(tra.at(i)!="")
            {
                if(j==0)
                {
                    QString translation = tra.at(i);
                    translation = translation.replace("\"","");
                    translation = translation.replace(",","");
                    dat.append( translation );
                    dat.append( "\n\n") ;
                } else {
                    QString translation = tra.at(i);
                    QStringList translations = translation.split(",");
                    for(int y=0;y<translations.count();y++)
                    {
                        translation = translations.at(y);
                        translation = translation.replace("\"","");
                        if(y==0)
                        {
                            dat.append( QString( translation + ": ") );
                        } else {
                            dat.append( QString( "\t" + translation + "\n" ) );
                        }
                    }
                    dat.append( "\n" );
                }
                j++;
            }
        }
    }
    ui->textEdit1->setPlainText(dat);
} else {            // translate.ru
  // обрабатываем полученные данные для читаемого текста
   substr = dat.fromUtf8( htp->readAll() );

int cnt = substr.indexOf("<b><i>",Qt::CaseInsensitive);
dat = substr.right(substr.length()-cnt-6);
cnt = dat.indexOf("</i></b>",Qt::CaseInsensitive);
dat.resize(cnt);

// получили строку перевода, пытаемся разобраться с умляутами, Quoted Printable и прочим мусором

bool ok;
int dec;
QChar a;
while (dat.contains("&#",Qt::CaseSensitive)) {
    cnt = dat.indexOf("&#");
    substr = dat.mid(cnt+2,3);
    dec = substr.toInt(&ok, 10);
    if (!ok) {
        dat.replace(dat.mid(cnt,6), "_");
    }
    else {
        a = QChar(dec);
        dat.replace(dat.mid(cnt,6), a);
    }
}
if (dat.contains("&quot;",Qt::CaseSensitive)) {  //фильдеперсовые кавычки - на обычные
    dat.replace("&quot;","\"");
}
ui->textEdit1->append(dat+" ");
dat=substr;
loop.exit(0);
}

}

void vsTranslator::loadsettings()
{
        QSettings settings("vsTranslator");
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,"$HOME/.config");
        settings.beginGroup("/Main_settings");

        if (settings.contains("windowpos")) {
           prp.m_ui->windowpos->setChecked(settings.value("windowpos").toBool());
        }
        if (settings.contains("saveTranslateDir")) {
            prp.m_ui->translatedir->setChecked(settings.value("saveTranslateDir").toBool());
        }
        prp.m_ui->autobuff->setChecked(settings.value("saveAutoBuff").toBool());

        if (settings.contains("saveTranslEngine")) {
            prp.m_ui->translengine->setChecked(settings.value("saveTranslEngine").toBool());
        }
        if (settings.contains("translEngine")) {
            prp.m_ui->boxEngine->setCurrentIndex(settings.value("translEngine").toInt());
        }
        else
        {
            prp.m_ui->boxEngine->setCurrentIndex(0);
        }

        if (settings.contains("autoTranslate")) {
            prp.m_ui->cbAutoTranslate->setChecked(settings.value("autoTranslate").toBool());
        }
        else
        {
            prp.m_ui->cbAutoTranslate->setCheckState(Qt::Unchecked);
        }
        settings.endGroup();

        settings.beginGroup("/Window_settings");
        if (settings.contains("posX")) {
           move(settings.value("posX").toInt(),settings.value("posY").toInt());
        }
        if (settings.contains("translateDir")) {
            ui->comboBox->setCurrentIndex(settings.value("translateDir").toInt());
        }
        if (settings.contains("translat0Dir")) {
            ui->comboBox_2->setCurrentIndex(settings.value("translat0Dir").toInt());
        }
        if (settings.contains("autoBuff")) {
            ui->checkBox->setChecked(settings.value("autoBuff").toBool());
        }
        settings.endGroup();

}

void vsTranslator::savesettings()
{
// сохраняем опции основные
        QSettings settings("vsTranslator");
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,"$HOME/.config");
        settings.clear();
        settings.beginGroup("/Main_settings");
        settings.setValue("saveTranslateDir",prp.m_ui->translatedir->isChecked());
        settings.setValue("saveAutoBuff",prp.m_ui->autobuff->isChecked());
        settings.setValue("autoTranslate",prp.m_ui->cbAutoTranslate->isChecked());
        settings.setValue("windowpos",prp.m_ui->windowpos->isChecked());
        settings.setValue("saveTranslEngine",prp.m_ui->translengine->isChecked());
        if (prp.m_ui->translengine->isChecked()) { // движок перевода
            settings.setValue("translEngine",prp.m_ui->boxEngine->currentIndex());
        }


        settings.endGroup();

}


void vsTranslator::transl()
{
int ti = ui->comboBox->currentIndex();

// тут приготовляем строку для отправки на сервер, взависимости от направления перевода

//dat = "http://m.translate.ru/translator/result/?text="+substr+"&dirCode=";
QByteArray bat = QUrl::toPercentEncoding(substr,"=&");

dat = "/translator/result/?text="+bat+"&usev2=0&dirCode=";
//http://m.translate.ru/translator/result/Default.aspx?usev2=0&text=work&dirCode=er
//dat = "/translator/form/Default.aspx?usev2=0&amp;dirCode=";
//er&amp;text=
//qDebug(dat.toUtf8());
switch (ti) {
case 0:
    dat.append("er");
    break;
case 1:
    dat.append("re");
    break;
case 2:
    dat.append("gr");
    break;
case 3:
    dat.append("rg");
    break;
case 4:
    dat.append("fr");
    break;
case 5:
    dat.append("rf");
    break;
case 6:
    dat.append("sr");
    break;
case 7:
    dat.append("rs");
    break;
case 8:
    dat.append("ir");
    break;
}

//dat.append("&amp;text="+substr);
//qDebug(dat.toUtf8());

//отправляем запрос на сервер, принимаем файл

/*
if (!buffer.open(QIODevice::WriteOnly)) {
  QMessageBox::warning(this, tr("HTTP Get"),
                       tr("Cannot write buffer."));
  return;
}
buffer.reset(); */

    if (prp.m_ui->gbProxy->isChecked()) {       // работа с прокси
        if ((prp.m_ui->lineServer->text() != "") && (prp.m_ui->linePort->text() != "")) {
            bool ok;
            if (prp.m_ui->lineLogin->text() != "") {
                QString prt = prp.m_ui->linePort->text();
                htp->setProxy(prp.m_ui->lineServer->text(), prt.toInt(&ok, 10),prp.m_ui->lineLogin->text(),prp.m_ui->linePass->text());
            } else {
                QString prt = prp.m_ui->linePort->text();
                htp->setProxy(prp.m_ui->lineServer->text(), prt.toInt(&ok, 10));
            }

        } else {
            QMessageBox::information(this, tr("Sorry"),
                tr("Set proxy server name|port in settings"
                "<br>or uncheck \"PROXY\""));
        }
    }
//connect(this,SIGNAL(requestFinished(int,bool)),SLOT(finished(int,bool)));
htp->setHost("m.translate.ru");
//QFile mfile("in.txt");
    QHttpRequestHeader hdr = QHttpRequestHeader("GET", dat, 1, 1);
        hdr.setValue("Host", "m.translate.ru");
        hdr.setValue("User-Agent", "Mozilla/5.0");
        hdr.setValue("Accept-Encoding", "deflate");
        hdr.setContentLength(substr.length());
        hdr.setValue("Connection", "Close");
//req_fine = FALSE;
htp->request(hdr,dat.toUtf8());
//qDebug(dat.toUtf8());
loop.exec();
//loop.exec();
//http.head(hdr.toString());
//http.syncGet(hdr.toString(),&buffer );
//http.syncGet(dat.toUtf8(),&buffer );
//http.syncGet(dat.toUtf8(),&mfile );
//http.syncGet(
//http.closeConnection();
//buffer.close();

//buffer.open(QIODevice::ReadOnly);

//substr = qApp->trUtf8(buffer.readAll());
//ui->textEdit1->setPlainText(substr );

//qdata = substr.data();
//qDebug(substr.toUtf8());
//debugstr=substr;

//buffer.close();

}

/*
void vsTranslator::httpDone(bool error)
{
  if (error)
    QMessageBox::warning(this, tr("HTTP Get"),
                         tr("Error while fetching file with "
                           "HTTP: %1.")
                         .arg(http.errorString()));
       buffer.close();
}
*/

void vsTranslator::closeEvent(QCloseEvent * event)
{
// сохраняем опции на выходе
        QSettings settings("vsTranslator");
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,"$HOME/.config");
        settings.beginGroup("/Window_settings");
        //settings.setValue("debug",debugstr);
        if (prp.m_ui->windowpos->isChecked()) { // позиция окна
            settings.setValue("posX",x());
            settings.setValue("posY",y());
        }
        if (prp.m_ui->translatedir->isChecked()) { // направление перевода
            settings.setValue("translateDir",ui->comboBox->currentIndex());
            settings.setValue("translat0Dir",ui->comboBox_2->currentIndex());
        }
        if (prp.m_ui->autobuff->isChecked()) { // автокопирование в буфер
            settings.setValue("autoBuff",ui->checkBox->isChecked());
        }
        settings.endGroup();
    QMainWindow::closeEvent(event);   // Обрабатываем сообщение стандартными средствами

}

void vsTranslator::on_pushButton_clicked()
{

//
QString str = ui->textEdit1->toPlainText();
str = str.simplified();
if (str.contains("#")) {        // убираем опасные символы
    str.replace("#", "");
}
if (str.contains("&")) {        // убираем опасные символы
    str.replace("&", " and ");
}

if (prp.m_ui->boxEngine->currentIndex() == 0) {     //если движок - промт
str.replace(" ", "+");
// процедура деления на подстроки
    ui->textEdit1->clear();

if (str.length()<=200) {   // если строка не длинная, отправляем на сервер и результат в окно
    substr =str;
    vsTranslator::transl(); // подготовка запроса и вызов сервера

    // результат - в окно
    //ui->textEdit1->setPlainText(dat);
}
else {  //тут пытаемся делить по предложениям/фразам
    //req_fine = TRUE;
    int count;
    QString mini;
    //str.append(".+");
    while (str.length()>=3) {
        if (str.length()>=200) {    // если ещё большая строка
            mini = str.left(200); // 200 символов максимум
            if (mini.contains(".+")) {      // ищем точки
               count = mini.lastIndexOf(".+")+1;
               substr = mini.left(count);
               vsTranslator::transl(); // подготовка запроса и вызов сервера
               //ui->textEdit1->append(dat+" ");
               str = str.right(str.length()-count-1);  //убрали уже переведённое

            }
            else {  // точек нету, ищем запятые или в крайнем случае пробел
                if (mini.contains(",+")) {      // ищем запятые
                   count = mini.lastIndexOf(",+")+1;
                   substr = mini.left(count);
                   vsTranslator::transl(); // подготовка запроса и вызов сервера
                   //ui->textEdit1->append(dat+" ");
                   str = str.right(str.length()-count-1);  //убрали уже переведённое
                }
                else {
                   count = mini.lastIndexOf("+")+1; // пробелы
                   substr = mini.left(count);
                   vsTranslator::transl(); // подготовка запроса и вызов сервера
                   //ui->textEdit1->append(dat+" ");
                   str = str.right(str.length()-count-1);  //убрали уже переведённое
                }
            }
       }
        else {      // если осталась маленькая строчка
            substr = str;
            str.clear();
            vsTranslator::transl(); // подготовка запроса и вызов сервера
            //ui->textEdit1->append(dat+" ");

        }


    }
}
} else {   // если гугл выбран
    substr =str;
    google();
}
    if (ui->checkBox->isChecked()) { // копируем перевод в буфер, если задано
        ui->textEdit1->selectAll();
        ui->textEdit1->copy();
        // костыли
        ui->textEdit1->paste();
    }

}



bool vsTranslator::eventFilter( QObject* o, QEvent* e ) {
        if( e->type() == QEvent::ApplicationActivate ) {

            // активация окна

            // сначала проверим, не посли настроек ли.
            if (prp.prpstate > -2) {
                    // тут процедуры смены интерфейса на разные движки
                switch (prp.prpstate) {
                    case 0:
                        setpromt();
                        savesettings();  // Сменили и записали настройки
                        //if (prp.lngstate != prp.m_ui->comboBox_2->currentIndex()) {
                            //ui->retranslateUi(
                        break;
                    case 1:
                        setgoogle();
                        savesettings();  // Сменили и записали настройки
                        break;
                    case -1:
                        loadsettings();  // например, меняли настройки, но нажали отмена. Приводим их в начальный вид.
                        break;
                    case 300:
                        savesettings();  // Сменили и записали настройки
                        break;
                    case 200:  // старт программы
                        switch (prp.m_ui->boxEngine->currentIndex()) {
                        case 0:
                            setpromt();
                            break;
                        case 1:
                            setgoogle();
                            break;
                        }
                        break;

                }

                prp.prpstate = -2;  // заново установили в -2
            }

            QString a;  // вводим, т.к. undo не работает нормально.
            if (ui->textEdit1->canPaste()) {        //вставка из буфера и перевод
                a = ui->textEdit1->toPlainText();
                ui->textEdit1->clear();
                ui->textEdit1->paste();
                if (localBuff != ui->textEdit1->toPlainText()){     // если буфер изменился (чтоб не переводило одно и тоже на автопереводе)
                    localBuff = ui->textEdit1->toPlainText();
                    if (prp.m_ui->cbAutoTranslate->isChecked()) {
                        //substr
                        ui->pushButton->click();;
                    }
                }
                else {
                    ui->textEdit1->setPlainText(a);
                }
            }
        }

        return QMainWindow::eventFilter( o, e );
}

void vsTranslator::on_pushButton_4_clicked()
{
    QMessageBox::about(this, tr("About vsTranslator"),
        tr("<h2>vsTranslator v.0.4</h2>"
        "<p>Copyright &copy; 2009 Vladimir S. Stepanov "
        "<br><b><a href=\"http://steplton.ho.ua\">http://steplton.ho.ua</a></b>"
        "<p>"
        "<b>Thanks to:</b>"
        "<br><b>Iulian M</b> for <a href=\"http://www.erata.net/qt-boost/synchronous-http-request/\">SyncHTTP</a>"
        "<br><b>Alex Snet</b> for <a href=\"http://alexsnet.ru/2009/02/google-translate-non-ajax-api/\">Google Translate Non Ajax API</a>"
        "<br><b><a href=\"http://www.translate.ru\">Promt</a> and <a href=\"http://translate.google.com\">Google</a> </b> for translation engines"));

}

void vsTranslator::on_pushButton_2_clicked()
{
    ui->textEdit1->selectAll();
    ui->textEdit1->copy();;
    // костыли
    ui->textEdit1->paste();

}

/*void vsTranslator::savesettings()
{
    //
}*/


void vsTranslator::on_pushButton_3_clicked()
{
    prp.prpstate = prp.m_ui->boxEngine->currentIndex(); // запоминаем движок перевода перед вызовом настроек
    prp.lngstate = prp.m_ui->comboBox_2->currentIndex(); // запоминаем язык перед вызовом настроек
    prp.show();

}


void vsTranslator::on_swap_clicked()
{
    int tmp = ui->comboBox_2->currentIndex();
    ui->comboBox_2->setCurrentIndex( ui->comboBox->currentIndex() );
    ui->comboBox->setCurrentIndex( tmp );

}
