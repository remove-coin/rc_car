#include "ros/ros.h"
#include "ros_pi/Rpi_car.h"

/// ===============================
void goLeft() {

}

/// ===============================
void goRight() {

}

/// ===============================
bool plan(ros_pi::Rpi_car::Request  &req,
         ros_pi::Rpi_car::Response &res)
{
    switch(req.mode) {
    case 1: ///
    {
        goLeft();
        break;}
    case 2: ///
    {
        goRight();
        break;}
    /// ############ ///
    default:
    {
        //res.TrajMsg = getTrajMsg(pos);
        return false;
        break;}
    }
    return true;
}

/// ===============================
int main(int argc, char **argv)
{

    ros::init(argc, argv, "car_service");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("/car_service", plan);
    ros::spin();

    service.shutdown();

    return 0;
}
