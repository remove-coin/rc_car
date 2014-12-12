#ifndef RC_CAR_H
#define RC_CAR_H

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QString>
#include <QTextBrowser>
#include <ros/ros.h>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include "ros_pi/Rpi_car.h"
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>

namespace Ui {
class RC_Car;
}

class RC_Car : public QMainWindow
{
    Q_OBJECT

public:
    explicit RC_Car(QWidget *parent = 0);
    ~RC_Car();

private:
    virtual void ImageCB(const sensor_msgs::Image::ConstPtr&  _msg);

signals:
    void cbOut(QImage);

protected slots:

    virtual void goLeft();
    virtual void stopLeft();
    virtual void goRight();
    virtual void stopRight();
    virtual void startCam();
    virtual void stopCam();
    void vidUp(QImage);
    void printOut(std::string);
    void printOut(QString);
    
private:
    Ui::RC_Car *ui;
    ros::Subscriber subscriber_;
    ros::ServiceClient car_client_, cam_client_;
    int argc;
    char **argv;

};

#endif // RC_CAR_H
