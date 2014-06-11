#include <QtGui/QApplication>
#include "vstranslator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vsTranslator w;
    //QTranslator * tor(0);
    //tor->load ( QString("vstranslator_en"),QString("."),QString("_."),QString(""));
    //w.installTranslator( &tor );
    w.show();
    return a.exec();
}

