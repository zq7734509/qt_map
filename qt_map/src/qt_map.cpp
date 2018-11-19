#include "qtComponent/qt_googleMap/mainwindow.h"	// 1.包含主界面头文件
#include <QApplication>		// 2.包含qt处理头文件
#include "roscommon.h"		// 3.ros处理相关头文件
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    roscommon rc(argc,argv,"qt_map_node");	// 4.第三个参数为节点的名称
    MainWindow w(&rc);		// 5.获取roscommon对象的地址并进行线程相关的处理
    w.show();		
    return a.exec();
}
