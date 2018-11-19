#include "roscommon.h"
#include "iostream"
#include <QString>
#include "china_shift.h"
#include <iomanip>

roscommon::roscommon(int argc , char **argv , const std::string name)
{
    ros::init(argc, argv, name);		// 1.初始化ros节点，name为唯一
    ros::start();		// 2.开始ros节点，如果不执行将无法注册节点
    ros::NodeHandle n;		// 3.定义nodehandle
    gpsOriginSub = n.subscribe("/gps",1000,&roscommon::gpsOriginCallback,this);
    gpsOutputSub = n.subscribe("/poseStamp",1000,&roscommon::gpsOutputCallback,this);
    imageSub = n.subscribe("/usb_cam/image_raw",1000,&roscommon::imageCallback,this);
    originGPSCount = 0;
}
void roscommon::doActive()		// 5.子线程执行函数实现
{
    std::cout << "begin" <<std::endl;
    ros::spin();
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    emit(rosShutDown());		// 6.退出spin循环后发送关闭窗口的信号
}
void roscommon::gpsOriginCallback(const lcm2ros::Gps &msg)
{
    if(originGPSCount == 5)
    {
        double wgs84_lat = msg.lat;
        double wgs84_lot = msg.lon;
        Location wgs84_coodinate = {wgs84_lot,wgs84_lat};
        Location gcj02_coodinate = transformFromWGSToGCJ(wgs84_coodinate);
        QString lat = QString::fromStdString(double2string(gcj02_coodinate.lat));
        QString lot = QString::fromStdString(double2string(gcj02_coodinate.lng));

        emit gpsOriginSig(lat,lot);
        emit originGPSInfoSig(QString::fromStdString(double2string(wgs84_lat)) + " , " + QString::fromStdString(double2string(wgs84_lot)));
        originGPSCount = 0;
    }
    else
        originGPSCount++;


}
void roscommon::gpsOutputCallback(const geometry_msgs::PoseStamped &msg)
{

}
void roscommon::imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
       cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
       emit imageSig();
    }
    catch (cv_bridge::Exception& e)
    {
       ROS_ERROR("cv_bridge exception: %s", e.what());
       return;
    }

}
void roscommon::rosShutDown_slot()        // 8.收到主界面的关闭信号时，停止ros，子线程执行函数自动退出
{
    if(ros::isStarted()) {
         ros::shutdown(); // explicitly needed since we use ros::start();
         ros::waitForShutdown();
       }
}
std::string roscommon::double2string(double d)
{
     std::ostringstream os;
     os.precision(10);
     os.setf(std::ios::fixed);
     if (os << d)
      return os.str();
     else
      return "invalid conversion";
}
