#include "ros/ros.h"
#include "std_msgs/Float64.h"

ros::Publisher pub;

int main(int argc, char **argv)
{
        ros::init(argc, argv, "srv_listener");
        ros::NodeHandle n;

        ros::Duration loop_time = ros::Duration(1.0);

        std_msgs::Float64 msg;

        pub = n.advertise<std_msgs::Float64>("master_publisher", 1000);
        int count = 0;
        while(ros::ok && count < 5) {
            msg.data = count;
            count++;

            pub.publish(msg);

            ros::spinOnce();
            loop_time.sleep();
        }
        pub.shutdown();


        return 0;
}
