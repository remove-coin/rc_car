#include "rc_car.h"
#include "ui_rc_car.h"

#include "std_srvs/Empty.h"

#include <boost/thread.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

RC_Car::RC_Car(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RC_Car)
{
    ui->setupUi(this);
    ros::init(argc, argv, "rc_car");
    ros::NodeHandle nh("rc_car");
    ros::AsyncSpinner aspin(1);
    if(aspin.canStart()){
        aspin.start();
        ROS_INFO("Started async spinner");
    } else {
        ROS_INFO("Can't start async spinner, anotherone is running");
    }


    car_client_ = nh.serviceClient<ros_pi::Rpi_car>("/car_service");
    cam_client_ = nh.serviceClient<ros_pi::Rpi_car>("/camera/image");
    subscriber_ = nh.subscribe("/camera/image", 1, &RC_Car::ImageCB, this);


    QObject::connect(ui->startCam, SIGNAL(pressed()), this, SLOT(startCam()));
    QObject::connect(ui->stopCam, SIGNAL(pressed()), this, SLOT(stopCam()));

    QObject::connect(ui->leftB, SIGNAL(pressed()), this, SLOT(goLeft()));
    QObject::connect(ui->leftB, SIGNAL(released()), this, SLOT(stopLeft()));
    QObject::connect(ui->rightB, SIGNAL(pressed()), this, SLOT(goRight()));
    QObject::connect(ui->rightB, SIGNAL(released()), this, SLOT(stopRight()));


    //update video feed
    QObject::connect(this, SIGNAL(cbOut(QImage)), this, SLOT(vidUp(QImage)));

    QImage image(640, 480, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));

}
/*
void RC_Car::onInit() {
    ROS_INFO("init");
    ros::NodeHandle nh("rc_car");
    const ros::NodeHandle np(nh);
    std::string topic = "/camera/image";
    std::string transport = "compressed";
    //image_transport::ImageTransport it(np);
    image_transport::TransportHints hints(transport, ros::TransportHints(), np, "image_transport");


}*/


RC_Car::~RC_Car()
{
    //subscriber_.shutdown();
    car_client_.shutdown();
    cam_client_.shutdown();
    delete ui;
}

/// ====================
void RC_Car::goLeft(){
    ros_pi::Rpi_car srv;
    srv.request.mode = 1;
    if (car_client_.call(srv))    {
        printOut(QString("go left"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
void RC_Car::stopLeft(){
    ros_pi::Rpi_car srv;
    srv.request.mode = -1;
    if (car_client_.call(srv))    {
        //printOut(QString("gone left"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}

/// ====================
void RC_Car::goRight(){
    ros_pi::Rpi_car srv;
    srv.request.mode = 2;
    if (car_client_.call(srv))    {
        printOut(QString("go right"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
void RC_Car::stopRight(){
    ros_pi::Rpi_car srv;
    srv.request.mode = -2;
    if (car_client_.call(srv))    {
        //printOut(QString("gone right"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}





/// ====================
void RC_Car::startCam(){
    //rosservice call /camera/start_capture
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("/camera/start_capture");
    std_srvs::Empty srv;
    if (client.call(srv)) {
        printOut(QString("Started camera capture"));
    } else {
        printOut(QString("Failed to start capture service"));
    }

}

/// ====================
void RC_Car::stopCam(){
    //rosservice call /camera/stop_capture
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("/camera/stop_capture");
    std_srvs::Empty srv;
    if (client.call(srv)) {
        printOut(QString("Stopped camera capture"));
    } else {
        printOut(QString("Failed to stop capture service"));
    }
}


/// ====================
void RC_Car::ImageCB(const sensor_msgs::Image::ConstPtr&  _msg) {
        ROS_INFO("update");
        //sensor_msgs::CvBridge bridge;
        //frame = bridge.imgMsgToCv(msg, "bgr8");
        //cv_bridge::toCvShare(msg, "bgr8")->image

        //QImage temp(&(_msg->data[0]), 640, 480, QImage::Format_RGB888);
        /// QImage temp(&(_msg->data[0]), _msg->width, _msg->height, QImage::Format_ARGB32_Premultiplied);
        //QImage image;
        //image = temp;
        //ui->label->setPixmap(QPixmap::fromImage(image));
        ros::Duration(0.03).sleep();

    /// emit cbOut(temp);
}

/// ====================
void RC_Car::vidUp(QImage image) {
    ui->label->clear();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

/// helper functions
void RC_Car::printOut(std::string _str) {
    QString str = _str.c_str();
    ui->output->append(str);
}

void RC_Car::printOut(QString _str) {
    ui->output->append(_str);
}
