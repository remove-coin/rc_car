#include "ros/ros.h"
#include "ros_pi/Rpi_car.h"
#include <wiringPi.h>

/*
    define the io pin of the transistor
*/
//use BCM numbers for code, and wiringPi for export in the setup  sh
//wiringPi pin 7 == BCM_GPIO 4
#define	LED_1 7
//wiringPi pin 4 == BCM_GPIO 23
#define LED_2 4
//wiringPi pin 0 == BCM_GPIO 17
#define LED_3 0

//wiringPi pin 1 == BCM_GPIO 18
//pwm_pin == enable pin of the engine 
#define PWM_PIN 1

//amount of gears/pwm levels
#define TOP_SPEED 20

int direction, speed;
bool accelerate, brake, lights;

//maximum of 1023
int values[TOP_SPEED + 1];

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
    for (int i = 0; i <= TOP_SPEED; i++) {
    	values[i] = i*(1000/TOP_SPEED);
    }

    wiringPiSetup();
    pinMode (LED_1, OUTPUT);
    pinMode (LED_2, OUTPUT);
    pinMode (LED_3, OUTPUT);
    pinMode (PWM_PIN, PWM_OUTPUT) ;

    //init pins
    digitalWrite(LED_2, HIGH);
    pwmWrite (PWM_PIN, 0) ;

    ros::init(argc, argv, "car_service");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("/car_service", plan);

    while(ros::ok()) {
        if(speed < TOP_SPEED && accelerate == true) {
            speed++;
	    pwmWrite(PWM_PIN, values[speed]);
        }
        if (speed > 0 && brake) {
            //braking added to rollout
            speed--;
	    pwmWrite(PWM_PIN, values[speed]);
        }
        if (speed > 0 && !accelerate) {
            //rollout
            speed--;
	    pwmWrite(PWM_PIN, values[speed]);
        }
        if(direction != 0) {
            if(direction == 1) {
                //ROS_INFO("go left");
                digitalWrite(LED_1, HIGH);	// On
		digitalWrite(LED_2, LOW);   // On
		digitalWrite(LED_3, LOW);   // On
                //delay (500) ;		// mS
            } else {
                //ROS_INFO("go right");
                digitalWrite(LED_1, LOW);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, HIGH);
            }
        } else {
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_2, HIGH);
		digitalWrite(LED_3, LOW);

	}
        /** set actual motors connected to the rpi*/

        ros::Duration(0.25).sleep();
        ros::spinOnce();
    }

    service.shutdown();

    return 0;
}
