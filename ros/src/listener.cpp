#include "ros/ros.h"
#include "std_msgs/Float64.h"

ros::Subscriber sub;



void receivedMsg(const std_msgs::Float64 msg)
{   
	ROS_INFO("%f", msg.data);
}  

int main(int argc, char **argv)
{

	ros::init(argc, argv, "rpi_listener");
	ros::NodeHandle n;

	sub = n.subscribe("master_publisher", 1000, &receivedMsg);

	ros::spin();
	return 0;
}

