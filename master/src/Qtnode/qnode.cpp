#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Qtnode {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv)
    {}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
}

bool QNode::init() {
    ros::init(init_argc,init_argv,"master_gui");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle nh;
    // Add your ros communications here.
    car_client_ = nh.serviceClient<ros_pi::Rpi_car>("/car_service");
    cam_client_ = nh.serviceClient<ros_pi::Rpi_car>("/camera/image");
    subscriber_ = nh.subscribe("/camera/image/compressed", 10, &QNode::ImageCB, this);
    start();
}

/// ====================
bool QNode::call_car(int mode) {
    ros_pi::Rpi_car srv;
    srv.request.mode = mode;
    if (car_client_.call(srv))    {
       return true;
    } else  {
        false;
    }
}

/// ====================
void QNode::ImageCB(const sensor_msgs::CompressedImage::ConstPtr&  _msg) {
        //ROS_INFO("got update");
        /// TODO get size from cam service
        uint width = 640;
        uint height = 480;
        uint size = width * height;
        QImage temp;
        temp.loadFromData(&(_msg->data[0]), size, "JPG");

        ros::Duration(0.03).sleep();

     emit cbOut(temp);
}
/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

/// ====================
void QNode::startCam(){
    //rosservice call /camera/start_capture
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("/camera/start_capture");
    std_srvs::Empty srv;
    if (client.call(srv)) {
        ROS_INFO(("Started camera capture"));
    } else {
        ROS_INFO(("Failed to start capture service"));
    }

}

/// ====================
void QNode::stopCam(){
    //rosservice call /camera/stop_capture
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("/camera/stop_capture");
    std_srvs::Empty srv;
    if (client.call(srv)) {
        ROS_INFO(("Stopped camera capture"));
    } else {
        ROS_INFO(("Failed to stop capture service"));
    }
}

/****************/
/// ====================
void QNode::run() {
    ros::Rate loop_rate(SPIN_RATE);
    while ( ros::ok() ) {

        //chatter_publisher.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    emit rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

}  // namespace Qtnode
