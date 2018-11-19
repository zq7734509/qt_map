#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include "roscommon.h"		// 1.包含新建类的头文件
#include <QThread>		// 2.包含QThread
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(roscommon *p,QWidget *parent = 0);
    ~MainWindow();
     roscommon *p_rosCommon;		// 4.声明新建类的对象指针
     QThread *m_thread;		// 5.声明QThread类对象指针
     QWebEngineView *m_view;
     QString jd,wd;
signals:

public slots:
    void run();
    void getJd(QString);
    void getWd(QString);
    void clear();
    void originGPSInfoSlot(QString);
    void drawOriginGpsLine(QString,QString);
    void imageSlot();

private:
    Ui::MainWindow *ui;
    void LabelDisplayMat(QLabel*, roscommon*);
};

#endif // MAINWINDOW_H
