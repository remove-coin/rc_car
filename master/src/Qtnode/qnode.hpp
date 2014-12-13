#ifndef Qtnode_QNODE_HPP_
#define Qtnode_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include "sensor_msgs/Image.h"
#include "ros_pi/Rpi_car.h"
#include "std_srvs/Empty.h"

#define SPIN_RATE 30


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Qtnode {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv );
    ~QNode();
    bool init();
    void run();
    bool call_car(int mode);

private:
    virtual void ImageCB(const sensor_msgs::Image::ConstPtr&  _msg);

signals:
    void rosShutdown();
    void cbOut(QImage);

public slots:
    void startCam();
    void stopCam();

private:
    int init_argc;
    char** init_argv;
    ros::Subscriber subscriber_;
    ros::ServiceClient car_client_, cam_client_;
};

}  // namespace Qtnode

#endif /* Qtnode_QNODE_HPP_ */
