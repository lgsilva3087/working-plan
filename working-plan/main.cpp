/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include <QApplication>
#include <QStyleFactory>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create("Fusion"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
