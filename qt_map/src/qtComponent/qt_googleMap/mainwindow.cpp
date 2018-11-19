#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(roscommon *p,QWidget *parent) :	// 1.重载构造函数，传入新建类对象的指针，注意第二个缺省参数不要漏掉
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p_rosCommon(p)	// 2.在构造的过程中对成员变量进行赋值
{
    ui->setupUi(this);
    m_thread = new QThread(this);		// 3.定义新线程，当前界面为父界面
    m_view = new QWebEngineView(this);
    m_view->load(QUrl::fromLocalFile("/home/allen/test.html"));
    ui->gridLayout->addWidget(m_view);
    m_view->show();

    connect(m_thread,SIGNAL(started()),p_rosCommon,SLOT(doActive()));		// 5.线程开始时，执行子线程中需要执行的函数
    connect(p_rosCommon,SIGNAL(rosShutDown()),this,SLOT(close()));		// 6.ros中止时，关闭主界面
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(run()));
    connect(ui->lineEdit_jd,SIGNAL(textChanged(QString)),this,SLOT(getJd(QString)));
    connect(ui->lineEdit_wd,SIGNAL(textChanged(QString)),this,SLOT(getWd(QString)));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(p_rosCommon,SIGNAL(originGPSInfoSig(QString)),this,SLOT(originGPSInfoSlot(QString)));
    connect(p_rosCommon,SIGNAL(gpsOriginSig(QString,QString)),this,SLOT(drawOriginGpsLine(QString,QString)));
    connect(p_rosCommon,SIGNAL(imageSig()),this,SLOT(imageSlot()));
    p_rosCommon->moveToThread(m_thread);		// 8.将新建类对象指针移交给线程进行管理
    m_thread->start();		// 9.在主界面进行初始化的时候开启线程
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::run()
{
    m_view->page()->runJavaScript(QString("Mark('%1' , '%2');").arg(wd).arg(jd));
}
void MainWindow::getJd(QString str)
{
    jd = str;
}
void MainWindow::getWd(QString str)
{
    wd = str;
}
void MainWindow::clear()
{
    m_view->page()->runJavaScript(QString("deleteMarkers();"));
}
void MainWindow::originGPSInfoSlot(QString str)
{
    ui->textBrowser_origin->insertPlainText(str+"\n");
    ui->textBrowser_origin->moveCursor(QTextCursor::Start);
}
void MainWindow::drawOriginGpsLine(QString lat, QString lot)
{
    m_view->page()->runJavaScript(QString("Line('%1' , '%2');").arg(lat).arg(lot));
}
void MainWindow::imageSlot()
{
    MainWindow::LabelDisplayMat(ui->label_image,p_rosCommon);
}
void MainWindow::LabelDisplayMat(QLabel *label, roscommon *p)
{
    cv::Mat mat = p->cv_ptr->image;
    cv::Mat mat_resize;
    cv::resize(mat,mat_resize,cv::Size(mat.cols/4,mat.rows/4),0,0,cv::INTER_LINEAR);
    cv::Mat Rgb;
    QImage Img;
    if (mat_resize.channels() == 3)//RGB Img
    {
        cv::cvtColor(mat_resize, Rgb, CV_BGR2RGB);//颜色空间转换
        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
    }
    else//Gray Img
    {
        Img = QImage((const uchar*)(mat_resize.data), mat_resize.cols, mat_resize.rows, mat_resize.cols*mat.channels(), QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(Img));
}
