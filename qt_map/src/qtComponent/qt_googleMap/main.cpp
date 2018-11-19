#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngineWidgets>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QWebEngineView *view = new QWebEngineView();
    //view->load(QUrl::fromLocalFile("/home/allen/test.html"));
    //view->show();
    return a.exec();
}
