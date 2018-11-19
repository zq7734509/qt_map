#ifndef ROSCOMMON_H
#define ROSCOMMON_H


#include <QObject>	// 1.包含QObject
#include "ros/ros.h"		// 2.包含ros相关的头文件
#include <string>
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include "lcm2ros/Gps.h"
#include <sensor_msgs/Image.h>
#include <sstream>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

class roscommon : public QObject		// 3.继承于QObject类
{
    Q_OBJECT		// 4.宏
    public:
        roscommon(int,char**,const std::string);
        ros::Subscriber gpsOriginSub;	// 6.声明订阅者，%%必须在头文件中进行声明，否则无法注册订阅者%%
        ros::Subscriber gpsOutputSub;
        ros::Subscriber imageSub;
        cv_bridge::CvImagePtr cv_ptr;
    public slots:
        void doActive();	// 3.执行spin循环的子线程执行函数
        void rosShutDown_slot();	// 4.收到主界面的关闭信号时，中止ros
    signals:
        void rosShutDown();	// 5.在ros结束时发送的关闭信号，关闭主界面
        void gpsOriginSig(QString,QString);
        void gpsOutputSig(QString,QString);
        void originGPSInfoSig(QString);
        void outputXYZInfoSig(QString);
        void imageSig();

    private:
        void gpsOriginCallback(const lcm2ros::Gps &msg);
        void gpsOutputCallback(const geometry_msgs::PoseStamped &msg);
        void imageCallback(const sensor_msgs::ImageConstPtr &msg);
        std::string double2string(double);
        int originGPSCount;
};

#endif // ROSCOMMON_H
