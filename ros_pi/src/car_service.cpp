#include "ros/ros.h"
#include "ros_pi/Rpi_car.h"
#include <wiringPi.h>

/*
    define the io pin of the transistor
*/
//wiringPi pin 7 == BCM_GPIO 4
#define	LED_RED	7

int direction, speed;
bool accelerate, brake, lights;

/// ===============================
void honk() {
    //honk
}

/// ===============================
bool plan(ros_pi::Rpi_car::Request  &req,
         ros_pi::Rpi_car::Response &res)
{
    switch(req.mode) {
    case -4: ///un-brake
    {
        brake = false;
        break;}
    case -3: ///un-accelerate
    {
        accelerate = false;
        break;}
    case -2: ///un-right
    {
        direction = 0;
        break;}
    case -1: ///un-left
    {
        direction = 0;
        break;}
    case 1: ///left
    {
        direction = 1;
        break;}
    case 2: ///right
    {
        direction = -1;
        break;}
    case 3: ///accelerate
    {
        accelerate = true;
        break;}
    case 4: ///brake
    {
        brake = true;
        break;}
    /// ############ ///
    default:
    {
        return false;
        break;}
    }
    return true;
}

/// ===============================
int main(int argc, char **argv)
{
    direction = 0;
    speed = 0;
    accelerate = false;

    wiringPiSetup();
    pinMode (LED_RED, OUTPUT) ;

    ros::init(argc, argv, "car_service");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("/car_service", plan);

    while(ros::ok()) {
        if(speed < 5 && accelerate == true) {
            speed++;
        }
        if (speed > 0 && brake) {
            //braking added to rollout
            speed--;
        }
        if (speed > 0 && !accelerate) {
            //rollout
            speed--;
        }
        if(direction != 0) {
            if(direction == 1) {
                //go left
                digitalWrite (LED_RED, HIGH) ;	// On
                delay (500) ;		// mS
                digitalWrite (LED_RED, LOW) ;	// Off
                delay (500) ;
            } else {
                //go right
            }
        }

        /** set actual motors connected to the rpi*/

        ros::Duration(0.5).sleep();
        ros::spinOnce();
    }

    service.shutdown();

    return 0;
}
