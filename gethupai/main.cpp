#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{

    QTextCodec *codec = QTextCodec::codecForName("system");
    //QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
