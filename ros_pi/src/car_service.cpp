#include "ros/ros.h"
#include "ros_pi/Rpi_car.h"
#include <wiringPi.h>
#include <softPwm.h>


/*
	define the io pins
	M1: fwd/backwd
	M2: steering
*/
//use BCM numbers for code, and wiringPi for export in the setup  sh
//wiringPi pin 7 == BCM_GPIO 4
#define	M1_A 7
//wiringPi pin 1 == BCM_GPIO 18
#define M1_B 1

//wiringPi pin 3 == BCM_GPIO 22
#define M2_A 3
//wiringPi pin 4 == BCM_GPIO 23
#define M2_B  4

//enable pin of the engine
//wiringPi pin 0 == BCM_GPIO 17
#define M1_E 0
//wiringPi pin 6 == BCM_GPIO 25
#define M2_E 6

//amount of gears/pwm levels
#define TOP_SPEED 100
//full stop at gear
#define FULLSTOP 25

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
    speed = FULLSTOP;
    accelerate = false;

    wiringPiSetup();
    pinMode (M1_A, OUTPUT);
    pinMode (M1_B, OUTPUT);
    pinMode (M2_A, OUTPUT);
    pinMode (M2_B, OUTPUT);
    //pin,initVal,pwmRange
    softPwmCreate (M1_E, 0, TOP_SPEED);
    softPwmCreate (M2_E, 0, 100) ;

    //init pins
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, LOW);
    digitalWrite(M2_A, LOW);
    digitalWrite(M2_B, LOW);
    softPwmWrite (M1_E, 0);
    softPwmWrite (M2_E, 0);

    ros::init(argc, argv, "car_service");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("/car_service", plan);

    while(ros::ok()) {
        if(speed < TOP_SPEED && accelerate == true) {
            speed++;
        }
        if (speed > 0 && brake) {
            //braking added to rollout and backwards
            speed--;
        }
        if (speed > FULLSTOP && !accelerate) {
            //rollout till fullstop
            speed--;
        }
	if (speed < FULLSTOP && !brake) {
	    //rollout braking
	    speed++;
	}
	//write pwm speed
	softPwmWrite(M1_E, abs(speed-FULLSTOP));

	if(speed >= FULLSTOP) {
	    //forward
	    digitalWrite(M1_A, LOW);
	    digitalWrite(M1_B, HIGH);
	} else {
	    //backward
	    digitalWrite(M1_B, LOW);
	    digitalWrite(M1_A, HIGH);
	}

        if(direction != 0) {
            if(direction == 1) {
                //ROS_INFO("go left");
            } else {
                //ROS_INFO("go right");
            }
        } else {

	}

        ros::Duration(0.25).sleep();
        ros::spinOnce();
    }

    service.shutdown();


    return 0;
}
