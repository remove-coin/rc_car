#include "rc_car.h"
#include "ui_rc_car.h"

#include "std_srvs/Empty.h"


#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

RC_Car::RC_Car(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RC_Car)
{
    ui->setupUi(this);
    ros::init(argc, argv, "rc_car");
    ros::NodeHandle nh;

    car_client_ = nh.serviceClient<ros_pi::Rpi_car>("/car_service");
    cam_client_ = nh.serviceClient<ros_pi::Rpi_car>("/camera/image");
    subscriber_ = nh.subscribe("camera/image/compressed", 1, &RC_Car::imageCB, this);

    QObject::connect(ui->leftB, SIGNAL(pressed()), this, SLOT(goLeft()));
    QObject::connect(ui->startCam, SIGNAL(pressed()), this, SLOT(startCam()));
    QObject::connect(ui->stopCam, SIGNAL(pressed()), this, SLOT(stopCam()));

    //update video feed
    QObject::connect(this, SIGNAL(cbOut(QString)), this, SLOT(vidUp(QString)));
}

RC_Car::~RC_Car()
{
    subscriber_.shutdown();
    car_client_.shutdown();
    delete ui;
}

/// ====================
void RC_Car::goLeft(){
    ros_pi::Rpi_car srv;
    srv.request.mode = 1;
    if (car_client_.call(srv))    {
        printOut(QString("gone left"));
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
void RC_Car::imageCB(const sensor_msgs::CompressedImage::ConstPtr&  _msg) {
        //QImage temp(&(_msg->data[0]), _msg->width, _msg->height, QImage::Format_RGB888);

        QImage temp(&(_msg->data[0]), 640, 480, QImage::Format_RGB888);
        QImage image;
        image = temp;

        ui->label->setPixmap(QPixmap::fromImage(image));
        //cv::cvWaitKey(1);

    QString str;
    emit cbOut(str);
}

/// ====================
void RC_Car::vidUp(QString _str) {
    //ui->cam
}

/// helper functions
void RC_Car::printOut(std::string _str) {
    QString str = _str.c_str();
    ui->output->append(str);
}

void RC_Car::printOut(QString _str) {
    ui->output->append(_str);
}
